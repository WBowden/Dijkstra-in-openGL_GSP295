#pragma once
#include <Windows.h>

void clearMarks(vector<Node> & graph)
{
	for (int i = 0; i < (signed)graph.size(); ++i) {
		graph[i].mark = 0;
	}
}

void ccolor(int color)
{
	glColor3ubv((GLubyte*)&color);
}

class Game
{

public:

	DijkstraData * area = 0;

	COORD min, max;
	vector<Node> nodes;
	bool running;
	char userInput;
	Node *cursor, *end;
	float distanceTraveled;
	static const char NEIGHBOR_LABEL_START = 'a';
	bool drawSearch;
	int animationIndex = 0;


	Game()
	{
		cout << "How many Nodes?: " << endl;
		int Input;
		cin >> Input;

		min.X = 2;
		max.X = 70;
		min.Y = 2;
		max.Y = 20;
		srand(time(NULL));

		nodes = generateRandomGraph(min, max, Input, 20, true);
		running = true;
		cursor = &nodes[0];
	}

	vector<Node*> listOfNodesInSearchOrder;

	void update(int a_value)
	{
		clearMarks(nodes);
		listOfNodesInSearchOrder.clear();

	}

	void draw()
	{
		if (drawSearch)
		{
			ccolor(STD_COLOR_BLACK);
			for (int i = 0; i < (signed)listOfNodesInSearchOrder.size(); ++i)
			{

				listOfNodesInSearchOrder[i]->draw();
			}
	
		}
		else
		{
			ccolor(STD_COLOR_BLACK);
			for (int i = 0; i < (int)nodes.size(); ++i)
			{
				nodes[i].draw();
			}
		}
		if (end != NULL)
		{

			Node * clickNode = end, *prev;
			ccolor(STD_COLOR_BLUE);
			while (clickNode)
			{
				prev = clickNode;
				clickNode = area->previous[clickNode];
				if (clickNode)
				{
					Edge * edge = clickNode->edgeTo(prev);
					edge->draw();
				}

			}
			end->draw();
		}

	}

};
