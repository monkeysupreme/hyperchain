#include "chain.h"

#include <iostream>
int main()
{
    CBlockChain chain = CBlockChain("blockchain-data");

    if (chain.HasGenesis)
    {
        std::cout << "Good." << "\n";
        CBlockHeader header = CBlockHeader();
        CBlock blk = CBlock(header);
        blk.Hash = CKeccak256().Hash256(blk.ToBytes());
        chain.SaveBlockToDisk(blk);
    }

    return 0;
}
