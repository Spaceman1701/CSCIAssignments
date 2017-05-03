#include "ChainingHashTable.h"
#include <cstring>
#include <string>

using namespace std;

ChainingHashTable::ChainingHashTable(int table_size) : HashTable(table_size) {
    table = new Node*[table_size];
    memset(table, 0, sizeof(Node*) * table_size);
}

ChainingHashTable::~ChainingHashTable() {
    for (int i = 0; i < getTableSize(); ++i) {
        Node* n = table[i];
        while (n) {
            Node* next = n->next;
            delete n;
            n = next;
        }
    }
    delete[] table;
}

bool ChainingHashTable::put(string key, PlayerData value) {
    if (containsKey(key)) {
        return false;
    }
    uint hash = hashString(key) % getTableSize();

    if (table[hash]) {
        conflicts++;
    }

    Node* node = new Node(key, value);
    node->next = table[hash];
    table[hash] = node;
    return true;
}

PlayerData* ChainingHashTable::getAndCount(string& key, int* ops) {
    uint hash = hashString(key) % getTableSize();
    
    Node* node = table[hash];
    while (node != NULL && node->key != key) {
        node = node->next;
        (*ops)++;
    }
    return node ? &node->value : NULL; 
}

bool ChainingHashTable::containsKey(string& key) {
    return (bool)get(key);
}

int ChainingHashTable::count() {
    int c = 0;
    for (int i = 0; i < getTableSize(); ++i) {
        Node* n = table[i];
        while (n) {
            ++c;
            n = n->next;
        }
    }
    return c;
}