#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <vector>
#include <algorithm>

int main()
{
	FILE* fin = fopen("src.txt", "r");
	if (fin == NULL)
	{
		printf("no file src.txt found\n");
		return -1;
	}

	int nv, ne;

	fscanf(fin, "%d %d", &nv, &ne);

	const int inf = 1000;
	std::vector<std::vector<int>> d(nv, std::vector<int>(nv, inf));
	for (int i = 0; i < nv; i++)
	{
		d[i][i] = 0;
	}
	for (int i = 0; i < ne; i++)
	{
		int v1, v2;
		fscanf(fin, "%d %d", &v1, &v2);
		v1--; v2--;
		d[v1][v2] = 0;
		d[v2][v1] = std::min(d[v2][v1], 1);
	}
	fclose(fin);
	for (int k = 0; k < nv; k++)
	{
		for (int i = 0; i < nv; i++)
		{
			for (int j = 0; j < nv; j++)
			{
				d[i][j] = std::min(d[i][j], d[i][k] + d[k][j]);
			}
		}
	}
	int max = 0;
	for (int i = 0; i < nv; i++)
	{
		for (int j = 0; j < nv; j++)
		{
			max = std::max(max, d[i][j]);
		}
	}
	printf("%d", max);

	return 0;
}