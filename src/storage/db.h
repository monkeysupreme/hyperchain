//
// Created by caleb on 12/17/25.
//

#ifndef HYPERCHAIN_DB_H
#define HYPERCHAIN_DB_H

#include <leveldb/db.h>
#include <vector>

class CKeyValueDatabase
{
public:
    leveldb::DB* DB{};

    explicit CKeyValueDatabase(const std::string& path)
        : m_Path(path)
    {
        m_Options.create_if_missing = true;

        leveldb::Status const status = leveldb::DB::Open(m_Options, path, &DB);
        assert(status.ok());
    }

    // writing to database
    void Put(leveldb::Slice key, leveldb::Slice value) const;
    void Delete(leveldb::Slice key) const;

    // reading from database
    leveldb::Slice Get(leveldb::Slice key) const;

private:
    std::string m_Path;

    leveldb::Options m_Options;
};

#endif //HYPERCHAIN_DB_H
