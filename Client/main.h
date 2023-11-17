//
// Created by Ido Abargel on 14/11/2023.
//

#ifndef DEFENSIVEPROJECT_FINAL_MAIN_H
#define DEFENSIVEPROJECT_FINAL_MAIN_H
#include <iostream>
#include "serverRequsetStruct.h"
#include <boost/asio.hpp>


bool checkUserFiles();
void readIpAndPort(std::string& ipAddress, std::string& port);
boost::asio::ip::tcp::socket connectToServer();
std::string  readUserName();
std::string readClientID();

#endif //DEFENSIVEPROJECT_FINAL_MAIN_H
