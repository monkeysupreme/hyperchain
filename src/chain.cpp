#include "chain.h"

#include "crypto/keccak.h"
#include <iostream>

#define MEMORY_USAGE_LIMIT 11

CBlockChain::CBlockChain(const std::string& dataPath)
    : ChainID(CKeccak256().Hash256("chainid")), HasGenesis(false), mPackager(ChainID.ToHex()), mBlockStore(dataPath)
{
    CreateGenesis();
    HasGenesis = true;
}

CBlock CBlockChain::GetBlockByHash(const std::string& hash)
{
    CBlockHeader header;
    CBlock found(header);
    mBlockStore.GetBlockByHash(hash, found);
    return found;
}

bool CBlockChain::SanityCheck()
{
    return !BlockMemory.empty();
}

void CBlockChain::SaveBlockToDisk(const CBlock& block)
{
    AddBlockToMemory(block);
    FlushBlockMemoryToDisk();
    mPackager.PackageBlock(block);
}

void CBlockChain::AddBlockToMemory(const CBlock& block)
{
    if (BlockMemory.size() >= MEMORY_USAGE_LIMIT)
        FlushBlockMemoryToDisk();

    BlockMemory.push_back(block);
}

void CBlockChain::StoreBlockWithVerification(const CBlock& block)
{
    if (!SanityCheck())
        throw std::runtime_error("Sanity check failed");

    mBlockStore.StoreBlock(block);
}

void CBlockChain::FlushBlockMemoryToDisk()
{
    for (const CBlock& block : BlockMemory)
        StoreBlockWithVerification(block);

    BlockMemory.clear();
}

void CBlockChain::CreateGenesis()
{
    CBlockHeader header;
    CBlock block(header);
    SaveBlockToDisk(block);
}
