#include <string>
#include <iostream>
#include <fstream>
#include <boost/asio.hpp>
#include <cryptopp/rsa.h>
#include <cryptopp/osrng.h>
#include <cryptopp/base64.h>
#include <tuple>
#include "publicAndPrivateKeys.h"
#include "serverRequsetStruct.h"
#include "requests.h"



using namespace boost::asio;
using namespace CryptoPP;

bool checkUserFiles(){

    //check if the file exist
    std::string filename;
    filename = "me.info";

    // Open the file for input
    std::ifstream file(filename);

    if (file.is_open())
    {// file exist
        file.close();
        std::cout << "File '" << filename << "' does exist.\n";

    }

    //me.info file doesn't exist
    else {
        std::cout << "File '" << filename << "' does not exist.\n creating a new me.info file\n";

        file.close();

        //reading info from transfer.info
        std::ifstream inputFile;
        inputFile.open("transfer.info");
        if (!inputFile.is_open()) {
            std::cout << "cant find transfer.info, please create the file and reopen the system" << std::endl;
            return false;
        }

        std::string line;
        std::getline(inputFile, line);


        //check there is second line with name
        if (std::getline(inputFile, line)) {
            // Open the output file
            std::ofstream outputFile("me.info");

            outputFile << line << std::endl;

            outputFile.close();
        }
            //error in the file
        else {

            std::cout << "Error: File doesn't have a second line.\n" << std::endl;
            return false; // Return an error code
        }


        inputFile.close();


        std::cout << "The Name from transfer.info has been written to me.info.\n" << std::endl;


        return true;
    }
    return true;
}

std::string readClientID() {
    std::string userNameFile = "me.info";
    // Open the file for input
    std::ifstream file(userNameFile);

    std::string line;
    if (file.is_open())
    {
        std::getline(file, line);
        std::getline(file, line);
    }

    return line;
}
std::string readUserName(){

    std::string userNameFile = "me.info";
    // Open the file for input
    std::ifstream file(userNameFile);

    std::string line;
    if (file.is_open())
    {
        std::getline(file, line);
    }

    return line;
}

//function that seperate the IP and the Port from the transfer file
void readIpAndPort(std::string& ipAddress, std::string& port){

    // Open the file for the IP and port
    std::ifstream file("transfer.info");

    std::string line;
    std::getline(file, line);

    size_t colonPos = line.find(':');
    ipAddress = line.substr(0, colonPos);
    port = line.substr(colonPos + 1);

}
ip::tcp::socket connectToServer(){

   // RequestToServer request{readUserName(), 1, 0001, 1000   , "HelloWorld"};

    io_service io;

    std::string ipAddress;
    std::string port;

    readIpAndPort(ipAddress,port);

    // Create an endpoint
    ip::tcp::endpoint endpoint(ip::address::from_string(ipAddress), std::stoi(port));

    // Create a socket
    ip::tcp::socket socket(io);

    try {
        // Connect to the server
        socket.connect(endpoint);
        boost::system::error_code error;

        std::cout << "Connected to the server from "<< ipAddress<< " in port " << port << std::endl;


        if (error) {
            throw boost::system::system_error(error);
        }

        std::cout << "waiting for answer from the server" << std::endl;

        if (error == boost::asio::error::eof) {
            // Connection closed by the server
            std::cout << "Connection closed by the server." << std::endl;
        } else if (error) {
            throw boost::system::system_error(error);
        }

        return socket;

    } catch (const boost::system::system_error& e) {
        std::cerr << "Error connecting to the server: " << e.what() << std::endl;
        return socket;
    }

}


int main() {
    //checkUserFiles();
    //createPublicAndPrivateKey();
    boost::asio::ip::tcp::socket socket = connectToServer();
    handle_requests(getRequestCode(),socket);//getRequestCode());
}

