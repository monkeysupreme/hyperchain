//
// Created by caleb on 12/22/25.
//

#include "transaction-pool.h"

#include <iostream>

CTransactionPool::CTransactionPool()
{
}

void CTransactionPool::Add(CTransaction& tx)
{
    if (PendingTransactions.size() >= Params.MAX_POOL_SIZE)
    {
        std::cout << "Transaction pool limit reached. Clearing..." << "\n";
        ClearPending();
    }
    PendingTransactions.push_back(tx);
}

void CTransactionPool::AddBatch(std::vector<CTransaction>& txs)
{
    for (auto& tx : txs)
    {
        if (PendingTransactions.size() >= Params.MAX_POOL_SIZE || txs.size() >= Params.MAX_POOL_SIZE)
        {
            std::cerr << "Transaction pool batch too large." << "\n";
            break;
        }
        PendingTransactions.push_back(tx);
    }
}

void CTransactionPool::Remove(const std::string& txid)
{
    PendingTransactions.remove_if(
        [&](const CTransaction& tx)
        {
            return tx.TxID.ToHex() == txid;
        }
    );
}

void CTransactionPool::ClearPending()
{
    PendingTransactions.clear();
}




