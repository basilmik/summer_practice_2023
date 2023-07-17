#include "stdio.h"
#include <stack>
#define MAX_VERTX 7

// A -> C -> B

class graph
{
public:
	int A[6][6] = { 0 };

	graph()
	{
		mid_flag = false;
		start = 0;
		mid = 0;
		end = 0;
		A[0][0] = 0;
		A[0][1] = 1;
		A[0][2] = 1;
		A[0][3] = 0;
		A[0][4] = 0;
		A[0][5] = 0;

		A[1][0] = 1;
		A[1][1] = 0;
		A[1][2] = 1;
		A[1][3] = 1;
		A[1][4] = 1;
		A[1][5] = 0;


		A[2][0] = 1;
		A[2][1] = 1;
		A[2][2] = 0;
		A[2][3] = 0;
		A[2][4] = 1;
		A[2][5] = 1;


		A[3][0] = 0;
		A[3][1] = 1;
		A[3][2] = 0;
		A[3][3] = 0;
		A[3][4] = 1;
		A[3][5] = 0;


		A[4][0] = 0;
		A[4][1] = 1;
		A[4][2] = 1;
		A[4][3] = 1;
		A[4][4] = 0;
		A[4][5] = 1;

		A[5][0] = 0;
		A[5][1] = 0;
		A[5][2] = 1;
		A[5][3] = 0;
		A[5][4] = 1;
		A[5][5] = 0;

	}

	int start;
	int end;
	int mid;

	std::stack<int> cur_path;
	bool mid_flag;

	int search(int cur)
	{
		cur_path.push(cur);

		if (cur == end)
		{
			if (mid_flag)
			{
				print();
				printf("\n");
				//return 0;
			}
			mid_flag = false;
			return 0;
		}
		else
		{
			if (cur == mid)
			{
				mid_flag = true;
			}

			for (int j = 0; j < 6; j++)
			{
				if (A[cur][j])
				{
					A[cur][j] = 0;
					A[j][cur] = 0;
					
					if (search(j) == 1)
						return 1;

					A[cur][j] = 1;
					A[j][cur] = 1;
					cur_path.pop();
				}
			}
			return 0;
		}
	}

	void print()
	{
		int v = 0;
		if (!cur_path.empty())
		{
			v = cur_path.top();
			cur_path.pop();
			print();
			printf("%d ", v);
			cur_path.push(v);
		}
	}



	void call_search()
	{
		search(start);
		if (mid_flag)
		{
			print();
			printf("\n");
		}
	}

};



int main()
{
	
	graph* g = new graph;
	g->start = 0;
	g->mid = 3;
	g->end = 4;
	g->call_search();

	return 0;
}