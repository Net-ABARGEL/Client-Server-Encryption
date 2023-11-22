//
// Created by Ido Abargel on 15/11/2023.
//

#ifndef DEFENSIVEPROJECT_FINAL_ANSWERS_H
#define DEFENSIVEPROJECT_FINAL_ANSWERS_H
#include <iostream>
#include "main.h"
#include <boost/asio.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include "serverAnswerStruct.h"
#include "answers.h"
#include "requests.h"
#include "encryption.h"
#include <fstream>
#include <bitset>
#include <sstream>
#include "checkSum.h"


void handleAnswer(boost::asio::ip::tcp::socket& socket);
AnswerFromServer getServerAnswer(boost::asio::ip::tcp::socket& socket);
std::string binaryToHex(const std::string& binaryString);
boost::multiprecision::cpp_int binaryToDecimal(const std::string& binaryString);
std::string decimalToHex(const boost::multiprecision::cpp_int& decimalValue) ;


void case_2100(AnswerFromServer& answer,boost::asio::ip::tcp::socket& socket);
void case_2101(AnswerFromServer& answer,boost::asio::ip::tcp::socket& socket);
void case_2102(AnswerFromServer& answer,boost::asio::ip::tcp::socket& socket);
void case_2103(AnswerFromServer& answer,boost::asio::ip::tcp::socket& socket);
void case_2104(AnswerFromServer& answer,boost::asio::ip::tcp::socket& socket);
void case_2105(AnswerFromServer& answer,boost::asio::ip::tcp::socket& socket);
void case_2106(AnswerFromServer& answer,boost::asio::ip::tcp::socket& socket);
void case_2107(AnswerFromServer& answer,boost::asio::ip::tcp::socket& socket);

void handle_answer_code(AnswerFromServer& answer,boost::asio::ip::tcp::socket& socket);
void writeUUID(AnswerFromServer& answer);




#endif //DEFENSIVEPROJECT_FINAL_ANSWERS_H
