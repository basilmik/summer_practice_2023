// create two stacks, change info beetween them w\o any arrays and etc
#define _CRT_SECURE_NO_WARNINGS

#include "stdio.h"
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include "../libwinbgi/src/graphics.h"


#define TIME_DELTA 500
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

	void draw_stack_elem(int stack_idx, int elem_id, int val, int clr)
	{
		char str[128] = { 0 };
		sprintf(str, "%d", val);
		setcolor(clr);

		outtextxy(stack_idx * 80, 800 - elem_id * 40, str);
	}



	/*void draw_full_stack(int _stack_idx)
	{
		elem* tmp = top;
		int i = 0;
		while (tmp != nullptr)
		{
			draw_stack_elem(_stack_idx, i, tmp->val);
			tmp = tmp->prev;
			i++;
		}

	}*/



	elem* top;
	int col;
	int last_placed;


	stack()
	{
		top = nullptr;
		col = 0;
		last_placed = 0;
	}

	void push(int v)
	{
		elem* n_el = new elem(v);
		n_el->prev = top;
		top = n_el;
		draw_stack_elem(col, last_placed, v, 15);
		last_placed++;
		//printf("pushed: %d\n", v);
	}

	void cover(int _col, int _lp)
	{
		setcolor(RED);
		rectangle(_col * 80, 800 - (_lp - 1) * 40, _col * 80 + 80, 800 - (_lp - 1) * 40 + 20);
		setfillstyle(LINE_FILL, BLACK);
		floodfill(_col * 80 + 5, 800 - (_lp - 1) * 40 + 5, RED);
		setcolor(BLACK);
		rectangle(_col * 80, 800 - (_lp - 1) * 40, _col * 80 + 80, 800 - (_lp - 1) * 40 + 20);
	}

	int pop()
	{
		elem* n_top = top->prev;
		
		int val = top->val;
		top = n_top;

		cover(col, last_placed);

		last_placed--;

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
			Sleep(TIME_DELTA);
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
		printf("\n");
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

		is_valid1 = 1;
		st1->cover(st1->col + 1, 1);
		st1->draw_stack_elem(st1->col + 1, 0, val1, 12);
	}

	Sleep(TIME_DELTA);
	if (!st2->is_empty())
	{
		val2 = st2->pop();
		//Sleep(1500);
		is_valid2 = 1;
		st2->cover(st2->col - 1, 1);
		st2->draw_stack_elem(st2->col - 1, 0, val2, 12); // next to
	}

	Sleep(TIME_DELTA);
	exchange(st1, st2);
	Sleep(TIME_DELTA);

	if (is_valid2)
	{
		st2->cover(st2->col - 1, 1);
		st2->draw_stack_elem(st2->col - 1, 0, val2, 12); // next to
	}
	if (is_valid1)
	{
		st1->cover(st1->col + 1, 1);
		st1->draw_stack_elem(st1->col + 1, 0, val1, 12);
	}

	if (is_valid2)
	{
		Sleep(TIME_DELTA);
		st1->push(val2);	
	}
	
	if (is_valid1)
	{
		Sleep(TIME_DELTA);
		st2->push(val1);		
	}
}

void draw_exchange(stack* st1, stack* st2)
{
	exchange(st1, st2);
	st1->cover(st1->col + 1, 1);
	st2->cover(st2->col - 1, 1);

}

int main()
{
	stack* st1 = new stack;
	st1->col = 2;
	stack* st2 = new stack;
	st2->col = 5;

	int s1 = 0;
	int s2 = 0;

	printf("size1 ");
	scanf("%d", &s1);

	printf("size2 ");
	scanf("%d", &s2);


	initwindow(1000, 1000);

	st1->random_fill(s1);	
	st1->print();

	st2->random_fill(s2);
	st2->print();

	draw_exchange(st1, st2);

	st1->print();
	
	st2->print();

	getch();
	closegraph();
	return 0;
}

// EOF main.cpp