#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <string>
#include "PlayerData.h"

using string = std::string;

class HashTable {
    public:
        HashTable(int table_size);
        virtual ~HashTable() = 0;
        virtual bool put(string key, PlayerData value) = 0;
        PlayerData* get(string& key);
        virtual PlayerData* getAndCount(string& key, int* ops) = 0;
        virtual bool containsKey(string& key) = 0;
        virtual int count() = 0;

        int getTableSize();
        long getNumConflicts();
        long getNumSearchOps();
    protected:
        uint hashString(std::string& key);
        
        long conflicts;
        long search_ops;
    private:
        int table_size;
};

#endif