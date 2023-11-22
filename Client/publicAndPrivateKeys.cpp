
#include "publicAndPrivateKeys.h"

using namespace CryptoPP;

// function that create the public and private key
RSA::PublicKey createPublicAndPrivateKey(){


	//Random number
	AutoSeededRandomPool rng;

    // Generate private key
	InvertibleRSAFunction privkey;
	privkey.Initialize(rng, 1024);

	//public key
	RSA::PublicKey pubkey(privkey);

	// save private key and public in binnary format
	ByteQueue privkeyQueue,publicQueue;
	privkey.DEREncode(privkeyQueue);

    //conver binary to Base64
	std::string encodedPrivKey,encodedPubKey;
    Base64Encoder privkeyEncoder(new StringSink(encodedPrivKey));
    privkeyQueue.CopyTo(privkeyEncoder);
	privkeyEncoder.MessageEnd();




	// save the private key
	std::ofstream privkeyFile("priv.key", std::ios::binary);
	privkeyFile << encodedPrivKey;
	privkeyFile.close();

    std::ofstream meFile("me.info", std::ios::app);
    meFile << encodedPrivKey;
    meFile.close();

    std::cout <<"the private key has saved in files" << std::endl;

    //return the public key that need to be sent the server
    return pubkey;

}

// function that return the private key in the RS format
RSA::PrivateKey LoadPrivateKeyFromFile() {
    // Read the base64-encoded private key from the file
    std::ifstream file("priv.key", std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Error opening file: priv.key");
    }

    std::string encodedPrivKey;
    file >> encodedPrivKey;

    file.close();

    // Decode base64 to binary
    StringSource(encodedPrivKey, true,
                 new Base64Decoder(
                         new ArraySink((byte *) &encodedPrivKey[0], encodedPrivKey.size())
                 )
    );

    // Load binary data into a ByteQueue
    ByteQueue privkeyQueue;
    privkeyQueue.Put((byte *) &encodedPrivKey[0], encodedPrivKey.size());
    privkeyQueue.MessageEnd();

    // Create an InvertibleRSAFunction and set it from the ByteQueue
    InvertibleRSAFunction privkey;
    privkey.BERDecode(privkeyQueue);

    // Create the private key
    RSA::PrivateKey privateKey(privkey);

    return privateKey;
}

