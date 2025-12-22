//
// Created by caleb on 12/17/25.
//

#include "wallet.h"

#include "../crypto/keccak.h"
#include "../crypto/keys.h"
#include "address.h"

#include <stdexcept>
#include <utility>

CWallet::CWallet() = default;

CWallet::CWallet(std::string annotation)
    : mAnnotation(std::move(annotation))
{
    Information.TotalNonce = 0;
    Information.Address = BytesToAddress(Keys.PublicKey);
}

bool CWallet::LoadPrivateKeyFromBytes(const std::vector<uint8_t>& privKeyBytes)
{
    if (privKeyBytes.size() != 32)
    {
        return false;
    }

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

uint64_t CWallet::GetTransactionCount() const
{
    return Information.TotalNonce;
}

CAmount CWallet::GetBalance() const
{
    return Information.Balance;
}

uint64_t CWallet::GetBalanceWei() const
{
    return Information.Balance.ToWei();
}

std::string CWallet::GetAnnotation() const
{
    return mAnnotation;
}

void CWallet::Nullify()
{
    Information.TotalNonce = 0;
    Information.Address.clear();
    Information.Balance = CAmount();
    Keys.PrivateKey.clear();
    Keys.PublicKey.clear();
    mAnnotation.clear();
    mPath.clear();
    mWalletDatabase.reset();
}

void CWallet::SetPath(const std::string& path)
{
    mPath = path;
    mWalletDatabase = std::make_unique<CKeyValueDatabase>(mPath);
}

std::string CWallet::GetPath() const
{
    return mPath;
}

void CWallet::Dump() const
{
    if (!mWalletDatabase)
    {
        throw std::runtime_error("Wallet database not initialized");
    }

    std::vector<uint8_t> out;
    Serialize(out);

    mWalletDatabase->Put(
        leveldb::Slice(Information.Address),
        leveldb::Slice(ToHex(out))
    );
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
    Keys.PublicKey = Serializer::ReadBytes(in, offset);
    Information.TotalNonce = Serializer::ReadUint64(in, offset);
    Information.Address = Serializer::ReadString(in, offset);
}
