//
// Created by caleb on 12/17/25.
//

#include "transaction.h"


void CTxData::Empty()
{
    Version = 0;
    Time = 0;
    Nonce = 0;
    ToAddr = uint256();
    FromAddr = uint256();
    Value.SetValue(0);

    GasLimit = 0;
    GasUsed = 0;
    GasPrice = 0;

    ExtraData.clear();
    ExtraDataHash = uint256();
}

bool CTxData::IsEmpty() const
{
    return Version == 0 && Time == 0 && Nonce == 0 && Value.GetValue() == 0;
}


void CTxData::Serialize(std::vector<uint8_t>& out) const
{
    Serializer::WriteUint64(out, Version);
    Serializer::WriteUint64(out, Time);
    Serializer::WriteUint64(out, GasLimit);
    Serializer::WriteUint64(out, GasUsed);
    Serializer::WriteUint64(out, GasPrice);
}

void CTxData::Deserialize(const std::vector<uint8_t>& in, size_t& offset)
{
    Version = Serializer::ReadUint64(in, offset);
    Time = Serializer::ReadUint64(in, offset);
    GasLimit = Serializer::ReadUint64(in, offset);
    GasUsed = Serializer::ReadUint64(in, offset);
    GasPrice = Serializer::ReadUint64(in, offset);
}

void CTransaction::SetData(const CTxData& data)
{
    if (TxData.IsEmpty())
    {
        TxData = data;
    }
}

CTxData CTransaction::GetData() const
{
    return TxData;
}

void CTransaction::SetGasLimit(uint64_t gasInWei)
{
    TxData.GasLimit = gasInWei;
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

CTransaction CreateTransaction(const CTxData& data)
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

uint64_t CalcGasUsed(const CTransaction& tx)
{
    return tx.TxData.GasUsed > 0 ? tx.TxData.GasUsed : tx.TxData.GasLimit;
}

uint64_t CalcGasPrice(const CTransaction& tx)
{
    return tx.TxData.GasPrice;
}

__uint128_t CalcTotalGasCost(const CTransaction& tx)
{
    return static_cast<__uint128_t>(CalcGasUsed(tx)) * CalcGasPrice(tx);
}