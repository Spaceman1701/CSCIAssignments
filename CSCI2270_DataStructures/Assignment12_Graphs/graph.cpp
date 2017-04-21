#include <fstream>
#include <sstream>
#include <iostream>
#include <queue>
#include <algorithm>

#include "graph.h"

using namespace std;

Graph::Graph(char* file_name) {
    parseFile(file_name);
}

Graph::~Graph() {
    delete[] vertices;
    delete[] edges;
}

void Graph::computeDistricts() {

}

int Graph::findShortestPath(string start_city, string end_city) {
    int start = -1, end = -1;
    for (int i = 0; i < num_verts; ++i) {
        if (vertices[i].name == start_city)
            start = i;
        else if (verticies[i].name == end_city)
            end = i;
    }

    vector<int> path = findShortestPath(start, end);
    return path.size(); // the number of edges. change later when adjusted to account for weighting
}

vector<int> findShortestPath(int start, int end) { //returns the shortest path. returns the whole path incase that's important for a later assignment
    if (start == -1 || end == -1)
        return -1;
    
    queue<int> discovered;
    discovered.push(start);
    
    int* path = new int[num_verts];
    for (int i = 0; i < num_verts; ++i)
        path[i] = -1;
    
    path[start] = start; 
    //since the key is an int, this is a visited set and values can point to the parent for path reconstruction

    while (!discovered.empty()) {
        int current = discovered.front();
        discovered.pop();
        if (current == end) {
            vector<int> output = pathToVector(end, path);
            delete[] path;
            return output;
        }
        for (int i = 0; i < num_verts; ++i) {
            if (path[i] != -1 && getEdgeBetween(current, i) > 0) {
                path[i] = current;
                discovered.push(i);
            }
        }
    }

    delete[] path;
    return vector<int>(); //this might not work
}

vector<int> pathToVector(int end, int* path) {
    vector<int> output;

    int current = end;
    while (path[current] != current) {
        output.push_back(current);
        current = path[current]; //pointer to it's parent'
    }

    reverse(output.begin(), output.end());
    return output;
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