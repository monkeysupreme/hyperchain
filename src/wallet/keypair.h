//
// Created by caleb on 12/17/25.
//

#ifndef HYPERCHAIN_KEYPAIR_H
#define HYPERCHAIN_KEYPAIR_H

#include "../crypto/keys.h"

struct CKeyPair
{
    std::vector<uint8_t> PrivateKey;
    std::vector<uint8_t> PublicKey;
};

CKeyPair GenerateKeyPair();

#endif //HYPERCHAIN_KEYPAIR_H
