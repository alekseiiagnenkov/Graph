#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <time.h>
#include <fstream>

using namespace std;

template < typename T >
struct Vertex {
    T name;
    int color;
    vector<Vertex<T>*> adjacent_vertexes;
};

template < class T >
class Graph {
private:
    int size_;

    vector<Vertex<T>*> vertexes_;

    void add_vertex(int, bool);

    bool find(int, int);

    void make_communication(int, int);

    bool find_color(int, int);

    bool find_name(T);

public:
    Graph();

    Graph(int, bool);

    int get_size() { return this->size_; };

    vector<Vertex<T>*> get_vertexes() { return this->vertexes_; }

    //если меняем size, то очищаем прошлый граф и создаем новый
    void set_size(int size, bool timing) {
        for (int i = 0; i < this->vertexes_.size(); i++)
            delete this->vertexes_[i];
        this->vertexes_.clear();
        this->size_ = size;
        for (int i = 0; i < size_; i++) add_vertex(i, timing);

    }

    //если ставим другой массив, то меняем и size(прошлый очищаем)
    void set_vertexes(vector<Vertex<T>*> vertexes) { 
        for (int i = 0; i < this->vertexes_.size(); i++)
            delete this->vertexes_[i];
        this->vertexes_.clear();
        this->size_ = vertexes.size();
        this->vertexes_ = vertexes; 
    }

    void create_graph();

    void initialization_vertexes(bool);

    void print_graph();

    void color_graph();

    void print_color();

    void clear_graph();
};

template < class T >
Graph<T>::Graph() : size_(0) {}

template < class T >
Graph<T>::Graph(int size, bool timing) {
    if (size < 0)
        throw exception();
    this->size_ = size;
    for (int i = 0; i < size_; i++) add_vertex(i, timing);
}

template < class T >
void Graph<T>::create_graph() {
    do {
        cout << "Enter size of graph: ";
        cin >> this->size_;
        cout << endl;
    } while (this->size_ < 0);
    for (int i = 0; i < size_; i++) add_vertex(i, false);
}

template < class T >
void Graph<T>::add_vertex(int i, bool timing) {
    srand(time(0));
    Vertex<T>* vert = new Vertex<T>;
    if (timing) {
        do {
            vert->name = rand() % 1000 * rand() % 1000;
        } while (this->find_name(vert->name));
    }
    else {
        do {
            cout << "Print key/name to [" << i << "] vertex: ";
            cin >> vert->name;
            cout << endl;
        } while (this->find_name(vert->name));
    }
    vert->color = -1;
    this->vertexes_.push_back(vert);
}

template < class T >
bool Graph<T>::find_name(T name) {
    for (int i = 0; i < this->vertexes_.size(); i++) {
        if (this->vertexes_[i]) {
            if (this->vertexes_[i]->name == name)
                return true;
        }
    }
    return false;
}

template < class T >
void Graph<T>::initialization_vertexes(bool timing) {
    srand(time(0));
    int j = -1;
    string strVertexes;
    for (int i = 0; i < this->size_; i++) {
        if (timing) {
            int size = (rand() % this->size_ * rand() % this->size_) % (this->size_-1);
            for(int k=0; k<size; k++)
                make_communication(i, rand()%(this->size_-1));
        }
        else {
            do {
                if (j != -1)
                    cout << "Enter vertexes adjacent to [" << i << "] vertex: ";
                getline(cin, strVertexes);
                j = 0;
            } while (int(strVertexes.size()) == 0);
            for (int a = int(strVertexes.size()) - 1; a >= 0; a--)
                if (strVertexes[a] == ' ')
                    strVertexes.pop_back();
                else {
                    j = (strVertexes[a]) - '0';
                    if (j >= this->size_)
                        throw std::exception();
                    make_communication(i, j);
                    strVertexes.pop_back();
                }
            strVertexes.clear();
            cout << endl;
        }
    }
}

template < class T >
void Graph<T>::make_communication(int i, int j) {
    if (i != j)
        if (!find(i, j)) {
            this->vertexes_[i]->adjacent_vertexes.push_back(this->vertexes_[j]);
            this->vertexes_[j]->adjacent_vertexes.push_back(this->vertexes_[i]);
        }
}

template < class T >
bool Graph<T>::find(int i, int j) {
    for (int k = 0; k < this->vertexes_[i]->adjacent_vertexes.size(); k++)
        if (this->vertexes_[i]->adjacent_vertexes[k] == this->vertexes_[j])
            return true;
    return false;
}

template < class T >
bool Graph<T>::find_color(int i, int color) {
    int j = 0;
    while (!(find(i, j) && vertexes_[j]->color == color) && j != i)
        j++;
    return (j == i);
}

template < class T >
void Graph<T>::color_graph() {
    int i = 0;
    int color = 0;
    if (this->size_ > 0) {
        vertexes_[i]->color = color;
        for (; i < this->size_; color = 0, i++) {
            while (!find_color(i, color))
                color++;
            vertexes_[i]->color = color;
        }
    }
    else cout << "It is not possible to color_graph a graph with size 0!";
}

template < class T >
void Graph<T>::print_graph() {
    cout << "   [GRAPH]" << endl;
    for (int i = 0; i < this->size_; i++) {
        cout << "{ing[" << i << "], name[" << vertexes_[i]->name << "]} - ";

        for (int j = 0; j < this->vertexes_[i]->adjacent_vertexes.size(); j++) {
            if (j != 0)
                cout << ", ";
            cout << "name[" << this->vertexes_[i]->adjacent_vertexes[j]->name << "]";
        }
        cout << endl;
    }
}

template < class T >
void Graph<T>::print_color() {
    std::ofstream outData;
    outData.open("../data.csv", ios::out);
    if (outData.is_open()) {
        outData << "Index" <<';'<< "Name" <<';'<< "Color" << endl;

        cout << "  [COLORS]" << endl;
        for (int i = 0; i < this->size_; i++)
            if (vertexes_[i] != nullptr) {
                cout << "Color {ind[" << i << "], name[" << vertexes_[i]->name << "]} - " << vertexes_[i]->color << endl;
                outData << i <<';'<< vertexes_[i]->name <<';'<< vertexes_[i]->color << std::endl;
            }
        outData.close();
    }
    else {
        cout << "error";
    }
}

template < class T >
void Graph<T>::clear_graph() {
    for (int i = 0; i < this->vertexes_.size(); i++) {
        delete this->vertexes_[i];
    }
    this->vertexes_.clear();
}