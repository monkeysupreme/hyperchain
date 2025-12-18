//
// Created by caleb on 12/17/25.
//

#ifndef HYPERCHAIN_TRANSACTION_H
#define HYPERCHAIN_TRANSACTION_H

#include "../crypto/keccak.h"
#include "../crypto/uint256.h"

#include "../util/serialization.h"

struct CTxInfo : Serializable
{
    uint64_t Version;
    uint64_t Time;

    uint64_t Nonce;

    // gas
    uint64_t GasLimit;
    uint64_t GasUsed;
    uint64_t GasPrice;

    // any arbitrary data (in bytes)
    // Example: A message -- later this can be extended to
    // image metadata / audio metadata...
    std::vector<uint8_t> ExtraData;
    uint256 ExtraDataHash;

    bool Empty() const;

    void Serialize(std::vector<uint8_t>& out) const override;
    void Deserialize(const std::vector<uint8_t>& in, size_t& offset) override;
};

class CTransaction : public Serializable
{
public:
    CTxInfo TxData;
    uint256 TxID;

    CTransaction() = default;

    // only allows you to set data if current "Data" attribute is not fulfilled
    void SetData(const CTxInfo& data);
    CTxInfo GetData();

    void Serialize(std::vector<uint8_t>& out) const override;
    void Deserialize(const std::vector<uint8_t>& in, size_t& offset) override;
};

CTransaction MakeTransaction(const CTxInfo& data);

uint256 HashTransaction(CKeccak256& k, const CTransaction& tx);
std::string GetTxHashString(const std::vector<uint8_t>& hash_bytes);

#endif //HYPERCHAIN_TRANSACTION_H
