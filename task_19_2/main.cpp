#include "stdio.h"
#include <stack>
#include <stdlib.h>
#include <time.h>
#include "../libwinbgi/src/graphics.h"

#define MAX_VERTX 8
#define X0 320
#define Y0 320
#define RAD 100
#define X 0
#define Y 1

using namespace std;

class graph
{
	void setValueByIdx(int _i, int _j, int _val)
	{
		edge[_i][_j] = _val;
		edge[_j][_i] = _val;
	}

	void print(stack<int>* _ptr)
	{
		int v = 0;
		if (!_ptr->empty())
		{
			v = _ptr->top();
			_ptr->pop();
			print(_ptr);
			printf("%d ", v);
			_ptr->push(v);
		}
	}

	void drawStack(stack<int>* _ptr, int prev)
	{
		setcolor(BLUE);
		int v = 0;
		if (!_ptr->empty())
		{
			v = _ptr->top();
			_ptr->pop();
			drawStack(_ptr, v);
			line(map[v][X], map[v][Y], map[prev][X], map[prev][Y]);

			_ptr->push(v);
		}

	}

	void findPath(int _idx)
	{
		pathStack.push(_idx);

		if (_idx == pointB)
		{
			if (targetFlag)
				allPaths.push(pathStack);

			targetFlag = false;
		}
		else
		{
			if (_idx == pointC)
				targetFlag = true;

			for (int i = 0; i < N; i++)
			{
				if (edge[_idx][i])
				{
					setValueByIdx(_idx, i, 0);
					findPath(i);
					setValueByIdx(_idx, i, 1);
					pathStack.pop();
				}
			}

		}
	}



public:


	int** edge;
	graph()
	{
		targetFlag = false;
		createEdges();

		pointA = getRandom(0, N -1);
		pointB = pointA;
		while (pointB == pointA)
			pointB = getRandom(0, N - 1);
		
		pointC = pointA;
		while (pointC == pointA || pointC == pointB)
			pointC = getRandom(0, N -1);
		
	}

	int pointA;
	int pointB;
	int pointC;
	int N;

	stack<int> pathStack;
	stack<stack<int>> allPaths;
	bool targetFlag;

	int getRandom(int low, int up)
	{
		if (up == 0 && low == 0)
			return rand();
		else
			return ((rand() % (up - low + 1)) + low);
	}

	void printShortest()
	{
		int maxSize = INT_MAX;
		stack<int> tmpPtr;

		while (!allPaths.empty())
		{
			if (allPaths.top().size() < maxSize)
			{
				maxSize = allPaths.top().size();
				tmpPtr = (allPaths.top());
			}

			allPaths.pop();
		}
		getch();
		drawStack(&tmpPtr, pointA);
		printf("path: ");
		print(&tmpPtr);
		printf("\n");
	}
	void search()
	{
		findPath(pointA);
	}

	void createEdges()
	{
		srand(time(0));

		N = getRandom(5, MAX_VERTX);

		edge = new int* [N];
		for (int i = 0; i < N; ++i)
			edge[i] = new int[N];

		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				setValueByIdx(i, j, (i == j) ? 0 : getRandom(0, 1));
			}
		}
	}


	float** map;
	int createMap()
	{
		map = new float* [N];
		for (int i = 0; i < N; ++i)
			map[i] = new float[N];

		double deg_delta = 360.0 / (double)N;
		double alpha = 0;

		for (int i = 0; i < N; ++i)
		{
			map[i][0] = X0 + RAD * cos(alpha * 0.017);
			map[i][1] = Y0 + RAD * sin(alpha * 0.017);
			alpha += deg_delta;
		}

		return 0;
	}

	void dPoints()
	{
		for (int i = 0; i < N; i++)
		{
			char message[4];
			setcolor(WHITE);
			sprintf_s(message, "%d", i);
			outtextxy(map[i][0], map[i][1], message);
		}
	}

	void dEdges()
	{
		setcolor(RED);
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)	
				if (edge[i][j])			
					line(map[i][0], map[i][1], map[j][0], map[j][1]);
	}

	void draw()
	{
		createMap();
		dEdges();
		dPoints();

	}


};



int main()
{

	graph* g = new graph;
	printf("A: %d C: %d B: %d\n", g->pointA, g->pointC, g->pointB);

	g->search();
	initwindow(700, 700);
	clearviewport();

	g->draw();
	g->printShortest();
	getch();
	closegraph();
	return 0;
}