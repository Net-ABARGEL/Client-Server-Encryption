

#include "encryption.h"

using namespace CryptoPP;

// function that decrypt the AES key that received from the server
std::string decryptAESKey(const std::string& encryptedKey) {
    // Load RSA private key from file
    InvertibleRSAFunction privateKey;

    // Read the private key data from the file
    std::ifstream privateKeyFile("priv.key");
    std::ostringstream privateKeyStream;
    privateKeyStream << privateKeyFile.rdbuf();
    privateKeyFile.close();

    // Decode the Base64-encoded private key into ByteQueue
    ByteQueue decodedPrivateKey;
    StringSource(privateKeyStream.str(), true,
                 new Base64Decoder(new Redirector(decodedPrivateKey)));
    privateKey.Load(decodedPrivateKey);




    // Decrypt the AES key using RSA private key
    AutoSeededRandomPool rng;

    // Decrypt the AES key using RSA private key
    std::string decryptedKey;
    RSAES_OAEP_SHA_Decryptor rsaDecryptor(privateKey);
    StringSource(encryptedKey, true,
                 new PK_DecryptorFilter(rng, rsaDecryptor,
                                        new StringSink(decryptedKey)));

    return decryptedKey;
}