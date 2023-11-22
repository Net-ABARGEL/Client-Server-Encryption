//
// Created by Ido Abargel on 20/11/2023.
//

#ifndef DEFENSIVEPROJECT_FINAL_BASE64WRAPPER_H
#define DEFENSIVEPROJECT_FINAL_BASE64WRAPPER_H
#pragma once

#include <string>
#include <base64.h>


class Base64Wrapper
{
public:
    static std::string encode(const std::string& str);
    static std::string decode(const std::string& str);
};

#endif //DEFENSIVEPROJECT_FINAL_BASE64WRAPPER_H
