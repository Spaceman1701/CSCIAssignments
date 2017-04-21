#include <iostream>
#include <string.h>

#include "graph.h"


int main(int argc, char** argv) {
    char* file_name = argv[1];

    Graph g(file_name);

    g.computeDistricts();
    g.printAllNodes();

    cout << g.findShortestPathLength("New York", "Chicago") << endl;
}