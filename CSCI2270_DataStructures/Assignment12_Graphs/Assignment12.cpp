#include <iostream>
#include <string.h>

#include "Graph.h"

int main(int argc, char** argv) {
    char* file_name = argv[1];

    Graph g(file_name);

    bool quit = false;
    while (!quit) {
        cout << "======Main Menu======" << endl;
        cout << "1. Print vertices" << endl;
        cout << "2. Find districts" << endl;
        cout << "3. Find shortest path" << endl;
        cout << "4. Quit" << endl;
        
        char c; 
        cin >> c;
        c -= '0';
        switch(c) {
            case 1:
                g.printAllNodes();
                break;
            case 2:
                g.computeDistricts();
                break;
            case 3:
                {
                    if (!g.districtsFound()) {
                        cout << "Please identify the districts before checking distances" << endl;
                        break;
                    }
                    string start, end;
                    cout << "Enter a starting city:" << endl;
                    cin.ignore(1, '\n');
                    getline(cin, start);
                    cout << "Enter an ending city:" << endl;
                    getline(cin, end);

                    if (!g.containsCity(start) || !g.containsCity(end)) {
                        cout << "One or more cities doesn't exist" << endl;
                        break;
                    }
                    vector<int> path = g.findShortestPath(start, end);
                    if (path.size() < 1) {
                        cout << "No safe path between cities" << endl;
                        break;
                    }

                    cout << path.size() - 1;
                    for (int i = 0; i < path.size(); ++i)
                        cout << "," << g.vertexFromIndex(path[i]).name;
                    cout << endl;
                    break;
                }
            case 4:
                quit = true;
                break;
        }
    }
    cout << "Goodbye!" << endl;
    return 0;
}