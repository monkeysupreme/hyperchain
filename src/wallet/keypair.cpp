//
// Created by caleb on 12/17/25.
//

#include "keypair.h"

CKeyPair GenerateKeyPair()
{
    CKeyPair keypair;
    const auto privateKey = CPrivateKey();
    keypair.PrivateKey = privateKey.GetPrivateKeyBytes();
    keypair.PublicKey = privateKey.GetPublicKeyBytes(true);
    return keypair;
}