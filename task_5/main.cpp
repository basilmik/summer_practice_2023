#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#include "string.h"

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

#include "../libwinbgi/src/graphics.h"


class marr_data
{
public:
	int* arr_all; int* arr1; int* arr2;

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

	void mmerge(int arr[], int left, int mid, int right)
	{
		int it1 = 0, it2 = 0;
		int size = right - left;
		int* res = new int[size];

		for (int i = 0; i < size; i++)
			res[i] = 0;


		while (left + it1 < mid && mid + it2 < right)
		{
			if (arr[left + it1] < arr[mid + it2])
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

	void msort(int* arr, int left, int right)
	{
		if (left + 1 >= right)
			return;

		int mid = (left + right) / 2;
		msort(arr, left, mid);
		msort(arr, mid, right);

		mmerge(arr, left, mid, right);
	}

	void sort_arr_all()
	{
		msort(arr_all, 0, size_all);
	}

	void print_arrs()
	{
		printf("arr1: ");
		for (int i = 0; i < size1; i++)
		{
			printf("%d ", arr1[i]);
		}
		printf("\narr2: ");
		for (int i = 0; i < size2; i++)
		{
			printf("%d ", arr2[i]);
		}
		printf("\narr_all: ");
		for (int i = 0; i < size_all; i++)
		{
			printf("%d ", arr_all[i]);
		}
		printf("\n");
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
		arr_all = new int[size_all];
		return 0;
	}

	int is_size_valid()
	{
		return (size1 > 0 && size2 > 0 && size_all > 0);
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

	for(int idx = 0; res->next(); idx++)
	{
		arrs->arr_all[idx] = res->getInt(1);

		if (idx  < arrs->size1)
			arrs->arr1[idx] = arrs->arr_all[idx];
		else
			arrs->arr2[idx - arrs->size1] = arrs->arr_all[idx];
	}

}


int main()
{
	initwindow(1000, 700);
	getch();
	closegraph();


	//marr_data * arrs = new marr_data;

	//read_arr_from_db(arrs);
	//arrs->print_arrs();

	//arrs->sort_arr_all();
	//arrs->print_arrs();



	return 0;
}