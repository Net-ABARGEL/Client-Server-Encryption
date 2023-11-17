//
// Created by Ido Abargel on 15/11/2023.
//
#include "answers.h"
#include "requests.h"
#include "serverAnswerStruct.h"
#include <fstream>



void handleAnswer(boost::asio::ip::tcp::socket& socket){

    std::vector<uint8_t> responseData(56); // 7 byte
    AnswerFromServer answer = setServerAnswer(socket);
    handle_answer_code(answer,socket);


}

AnswerFromServer setServerAnswer(boost::asio::ip::tcp::socket& socket){

    std::vector<uint8_t> responseData(1024);
    size_t bytesRead = boost::asio::read(socket,boost::asio::buffer(responseData,7));
    std::cout   <<"red the payload size"<< std::endl;
    uint8_t version_byte;           // 1 Byte integer
    uint16_t code_byte;             // 2 Byte Integer
    uint32_t payloadSize_byte;      // 4 byte integer

    std::memcpy(&version_byte, responseData.data(), sizeof(version_byte));
    std::memcpy(&code_byte, responseData.data() + sizeof(version_byte), sizeof(code_byte));
    std::memcpy(&payloadSize_byte, responseData.data() + sizeof(version_byte) + sizeof(code_byte), sizeof(payloadSize_byte));

    bytesRead = boost::asio::read(socket,boost::asio::buffer(responseData,payloadSize_byte));

    // Resize Payload vector and copy the payload data
    std::vector<uint8_t> payload_byte(static_cast<int>(payloadSize_byte));
    std::memcpy(&payload_byte[0], responseData.data(), payloadSize_byte);

    AnswerFromServer answer{version_byte,code_byte,payloadSize_byte,payload_byte};


    std::string str(payload_byte.begin(), payload_byte.end());
    return answer;


}

//The Client has registered
void case_2100(AnswerFromServer& answer,boost::asio::ip::tcp::socket& socket) {
    std::cout << "The Client has registered" << std::endl;
    writeUUID(answer);
    case_1026(socket);

}

//Registration has failed
void case_2101(AnswerFromServer& answer,boost::asio::ip::tcp::socket& socket) {
    std::cout << "Registration has failed" << std::endl;
}

//public key sent correctly, received AES key
void case_2102(AnswerFromServer& answer,boost::asio::ip::tcp::socket& socket) {
    std::cout << "public key sent correctly, received AES key" << std::endl;
}

//The file sent correctly, Received CRC code
void case_2103(AnswerFromServer& answer,boost::asio::ip::tcp::socket& socket) {
    std::cout << "Handling case 2103" << std::endl;
}

//Server Received Request (for 1029 or 1031)
void case_2104(AnswerFromServer& answer,boost::asio::ip::tcp::socket& socket) {
    std::cout << "Server Received Request" << std::endl;
}

void case_2105(AnswerFromServer& answer,boost::asio::ip::tcp::socket& socket) {
    std::cout << "Handling case 2105" << std::endl;
}

void case_2106(AnswerFromServer& answer,boost::asio::ip::tcp::socket& socket) {
    std::cout << "Handling case 2106" << std::endl;
}

void case_2107(AnswerFromServer& answer,boost::asio::ip::tcp::socket& socket) {
    std::cout << "Handling case 2107" << std::endl;
}

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
            std::cout << "Number is not in the range 2100 to 2107" << std::endl;
    }
}

void writeUUID(AnswerFromServer& answer){
    std::ofstream outputFile("me.info",std::ios::app);
    std::string stringValue(answer.payload.begin(), answer.payload.end());
    outputFile << stringValue << std::endl;
    outputFile.close();
    std::cout <<"the UUID had writen correctly" <<std::endl;
}

