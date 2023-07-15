#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include <iostream>
#include <stack>
#include <queue>
#include <string>

int get_val(char _c)
{
	switch (_c)
	{
	case '(': return 1;
	case ')': return -1;
	case '[': return 2;
	case ']': return -2;
	case '<': return 3;
	case '>': return -3;
	case '{': return 4;
	case '}': return -4;
	default: return 0;
	}

}

int check_correct(int* str, int beg, int end)
{
	std::stack<int> stack;

	for (int i = beg -1; i < end; i++)
	{
		if (stack.empty())
		{
			stack.push(str[i]);
		}
		else
		{
			if (stack.top() != -str[i])
			{
				stack.push(str[i]);
			}
			else
			{
				stack.pop();
			}
		}

	}

	return (stack.empty());
}



int main()
{
	int len = 0;
	scanf("%d", &len);

	int* str = new int[len];

	std::string cpp_str;
	std::cin >> cpp_str;
	char* cstr = (char*) cpp_str.c_str();

	for (int i = 0; i < len; i++)
	{	
		str[i] = get_val(cstr[i]);		
	}

	int com_n = 0;
	scanf("%d", &com_n);
	int com_t = 0;
	char c;
	int idx = 0;
	int beg = 0;
	int end = 0;

	std::queue<std::string> output;

	for (int i = 0; i < com_n; i++)
	{
		scanf("%d", &com_t);
		switch (com_t)
		{
		case 1:

			scanf("%d %c", &idx, &c);

			str[idx-1] = get_val(c);
			break;
		case 2:

			scanf("%d %d", &beg, &end);
			if (check_correct(str, beg, end))
				output.push("Yes");
			else
				output.push("No");
			break;
		default:
			return -1;


		}

	}

	while (!output.empty())
	{
		std::cout << output.front() << std::endl;
		output.pop();
	}

	return 0;
}