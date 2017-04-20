#include <fstream>
#include <sstream>
#include <iostream>
#include <queue>
#include <unordered_set>

#include "graph.h"

using namespace std;

Graph::Graph(char* file_name) {
    parseFile(file_name);
}

Graph::~Graph() {
    delete[] vertices;
    delete[] edges;
}

int Graph::findShortestPath(string start_city, string end_city) {
    int start = -1, end = -1;
    for (int i = 0; i < num_verts; ++i) {
        if (vertices[i].name == start_city)
            start = i;
        else if (verticies[i].name == end_city)
            end = i;
    }

    findShortestPath(start, end);
}

int findShortestPath(int start, int end) {
    if (start == -1 || end == -1)
        return -1;
    unordered_set<int> visited;
    queue<int> discovered;

    discovered.push(start);
    visited.insert(start);

    while (!discovered.empty()) {
        int current = discovered.front();
        discovered.pop();
        if (current == end) {
            
        }
    }
}

int Graph::getEdgeBetween(int from, int to) {
    return edges[from + to * num_verts];
}

void Graph::setEdgeBetween(int from, int to, int value) {
    edges[from + to * num_verts] = value;
}

void Graph::parseFile(char* file_name) {
    ifstream data_file(file_name);

    string raw_first_line;
    getline(data_file, raw_first_line);
    
    vector<string> first_line;
    splitLine(raw_first_line, ',', first_line);
    
    num_verts = first_line.size() - 1;

    vertices = new VertData[num_verts];
    edges = new int[num_verts * num_verts];

    for (int i = 0; i < num_verts; ++i) {
        string line;
        getline(data_file, line);
        vector<string> line_data;
        splitLine(line, ',', line_data);

        vertices[i] = VertData(line_data[0], i);
        
        for (int j = 0; j < num_verts; ++j) {
            setEdgeBetween(i, j, stoi(line_data[j + 1]));
        }
    }

    data_file.close();    
}

void Graph::splitLine(string& line, char sep, vector<string>& out) {
    string part;
    stringstream ss(line);
    while(getline(ss, part, sep))
        out.push_back(part);
}