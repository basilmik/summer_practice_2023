// create two stacks, change info beetween them w\o any arrays and etc
#define _CRT_SECURE_NO_WARNINGS

#include "stdio.h"
#include <stdlib.h>
#include <time.h>

int get_random_in_range(int low, int up)
{
	if (up == 0 && low == 0)
		return rand();
	else
	if (up > 0)
		return ((rand() % (up - low + 1)) + low);
	else
		return ((rand() % (low + 1)) + low);
}

class elem
{
public:

	int val;
	elem* prev;
	elem()
	{
		val = 0;
		prev = nullptr;
	}
	elem(int v) : val(v)
	{
		prev = nullptr;
	}

};

class stack
{
public:
	elem* top;
	stack()
	{
		top = nullptr;
	}

	void push(int v)
	{
		elem* n_el = new elem(v);
		n_el->prev = top;
		top = n_el;
	}

	int pop()
	{
		elem* n_top = top->prev;
		
		int val = top->val;
		top = n_top;
		return val;
	}

	int is_empty()
	{
		return (top == nullptr);
	}

	void random_fill(int size)
	{
		srand(time(0));	
		for (int i = 0; i < size; i++)
		{
			push(get_random_in_range(0,0));
		}
	}

	void print()
	{
		elem* tmp = top;
		while (tmp != nullptr)
		{
			printf("%d\n", tmp->val);
			tmp = tmp->prev;
		}
	}

};

void exchange(stack* st1, stack* st2)
{
	if (st1->is_empty() && st2->is_empty())
		return;
	int is_valid1 = 0;
	int is_valid2 = 0;

	int val1 = 0; int val2 = 0;

	if (!st1->is_empty())
	{
		val1 = st1->pop();
	}
	if (!st2->is_empty())
	{
		val2 = st2->pop();
	}

	exchange(st1, st2);

	if (is_valid1)
		st1->push(val2);

	if (is_valid2)
		st1->push(val1);
	return;

}

int main()
{
	stack* st1 = new stack;

	int s = 0;
	printf("size1^ ");
	scanf("%d", &s);
	st1->random_fill(s);
	st1->print();

	stack* st2 = new stack;

	printf("size2^ ");
	scanf("%d", &s);
	st2->random_fill(s);
	st2->print();

	exchange(st1, st2);
	st1->print();
	st2->print();

	return 0;
}

// EOF main.cpp