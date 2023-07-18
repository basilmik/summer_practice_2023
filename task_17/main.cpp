#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "../libwinbgi/src/graphics.h"
#include <stdlib.h>
#include <time.h>


#define MAX 123456789
#define X0 300
#define Y0 300
#define RAD 300
#define MAX_VERTX_NUM 7

int get_random_in_range(int low, int up)
{
    if (up == 0 && low == 0)
        return rand();
    else
        return ((rand() % (up - low + 1)) + low);
}

class graph
{
public:
    float* map;
    int N;
    int target_vertex;

    int init_map()
    {
        map = (float*)calloc(N * 2, sizeof(float));
        if (map == NULL)
            return -1;

        float deg_delta = 360.0 / (float)N;
        float alpha = 0;

        for (int i = 0; i < N; i++)
        {
            map[i * 2 + 0] = X0 + RAD * cos((double)alpha * 0.017);
            map[i * 2 + 1] = Y0 + RAD * sin((double)alpha * 0.017);

            alpha += deg_delta;
        }

        return 0;

    }

    void drav_points()
    {
        for (int i = 0; i < N; i++)
        {
            char message[4];
            if (i == target_vertex )
                setcolor(YELLOW);
            else
            setcolor(WHITE);
            sprintf_s(message, "%d", i);
            outtextxy(map[i * 2 + 0], map[i * 2 + 1], message);
        }
    }

    void draw_connect(int arr[][MAX_VERTX_NUM])
    {
        setcolor(LIGHTCYAN);

        for (int i = 0; i < N; i++)
        {       for (int j = 0; j < N; j++)
            {
                int val = arr[i][j];
                //printf("[%d][%d] %d ", i, j, val);
                if (val == 1)
                {
                    line(map[i * 2 + 0], map[i * 2 + 1],
                        map[j * 2 + 0], map[j * 2 + 1]);
                }
            }
        //printf("\n");
        }
        //Sleep(5);
    }

    void draw_m_graph(int a[][MAX_VERTX_NUM])
    {
        drav_points();
        Sleep(5);
    }

}; 


int main()
{
    srand(time(0));
    initwindow(1000, 700);
    clearviewport();
    int N;
    N = get_random_in_range(4, MAX_VERTX_NUM);

    int A[MAX_VERTX_NUM][MAX_VERTX_NUM] = {};

    // Ввод матрицы смежности
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
        {
            int v = get_random_in_range(0, 1);            
            if (i == j)
                v = 0;
            A[i][j] = v;
            A[j][i] = v;
        }

    graph* g = new graph;
    g->N = N;
    g->init_map();

    // so there are no not connected vertexs
    for (int i = 0; i < N; i++)
    {
        int sum = 0;
        for (int j = 0; j < N; j++)
        {
            sum += A[i][j];
        }
        if (sum == 0)
        {
            int rand_j = get_random_in_range(0, N - 1);
            A[i][rand_j] = 1;
            A[rand_j][i] = 1;
        }
    }

    g->draw_connect(A);

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
        {
            int v = A[i][j];
            if (v == 0)
                v = MAX;
            A[i][j] = v;
            A[j][i] = v;
        }



    // Алгоритм Флойда-Уоршелла
    for (int k = 0; k < N; ++k)
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                A[i][j] = min(A[i][j], A[i][k] + A[k][j]);
    

    int V_min = 0;

    // Ищем вершину с минимальной суммой
    int TS = MAX;
    long int sum = 0;
    for (int i = 0; i < N; i++)
    {
        sum = 0;
       
        for (int j = 0; j < N; j++)
            sum += A[i][j];
        if (sum < TS)
        {
            TS = sum;
            V_min = i;
        }
    }

    g->target_vertex = V_min;
    
    g->draw_m_graph(A);

    printf("%d", V_min);

    getch();
    closegraph();
}