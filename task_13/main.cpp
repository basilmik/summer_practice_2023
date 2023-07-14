#define _CRT_SECURE_NO_WARNINGS

#include "stdio.h"
#include <stdlib.h>
#include <windows.h>

#include <time.h>
#include "../libwinbgi/src/graphics.h"

#define ALL_EMPTY 0
#define NOT_ALL_EMPTY 1
#define X0 20
#define Y0 30
#define RAD 20
#define TIME_DELAY 5000
#define PLANNING 1
#define WORKING 0


int get_x(int c)
{
	return c * 70 + X0;
}

int get_y(int r)
{
	return r * 70 + Y0;
}

void draw_box(int x, int y, int w, int h)
{
	setcolor(LIGHTGRAY);
	rectangle(x, y, x + w, y + h);


}


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

	void draw_line(int c, int r, int clr)
	{
		int x = get_x(c);
		int y = get_y(r);
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

	void draw(int c, int r, int _n)
	{
		draw(c, r);

		char num[5] = { 0 };
		sprintf(num, "%d", _n);
		setcolor(WHITE);
		outtextxy(get_x(c) + 25, get_y(r) + 25, num);
	}

	void draw(int c, int r)
	{
		
		int x = get_x(c);
		int y = get_y(r);
		draw_line(c, r, type + 1);

		setfillstyle(SOLID_FILL, type + 5);
		floodfill(x + 25, y + 25, type + 1);
		draw_line(c, r, type + 5);
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


	void draw()
	{
		int c = 0;
		int r = 0;
		draw_box(get_x(c) - 10, get_y(r) - 10, 900, 100);
		outtextxy(get_x(c) - 15, get_y(r) - 25, (char*)"stack");
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


	void draw()
	{
		int c = 0;
		int r = 2;
		draw_box(get_x(c) - 10, get_y(r) - 10, 900, 100);
		outtextxy(get_x(c) - 15, get_y(r) - 25, (char*)"queue");
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

	void draw_procs()
	{
		draw_box(get_x(0) - 10, get_y(8) - 10, 250, 80);
		outtextxy(get_x(0) - 15, get_y(8) - 25, (char*)"procs");


		for (int i = 0; i < 3; i++)
		{
			procs[i].type = i;
			if (p[i] >= 0)
				procs[i].draw(i, 8, p[i]); // busy
			else
				procs[i].draw_line(i, 8, i + 5);
		}
	}

	void draw_planner()
	{
		draw_box(get_x(10) - 10, get_y(8) - 10, 80, 80);

		outtextxy(get_x(10) - 15, get_y(8) - 25, (char*)"planner");


		if (t != -1)
		{
			task* t_task = new task;
			t_task->type = t;
			t_task->draw(10, 8);
		}

		if (t_st != -1)
		{
			task* t_task = new task;
			t_task->type = t_st;
			t_task->draw(11, 8);
		}
	}

	int plan()
	{
		if (st->is_empty() && qu->is_empty())
			return ALL_EMPTY;

		t = qu->get();
		draw_stats();
		if (p[t] >= 0)
		{
			st->push(t);
		}
		else
		{
			p[t] = t + 1;
		}
		t = -1;
		draw_stats();

		if (!st->is_empty())
		{
			t = st->pop();
			draw_stats();
			if (p[t] >= 0) // busy
			{
				st->push(t);
				t = -1;
			}
			else
			{
				st->pop();
				p[t] = t + 1;
			}
			draw_stats();
			t = -1;
			draw_stats();
		}
		for (int i = 0; i < 3; i++)
		{
			if (p[i] >= 0)
				p[i] --;
		}

		return NOT_ALL_EMPTY;
	}


public:
	int p[3];
	task procs[3];

	stack* st;
	queue* qu;

	int t;
	int t_st;
	int mode;

	sys()
	{
		p[0] = p[1] = p[2] = -1;
		st = new stack;
		qu = new queue;
		t = -1;
		t_st = -1;
		mode = PLANNING;
	}


	void draw_stats()
	{
		cleardevice();
		
		st->draw();
		qu->draw();

		draw_procs();
		draw_planner();
		getch();
	}


	void emulate()
	{
		do
		{
			qu->add(rand() % 3);
		} while (plan() != ALL_EMPTY);
	}
};

int main()
{
	sys* msys = new sys;

	int t = 0;
	srand(time(0));

	for (int i = 0; i < 8; i++)
	{
		msys->qu->add(rand() % 3);
	}

	initwindow(1000, 700);

	msys->draw_stats();
	msys->emulate();
	getch();
	closegraph();
	return 0;
}