#include "HashTable.h"
#include <string>
#include "PlayerData.h"

using string = std::string;

HashTable::HashTable(int table_size) {
    this->table_size = table_size;

    conflicts = 0;
    search_ops = 0;
}

HashTable::~HashTable() {}

uint HashTable::hashString(string& key) {
    uint hash = 7;
    for (uint i = 0; i < key.length(); ++i) {
        hash = hash * 7 + key[i];
    }
    return hash;
}

int HashTable::getTableSize() {
    return table_size;
}

long HashTable::getNumConflicts() {
    return conflicts;
}

long HashTable::getNumSearchOps() {
    return search_ops;
}

PlayerData* HashTable::get(string& key) {
    int ops;
    return getAndCount(key, &ops);
}