#ifndef HYPERCHAIN_WALLET_H
#define HYPERCHAIN_WALLET_H

#include <vector>
#include <string>
#include <cstdint>

#include "../storage/db.h"
#include "../util/serialization.h"
#include "keypair.h"

struct CWalletInfo
{
    uint64_t TotalNonce{0};
    std::string Address;
};

class CWallet : public Serializable
{
public:
    CKeyPair Keys;
    CWalletInfo Information;

    CWallet();
    explicit CWallet(const std::string& annotation);

    bool LoadPrivateKeyFromBytes(const std::vector<uint8_t>& privKeyBytes);

    std::vector<uint8_t> GetPrivateKeyBytes() const;
    std::vector<uint8_t> GetPublicKeyBytes() const;

    void Dump() const;

    void Serialize(std::vector<uint8_t>& out) const override;
    void Deserialize(const std::vector<uint8_t>& in, size_t& offset) override;

private:
    std::string mAnnotation;
    CKeyValueDatabase mWalletDatabase;
};

#endif // HYPERCHAIN_WALLET_H

