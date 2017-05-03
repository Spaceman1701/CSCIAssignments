#include <string>
#include "OAHashTable.h"
#include "PlayerData.h"
#include <iostream>

using namespace std;

OAHashTable::OAHashTable(int table_size) : HashTable(table_size) {
    table = new Pair[table_size];
}

OAHashTable::~OAHashTable() {
    delete[] table;
}

bool OAHashTable::put(string key, PlayerData value) {
    if (containsKey(key)) {
        return false;
    }
    uint hash = hashString(key);
    uint mod_hash = hash % getTableSize();

    uint inital_hash = mod_hash;
    if (table[mod_hash].value.year != -1) {
        conflicts++;
    }
    while (table[mod_hash].value.year != -1) {
        ++search_ops;
        ++hash;
        mod_hash = hash % getTableSize();

        if (inital_hash == mod_hash) //cycle!
            return false; //no room
    }
    table[mod_hash] = Pair(key, value);
}

PlayerData* OAHashTable::getAndCount(string& key, int* ops) {
    uint hash = hashString(key);
    uint mod_hash = hash % getTableSize();

    uint inital_hash = mod_hash;
    while (table[mod_hash].value.year != -1 && table[mod_hash].key != key) {
        (*ops)++;
        hash++;
        mod_hash = hash % getTableSize();

        if (inital_hash == mod_hash) //cycle
            return NULL; //no room
    }

    if (table[mod_hash].value.year == -1) {
        return NULL;
    } else {
        return &table[mod_hash].value; 
    }
}

bool OAHashTable::containsKey(string& key) {
    return (bool)get(key);
}

int OAHashTable::count() {
    int c = 0;
    for (int i = 0; i < getTableSize(); ++i) {
        if (table[i].value.year != -1)
            ++c;
    }
    return c;
}