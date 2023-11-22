
#include "requests.h"

//function that get the request cofe from the client - register or reconnect
int getRequestCode(){

    int user_input;

    while (true) {
        std::cout << "Please choose: \n 1 - Register to the system \n 2 - connect the system ";
        std::cin >> user_input;

        if (std::cin.fail()) {
            // Handle non-numeric input
            std::cin.clear(); // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            std::cout << "Invalid input. Please enter a numeric value." << std::endl;
        } else if (user_input >= 1 && user_input <= 2) {
            if (user_input == 1)
                return 1025;    //register
            else
                return 1027;    //reconnect
        } else {
            std::cout << "Invalid input. Please enter a 4-digit request." << std::endl;
        }
    }

}

//Register to the system
void case_1025(boost::asio::ip::tcp::socket& socket) {
    std::cout << "Starting registration" << std::endl;

    //error with transfer.info file
    if(!checkUserFiles()) {
        std::cout << "error finding transfer.info file, cant register" << std::endl;
        return;
    }

    //getting all the request needed information
    std::string username = readUserName();
    std::vector<uint8_t> payload(255,0);
    std::memcpy(payload.data(),username.c_str(),username.size());
    RequestToServer request{"",3,1025,255,payload};
    //serialized the request
    std::vector<uint8_t> serializedData = request.serialize();
    boost::system::error_code error;
    socket.write_some(boost::asio::buffer(serializedData),error);
    //sending request to the server
    return handleAnswer(socket);


}

//sending public key to the server
void case_1026(boost::asio::ip::tcp::socket& socket) {
    std::cout << "Sending public key" << std::endl;
    //generate public and privarte keys
    const RSA::PublicKey pubkey = createPublicAndPrivateKey();
    std::string encodedPubKey = getEncodedPubKey(pubkey);

    //getting all the needed information to the request struct
    std::string username = readUserName();
    std::vector<uint8_t> payload(255+encodedPubKey.size(),0);
    std::memcpy(payload.data(),username.c_str(),username.size());
    std::memcpy(payload.data()+255,encodedPubKey.c_str(),encodedPubKey.size()); //always 160 byte
    std::string clientID = readClientID();
    uint32_t size = encodedPubKey.size()+255;
    RequestToServer request{clientID,3,1026,size,payload};

    //serialized the struct and sent to the server
    std::vector<uint8_t> serializedData = request.serialize();
    boost::system::error_code error;
    socket.write_some(boost::asio::buffer(serializedData),error);
    return handleAnswer(socket);


}

//Reconnect to the server - known client
void case_1027(boost::asio::ip::tcp::socket& socket) {
    std::cout << " Reconnecting" <<std::endl;

    if(!checkUserFiles()) {
        std::cout << "error finding transfer.info file, cant register" << std::endl;
        return;
    }
    //reading the user name
    std::string username = readUserName();

    //add all the needed information to the request struct
    std::vector<uint8_t> payload(255,0);
    std::memcpy(payload.data(),username.c_str(),username.size());
    RequestToServer request{"",3,1027,255,payload};
    std::vector<uint8_t> serializedData = request.serialize();
    boost::system::error_code error;
    socket.write_some(boost::asio::buffer(serializedData),error);

    //sending request to the server
    return handleAnswer(socket);
}

//sending the  file to the server
void case_1028(boost::asio::ip::tcp::socket& socket,std::string& decryptAES) {
    std::cout << "Encrypting file with AES" << std::endl;
    std::string filePath = getFilePath();

    //encrypting the file using ARS
    AESWrapper aesWrapper(reinterpret_cast<const unsigned char*>(decryptAES.c_str()),16);
    std::string file_to_encrypt = read_file(filePath);
    std::string encryptedFile = aesWrapper.encrypt(file_to_encrypt.c_str(),file_to_encrypt.size());

    //fopy the encrypted file
    std::vector<uint8_t> file_encyrpted_byte(encryptedFile.size(),0);
    std::memcpy(file_encyrpted_byte.data(),encryptedFile.c_str(),encryptedFile.size());

    // get file size
    int32_t content_size = encryptedFile.size();  //4 byte size
    //set request needed data
    std::vector<uint8_t> payload(4+255+content_size,0);
    std::memcpy(payload.data(),&content_size,sizeof(int32_t));
    std::memcpy(payload.data()+4,filePath.c_str(),filePath.size());
    std::memcpy(payload.data()+4+255,encryptedFile.c_str(),encryptedFile.size());
    std::string clientID = hexStringToBinary(readClientID());
    uint32_t requestSize = payload.size();

    //receive request struct
    RequestToServer request{clientID,3,1028,requestSize,payload};
    //serialize and send to the server
    std::vector<uint8_t> serializedData = request.serialize();
    boost::system::error_code error;
    socket.write_some(boost::asio::buffer(serializedData),error);
    return handleAnswer(socket);

}



//CRC is correct
void case_1029(boost::asio::ip::tcp::socket& socket) {
    //sending the 1029 case - CRC are equal
    std::vector<uint8_t> payload(255,0);
    std::string fileName = getFilePath();
    std::memcpy(payload.data(),fileName.c_str(),fileName.size());
    std::string clientID = hexStringToBinary(readClientID());
    uint32_t requestSize = payload.size();

    //receive request struct
    RequestToServer request{clientID,3,1029,requestSize,payload};
    //serialize and send to the server
    std::vector<uint8_t> serializedData = request.serialize();
    boost::system::error_code error;
    socket.write_some(boost::asio::buffer(serializedData),error);
    return handleAnswer(socket);

}
//CRC isn't Correct generate case 1028 right after
void case_1030(boost::asio::ip::tcp::socket& socket) {
    std::cout << "Error with CRC - sending the file again\n" << std::endl;

    //sending the file data again
    /*std::vector<uint8_t> payload(255,0);
    std::string fileName = getFilePath();
    std::memcpy(payload.data(),fileName.c_str(),fileName.size());
    std::string clientID = hexStringToBinary(readClientID());
    uint32_t requestSize = payload.size();

    //sending 1030 request
    RequestToServer request{clientID,3,1030,requestSize,payload};*/
    //exporting the AES key
    std::string aes = read_file("aes_decrypted.key");
    return case_1028(socket,aes);


}

//CRC isn't correct for the forth time
void case_1031(boost::asio::ip::tcp::socket& socket) {

    boost::system::error_code ec;
    //closing the socket and the system
    if (socket.is_open()) {
        socket.close(ec);
        std::cout << "\nSocket closed successfully." << std::endl;
    } else {
        std::cerr << "Attempted to close an closed socket." << std::endl;
    }

    if (ec) {
        std::cerr << "Error closing socket: " << ec.message() << std::endl;
    } else {
        std::cout << "Socket closed successfully." << std::endl;
    }
    return;
}

//function that hanlde the request to the server by the code
void handle_requests(int number,boost::asio::ip::tcp::socket& socket) {
    switch (number) {
        // Cases between 1025 and 1031
        case 1025:
            case_1025(socket);
            break;
        case 1026:
            case_1026(socket);
            break;
        case 1027:
            case_1027(socket);
            break;
      //  case 1028:
        //    case_1028(socket);
          //  break;
        case 1029:
            case_1029(socket);
            break;
        case 1030:
            case_1030(socket);
            break;
        case 1031:
            case_1031(socket);
            break;
    }
}

//function that encode the public key from the server
std::string getEncodedPubKey(const RSA::PublicKey& pubkey){

    ByteQueue pubKeyQueue;
    pubkey.DEREncode(pubKeyQueue);

    // Convert binary to Base64
    std::string encodedPubKey;
    Base64Encoder pubKeyEncoder(new StringSink(encodedPubKey));
    pubKeyQueue.CopyTo(pubKeyEncoder);
    pubKeyEncoder.MessageEnd();

    return encodedPubKey;
}

//function that read the file we want to send to the server
std::string read_file(const std::string& file_path) {

    std::ifstream file(file_path);
    std::ostringstream content_stream;
    //check if file exist
    if (file.is_open()) {
        content_stream << file.rdbuf(); //take all file content
        file.close();
        return content_stream.str();
    } else {
        std::cerr << "Error: Unable to open file - " << file_path << std::endl;
        return "";
    }
}

// convert Hex har to binary
std::string hexToBinary(char hexChar) {
    switch (hexChar) {
        case '0': return "0000";
        case '1': return "0001";
        case '2': return "0010";
        case '3': return "0011";
        case '4': return "0100";
        case '5': return "0101";
        case '6': return "0110";
        case '7': return "0111";
        case '8': return "1000";
        case '9': return "1001";
        case 'a': case 'A': return "1010";
        case 'b': case 'B': return "1011";
        case 'c': case 'C': return "1100";
        case 'd': case 'D': return "1101";
        case 'e': case 'E': return "1110";
        case 'f': case 'F': return "1111";
        default:
            std::cerr << "Invalid hex character: " << hexChar << std::endl;
            return "";
    }
}

//function that conver hex base 64 to binary
std::string hexStringToBinary(const std::string& hexString) {
    std::string binaryString;

    //going through each char
    for (char hexChar : hexString) {
        std::string nibble = hexToBinary(hexChar);
        if (nibble.empty()) {
            return "";  // Invalid hex character
        }
        binaryString += nibble;
    }

    return binaryString;
}
