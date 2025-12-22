#include "amount.h"

CAmount::CAmount() : mValue(0)
{
}
CAmount::CAmount(uint64_t value) : mValue(value)
{
}
CAmount::CAmount(__uint128_t value) : mValue(value)
{
}

void CAmount::SetValue(__uint128_t value)
{
    mValue = value;
}
__uint128_t CAmount::GetValue() const
{
    return mValue;
}

void CAmount::FromHype(double hype)
{
    mValue = static_cast<__uint128_t>(hype * 1e18);
}
double CAmount::ToHype() const
{
    return static_cast<double>(mValue) / 1e18;
}
__uint128_t CAmount::ToWei() const
{
    return mValue;
}

void CAmount::Add(const CAmount& other)
{
    __uint128_t sum = mValue + other.mValue;
    if (sum < mValue)
        throw std::overflow_error("CAmount overflow");
    mValue = sum;
}
