//
// Created by caleb on 12/17/25.
//

#include "db.h"

void CKeyValueDatabase::Put(const leveldb::Slice key, const leveldb::Slice value) const
{
    leveldb::Status status = DB->Put(leveldb::WriteOptions(), key, value);\
    assert(status.ok());
}

void CKeyValueDatabase::Delete(leveldb::Slice key) const
{
    leveldb::Status status = DB->Delete(leveldb::WriteOptions(), key);
    assert(status.ok());
}

leveldb::Slice CKeyValueDatabase::Get(leveldb::Slice key) const
{
    std::string value;
    leveldb::Status status = DB->Get(leveldb::ReadOptions(), key, &value);
    assert(status.ok());
    return leveldb::Slice(value);
}

