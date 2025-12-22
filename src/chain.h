#ifndef HYPERCHAIN_CHAIN_H
#define HYPERCHAIN_CHAIN_H

#include "primitives/block.h"
#include "storage/block-packager.h"
#include "storage/block-store.h"

class CBlockChain
{
public:
    uint256 ChainID;
    std::vector<CBlock> BlockMemory;
    bool HasGenesis;

    explicit CBlockChain(const std::string& dataPath);

    CBlock GetBlockByHash(const std::string& hash);
    bool SanityCheck();
    void SaveBlockToDisk(const CBlock& block);

private:
    void AddBlockToMemory(const CBlock& block);
    void StoreBlockWithVerification(const CBlock& block);
    void FlushBlockMemoryToDisk();
    void CreateGenesis();

private:
    CBlockPackager mPackager;
    CBlockStore mBlockStore;
};

#endif
