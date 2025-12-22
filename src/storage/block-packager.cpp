#include "block-packager.h"
#include "../primitives/block.h"

#include <ctime>
#include <iostream>
#include <sstream>

CBlockFile::CBlockFile(const std::string& pkgHash, int pkgTime)
    : mPkgHash(pkgHash), mPkgTime(pkgTime)
{
    CreateFileDirectory();
    FileOutputStream.open("blockdata/disk/" + AssembleLabel(), std::ios::binary);
}

void CBlockFile::CreateFileDirectory()
{
    if (mkdir("blockdata/disk", 0777) == 0)
    {
        std::cout << "Blocks will be saved to /blockdata/disk directory" << "\n";
    }
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
