#include "Graph.h"

using namespace std;

template < class T >
Graph<T>::Graph() : size_(0), vertexes_(nullptr) {}

template < class T >
void Graph<T>::create_graph() {
    do {
        cout << "Enter size of graph: ";
        cin >> this->size_;
        cout << endl;
    } while (this->size_ < 0);
    this->vertexes_ = new Vertex * [this->size_];
    for (int i = 0; i < size_; i++) add_vertex(i);
}

template < class T >
void Graph<T>::add_vertex(int i) {
    Vertex<T>** vert = new Vertex;
    vert->key = i;
    vert->color = -1;
    this->vertexes_[i] = vert;
}

template < class T >
void Graph<T>::initialization_vertexes() {
    int j = -1;
    string strVertexes;
    for (int i = 0; i < this->size_; i++) {
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
        cout << "[" << i << "] - ";
        for (int j = 0; j < this->vertexes_[i]->adjacent_vertexes.size(); j++) {
            if (j != 0)
                cout << ", ";
            cout << this->vertexes_[i]->adjacent_vertexes[j]->key;
        }
        cout << endl;
    }
}

template < class T >
void Graph<T>::print_color() {
    cout << endl;
    cout << "  [COLORS]" << endl;
    for (int i = 0; i < this->size_; i++)
        if (vertexes_[i] != nullptr) {
            cout << "Color [" << i << "] - " << vertexes_[i]->color << endl;
        }
}