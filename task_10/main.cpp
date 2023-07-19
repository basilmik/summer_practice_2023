#define _CRT_SECURE_NO_WARNINGS
#include "../libwinbgi/src/graphics.h"
#include "stdio.h"

class classPoint{
public:
	int x;
	int y;
	int count;

	classPoint(){
		x = 0;
		y = 0;
		count = 0;
	}

	void set(int _x, int _y){
		x = _x;	y = _y;
	}

	void draw(int clr){
		setcolor(clr);
		circle(x, y, 4);
	}
};

class classBunch {
public:
	int size;
	classPoint* coord;
	int maxIdx;
	int maxCount;
	bool flag;

	classBunch(){
	}

	classBunch(int s){
		maxIdx = 0;
		maxCount = 0;
		flag = false;
		if (s > 0)
		{
			size = s;
			coord = new classPoint[size];
		}
	}

	classPoint* operator[](int idx)	{
		return &coord[idx];
	}


	void compare(classBunch* ptr)	{
		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)		
				if (coord[i].x == (*ptr)[j]->x && coord[i].y == (*ptr)[j]->y)			
					(*ptr)[j]->count++;	
	}

	void calcMaxIdx(){
		for (int i = 0; i < size; i++)
			if (coord[i].count > maxCount)
			{
				maxCount = coord[i].count;
				maxIdx = i;
			}		
	}

	void draw(int _c){
		for (int i = 0; i < size; i++)
			coord[i].draw(_c);		
	}


	int check(int x, int y)	{
		for (int i = 0; i < size; i++)
			if (coord[i].x == x && coord[i].y == y)
				return 1;			
		return 0;
	}

};



int main(){
	FILE* fin = fopen("config.txt", "r");
	if (fin == NULL)
		return -1;

	int M = 0, N = 0;	

	fscanf(fin, "%d", &M);
	fscanf(fin, "%d", &N);

	classBunch* bunch = new classBunch[M];
	for (int i = 0; i < M; i++)
		bunch[i] = *(new classBunch(N));
	

	int x = 0, y = 0;
	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++)	{
			fscanf(fin, "%d %d", &x, &y);
			classBunch tmp = bunch[i];
			tmp[j]->set(x, y);
		}
	
	fclose(fin);


	for (int i = 1; i < M; i++)
		bunch[i].compare(&bunch[0]);	
	bunch[0].calcMaxIdx();


	x = bunch[0][bunch[0].maxIdx]->x;
	y = bunch[0][bunch[0].maxIdx]->y;

	for (int i = 0; i < M; i++)
		if (bunch[i].check(x, y))
			bunch[i].flag = true;
	

	printf("resultat: x = %d, y = %d, count = %d", x, y, bunch[0].maxCount + 1);
	initwindow(900, 900);

	for (int i = 0; i < M; i++)	{
		if (bunch[i].flag)
			bunch[i].draw((i+ 6) % 15);
		else
			bunch[i].draw(15);
	}

	bunch[0].coord[bunch[0].maxIdx].draw(MAGENTA);

	getch();
	closegraph();
	return 0;
}