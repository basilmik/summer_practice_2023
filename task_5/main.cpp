#include "stdio.h"
#include <algorithm>
#include <cstddef>
#include <iterator>
#include <memory>

//void mcopy(int* _arr)
//{
//
//}
//
//
//
//void merge_sort(int* arr, int size)
//{
//	if (size > 1)
//	{
//		int left_size = size / 2;
//		int right_size = size - left_size;
//
//		merge_sort(&arr[0], left_size);
//		merge_sort(&arr[left_size], right_size);
//
//		int lidx = 0, ridx = left_size, idx = 0;
//		int* tmp_arr = new int[size];
//
//		while (lidx < left_size || ridx < size)
//		{
//			if (arr[lidx] < arr[ridx])
//			{
//				tmp_arr[idx++] = std::move(arr[lidx]);
//				lidx++;
//			}
//			else
//			{
//				tmp_arr[idx++] = arr[ridx];
//				ridx++;
//			}
//
//			if (lidx == left_size)
//			{
//				// copy ridx, size, idx
//				break;
//			}
//			if (ridx == size)
//			{
//				// copy
//				break;
//			}
//
//			// copy tmp_arr->arr
//
//
//
//
//		}
//
//	}
//
//
//}


void mmerge(int arr[], int left, int mid, int right)
{
	int it1 = 0, it2 = 0;
	int size = right - left;
	int* res = new int[size];
	for (int i = 0; i < size; i++)
		res[i] = 0;
	
	printf("res: \n");
	for (int i = 0; i < size; i++)
	{
		printf("%d ", res[i]);
	}

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

	printf("res: \n");
	for (int i = 0; i < size; i++)
	{
		printf("%d ", res[i]);
	}

	while (left + it1 < mid)
	{
		res[it1 + it2] = arr[left + it1];
		it1++;
	}

	printf("res: \n");
	for (int i = 0; i < size; i++)
	{
		printf("%d ", res[i]);
	}

	while (mid + it2 < right)
	{
		res[it1 + it2] = arr[mid + it2];
		it2++;
	}

	printf("res: \n");
	for (int i = 0; i < size; i++)
	{
		printf("%d ", res[i]);
	}

	for (int i = 0; i < it1 + it2; i++)
	{
		arr[left + i] = res[i];
	}
	printf("arr: \n");
	for (int i = 0; i < 10; i++)
	{
		printf("%d ", arr[i]);
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
	printf("\n");
	for (int i = 0; i < 10; i++)
	{
		printf("%d ", arr[i]);
	}
}


int main()
{
	int arr[] = { 4, 2, 0, 5, 1, 6, 3, 7, 8, 9 };

	for (int i = 0; i < 10; i++)
	{
		printf("%d ", arr[i]);
	}

	printf("\n");

	msort(arr, 0, 10);
	printf("\n");
	for (int i = 0; i < 10; i++)
	{
		printf("%d ", arr[i]);
	}

	return 0;
}