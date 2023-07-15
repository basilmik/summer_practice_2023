#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#include <string>
#include <iostream>
#include "malloc.h"


int main()
{
	int n = 0; //  num of sales
	int k = 0; //  min time

	scanf("%d %d", &n, &k);

	int* line = (int*)calloc(n, sizeof(int));

	for (int i = 0; i < n; i++)
	{
		scanf("%d", &line[i]);
	}


	for (int i = 1; i < n; i++)
	{
		if (line[i] - line[i - 1] < k)
		{
			line[i] = line[i - 1] + k;
		}
	}	

	for (int i = 0; i < n; i++)
	{
		printf("%d ", line[i]);
	}
	printf("\n");

	return 0;
}