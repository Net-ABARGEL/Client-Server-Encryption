cmake_minimum_required(VERSION 3.26)
project(DefensiveProject_final)

set(CMAKE_CXX_STANDARD 17)

include_directories("/Users/abargel_ido/cryptopp")
include_directories(/Users/abargel_ido/Documents/boost_1_83_0/)
include_directories(/Users/abargel_ido/Documents/cryptopp/)
link_directories("/Users/abargel_ido/cryptopp")

list(APPEND CMAKE_MODULE_PATH "/Users/abargel_ido/cryptopp")


add_executable(DefensiveProject_final main.cpp
        publicAndPrivateKeys.cpp
        publicAndPrivateKeys.h
        serverRequsetStruct.h
        requests.cpp
        requests.h
        main.h
        answers.cpp
        answers.h
        serverAnswerStruct.h)

set(CryptoPP_DIR /Users/abargel_ido/cryptopp)

target_link_libraries(DefensiveProject_final PRIVATE cryptopp)
