//
// Created by Ido Abargel on 18/11/2023.
//

#ifndef DEFENSIVEPROJECT_FINAL_ENCRYPTION_H
#define DEFENSIVEPROJECT_FINAL_ENCRYPTION_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <cryptopp/aes.h>
#include <cryptopp/files.h>
#include <cryptopp/osrng.h>
#include <cryptopp/rsa.h>
#include <cryptopp/base64.h>

using namespace CryptoPP;

std::string decryptAESKey(const std::string& encryptedKey);

#endif //DEFENSIVEPROJECT_FINAL_ENCRYPTION_H
