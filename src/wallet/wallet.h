#ifndef HYPERCHAIN_WALLET_H
#define HYPERCHAIN_WALLET_H

#include "../storage/db.h"
#include "../util/serialization.h"
#include "../amount.h"
#include "keypair.h"

#include <cstdint>
#include <memory>
#include <string>
#include <vector>
#include <sstream>

struct CWalletInfo
{
    uint64_t TotalNonce{0};
    std::string Address;
    CAmount Balance = CAmount(0);
};

class CWallet : public Serializable
{
public:
    CKeyPair Keys;
    CWalletInfo Information;

    CWallet();
    explicit CWallet(std::string annotation);

    bool LoadPrivateKeyFromBytes(const std::vector<uint8_t>& privKeyBytes);

    std::vector<uint8_t> GetPrivateKeyBytes() const;
    std::vector<uint8_t> GetPublicKeyBytes() const;

    uint64_t GetTransactionCount() const;

    CAmount GetBalance() const;
    uint64_t GetBalanceWei() const;

    std::string GetAnnotation() const;

    void Nullify();

    void Dump() const;

    void SetPath(const std::string& path);
    std::string GetPath() const;

    void Serialize(std::vector<uint8_t>& out) const override;
    void Deserialize(const std::vector<uint8_t>& in, size_t& offset) override;

private:
    std::string mAnnotation;
    std::string mPath;
    std::unique_ptr<CKeyValueDatabase> mWalletDatabase;
};

inline std::string GenerateWalletDumpPath(
    const std::string& annotation,
    const std::vector<uint8_t>& pubKeyBytes)
{
    std::stringstream ss;
    ss << "w-" << annotation << "-" << ToHex(pubKeyBytes);
    return ss.str();
}

#endif // HYPERCHAIN_WALLET_H
