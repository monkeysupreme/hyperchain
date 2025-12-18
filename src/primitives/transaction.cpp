//
// Created by caleb on 12/17/25.
//

#include "transaction.h"

bool CTxInfo::Empty() const
{
    return ExtraData.empty();
}

void CTxInfo::Serialize(std::vector<uint8_t>& out) const
{
    Serializer::WriteUint64(out, Version);
    Serializer::WriteUint64(out, Time);
    Serializer::WriteUint64(out, GasLimit);
    Serializer::WriteUint64(out, GasUsed);
    Serializer::WriteUint64(out, GasPrice);
}

void CTxInfo::Deserialize(const std::vector<uint8_t>& in, size_t& offset)
{
    Version = Serializer::ReadUint64(in, offset);
    Time = Serializer::ReadUint64(in, offset);
    GasLimit = Serializer::ReadUint64(in, offset);
    GasUsed = Serializer::ReadUint64(in, offset);
    GasPrice = Serializer::ReadUint64(in, offset);
}

void CTransaction::SetData(const CTxInfo& data)
{
    if (TxData.Empty())
    {
        TxData = data;
    }
}

CTxInfo CTransaction::GetData()
{
    return TxData;
}

void CTransaction::Serialize(std::vector<uint8_t>& out) const
{
    TxData.Serialize(out);
    Serializer::WriteUint256(out, TxID);
}

void CTransaction::Deserialize(const std::vector<uint8_t>& in, size_t& offset)
{
    TxData.Deserialize(in, offset);
    TxID = Serializer::ReadUint256(in, offset);
}

CTransaction MakeTransaction(const CTxInfo& data)
{
    CTransaction tx;
    tx.SetData(data);
    auto hasher = CKeccak256();
    tx.TxID = HashTransaction(hasher, tx);
    return tx;
}

uint256 HashTransaction(CKeccak256& k, const CTransaction& tx)
{
    const auto tx_bytes = tx.ToBytes();
    const auto hash_bytes = k.Hash256(tx_bytes);
    return hash_bytes; // type: uint256
}

std::string GetTxHashString(const uint256& hash_bytes)
{
    return hash_bytes.ToHex();
}