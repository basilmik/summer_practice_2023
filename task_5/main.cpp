#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "string.h"
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include "../libwinbgi/src/graphics.h"

#define X0 30
#define Y0 30
#define MAX_WIN_SIZE 1000
#define MAX_RL_NUM 10

typedef struct mdata_t
{
	int clr;
	int val;

} clr_int;

class marr_data
{
private:
	int is_size_valid()
	{
		return (size1 > 0 && size2 > 0 && size_all > 0);
	}

	void new_msort(clr_int* arr, int left, int right)
	{
		if (left + 1 >= right)
			return;

		int mid = (left + right) / 2;
		new_msort(arr, left, mid);
		new_msort(arr, mid, right);

		new_mmerge(arr, left, mid, right);
	}

	void new_mmerge(clr_int arr[], int left, int mid, int right)
	{
		int it1 = 0, it2 = 0;
		int size = right - left;
		clr_int* res = new clr_int[size];

		for (int i = 0; i < size; i++)
			res[i].val = 0;


		while (left + it1 < mid && mid + it2 < right)
		{
			if (arr[left + it1].val < arr[mid + it2].val)
			{
				res[it1 + it2] = arr[left + it1];
				it1++;
			}
			else
			{
				res[it1 + it2] = arr[mid + it2];
				it2++;
			}
		}


		while (left + it1 < mid)
		{
			res[it1 + it2] = arr[left + it1];
			it1++;
		}


		while (mid + it2 < right)
		{
			res[it1 + it2] = arr[mid + it2];
			it2++;
		}

		for (int i = 0; i < it1 + it2; i++)
		{
			arr[left + i] = res[i];
		}
	}

public:
	clr_int* arr_all; int* arr1; int* arr2;

	int size1;
	int size2;
	int size_all;

	marr_data()
	{
		size1 = -1;
		size2 = -1;
		size_all = -1;
		arr1 = nullptr;
		arr2 = nullptr;
		arr_all = nullptr;
	}

	void sort_arr_all()
	{
		new_msort(arr_all, 0, size_all);
	}

	void set_size1(int _s)
	{
		size1 = _s;
	}
	void set_size2(int _s)
	{
		size2 = _s;
	}
	void set_size_all(int _s)
	{
		size_all = _s;
	}

	int create_by_size()
	{
		if (!is_size_valid())
			return -1;

		arr1 = new int[size1];
		arr2 = new int[size2];
		arr_all = new clr_int[size_all];

		return 0;
	}


	void draw_vagon(int row, int column, int color, int val)
	{
		int ax, ay, bx, by, cx, cy, dx, dy;
		ax = X0 + column * 80;
		ay = Y0 + row * 80;
		bx = ax;
		by = ay + 40;
		dx = ax + 40;
		dy = ay;
		cx = dx;
		cy = by;

		setcolor(color);

		line(ax, ay, bx, by);
		line(cx, cy, bx, by);
		line(cx, cy, dx, dy);
		setcolor(color+1);

		char st[256];
		sprintf(st, "%d", val);
		outtextxy(ax + 2, ay + 15, st);
	}

	void connect_vagons(int row1, int col1, int row2, int col2, int color)
	{
		int x1 = X0 + col1 * 80 + 40;
		int y1 = Y0 + row1 * 80 + 20;

		int x2 = X0 + col2 * 80;
		int y2 = Y0 + row2 * 80 + 20;

		setcolor(color);
		line(x1, y1, x1 + 20, y1);
		line(x2 - 20, y2, x2, y2);

	}

	void draw_array(int* arr, int size, int main_clr, int con_clr, int* start_row, int* start_col)
	{
		int counter = 0;
		int col = *start_col;
		int row = *start_row;
		int prev_col = 0; 
		int prev_row = 0;
		
		for (int i = 0; i < size; i++)
		{
			draw_vagon(row, col, main_clr, arr[i]);
			prev_col = col;
			prev_row = row;

			col++;
			if (col == MAX_RL_NUM)
			{
				col = 0;
				row++;
			}

			if (i != size - 1)
			connect_vagons(prev_row, prev_col, row, col, con_clr);

		}

		*start_row= row + 1;	
	}

	void draw_array(clr_int* arr, int size, int main_clr, int con_clr, int* start_row, int* start_col)
	{
		int counter = 0;
		int col = *start_col;
		int row = *start_row;
		int prev_col = 0;
		int prev_row = 0;

		for (int i = 0; i < size; i++)
		{
			draw_vagon(row, col, arr[i].clr, arr[i].val);
			prev_col = col;
			prev_row = row;

			col++;
			if (col == MAX_RL_NUM)
			{
				col = 0;
				row++;
			}

			if (i != size - 1)
				connect_vagons(prev_row, prev_col, row, col, con_clr);

		}

		*start_row = row + 1;
	}

	void draw_arrs()
	{
		int col = 0;
		int row = 0;
		draw_array(arr1, size1, 5, 12, &row, &col);
		draw_array(arr2, size2, 8, 12, &row, &col);
		draw_array(arr_all, size_all, 0, 12, &row, &col);
	}
};



void read_arr_from_db(marr_data* arrs)
{
	const char* server = "tcp://127.0.0.1:3306";
	const char* username = "root";
	const char* password = "11323";

	sql::Driver* driver;
	sql::Connection* con;
	sql::Statement* stmt;
	sql::ResultSet* res;
	sql::ResultSet* res_dev_id;
	sql::ResultSet* res_size_full;


	try
	{
		driver = get_driver_instance();
		con = driver->connect(server, username, password);
		con->setSchema("practice_task_5");
	}
	catch (sql::SQLException e)
	{
		printf("Error message: %s", e.what());
		system("pause");
		exit(1);
	}


	stmt = con->createStatement();


	try
	{
		res_dev_id = stmt->executeQuery("SELECT min(id) FROM origin WHERE val < 0");
		res_size_full = stmt->executeQuery("SELECT COUNT(*) FROM origin");
	}
	catch (sql::SQLException e)
	{
		printf("Error message: %s", e.what());
		exit(1);
	}

	res_dev_id->next();
	int dev_idx = res_dev_id->getInt(1);
	
	res_size_full->next();
	int size_full = res_size_full->getInt(1);


	char st[128] = { 0 };
	sprintf_s(st, "SELECT val FROM origin WHERE id!=%d", dev_idx);

	try
	{
		res = stmt->executeQuery(st);
	}
	catch (sql::SQLException e)
	{
		printf("Error message: %s", e.what());
		exit(1);
	}

	delete con;
	delete stmt;


	arrs->set_size_all(size_full - 1);
	arrs->set_size1(dev_idx - 1);
	arrs->set_size2(arrs->size_all - dev_idx + 1);

	if (arrs->create_by_size() < 0)
	{
		printf("error creating arrays, invalid size\n");
		exit(-1);
	}

	for (int idx = 0; res->next(); idx++)
	{
		arrs->arr_all[idx].val = res->getInt(1);

		if (idx < arrs->size1)
		{
			arrs->arr1[idx] = arrs->arr_all[idx].val;
			arrs->arr_all[idx].clr = 5;
		}
		else
		{
			arrs->arr2[idx - arrs->size1] = arrs->arr_all[idx].val;
			arrs->arr_all[idx].clr = 8;
		}
	}
}


void write_result(marr_data* arrs)
{
	const char* server = "tcp://127.0.0.1:3306";
	const char* username = "root";
	const char* password = "11323";

	sql::Driver* driver;
	sql::Connection* con;
	sql::Statement* stmt;
	sql::ResultSet* res;

	try
	{
		driver = get_driver_instance();
		con = driver->connect(server, username, password);
		con->setSchema("practice_task_5");	
	}
	catch (sql::SQLException e)
	{
		printf("Error message: %s", e.what());
		system("pause");
		exit(1);
	}

	stmt = con->createStatement();
	stmt->execute("INSERT INTO result(val) VALUES (-555)");

	for (int i = 0; i < arrs->size_all; i++)
	{
		char st[256];
		sprintf(st, "INSERT INTO result(val) VALUES (%d)", arrs->arr_all[i].val);
		
		stmt->execute(st);
	}

	delete con;
	delete stmt;
}


int main()
{
	marr_data * arrs = new marr_data;
	read_arr_from_db(arrs);
	arrs->sort_arr_all();

	initwindow(1000, 700);
	arrs->draw_arrs();
	getch();
	closegraph();

	write_result(arrs);
	return 0;
}