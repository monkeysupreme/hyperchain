#include "keccak.h"
#include <stdexcept>
#include <cryptopp/keccak.h>

using namespace CryptoPP;

uint256 CKeccak256::Hash256(const std::vector<uint8_t>& data)
{
    Keccak_256 hash;

    uint8_t digest[32];
    if (!data.empty())
        hash.Update(data.data(), data.size());
    hash.Final(digest);

    return uint256(digest);
}

uint256 CKeccak256::Hash256(const std::string& data)
{
    Keccak_256 hash;

    uint8_t digest[32];
    if (!data.empty())
        hash.Update(reinterpret_cast<const uint8_t*>(data.data()), data.size());
    hash.Final(digest);

    return uint256(digest);
}
