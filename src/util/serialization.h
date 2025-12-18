//
// Created by caleb on 12/17/25.
//

#ifndef HYPERCHAIN_SERIALIZATION_H
#define HYPERCHAIN_SERIALIZATION_H

#include "../crypto/uint256.h"
#include <string>
#include <cstdint>
#include <vector>

class Serializer
{
public:
    static void WriteUint64(std::vector<uint8_t>& out, uint64_t v);
    static uint64_t ReadUint64(const std::vector<uint8_t>& in, size_t& offset);

    static void WriteString(std::vector<uint8_t>& out, const std::string& str);
    static std::string ReadString(const std::vector<uint8_t>& in, size_t& offset);

    static void WriteUint256(std::vector<uint8_t>& out, const uint256& v);
    static uint256 ReadUint256(const std::vector<uint8_t>& in, size_t& offset);

    static void WriteBytes(std::vector<uint8_t>& out,
                           const std::vector<uint8_t>& bytes);

    static std::vector<uint8_t> ReadBytes(const std::vector<uint8_t>& in,
                                          size_t& offset);
};

class Serializable
{
public:
    virtual ~Serializable() = default;

    virtual void Serialize(std::vector<uint8_t>& out) const = 0;
    virtual void Deserialize(const std::vector<uint8_t>& in, size_t& offset) = 0;

    std::vector<uint8_t> ToBytes() const;
};

std::string ToHex(const std::vector<uint8_t>& in);

#endif //HYPERCHAIN_SERIALIZATION_H
