//
// Created by Ido Abargel on 14/11/2023.
//

#ifndef DEFENSIVEPROJECT_FINAL_MAIN_H
#define DEFENSIVEPROJECT_FINAL_MAIN_H
#include <iostream>
#include "serverRequsetStruct.h"
#include <boost/asio.hpp>
#include "requests.h"
#include <string>
#include <fstream>

bool checkUserFiles();
void readIpAndPort(std::string& ipAddress, std::string& port);
boost::asio::ip::tcp::socket connectToServer();
std::string  readUserName();
std::string readClientID();
std::string getFilePath();

#endif //DEFENSIVEPROJECT_FINAL_MAIN_H
