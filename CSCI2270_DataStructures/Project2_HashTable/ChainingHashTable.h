#ifndef CHAINING_HASH_TABLE_H
#define CHAINING_HASH_TABLE_H

#include <stddef.h>
#include <iostream>
#include "HashTable.h"
#include "PlayerData.h"
#include <string>

using string = std::string;

struct Node{
    string key;
    PlayerData value;
    Node* next;

    Node (string key, PlayerData value) {
        this->key = key;
        this->value = value;
        next = NULL;
    }
};

class ChainingHashTable : public HashTable {
    public:
        ChainingHashTable(int table_size);
        virtual ~ChainingHashTable();
        bool put(string key, PlayerData value);
        PlayerData* getAndCount(string& key, int* ops);
        bool containsKey(string& key);
        int count();
    private:
        Node** table;
};

#endif