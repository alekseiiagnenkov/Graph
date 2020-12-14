#include "pch.h"
#include "../graph/Graph.h"

TEST(Constructor, Graph) {
	//конструктор 1
	Graph<int> G;
	//проверяем, присвоились ли дефолтные значения
	ASSERT_EQ(0, G.get_size());
	//т.к. size=0, то и вершин просто нет
	ASSERT_EQ(0, G.get_vertexes().size());
	//конструктор 2
	Graph<int> G_1(5, true);
	//тот ли размер
	ASSERT_EQ(5, G_1.get_size());
	//проверяем, создались ли вершины
	for (int i = 0; i < G_1.get_size(); i++) {
		ASSERT_TRUE(G_1.get_vertexes()[i]);
	}
	G_1.clear_graph();
	//конструктор 2, но с вызовом exception, т.к. передается отрицательный size
	ASSERT_ANY_THROW(Graph<int> G_2(-1, true));
}

TEST(Setters, Graph) {
	Graph<int> G;
	//кладем 5 в размер(bool добавила для рандомного присваивания имен вершинам)
	G.set_size(5, true);
	//проверяем, создались ли вершины
	for (int i = 0; i < G.get_size(); i++) {
		ASSERT_TRUE(G.get_vertexes()[i]);
	}
	//проверяем, правильно ли добавилось
	ASSERT_EQ(5, G.get_size());

	//проверяем вставку готового массива вершин
	vector<Vertex<int>*> vertexes;
	for (int i = 0; i < 5; i++) {
		vertexes.push_back( new Vertex<int>);
		vertexes[i]->name = i;
		vertexes[i]->color = -1;
	}
	G.set_vertexes(vertexes);

	//проверяем, все ли хорошо добавилось
	for (int i = 0; i < 5; i++) {
		ASSERT_EQ(i, G.get_vertexes()[i]->name);
		ASSERT_EQ(-1, G.get_vertexes()[i]->color);
	}
	G.clear_graph();
}

TEST(Color, Graph) {
	//создаем рандомный граф для раскраски
	Graph<int> G(5, true);
	G.initialization_vertexes(true);
	G.color_graph();
	//проверям, все ли вершины покрасились
	for (int i = 0; i < G.get_size(); i++) {
		ASSERT_LT(-1, G.get_vertexes()[i]->color);
	}
}



