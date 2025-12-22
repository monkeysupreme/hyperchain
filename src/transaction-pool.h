//
// Created by caleb on 12/22/25.
//

#ifndef HYPERCHAIN_TRANSACTION_POOL_H
#define HYPERCHAIN_TRANSACTION_POOL_H
#include "primitives/transaction.h"


#include <list>

struct CTxPoolParams
{
    const int MAX_POOL_SIZE = 100;
    // ...
};

class CTransactionPool
{
public:
    CTxPoolParams Params;

    std::list<CTransaction> PendingTransactions;

    CTransactionPool();

    void Add(CTransaction& tx);
    void AddBatch(std::vector<CTransaction>& txs);

    void Remove(const std::string& txid);
    void ClearPending();
};

#endif //HYPERCHAIN_TRANSACTION_POOL_H
