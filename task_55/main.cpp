#define _CRT_SECURE_NO_WARNINGS

#include "stdio.h"
#include "malloc.h"

int main()
{
	int m = 0; // winter length
	int n = 0; // houses number

	scanf("%d", &n);
	scanf("%d", &m);
	getchar();

	int* counter = (int*)calloc(n, sizeof(int));
	bool* stats = (bool*)calloc(n, sizeof(bool));
	char c;
	int li = 0; int ri = 0;

	for (int i = 0; i < m; i++)
	{

		scanf("%c", &c);
		scanf("%d", &li);
		scanf("%d", &ri);
		getchar();

		// change stats
		for (int j = li -1; j < ri; j++)
		{
			switch (c)
			{
			case '+':
				if (stats[j] != true) 
					stats[j] = true;
				break;
			case '-':
				if (stats[j] != false) 
					stats[j] = false;
				break;
			}
		}

		for (int i = 0; i < n; i++)
		{
			if (stats[i] == false) counter[i]++;
		}

	}

	for (int i = 0; i < n; i++)
	{
		printf("%d ", counter[i]);
	}

	return 0;
}
