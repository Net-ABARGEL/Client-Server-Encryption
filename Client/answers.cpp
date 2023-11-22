//
// Created by Ido Abargel on 15/11/2023.
//
#include "answers.h"

namespace mp = boost::multiprecision;

//function that handle the answer from the server by the answer code
void handleAnswer(boost::asio::ip::tcp::socket& socket){

    std::vector<uint8_t> responseData(56); // 7 byte
    AnswerFromServer answer = getServerAnswer(socket); //receive the answer struct
    handle_answer_code(answer,socket);//handling according to the code

}

// function that return AnswerFromServer struct by using the socket info
AnswerFromServer getServerAnswer(boost::asio::ip::tcp::socket& socket){

    std::vector<uint8_t> responseData(1024);
    // first reading the 7 bytes
    size_t bytesRead = boost::asio::read(socket,boost::asio::buffer(responseData,7));
    uint8_t version_byte;           // 1 Byte integer
    uint16_t code_byte;             // 2 Byte Integer
    uint32_t payloadSize_byte;      // 4 byte integer

    //copy the info to the Uint types
    std::memcpy(&version_byte, responseData.data(), sizeof(version_byte));
    std::memcpy(&code_byte, responseData.data() + sizeof(version_byte), sizeof(code_byte));
    std::memcpy(&payloadSize_byte, responseData.data() + sizeof(version_byte) + sizeof(code_byte), sizeof(payloadSize_byte));

    //read the rest of the answer after knowing the payload size
    bytesRead = boost::asio::read(socket,boost::asio::buffer(responseData,payloadSize_byte));
    // Resize Payload vector and copy the payload data
    std::vector<uint8_t> payload_byte(static_cast<int>(payloadSize_byte));
    std::memcpy(&payload_byte[0], responseData.data(), payloadSize_byte);

    AnswerFromServer answer{version_byte,code_byte,payloadSize_byte,payload_byte};

    return answer;


}

//The Client has registered
void case_2100(AnswerFromServer& answer,boost::asio::ip::tcp::socket& socket) {
    std::cout << "The Client has registered" << std::endl;
    writeUUID(answer);  //writing the UUID in the files
    case_1026(socket);  // handling case 1026 - sending public key to the server

}

//Registration has failed - error
void case_2101(AnswerFromServer& answer,boost::asio::ip::tcp::socket& socket) {
    std::cout << "Registration has failed" << std::endl;
}

//public key sent correctly, received AES key
void case_2102(AnswerFromServer& answer,boost::asio::ip::tcp::socket& socket) {
    std::cout << "public key sent correctly\n" << std::endl;
    //reading the encrypt AES key
    std::vector<unsigned char> aesKey_encrypted_byte(answer.payload.begin() + 128, answer.payload.end());
    std::string aesKey_encrypted(aesKey_encrypted_byte.begin(), aesKey_encrypted_byte.end());
    std::cout << "received AES key\n" << std::endl;

    //save in the file
    std::ofstream outputFile("aes_encrypted.key");
    outputFile << aesKey_encrypted << std::endl;
    outputFile.close();

    //decrypt the AES key and save in file
    std::string decryptAES = decryptAESKey(aesKey_encrypted);
    std::ofstream outputFileDecryptAES("aes_decrypted.key");
    outputFileDecryptAES << decryptAES << std::endl;
    outputFileDecryptAES.close();

    return case_1028(socket,decryptAES);// return case 1028 - sending the encrypt file

}

//The file sent correctly, Received CRC code
void case_2103(AnswerFromServer& answer,boost::asio::ip::tcp::socket& socket) {

    //counter until 4th
    static int wrongCRC=0;
    //copying the crc code
    std::string crc(answer.payload.end() - 32 , answer.payload.end());
    size_t nullPos = crc.find('\0'); //taking off the nulls
    crc.erase(nullPos);

    //checking the CRC of the file
    std::string filePath = getFilePath();
    std::string checkSum = readfile(filePath);
    if (checkSum == crc) {
        std::cout << "The CRC's are equal." << std::endl;
        return case_1029(socket);
    } else {
        std::cout << "The CRC's are not equal. send again\n" << std::endl;
        wrongCRC++;
        if (wrongCRC==4)
            return case_1031(socket);   //error to encrypt the file
        return case_1030(socket);   //sending the file again
    }


}

//Server Received Request (for 1029 or 1031)
void case_2104(AnswerFromServer& answer,boost::asio::ip::tcp::socket& socket) {
    std::cout << "Server Received Request, logging off from the Server" << std::endl;
    boost::system::error_code ec;
    //closing the socket
    if (socket.is_open()) {
        if (&socket != nullptr) {
            socket.close(ec);// close the socket
            std::cout << "Socket closed successfully." << std::endl;
        } else {
            std::cerr << "Error: Socket is null or uninitialized." << std::endl;
        }
    } else {
        std::cerr << "Attempted to close an closed socket." << std::endl;
    }

    //error with the socket
    if (ec) {
        std::cerr << "Error closing socket: " << ec.message() << std::endl;
    } else {
        std::cout << "Socket closed successfully." << std::endl;
    }
    return;
}

//reconnecting request accepted - received AES key
void case_2105(AnswerFromServer& answer,boost::asio::ip::tcp::socket& socket) {
    std::cout << "Reconnected request accepted\n" << std::endl;
    //exporting the AES key
    std::vector<unsigned char> aesKey_encrypted_byte(answer.payload.begin() + 128, answer.payload.end());
    std::string aesKey_encrypted(aesKey_encrypted_byte.begin(), aesKey_encrypted_byte.end());
    std::cout << "received AES key" << std::endl;

    //save in the file
    std::ofstream outputFile("aes_encrypted.key");
    outputFile << aesKey_encrypted << std::endl;
    outputFile.close();

    //decrypt the file and save in the decrypt file
    std::string decryptAES = decryptAESKey(aesKey_encrypted);
    std::ofstream outputFileDecryptAES("aes_decrypted.key");
    outputFileDecryptAES << decryptAES << std::endl;
    outputFileDecryptAES.close();

    // return case 1028 - sending the encrypted file
    return case_1028(socket,decryptAES);
}

//function that handle code 2106 - Client hasn't recognized, starting registration process
void case_2106(AnswerFromServer& answer,boost::asio::ip::tcp::socket& socket) {
    std::cout << "Client is not recognized, please Register" << std::endl;
    return handle_requests(1025,socket); //registration process
}

//function that represent code 2107 - any error with the server
void case_2107(AnswerFromServer& answer,boost::asio::ip::tcp::socket& socket) {
    std::cout << "Error with the Server" << std::endl;
}

//function that handle the answer code that we receive from the server
void handle_answer_code(AnswerFromServer& answer,boost::asio::ip::tcp::socket& socket) {
    int number = answer.code;
    switch (number) {
        case 2100:
            case_2100(answer,socket);
            break;
        case 2101:
            case_2101(answer,socket);
            break;
        case 2102:
            case_2102(answer,socket);
            break;
        case 2103:
            case_2103(answer,socket);
            break;
        case 2104:
            case_2104(answer,socket);
            break;
        case 2105:
            case_2105(answer,socket);
            break;
        case 2106:
            case_2106(answer,socket);
            break;
        case 2107:
            case_2107(answer,socket);
            break;
        default:
            std::cout << "Number is not in the range of 2100 to 2107" << std::endl;
    }
}

// function that create a UUID for the username un the me.info file
void writeUUID(AnswerFromServer& answer){

    std::ofstream outputFile("me.info",std::ios::app); // read the username from the file
    std::string stringValue(answer.payload.begin(), answer.payload.end());
    //convert the UUID to hex Base 64 and save in the file
    std::string hexUUID = binaryToHex(stringValue);
    outputFile << hexUUID << std::endl;
    outputFile.close();
    std::cout <<"the UUID had writen correctly" <<std::endl;
}

// function that conver binary string to hex
std::string binaryToHex(const std::string& binaryString) {
    // Convert binary string to decimal integer

    boost::multiprecision::cpp_int decimalValue = binaryToDecimal(binaryString);

    // Convert decimal integer to hexadecimal string
    std::string hexString = decimalToHex(decimalValue);

    return hexString;
}

// function that convert binary string number to decimal
boost::multiprecision::cpp_int binaryToDecimal(const std::string& binaryString) {
    boost::multiprecision::cpp_int decimalValue = 0;

    for (char bit : binaryString) {
        decimalValue = (decimalValue << 1) | (bit - '0');
    }

    return decimalValue;
}

// function that convert decimal number to Hex
std::string decimalToHex(const boost::multiprecision::cpp_int& decimalValue) {
    std::stringstream hexStream;
    hexStream << std::hex << decimalValue;
    return hexStream.str();
}

