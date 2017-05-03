#ifndef OA_HASH_TABLE_H
#define OA_HASH_TABLE_H

#include <string>
#include "PlayerData.h"
#include "HashTable.h"

using namespace std;

struct Pair {
    string key;
    PlayerData value;

    Pair() {
        value.year = -1;
    }

    Pair(string key, PlayerData value) {
        this->key = key;
        this->value = value;
    }
};

class OAHashTable : public HashTable {
    public:
        OAHashTable(int table_size);
        virtual ~OAHashTable();
        bool put(string key, PlayerData value);
        PlayerData* getAndCount(string& key, int* ops);
        bool containsKey(string& key);
        int count();
    private:
        Pair* table;
};

#endif