#include "Graph.h"

int main() {
    try {
        Graph<string> G;
        G.create_graph();
        G.initialization_vertexes(false);
        G.print_graph();
        G.color_graph();
        G.print_color();
        G.clear_graph();
    }
    catch (const std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }
}