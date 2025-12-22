//
// Created by caleb on 12/19/25.
//

#include "address.h"

#include "../crypto/keccak.h"
#include "../util/serialization.h"

std::string BytesToAddress(std::vector<uint8_t> bytes)
{
    uint256 hash = CKeccak256().Hash256(bytes);
    std::vector<uint8_t> addressBytes(hash.data() + 12, hash.data() + 32);
    return ToHex(addressBytes);
}