#include <iostream>
#include "glut.h"
#include <ctime>
#include <Windows.h>
#include "vec2.h"
#include "drawCircle.h"
#include "graph.h"
#include "dijkstra.h"
#include "game.h"

Game game;

using namespace std;

void display()
{
	glClearColor(1, 1, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3ub(0, 0, 0);
	glBegin(GL_LINES);
	glEnd();
	game.draw();
	glFlush();
	glutSwapBuffers();
}

Node * nodeAt(vec2 location)
{
	for (int i = 0; i < (signed)game.nodes.size(); ++i)
	{
		COORD c = game.nodes[i].position;
		vec2 nodeLoc(c.X, c.Y);
		if (location.distance(nodeLoc) < 1)
		{
			return &game.nodes[i];
		}
	}
	return 0;
}

void mouse(int button, int state, int x, int y)
{
	vec2 click( x / 10.0f, (480 - y) / (10) );
	game.end = nodeAt(click);

	if (game.area)
	{
		delete game.area;
	}
	game.area = Dijkstra(game.nodes, game.cursor);

}

time_t now = clock(), then, passed;
void gameUpdate(int value)
{
	then = now;
	now = clock();
	passed = now - then;
	game.update((int)passed);
	glutTimerFunc(value, gameUpdate, value);
	glutPostRedisplay();
}

void reshape(int a_width, int a_height)
{
	glLoadIdentity();
	gluOrtho2D(-1, 64, -1, 48);
	glutPostRedisplay();
}

int main(int argc, char * argv[])
{
	glutInit(&argc, argv);
	glutInitWindowSize(640, 480);
	glViewport(0, 0, (int)640, (int)480);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutCreateWindow("data structures");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	const int TARGETFPS = 40, TARGET_DELAY = 1000 / TARGETFPS;
	glutTimerFunc(0, gameUpdate, TARGET_DELAY);
	glutMainLoop();
	return 0;
}