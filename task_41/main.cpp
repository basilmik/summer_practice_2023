#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#include "malloc.h"

int comp(const int* i, const int* j)
{
	return *i - *j;
}

int main()
{
	int N;
	scanf("%d", &N);

	int epsilon;
	scanf("%d", &epsilon);

	int* cor = (int*)calloc(N, sizeof(int));

	for (int i = 0; i < N; i++)
	{
		scanf("%d", &cor[i]);
	}


	qsort(cor, N, sizeof(int), 
		(int(*) (const void*, const void*)) comp);
	
	int count = 0;
	int start_x = cor[0];;
	int len = 0;

	for (int i = 1; i < N; i++)
	{
		int delta = (cor[i] - cor[i - 1]);

		if (delta > epsilon)
		{
			if (len > 0)
			{
				printf("length: %d\n", len);
				count++;
			}
			start_x = cor[i];
			len = 0;		
		}
		else
			len += delta;
		
	}

	if (len > 0)
	{
		printf("length: %d\n", len);
		count++;
	}

	printf("count: %d\n", count);

	return 0;
}