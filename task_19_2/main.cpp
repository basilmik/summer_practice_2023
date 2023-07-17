#include "stdio.h"
#include <stack>

#define MAX_VERTX 7

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

			for (int i = 0; i < 6; i++)
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

		print(&tmpPtr);
		printf("\n");
	}

public:
	int edge[6][6] = { 0 };

	graph()
	{
		targetFlag = false;
		pointA = 0;
		pointC = 0;
		pointB = 0;
		edge[0][0] = 0;
		edge[0][1] = 1;
		edge[0][2] = 1;
		edge[0][3] = 0;
		edge[0][4] = 0;
		edge[0][5] = 0;

		edge[1][0] = 1;
		edge[1][1] = 0;
		edge[1][2] = 1;
		edge[1][3] = 1;
		edge[1][4] = 1;
		edge[1][5] = 0;


		edge[2][0] = 1;
		edge[2][1] = 1;
		edge[2][2] = 0;
		edge[2][3] = 0;
		edge[2][4] = 1;
		edge[2][5] = 1;


		edge[3][0] = 0;
		edge[3][1] = 1;
		edge[3][2] = 0;
		edge[3][3] = 0;
		edge[3][4] = 1;
		edge[3][5] = 0;


		edge[4][0] = 0;
		edge[4][1] = 1;
		edge[4][2] = 1;
		edge[4][3] = 1;
		edge[4][4] = 0;
		edge[4][5] = 1;

		edge[5][0] = 0;
		edge[5][1] = 0;
		edge[5][2] = 1;
		edge[5][3] = 0;
		edge[5][4] = 1;
		edge[5][5] = 0;

	}

	int pointA;
	int pointB;
	int pointC;

	stack<int> pathStack;
	stack<stack<int>> allPaths;
	bool targetFlag;



	void search()
	{
		findPath(pointA);
		printShortest();	
	}

};



int main()
{

	graph* g = new graph;
	g->pointA = 0;
	g->pointC = 3;
	g->pointB = 4;
	g->search();

	return 0;
}