#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#include <string>
#include <iostream>

int start = -1;
char* s;
int len;

int get_next_start()
{
	do
	{
		start++;
	} while (s[start] != '1' && start != len);
	return start;
}

int main()
{
	int n = 0; //  num of der to travel by

	scanf("%d", &n);
	getchar();
	
	std::string str;
	std::cin >> str;

	len = str.length();
	s = (char*)str.c_str();
	int pos = 0;
	while (start != len)
	{
		pos = get_next_start();
		int v_count = 0;
		int stop_count = 0;
		pos++;
		if (pos > len)
			break;
		while (pos != len && v_count != n)
		{
			if (s[pos] == '1')
				v_count++;
			stop_count++;
			pos++;

		}

		printf("%d ", (v_count > 0) ? stop_count*2 : 0);
	}

	return 0;
}