//
// Created by Ido Abargel on 14/11/2023.
//

#ifndef DEFENSIVEPROJECT_FINAL_SERVERREQUSETSTRUCT_H
#define DEFENSIVEPROJECT_FINAL_SERVERREQUSETSTRUCT_H

#include <iostream>
#include <cstring>

struct RequestToServer {
    uint8_t ClientId[128];      // 16 bytes (128 bits)
    uint8_t Version;           // 1 Byte integer
    uint16_t Code;             // 2 Byte Integer
    uint32_t PayloadSize;      // 4 byte integer
    std::vector<uint8_t> Payload;       // Payload with a length equal to PayloadSize

    // Constructor to initialize the struct
    RequestToServer(const std::string& clientId, uint8_t version, uint16_t code, uint32_t payloadSize, const std::vector<uint8_t>& payload)
            : Version(version), Code(code), PayloadSize(payloadSize), Payload(payload) {

        // Copy clientId into the ClientId array and fill the remaining space with null characters
        std::memset(ClientId, 0, sizeof(ClientId));
        std::memcpy(ClientId, clientId.c_str(), std::min(clientId.length(), sizeof(ClientId)));
    }

    std::vector<uint8_t> serialize() const {
        std::vector<uint8_t> serializedData;
        serializedData.reserve(sizeof(ClientId) + sizeof(Version) + sizeof(Code) + sizeof(PayloadSize) + PayloadSize);

        // Append each member to the serialized data

        serializedData.insert(serializedData.end(), ClientId, ClientId + sizeof(ClientId));
        serializedData.push_back(Version);
        serializedData.push_back((Code >> 8) & 0xFF); // high byte
        serializedData.push_back(Code & 0xFF);        // low byte
        serializedData.push_back((PayloadSize >> 24) & 0xFF);
        serializedData.push_back((PayloadSize >> 16) & 0xFF);
        serializedData.push_back((PayloadSize >> 8) & 0xFF);
        serializedData.push_back(PayloadSize & 0xFF);
        serializedData.insert(serializedData.end(), Payload.begin(), Payload.end());

        return serializedData;
    }
};

#endif //DEFENSIVEPROJECT_FINAL_SERVERREQUSETSTRUCT_H
