#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;

template < typename T >
struct Vertex {
    T key;
    int color;
    vector<Vertex<T>*> adjacent_vertexes;
};

template < class T >
class Graph {
private:
    int size_;

    Vertex<T>** vertexes_;

    void add_vertex(int);

    bool find(int, int);

    void make_communication(int, int);

    bool find_color(int, int);

public:
    Graph();

    int get_size() { return this->size_; };

    Vertex<T>** get_vertexes() { return this->vertexes_; }

    void set_size(int size) { this->size_ = size; }

    void set_vertexes(Vertex<T>** vertexes) { this->vertexes_ = vertexes; }

    void create_graph();

    void initialization_vertexes();

    void print_graph();

    void color_graph();

    void print_color();
};
