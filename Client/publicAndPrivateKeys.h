//
// Created by Ido Abargel on 14/11/2023.
//

#ifndef DEFENSIVEPROJECT_FINAL_PUBLICANDPRIVATEKEYS_H
#define DEFENSIVEPROJECT_FINAL_PUBLICANDPRIVATEKEYS_H

#include <cryptopp/rsa.h>
#include <cryptopp/osrng.h>
#include <cryptopp/base64.h>
#include <iostream>
#include <fstream>


using namespace CryptoPP;



RSA::PublicKey createPublicAndPrivateKey();

#endif //DEFENSIVEPROJECT_FINAL_PUBLICANDPRIVATEKEYS_H
