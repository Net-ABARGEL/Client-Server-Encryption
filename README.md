Secure File Transfer System

This project implements a secure file transfer system with a client-server architecture. The client is written in C++, and the server is implemented in Python. The communication between the client and server is secured using encryption with public and private keys, as well as an AES key.

Features

Secure Communication: The communication between the client and server is encrypted using a combination of public-key cryptography and symmetric-key cryptography (AES).
File Transfer: The system allows the secure transfer of files between the client and server.
Public and Private Key Encryption: Public-key cryptography is used to establish a secure channel for exchanging the symmetric key (AES key) between the client and server.
AES Encryption: Once the symmetric key is exchanged, AES encryption is used to secure the actual file transfer.
Prerequisites

C++ compiler (for the client)
Python 3 (for the server)
Usage

Configuration

Adjust the server address and port in both the client and server source code files if necessary.
Customize encryption algorithms, key lengths, or any other security parameters as needed.
Dependencies

OpenSSL library for C++ (for cryptographic functions)
Contributing

Feel free to contribute by submitting issues or pull requests.

Acknowledgments

This project is inspired by the need for secure file transfer in various applications.
Special thanks to the contributors and the open-source community for their valuable feedback and support.


Author

Ido Abargel
