#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include <windows.h>
#include "../libwinbgi/src/graphics.h"

#define SIDE 20
#define X0 10
#define Y0 20

void draw_square_outline(int c, int r, int clr)
{
    setcolor(clr);
    setlinestyle(0, 0, 3);
    rectangle(c * SIDE + X0, r * SIDE + Y0, (c+1)*SIDE + X0, (r+1)*SIDE + Y0);
}

void draw_grid(int c, int r)
{
    for (int i = 0; i < c; i++)
        for (int j = 0; j < r; j++)
        {draw_square_outline(i, j, LIGHTBLUE);
        }
}

void draw_path(int _c, int _r)
{
    int max_x = _c * SIDE + X0;
    int x1 = X0;
    int y1 = _r*SIDE + Y0;
    int x2 = _c*SIDE + X0;
    int y2 = Y0;

    float a = ((float)(y2 - y1) / (float)(x2 - x1) );
    float b = y2 - a* x2;

    for (float x = X0; x < max_x; x++)
    {
        float y = a * x + b;
        int clr = getpixel(x, y);
        if (clr == RED || clr == LIGHTBLUE)
            continue;

        if (clr != RED &&  clr != LIGHTBLUE)
        {
            setfillstyle(SOLID_FILL, RED);
            floodfill(x, y, LIGHTBLUE);
           
        }
        putpixel(x , y , 12);
       
    }

    setcolor(LIGHTGREEN);
    line(x1, y1, x2, y2);
}


 int NOD(int a, int b)
{
     while (a > 0 && b > 0)
         (a > b) ? a %= b : b %= a;
     
    return a + b;
}

int main()
{
    int x, y;
    scanf("%d %d", &x, &y);

    int count = x + y - NOD(x, y);

    initwindow(1000, 900);

    draw_grid(x, y);
    draw_path(x, y);
    printf("total count: %d\n", count);
    
    getch();
    closegraph();
	return 0;
}
