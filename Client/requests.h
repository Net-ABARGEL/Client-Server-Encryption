//
// Created by Ido Abargel on 14/11/2023.
//

#ifndef DEFENSIVEPROJECT_FINAL_REQUESTS_H
#define DEFENSIVEPROJECT_FINAL_REQUESTS_H
#include <iostream>
#include "main.h"
#include <boost/asio.hpp>
#include "publicAndPrivateKeys.h"


int getRequestCode();
void case_1025(boost::asio::ip::tcp::socket& socket);
void case_1026(boost::asio::ip::tcp::socket& socket);
void case_1027(boost::asio::ip::tcp::socket& socket);
void case_1028(boost::asio::ip::tcp::socket& socket);
void case_1029(boost::asio::ip::tcp::socket& socket);
void case_1030(boost::asio::ip::tcp::socket& socket);
void case_1031(boost::asio::ip::tcp::socket& socket);

void handle_requests(int number,boost::asio::ip::tcp::socket& socket);
std::string getEncodedPubKey(const RSA::PublicKey& pubkey);

#endif //DEFENSIVEPROJECT_FINAL_REQUESTS_H
