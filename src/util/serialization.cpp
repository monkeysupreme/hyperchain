//
// Created by caleb on 12/17/25.
//

#include "serialization.h"

#include <cstring>
#include <iomanip>
#include <ios>
#include <memory>
#include <stdexcept>

static void Require(const std::vector<uint8_t>& in, size_t offset, size_t n)
{
    if (offset + n > in.size())
        throw std::runtime_error("buffer underrun");
}

void Serializer::WriteUint64(std::vector<uint8_t>& out, uint64_t v)
{
    for (int i = 0; i < 8; ++i) {
        out.push_back(static_cast<uint8_t>(v & 0xff));
        v >>= 8;
    }
}

uint64_t Serializer::ReadUint64(const std::vector<uint8_t>& in, size_t& offset)
{
    Require(in, offset, 8);
    uint64_t v = 0;
    for (int i = 0; i < 8; ++i)
        v |= static_cast<uint64_t>(in[offset++]) << (8 * i);
    return v;
}

void Serializer::WriteString(std::vector<uint8_t>& out, const std::string& str)
{
    WriteUint64(out, str.size());
    out.insert(out.end(), str.begin(), str.end());
}

std::string Serializer::ReadString(const std::vector<uint8_t>& in, size_t& offset)
{
    uint64_t len = ReadUint64(in, offset);
    Require(in, offset, len);
    std::string s(reinterpret_cast<const char*>(&in[offset]), len);
    offset += len;
    return s;
}

void Serializer::WriteUint256(std::vector<uint8_t>& out, const uint256& v)
{
    const uint8_t* p = v.begin();
    out.insert(out.end(), p, p + 32);
}

uint256 Serializer::ReadUint256(const std::vector<uint8_t>& in, size_t& offset)
{
    Require(in, offset, 32);
    uint256 v;
    memcpy(v.begin(), &in[offset], 32);
    offset += 32;
    return v;
}

void Serializer::WriteBytes(std::vector<uint8_t>& out,
                            const std::vector<uint8_t>& bytes)
{
    WriteUint64(out, bytes.size());
    out.insert(out.end(), bytes.begin(), bytes.end());
}

std::vector<uint8_t> Serializer::ReadBytes(const std::vector<uint8_t>& in,
                                           size_t& offset)
{
    uint64_t len = ReadUint64(in, offset);
    Require(in, offset, len);
    std::vector<uint8_t> v(in.begin() + offset,
                           in.begin() + offset + len);
    offset += len;
    return v;
}

std::vector<uint8_t> Serializable::ToBytes() const
{
    std::vector<uint8_t> out;
    Serialize(out);
    return out;
}

std::string ToHex(const std::vector<uint8_t>& in)
{
    std::stringstream h;
    for (const auto& byte : in)
    {
        h << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
    }
    return h.str();
}
