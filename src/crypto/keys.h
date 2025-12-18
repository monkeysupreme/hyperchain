#ifndef HYPERCHAIN_KEYS_H
#define HYPERCHAIN_KEYS_H

#include <vector>
#include <cstdint>

#include <cryptopp/eccrypto.h>
#include <cryptopp/oids.h>
#include <cryptopp/osrng.h>

class CPrivateKey
{
public:
    CPrivateKey();
    explicit CPrivateKey(const std::vector<uint8_t>& privKeyBytes);

    std::vector<uint8_t> GetPrivateKeyBytes() const;
    std::vector<uint8_t> GetPublicKeyBytes(bool compressed = true) const;

    void LoadKey(const std::vector<uint8_t>& privKeyBytes);

private:
    void GenerateKey();

private:
    CryptoPP::ECDSA<CryptoPP::ECP, CryptoPP::SHA256>::PrivateKey mPrivKey;
};

#endif