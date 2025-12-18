//
// Created by caleb on 12/17/25.
//

#ifndef HYPERCHAIN_KECCAK_H
#define HYPERCHAIN_KECCAK_H

#include "uint256.h"

#include <vector>
#include <cryptopp/keccak.h>

class CKeccak256
{
public:
    CKeccak256() = default;

    uint256 Hash256(const std::string& data);
    uint256 Hash256(const std::vector<uint8_t>& data);
};

#endif //HYPERCHAIN_KECCAK_H
