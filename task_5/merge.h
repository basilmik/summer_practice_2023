#pragma once
#include "stdio.h"

void mmerge(int arr[], int left, int mid, int right)
{
	int it1 = 0, it2 = 0;
	int size = right - left;
	int* res = new int[size];

	for (int i = 0; i < size; i++)
		res[i] = 0;


	while (left + it1 < mid && mid + it2 < right)
	{
		if (arr[left + it1] < arr[mid + it2])
		{
			res[it1 + it2] = arr[left + it1];
			it1++;
		}
		else
		{
			res[it1 + it2] = arr[mid + it2];
			it2++;
		}
	}


	while (left + it1 < mid)
	{
		res[it1 + it2] = arr[left + it1];
		it1++;
	}


	while (mid + it2 < right)
	{
		res[it1 + it2] = arr[mid + it2];
		it2++;
	}

	for (int i = 0; i < it1 + it2; i++)
	{
		arr[left + i] = res[i];
	}
}

void msort(int* arr, int left, int right)
{
	if (left + 1 >= right)
		return;

	int mid = (left + right) / 2;
	msort(arr, left, mid);
	msort(arr, mid, right);

	mmerge(arr, left, mid, right);
}
