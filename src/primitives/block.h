//
// Created by caleb on 12/17/25.
//

#ifndef HYPERCHAIN_BLOCK_H
#define HYPERCHAIN_BLOCK_H

#include "../crypto/keccak.h"
#include "../crypto/uint256.h"
#include "../util/serialization.h"

#include <vector>

class CBlockHeader : public Serializable
{
public:
    uint64_t Version;
    uint256 ParentBlockHash;
    uint64_t Number;
    uint64_t BaseFee;
    uint64_t TotalGasTx;
    uint64_t Nonce;

    std::vector<uint8_t> ExtraData;
    uint256 ExtraDataHash;

    CBlockHeader();

    void Nullify();
    bool IsNull();

    size_t GetSize() const;

    void Serialize(std::vector<uint8_t>& out) const override;
    void Deserialize(const std::vector<uint8_t>& in, size_t& offset) override;
};

class CBlock : public CBlockHeader
{
public:
    uint256 Hash;

    explicit CBlock(const CBlockHeader& header)
    {
        Nullify();
        *(static_cast<CBlockHeader*>(this)) = header;
    }

    void Serialize(std::vector<uint8_t>& out) const override;
    void Deserialize(const std::vector<uint8_t>& in, size_t& offset) override;
};

#endif //HYPERCHAIN_BLOCK_H
