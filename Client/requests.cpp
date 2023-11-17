#include <iostream>
#include "main.h"
#include "serverRequsetStruct.h"
#include "answers.h"
#include <boost/asio.hpp>
#include "publicAndPrivateKeys.h"
#include "requests.h"


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
                return 1025;
            else
                return 1027;
        } else {
            std::cout << "Invalid input. Please enter a 4-digit request." << std::endl;
        }
    }

}

//Register to the system
void case_1025(boost::asio::ip::tcp::socket& socket) {
    std::cout << "Starting registration" << std::endl;
    if(!checkUserFiles()) {
        std::cout << "error finding transfer.info file, cant register" << std::endl;
        return;
    }

    uint32_t nameLength = readUserName().length();
    std::string username = readUserName();
    std::vector<uint8_t> payload(255,0);
    std::memcpy(payload.data(),username.c_str(),username.size());
    RequestToServer request{"",3,1025,255,payload};
    std::vector<uint8_t> serializedData = request.serialize();
    boost::system::error_code error;
    socket.write_some(boost::asio::buffer(serializedData),error);

    handleAnswer(socket);


}

//sending public key
void case_1026(boost::asio::ip::tcp::socket& socket) {
    std::cout << "Sending public key" << std::endl;
    const RSA::PublicKey pubkey = createPublicAndPrivateKey();
    std::string encodedPubKey = getEncodedPubKey(pubkey);
    std::cout <<encodedPubKey<<"\n"<<std::endl;
    std::string username = readUserName();
    std::vector<uint8_t> payload(255+encodedPubKey.size(),0);
    std::memcpy(payload.data(),username.c_str(),username.size());
    std::memcpy(payload.data()+255,encodedPubKey.c_str(),encodedPubKey.size()); //always 160 byte
    std::string clientID = readClientID();
    uint32_t size = encodedPubKey.size()+255;
    RequestToServer request{clientID,3,1026,size,payload};

    std::vector<uint8_t> serializedData = request.serialize();
    boost::system::error_code error;
    socket.write_some(boost::asio::buffer(serializedData),error);


}

//Reconnect
void case_1027(boost::asio::ip::tcp::socket& socket) {
    std::cout << "Handling case 1027" << std::endl;
}

//sending file
void case_1028(boost::asio::ip::tcp::socket& socket) {
    std::cout << "Handling case 1028" << std::endl;
}

//CRC Correct
void case_1029(boost::asio::ip::tcp::socket& socket) {
    std::cout << "Handling case 1029" << std::endl;
}

//CRC isnt correct
void case_1030(boost::asio::ip::tcp::socket& socket) {
    std::cout << "Handling case 1030" << std::endl;
}

//CRC isnt correct for the forth time
void case_1031(boost::asio::ip::tcp::socket& socket) {
    std::cout << "Handling case 1031" << std::endl;
}

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
        case 1028:
            case_1028(socket);
            break;
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
