#ifndef HYPERCHAIN_AMOUNT_H
#define HYPERCHAIN_AMOUNT_H

#include <cstdint>

class CAmount
{
public:
    CAmount();
    explicit CAmount(uint64_t value);

    void SetValue(uint64_t value);
    uint64_t GetValue() const;

    uint64_t ToWei() const;
    uint64_t ToHype() const;

private:
    uint64_t mValue;
    static constexpr uint64_t WEI_PER_ETHER = 1000000000000000000ULL;
};

#endif

