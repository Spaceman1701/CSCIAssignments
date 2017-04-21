#ifndef GRAPH_H
#define GRAPH_H

#include <string.h>
#include <vector>
#include <iostream>

using namespace std;

struct VertData {
    string name;
    int district;
    int index;

    VertData() {
        district = -1;
        index = -1;
    }
    VertData(string name, int index) {
        this->name = name;
        this->index = index;
        this->district = -1;
    }
};

class Graph {
    public:
        Graph(char* file_name);
        virtual ~Graph();
        int findShortestPathLength(string start_city, string end_city);
        vector<int> findShortestPath(string start, string end);
        void computeDistricts();
        void printAllNodes();
        bool districtsFound();
        bool containsCity(string& name);
        VertData& vertexFromIndex(int index);
    private:
        int* edges;
        VertData* vertices;
        int num_verts;

        vector<int> findShortestPath(int start, int end);
        int findShortestPathLength(int start, int end);
        int getEdgeBetween(int vert_one, int vert_two);
        void setEdgeBetween(int vert_one, int vert_two, int value);
        void parseFile(char* file_name);
        void splitLine(string& line, char sep, vector<string>& out);
        vector<int> pathToVector(int end, int* path);
};

#endif