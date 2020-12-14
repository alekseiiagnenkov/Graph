#include "pch.h"
#include "../graph/Graph.h"

TEST(Constructor, Graph) {
	//����������� 1
	Graph<int> G;
	//���������, ����������� �� ��������� ��������
	ASSERT_EQ(0, G.get_size());
	//�.�. size=0, �� � ������ ������ ���
	ASSERT_EQ(0, G.get_vertexes().size());
	//����������� 2
	Graph<int> G_1(5, true);
	//��� �� ������
	ASSERT_EQ(5, G_1.get_size());
	//���������, ��������� �� �������
	for (int i = 0; i < G_1.get_size(); i++) {
		ASSERT_TRUE(G_1.get_vertexes()[i]);
	}
	G_1.clear_graph();
	//����������� 2, �� � ������� exception, �.�. ���������� ������������� size
	ASSERT_ANY_THROW(Graph<int> G_2(-1, true));
}

TEST(Setters, Graph) {
	Graph<int> G;
	//������ 5 � ������(bool �������� ��� ���������� ������������ ���� ��������)
	G.set_size(5, true);
	//���������, ��������� �� �������
	for (int i = 0; i < G.get_size(); i++) {
		ASSERT_TRUE(G.get_vertexes()[i]);
	}
	//���������, ��������� �� ����������
	ASSERT_EQ(5, G.get_size());

	//��������� ������� �������� ������� ������
	vector<Vertex<int>*> vertexes;
	for (int i = 0; i < 5; i++) {
		vertexes.push_back( new Vertex<int>);
		vertexes[i]->name = i;
		vertexes[i]->color = -1;
	}
	G.set_vertexes(vertexes);

	//���������, ��� �� ������ ����������
	for (int i = 0; i < 5; i++) {
		ASSERT_EQ(i, G.get_vertexes()[i]->name);
		ASSERT_EQ(-1, G.get_vertexes()[i]->color);
	}
	G.clear_graph();
}

TEST(Color, Graph) {
	//������� ��������� ���� ��� ���������
	Graph<int> G(5, true);
	G.initialization_vertexes(true);
	G.color_graph();
	//��������, ��� �� ������� �����������
	for (int i = 0; i < G.get_size(); i++) {
		ASSERT_LT(-1, G.get_vertexes()[i]->color);
	}
}



