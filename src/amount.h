#ifndef HYPERCHAIN_AMOUNT_H
#define HYPERCHAIN_AMOUNT_H

#include <cstdint>
#include <stdexcept>

class CAmount
{
public:
    CAmount();
    explicit CAmount(uint64_t value);
    explicit CAmount(__uint128_t value);

    void SetValue(__uint128_t value);
    __uint128_t GetValue() const;

    void FromHype(double hype);
    double ToHype() const;
    __uint128_t ToWei() const;
    void Add(const CAmount& other);

private:
    __uint128_t mValue;
};

#endif
