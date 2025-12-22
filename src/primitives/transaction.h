#ifndef HYPERCHAIN_TRANSACTION_H
#define HYPERCHAIN_TRANSACTION_H

#include "../amount.h"
#include "../crypto/uint256.h"
#include "../crypto/keccak.h"
#include "../util/serialization.h"
#include <cstdint>
#include <vector>

struct CTxData : Serializable
{
    uint64_t Version;
    uint64_t Time;
    uint64_t Nonce;
    uint256 ToAddr;
    uint256 FromAddr;
    CAmount Value;

    uint64_t GasLimit;
    uint64_t GasUsed;
    uint64_t GasPrice;

    std::vector<uint8_t> ExtraData;
    uint256 ExtraDataHash;

    void Empty();
    bool IsEmpty() const;

    void Serialize(std::vector<uint8_t>& out) const override;
    void Deserialize(const std::vector<uint8_t>& in, size_t& offset) override;
};

class CTransaction : public Serializable
{
public:
    CTxData TxData;
    uint256 TxID;

    CTransaction() = default;

    void SetData(const CTxData& data);
    CTxData GetData() const;

    void SetGasLimit(uint64_t gasInWei);

    void Serialize(std::vector<uint8_t>& out) const override;
    void Deserialize(const std::vector<uint8_t>& in, size_t& offset) override;
};

CTransaction CreateTransaction(const CTxData& data);
uint256 HashTransaction(CKeccak256& k, const CTransaction& tx);
std::string GetTxHashString(const std::vector<uint8_t>& hash_bytes);

uint64_t CalcGasUsed(const CTransaction& tx);
uint64_t CalcGasPrice(const CTransaction& tx);
__uint128_t CalcTotalGasCost(const CTransaction& tx);

#endif

