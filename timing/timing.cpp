#include "../graph/Graph.h"

int main(){
	srand(time(nullptr));
	clock_t first, last;
	int number = 10;//кол-во опытов
	int size = 25; //размер графа
	for (int i = 1; i <= number; i++) {
		Graph<int> G(size * i, true);
		G.initialization_vertexes(true);
		first = clock();
		G.color_graph();
		last = clock();
		std::cout << "Number vertex - [" << size * i << "], time - [" << last - first << "]" << std::endl;
		G.clear_graph();
	}
}