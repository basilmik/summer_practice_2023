#include "stdio.h"
#include <stdlib.h>
#include <time.h>
#include <stack>
#include "../libwinbgi/src/graphics.h"

#define VMAX 7

// A -> C -> B

class graph
{
	int mrand(int a, int b)
	{
		return (b == 0 && a == 0) ? rand() : ((rand() % (b - a + 1)) + a);
	}


public:
	int** A;
	int N;
	int start;
	int end;
	int mid;

	std::stack<int> cur_path;
	bool mid_flag;

	graph()
	{
		mid_flag = false;
		start = 0;
		mid = 0;
		end = 0;

		srand(time(0));

		N = mrand(5, VMAX);

		A = new int* [N];
		for (int i = 0; i < N; ++i)
			A[i] = new int[N];

		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
			{
				int v = mrand(0, 1);
				if (i == j) v = 0;

				A[i][j] = v;
				A[j][i] = v;
				
			}
		

		start = mrand(0, N - 1);
		mid = mrand(0, N - 1);
		while (start == mid)
		{
			mid = mrand(0, N - 1);
		}
		end = mrand(0, N - 1);
		while (end == mid || mid == start)
		{
			end = mrand(0, N - 1);
		}
	}



	int search(int cur)
	{
		cur_path.push(cur);

		if (cur == end)
		{
			if (mid_flag)
				return 1;
			
			mid_flag = false;
			return 0;
		}
		else
		{
			if (cur == mid)
				mid_flag = true;
			

			for (int j = 0; j < N; j++)
			{
				if (A[cur][j])
				{
					A[cur][j] = 0;
					A[j][cur] = 0;
					
					if (search(j) == 1)
					{
						A[cur][j] = 1;
						A[j][cur] = 1;
						return 1;
					}
					A[cur][j] = 1;
					A[j][cur] = 1;
					cur_path.pop();
				}
			}
			return 0;
		}
	}

	void print(int x, int y)
	{
		int v = 0;
		if (!cur_path.empty())
		{
			v = cur_path.top();
			cur_path.pop();
			print(x, y + 20);
			
			char m[4];
			sprintf_s(m, "%d", v);
			outtextxy(x, y, m);
			cur_path.push(v);
		}
	}



	void call_search()
	{
		search(start);

		
		mdraw();
		
	}

	void mdraw()
	{
		initwindow(750, 750);
		clearviewport();
		setcolor(LIGHTRED);

		char m[16];
		sprintf_s(m, "%d->%d->%d", end, mid, start);

		outtextxy(100, 20, m);

		float** map = new float* [N];
		for (int i = 0; i < N; i++)
			map[i] = new float[N];

		float del = 360.0 / (float)N;
		float alpha = 0;

		for (int i = 0; i < N; ++i)
		{
			map[i][0] = 200 * cos(alpha * 0.017) + 350;
			map[i][1] = 200 * sin(alpha * 0.017) + 350;

			alpha += del;
		}
		setlinestyle(0, 0, 3);

		setcolor(LIGHTGRAY);
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				if (A[i][j])
					line(map[i][0], map[i][1], map[j][0], map[j][1]);

		setcolor(LIGHTGRAY);
		for (int i = 0; i < N; i++)
		{
			char m[4];
			sprintf_s(m, "%d", i);
			outtextxy(map[i][0], map[i][1], m);
		}
		getch();
		setlinestyle(DASHED_LINE, 0, 3);
		setcolor(LIGHTBLUE);

		if (mid_flag)
		{
			
			int v = 0;
			int prev = cur_path.top();
			int cx = 100;
			int cy = 40;

			while (!cur_path.empty())
			{
				v = cur_path.top();
				cur_path.pop();
				char m[4];
				sprintf_s(m, "%d", v);
				outtextxy(cx, cy, m);
				cx += 20;
				

				line(map[v][0], map[v][1], map[prev][0], map[prev][1]);
				prev = v;
			}
		}
		else
		{
			setcolor(LIGHTRED);
			outtextxy(100, 40, (char*)"no path was found");
		}
		getch();
		closegraph();


	}


};



int main()
{
	graph* g = new graph;

	g->call_search();

	return 0;
}