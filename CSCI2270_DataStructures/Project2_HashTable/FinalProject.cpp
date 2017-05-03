#include <iostream>
#include "ChainingHashTable.h"
#include "OAHashTable.h"
#include "PlayerData.h"
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <cstdlib>

using namespace std;


vector<string> splitString(string s, char delim) {
    string line;
    stringstream ss(s);
    vector<string> result;
    while (getline(ss, line, delim)) {
        result.push_back(line);
    }
    return result;
}

void LoadPlayerData(char* file_name, OAHashTable& oaTable, ChainingHashTable& cTable) {
    ifstream file(file_name);

    string line;
    getline(file, line);
    //bug lies below!
    while (getline(file, line)) {
        vector<string> data = splitString(line, ',');
        string id = data[3];
        if (!cTable.containsKey(id)) {
            PlayerData player;
            player.last_name = data[6];
            player.first_name = data[5];
            player.year = stoi(data[7]);
            player.country = data[8];
            player.weight = stoi(data[9]);
            player.height = stoi(data[10]);
            player.bats = data[11] == "R" ? RIGHT : LEFT;
            player.throws = data[12] == "R" ? RIGHT : LEFT;
            cTable.put(id, player);
            oaTable.put(id, player);
        }
        
        PlayerData* pdc = cTable.get(id);
        PlayerData* pdoa = oaTable.get(id);
        TeamData td;
        td.year = stoi(data[0]);
        td.name = data[1];
        td.league = data[2] == "NL" ? NL : AL;
        td.salery = stoi(data[4]);
        pdc->teams.push_back(td);
        pdoa->teams.push_back(td);
    }
    file.close();
}

bool verifyData(HashTable* a, HashTable* b, char* file_name) {
    ifstream file(file_name);

    string line;
    getline(file, line);
    //bug lies below!
    while (getline(file, line)) {
        vector<string> data = splitString(line, ',');
        string id = data[3];

        bool match = a->get(id)->toString() == b->get(id)->toString();
        if (!match) {
            return false;
        }
    }
    return true;
}


int main(int argc, char** argv) {
    char* file_name = argv[1];
    int table_size = atoi(argv[2]);

    OAHashTable oaTable(table_size);
    ChainingHashTable cTable(table_size);

    LoadPlayerData(file_name, oaTable, cTable);
    if (!verifyData(&oaTable, &cTable, file_name)) {
        cout << "invalid tables" << endl;
    }
    
    cout << "Hash table size: " << table_size << endl;
    cout << "Collisions using open addressing: " << oaTable.getNumConflicts() << endl;
    cout << "Collisions using chaining: " << cTable.getNumConflicts() << endl;
    cout << "Search operations using open addressing: " << oaTable.getNumSearchOps() << endl;
    cout << "Search operations using chaining: " << cTable.getNumSearchOps() << endl; 

    while (true) {
        cout << "1. Query hash table" << endl;
        cout << "2. Quit program" << endl;

        char op;
        cin >> op;

        if (op == '1') {
            cout << "Enter the LEAGUE ID of a player: ";
            string id;
            cin >> id;
            int cops = 0;
            int oaops = 0;
            PlayerData* result = cTable.getAndCount(id, &cops);
            oaTable.getAndCount(id, &oaops);
            if (result) {
                cout << result->toString() << endl;
                cout << "Search operations using open addressing: " << oaops << endl;
                cout << "Search operations using chaining: " << cops << endl;
            } else {
                cout << "Player not found." << endl;
            }
        } else if (op == '2') {
            break;
        } else if (op == 'A') { //for automated data gathering
            string id;
            cin >> id;
            int cops = 0;
            int oaops = 0;
            PlayerData* result = cTable.getAndCount(id, &cops);
            oaTable.getAndCount(id, &oaops);
            if (result) {
                cout << "FOUND " << oaops << " " << cops << endl;
            } else {
                cout << "NOTFOUND" << endl;
            }
        }
    }
}