//
// Created by Ido Abargel on 15/11/2023.
//

#ifndef DEFENSIVEPROJECT_FINAL_SERVERANSWERSTRUCT_H
#define DEFENSIVEPROJECT_FINAL_SERVERANSWERSTRUCT_H

#include <iostream>
#include <cstring>

struct AnswerFromServer{

    uint8_t version;           // 1 Byte integer
    uint16_t code;             // 2 Byte Integer
    uint32_t payloadSize;      // 4 byte integer
    std::vector<uint8_t> payload;

    //initialize ansewer struct from the server
    AnswerFromServer(uint8_t version, uint16_t code, uint32_t payloadSize, const std::vector<uint8_t>& payload)
            : version(version), code(code), payloadSize(payloadSize), payload(payload){
    }
};

#endif //DEFENSIVEPROJECT_FINAL_SERVERANSWERSTRUCT_H
