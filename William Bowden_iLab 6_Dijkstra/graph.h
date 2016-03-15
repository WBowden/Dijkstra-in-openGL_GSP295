#pragma once
#include <Windows.h>
#include "vec2.h"
#include <vector>
using namespace std;

class Node;

const int STD_COLOR_BLACK = 0x000000;
const int STD_COLOR_BLUE = 0xff00000;

struct Edge
{
	Node * from, *to;
	float cost;
	Edge(Node * start, Node * end);

	void draw();
};

class Node
{
public:
	vector<Edge> edges;
	char id;
	COORD position;
	int mark;

	bool AddNeighbor(Node * n)
	{
		for (int i = 0; i < (int)edges.size(); ++i)
		{
			if (edges[i].to == n)	{ return false; }
		}
		edges.push_back(Edge(this, n));
		return true;
	}
	int getNeighborCount() { return edges.size(); }

	Node * getNeighbor(int index){ return edges[index].to; }

	Node(char id, int x, int y) : id(id), mark(0)
	{
		position.X = x;
		position.Y = y;
	}

	void draw()
	{
		vec2 pos(position.X, position.Y);

		glBegin(GL_LINE_STRIP);
		for (int i = 0; i < CIRCLE_POINTS; ++i)
		{
			vec2 p = pos + circle[i];
			glVertex2f(p.x, p.y);
		}

		glEnd();

		for (int i = 0; i < (signed)edges.size(); ++i)
		{
			edges[i].draw();
		}

	}

	Edge * edgeTo(Node * n)
	{
		for (int i = 0; i < (signed)edges.size(); ++i)
		{
			if (edges[i].to == n)
			{
				return &edges[i];
			}
		}
		return 0;
	}

};

Edge::Edge(Node* start, Node* end) : from(start), to(end)
{
	float dx = (float)(start->position.X - end->position.X);
	float dy = (float)(start->position.Y - end->position.Y);
	cost = sqrt((float)(dx*dx + dy*dy));

}
void Edge::draw()
{
	vec2 start = vec2(from->position.X, from->position.Y);
	vec2 end = vec2(to->position.X, to->position.Y);
	glBegin(GL_LINES);
	glVertex2f(start.x, start.y);
	glVertex2f(end.x, end.y);
	glEnd();

}

Node * getNodeNamed(vector<Node> & nodes, char id)
{
	for (int i = 0; i < (int)nodes.size(); ++i)
	{
		if (nodes[i].id == id) { return &nodes[i]; }
	}
	return 0;
}

float distanceBetween(COORD position, Node* n)
{
	float dx = (float)(position.X - n->position.X);
	float dy = (float)(position.Y - n->position.Y);
	return sqrt(dx*dx + dy*dy);
}

vector<Node*> nodesWithin(COORD location, float maxDist, bool atLeast1Neighbor, vector<Node> & list)
{
	vector<Node*> out;
	float closest = -1;
	Node * closestNode = 0;
	for (int i = 0; i < (int)list.size(); ++i)
	{
		float dist = distanceBetween(location, &list[i]);
		if (dist == 0) { continue; }
		if (closest == -1 || dist < closest)
		{
			closest = dist;
			closestNode = &list[i];
		}
		if (dist < maxDist)
		{
			out.push_back(&list[i]);
		}
	}
	if (atLeast1Neighbor && out.size() == 0 && closestNode)
	{
		out.push_back(closestNode);
	}
	return out;
}

vector<Node> generateRandomGraph(COORD min, COORD max, int count, float maxNdist, bool atLeast1Neighbor)
{
	vector<Node> list;
	int dx = max.X - min.X;
	int dy = max.Y - min.Y;

	for (int i = 0; i < count; ++i)
	{
		list.push_back(Node((i % 26) + 'a', min.X + rand() % dx, min.Y + rand() % dy));
	}
	for (int i = 0; i < (signed)list.size(); ++i)
	{
		vector<Node*> neighbors = nodesWithin(list[i].position, maxNdist, atLeast1Neighbor, list);
		for (int a = 0; a < (int)neighbors.size(); ++a)
		{
			Node * n = neighbors[a];
			if (!n)
			{
				cout << "Y U no give good node?!" << endl;
			}
			list[i].AddNeighbor(n);
		}
		if (neighbors.size() == 1)
		{
			neighbors[0]->AddNeighbor(&list[i]);
		}
	}
	return list;
}

