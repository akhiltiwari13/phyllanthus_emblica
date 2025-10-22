#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>
#include <cryptopp/sha.h>
#include <iostream>
#include <string>

using namespace CryptoPP;

int main() {
    // Key and IV setup
    byte key[AES::DEFAULT_KEYLENGTH];
    byte iv[AES::BLOCKSIZE];
    memset(key, 0x01, AES::DEFAULT_KEYLENGTH);
    memset(iv, 0x01, AES::BLOCKSIZE);

    // Message to be encrypted
    std::string plaintext = "Hello, Crypto++!";
    std::string ciphertext;
    std::string decryptedtext;

    // Encryption
    try {
        CBC_Mode<AES>::Encryption encryptor;
        encryptor.SetKeyWithIV(key, sizeof(key), iv);

        StringSource(plaintext, true,
            new StreamTransformationFilter(encryptor,
                new StringSink(ciphertext)
            )
        );
    }
    catch(const Exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    // Print encrypted message as hex
    std::string encoded;
    StringSource(ciphertext, true,
        new HexEncoder(
            new StringSink(encoded)
        )
    );
    std::cout << "Ciphertext: " << encoded << std::endl;

    // Decryption
    try {
        CBC_Mode<AES>::Decryption decryptor;
        decryptor.SetKeyWithIV(key, sizeof(key), iv);

        StringSource(ciphertext, true,
            new StreamTransformationFilter(decryptor,
                new StringSink(decryptedtext)
            )
        );
    }
    catch(const Exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    std::cout << "Decrypted: " << decryptedtext << std::endl;

    std::string message = "Hash this message";
    std::string digest;

    SHA256 hash;
    
    StringSource(message, true,
        new HashFilter(hash,
            new HexEncoder(
                new StringSink(digest)
            )
        )
    );

    std::cout << "SHA-256: " << digest << std::endl;
    return 0;
}
