#include "block-store.h"

CBlockStore::CBlockStore(const std::string& path)
    : mDatabase(path)
{
}

void CBlockStore::StoreBlock(const CBlock& block) const
{
    mDatabase.Put(
        leveldb::Slice(block.Hash.ToHex()),
        leveldb::Slice(ToHex(block.ToBytes()))
    );
}

void CBlockStore::GetBlockByHash(const std::string& hash, CBlock& out) const
{
    leveldb::Slice result = mDatabase.Get(leveldb::Slice(hash));
    std::string value(result.data(), result.size());
    std::vector<uint8_t> bytes(value.begin(), value.end());
    size_t offset = 0;
    out.Deserialize(bytes, offset);
}
