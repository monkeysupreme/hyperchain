//
// Created by caleb on 12/17/25.
//

#include "block.h"

CBlockHeader::CBlockHeader()
{
    Nullify();
}

void CBlockHeader::Nullify()
{
    Version = 0;
    ParentBlockHash = uint256();
    Number = 0;
    BaseFee = 0;
    TotalGasTx = 0;
    Nonce = 0;
    ExtraData.clear();
    ExtraDataHash = uint256();
}

bool CBlockHeader::IsNull()
{
    return GetSize() == 0 ? true : false;
}

size_t CBlockHeader::GetSize() const
{
    std::vector<uint8_t> out;
    Serialize(out);
    return out.size();
}

void CBlockHeader::Serialize(std::vector<uint8_t>& out) const
{
    Serializer::WriteUint64(out, Version);
    Serializer::WriteUint256(out, ParentBlockHash);
    Serializer::WriteUint64(out, Number);
    Serializer::WriteUint64(out, BaseFee);
    Serializer::WriteUint64(out, TotalGasTx);
    Serializer::WriteUint64(out, Nonce);
    Serializer::WriteBytes(out, ExtraData);
    Serializer::WriteUint256(out, ExtraDataHash);
}

void CBlockHeader::Deserialize(const std::vector<uint8_t>& in, size_t& offset)
{
    Version = Serializer::ReadUint64(in, offset);
    ParentBlockHash = Serializer::ReadUint256(in, offset);
    Number = Serializer::ReadUint64(in, offset);
    BaseFee = Serializer::ReadUint64(in, offset);
    TotalGasTx = Serializer::ReadUint64(in, offset);
    Nonce = Serializer::ReadUint64(in, offset);
    ExtraData = Serializer::ReadBytes(in, offset);
    ExtraDataHash = Serializer::ReadUint256(in, offset);
}

void CBlock::Serialize(std::vector<uint8_t>& out) const
{
    CBlockHeader::Serialize(out);
    Serializer::WriteUint256(out, Hash);
}

void CBlock::Deserialize(const std::vector<uint8_t>& in, size_t& offset)
{
    Hash = Serializer::ReadUint256(in, offset);
}