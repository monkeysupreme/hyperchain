//
// Created by caleb on 12/19/25.
//

#include "amount.h"
#include <stdexcept>

CAmount::CAmount() : mValue(0)
{
}

CAmount::CAmount(uint64_t value)
{
    SetValue(value);
}

void CAmount::SetValue(uint64_t value)
{
    if (value > UINT64_MAX / WEI_PER_ETHER)
    {
        throw std::overflow_error("amount overflow");
    }

    mValue = value;
}

uint64_t CAmount::GetValue() const
{
    return mValue;
}

uint64_t CAmount::ToWei() const
{
    return mValue * WEI_PER_ETHER;
}

uint64_t CAmount::ToHype() const
{
    return mValue;
}