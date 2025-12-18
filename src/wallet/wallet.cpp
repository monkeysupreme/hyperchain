//
// Created by caleb on 12/17/25.
//

#include <iostream>

#include "wallet.h"

#include "../crypto/keys.h"
#include "../crypto/keccak.h"

CWallet::CWallet() : mWalletDatabase(CKeyValueDatabase("walletdata"))
{
}

CWallet::CWallet(const std::string& annotation) : mWalletDatabase(CKeyValueDatabase(annotation))
{
    mAnnotation = annotation;

    Information.Address = CKeccak256().Hash256("Hello World").ToHex();

    Information.TotalNonce = 0;
}

bool CWallet::LoadPrivateKeyFromBytes(const std::vector<uint8_t>& privKeyBytes)
{
    if (privKeyBytes.size() != 32)
        return false;

    try
    {
        Keys.PrivateKey = privKeyBytes;

        CPrivateKey priv(privKeyBytes);
        Keys.PublicKey = priv.GetPublicKeyBytes(true);

        return true;
    }
    catch (...)
    {
        Keys.PrivateKey.clear();
        Keys.PublicKey.clear();
        return false;
    }
}

std::vector<uint8_t> CWallet::GetPrivateKeyBytes() const
{
    return Keys.PrivateKey;
}

std::vector<uint8_t> CWallet::GetPublicKeyBytes() const
{
    return Keys.PublicKey;
}

void CWallet::Dump() const
{
    std::vector<uint8_t> out;
    Serialize(out);
    mWalletDatabase.Put(leveldb::Slice(Information.Address), leveldb::Slice(ToHex(out)));
    std::cout << "Wallet '" << mAnnotation << "' dumped to /" << mAnnotation << "\n";
}

void CWallet::Serialize(std::vector<uint8_t>& out) const
{
    Serializer::WriteBytes(out, Keys.PrivateKey);
    Serializer::WriteBytes(out, Keys.PublicKey);
    Serializer::WriteUint64(out, Information.TotalNonce);
    Serializer::WriteString(out, Information.Address);
}

void CWallet::Deserialize(const std::vector<uint8_t>& in, size_t& offset)
{
    Keys.PrivateKey = Serializer::ReadBytes(in, offset);
    Keys.PublicKey  = Serializer::ReadBytes(in, offset);
    Information.TotalNonce = Serializer::ReadUint64(in, offset);
    Information.Address    = Serializer::ReadString(in, offset);
}
