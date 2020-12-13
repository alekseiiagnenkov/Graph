#include "Graph.h"

int main() {
    try {
        Graph G;
        G.create_graph();
        G.initialization_vertexes();
        G.print_graph();
        G.color_graph();
        G.print_color();
    }
    catch (const std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }
}