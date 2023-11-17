//
// Created by Ido Abargel on 15/11/2023.
//

#ifndef DEFENSIVEPROJECT_FINAL_ANSWERS_H
#define DEFENSIVEPROJECT_FINAL_ANSWERS_H
#include <iostream>
#include "main.h"
#include <boost/asio.hpp>
#include "serverAnswerStruct.h"

void handleAnswer(boost::asio::ip::tcp::socket& socket);
AnswerFromServer setServerAnswer(boost::asio::ip::tcp::socket& socket);

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
