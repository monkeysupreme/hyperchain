#include "block-packager.h"
#include "../primitives/block.h"

#include <sstream>
#include <ctime>

CBlockFile::CBlockFile(const std::string& pkgHash, int pkgTime)
    : mPkgHash(pkgHash), mPkgTime(pkgTime)
{
    FileOutputStream.open(AssembleLabel(), std::ios::binary);
}

std::string CBlockFile::AssembleLabel() const
{
    std::stringstream ss;
    ss << "block-" << mPkgHash << "-" << mPkgTime << ".dat";
    return ss.str();
}

CBlockPackager::CBlockPackager(const std::string& chainHash)
    : mChainHash(chainHash)
{
}

void CBlockPackager::PackageBlock(const CBlock& block)
{
    CBlockFile file(mChainHash, static_cast<int>(std::time(nullptr)));
    std::string hex = ToHex(block.ToBytes());
    file.FileOutputStream.write(hex.data(), hex.size());
}
