//
// Created by Ido Abargel on 14/11/2023.
//

#ifndef DEFENSIVEPROJECT_FINAL_REQUESTS_H
#define DEFENSIVEPROJECT_FINAL_REQUESTS_H
#include <iostream>
#include "main.h"
#include "serverRequsetStruct.h"
#include "answers.h"
#include <boost/asio.hpp>
#include "publicAndPrivateKeys.h"
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/filters.h>
#include "AESWrapper.h"



int getRequestCode();
void case_1025(boost::asio::ip::tcp::socket& socket);
void case_1026(boost::asio::ip::tcp::socket& socket);
void case_1027(boost::asio::ip::tcp::socket& socket);
void case_1028(boost::asio::ip::tcp::socket& socket,std::string& decryptAES);
void case_1029(boost::asio::ip::tcp::socket& socket);
void case_1030(boost::asio::ip::tcp::socket& socket);
void case_1031(boost::asio::ip::tcp::socket& socket);

std::string read_file(const std::string& file_path);
std::string aes_encrypt(const std::string& input, const std::string& key);

void handle_requests(int number,boost::asio::ip::tcp::socket& socket);
std::string getEncodedPubKey(const RSA::PublicKey& pubkey);

std::string hexToBinary(char hexChar);
std::string hexStringToBinary(const std::string& hexString);

#endif //DEFENSIVEPROJECT_FINAL_REQUESTS_H
