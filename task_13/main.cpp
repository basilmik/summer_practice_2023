#define _CRT_SECURE_NO_WARNINGS

#include "stdio.h"
#include <stdlib.h>
#include <windows.h>

#include "../libwinbgi/src/graphics.h"

#define ALL_EMPTY 0
#define NOT_ALL_EMPTY 1
#define X0 20
#define Y0 20
#define RAD 20
class task
{
public:
	int type; // 0 -- 2
	task* prev;
	task* next;

	task()
	{

	}

	task(int _type)
	{
		type = _type;
	}

	void draw_line(int x, int y, int clr)
	{
		setcolor(clr);
		
		switch (type)
		{
		case 0:

			circle(x + RAD, y + RAD, RAD + 5);
			break;
		case 1:
			rectangle(x, y, x + RAD * 2, y + RAD * 2);
			break;
		case 2:
			rectangle(x, y+ 5, x + RAD * 2 + 10, y + RAD * 2 - 10);
			break;
		}
	}

	void draw(int c, int r)
	{
		printf("c %d r  %d\n", c, r);
		int x = c * 70 + X0 ;
		int y = r * 70 + Y0 ;
		draw_line(x,y, type + 1);

		setfillstyle(SOLID_FILL, type + 5);
		floodfill(x + 25, y + 25, type + 1);
		draw_line(x, y, type + 5);
	}
};

class stack
{
public:
	task* top_task;

	bool is_empty()
	{
		return (top_task == nullptr);
	}

	stack()
	{
		top_task = nullptr;
		
	}

	int pop()
	{
		if (top_task == nullptr)
			return -1;

		task* t = top_task->next;
		int type = top_task->type;
		top_task = t;

		return type;
	}

	void push(int _type)
	{
		if (_type < 0 || _type > 2)
			return;
		task* t = new task(_type);
		t->next = top_task;
		top_task = t;
	}

	void print()
	{
		printf("st\n");
		task* tmp = top_task;
		while (tmp != nullptr)
		{
			printf("%d ", tmp->type);
			tmp = tmp->next;
		}
		printf("\n");
	}

	void draw()
	{
		int c = 0;
		int r = 0;

		task* tmp = top_task;
		while (tmp != nullptr)
		{
			tmp->draw(c, r);
			c++;
			if (c == 10)
			{
				c = 0;
				r++;
			}
			tmp = tmp->next;
		}
	}

};

class queue
{
public:
	task* top_task;
	task* last_task;
	int size;

	queue()
	{
		top_task = nullptr;
		last_task = nullptr;
		size = 0;
	}


	int get()
	{
		if (size == 0)
			return -1;

		task* t = top_task->next;
		int type = top_task->type;
		
		top_task->prev = nullptr;
		top_task = t;
		size--;
		return type;
	}

	void add(int _type)
	{		
		task* t = new task(_type);
		t->prev = last_task;		
		if (size == 0)
		{
			top_task = t;			
		}
		else
		{		
			last_task->next = t;
		}
		last_task = t;
		size++;
	}

	void print()
	{
		printf("qu\n");
		task* tmp = top_task;
		while (tmp != nullptr)
		{
			printf("%d ", tmp->type);
			tmp = tmp->next;
		}
		printf("\n");

	}

	void draw()
	{
		int c = 0;
		int r = 0;

		task* tmp = top_task;
		while (tmp != nullptr)
		{
			tmp->draw(c, r);
			c++;
			if (c == 10)
			{
				c = 0;
				r++;
			}
			tmp = tmp->next;
		}
	}

	bool is_empty()
	{
		return (size == 0);
	}
};


class sys
{
public:
	bool p[3];

	stack* st;
	queue* qu;

	int t;
	int t_st;

	sys()
	{
		p[0] = p[1] = p[2] = false;
		st = new stack;
		qu = new queue;
	}

	void print_all()
	{
		st->print();
		qu->print();
	}

	int plan_stack()
	{
		int t_st = st->pop();
		if (p[t_st] != true)
		{
			p[t_st] = true;
			return t_st;
		}
		else
		{
			st->push(t_st);
			return -1;
		}
	}

	int plan() 
	{
		if (st->is_empty() && qu->is_empty())
			return ALL_EMPTY;


		t = qu->get();
		t_st = -1;

		if (t == -1) // qu is empty
		{
			t_st = plan_stack();
		}
		else // qu is not empty
		{
			if (p[t] == true) // this p is busy
			{
				// to stack
				st->push(t);
				t = -1;
			}
			else
			{
				// to p[t]
				p[t] = true;
				t_st = plan_stack();
			}
		
		}
		// clear all than not now placed

		for (int i = 0; i < 3; i++)
		{
			if (i != t && i != t_st)
				p[i] = false;
		}

		return NOT_ALL_EMPTY;
	}

	void print_stats()
	{
		//system("CLS");
		printf("-----------------------\n");
		st->print();
		qu->print();
		printf("%d %d %d\n", p[0], p[1], p[2]);
		printf("-----------------------\n");
	}

	void draw_stats()
	{
		qu->draw();

	}


	void emulate()
	{
		do
		{
			
			print_stats();
			Sleep(2500);
		} while (plan() != ALL_EMPTY);
	}


};

int main()
{
	sys* msys = new sys;

	int t = 0;
	while (t != -1)
	{
		scanf("%d", &t);
		if (t != -1)
			msys->qu->add(t);
	}
initwindow(1000, 700);
msys->qu->draw();
getch();

	msys->print_all();
	
	msys->emulate();
	getch();
	closegraph();
	return 0;
}