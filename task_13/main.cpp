#include "stdio.h"

class task
{
public:
	int type; // 1 -- 3
	task* prev;
	task* next;

	task()
	{

	}

	task(int _type)
	{
		type = _type;
	}
};

class stack
{
public:
	task* top_task;

	stack()
	{
		top_task = nullptr;
		for (int i = 0; i < 10; i++)
		{
			push(i % 3);
		}
	}

	int pop()
	{
		task* t = top_task->next;
		int type = top_task->type;
		top_task = t;

		return type;
	}

	void push(int _type)
	{
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

		for (int i = 0; i < 10; i++)
		{
			add(i % 3);
		}
	}


	int get()
	{
		task* t = top_task->next;
		int type = top_task->type;
		top_task = t;
		top_task->prev = nullptr;
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


};


class sys
{
public:
	bool p1;
	bool p2;
	bool p3;

	stack* st;
	queue* qu;

	sys()
	{
		p1 = p2 = p3 = false;
		st = new stack;
		qu = new queue;
	}

	void print_all()
	{
		st->print();
		qu->print();
	}

};

int main()
{
	sys* msys = new sys;
	msys->print_all();
	return 0;
}