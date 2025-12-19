#ifndef HYPERCHAIN_WALLET_H
#define HYPERCHAIN_WALLET_H

#include "amount.h"
#include "../storage/db.h"
#include "../util/serialization.h"
#include "keypair.h"

#include <cstdint>
#include <string>
#include <vector>

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
    explicit CWallet(const std::string& annotation);

    bool LoadPrivateKeyFromBytes(const std::vector<uint8_t>& privKeyBytes);

    std::vector<uint8_t> GetPrivateKeyBytes() const;
    std::vector<uint8_t> GetPublicKeyBytes() const;

    // Returns Information.TotalNonce - just a transaction counter.
    // TotalNonce means no two transactions can have the same nonce
    // thus avoiding double spending. If TotalNonce is seen twice
    // it will reject.
    uint64_t GetTransactionCount() const;

    // Returns balance in HYPE
    CAmount GetBalance() const;
    uint64_t GetBalanceWei() const;

    // Nullify just empties the wallet and reverts it back to
    // state of instantiation.
    void Nullify();

    // Save the wallet to leveldb
    void Dump() const;

    void Serialize(std::vector<uint8_t>& out) const override;
    void Deserialize(const std::vector<uint8_t>& in, size_t& offset) override;

private:
    std::string mAnnotation;
    CKeyValueDatabase mWalletDatabase;
};

#endif // HYPERCHAIN_WALLET_H

