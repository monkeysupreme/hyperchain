#ifndef HYPERCHAIN_BLOCK_STORE_H
#define HYPERCHAIN_BLOCK_STORE_H

#include "../primitives/block.h"
#include "db.h"

class CBlockStore
{
public:
    explicit CBlockStore(const std::string& path);

    void StoreBlock(const CBlock& block) const;
    void GetBlockByHash(const std::string& hash, CBlock& out) const;

private:
    CKeyValueDatabase mDatabase;
};

#endif
