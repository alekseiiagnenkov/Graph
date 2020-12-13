#pragma once
#include <iostream>
#include <vector>
#include <string>

typedef struct Vertex* ptrVert;
using namespace std;

struct Vertex {
    int key;
    int color;
    vector<Vertex*> adjacent_vertexes;
};

class Graph {
private:
    int size_;

    ptrVert* vertexes_;

    void add_vertex(int);

    bool find(int, int);

    void make_communication(int, int);

    bool find_color(int, int);

public:
    Graph();

    void create_graph();

    void initialization_vertexes();

    void print_graph();

    void color_graph();

    void print_color();
};
