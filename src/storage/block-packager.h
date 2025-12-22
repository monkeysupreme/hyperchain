#ifndef HYPERCHAIN_BLOCK_PACKAGER_H
#define HYPERCHAIN_BLOCK_PACKAGER_H

#include <fstream>
#include <string>
#include <sys/stat.h>

class CBlock;

class CBlockFile
{
public:
    CBlockFile(const std::string& pkgHash, int pkgTime);
    std::ofstream FileOutputStream;

private:
    void CreateFileDirectory();
    std::string AssembleLabel() const;

private:
    std::string mPkgHash;
    int mPkgTime;
};

class CBlockPackager
{
public:
    explicit CBlockPackager(const std::string& chainHash);

    void PackageBlock(const CBlock& block);

private:
    std::string mChainHash;
};

#endif

