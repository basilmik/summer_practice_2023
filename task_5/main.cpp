#include "stdio.h"
#include "merge.h"

#include "string.h"

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>






void read_arr_from_db(char* db_name, char* table_name)
{
	const char* server = "tcp://127.0.0.1:3306";
	const char* username = "root";
	const char* password = "11323";

	sql::Driver* driver;
	sql::Connection* con;
	sql::Statement* stmt;
	//sql::PreparedStatement* pstmt;


	try
	{
		driver = get_driver_instance();
		con = driver->connect(server, username, password);
	}
	catch (sql::SQLException e)
	{
		printf("Could not connect to server. Error message: %s", e.what());
		system("pause");
		exit(1);
	}
	try
	{
		con->setSchema(db_name);
	}
	catch (sql::SQLException e)
	{
		printf("Could not connect to database. Error message: %s", e.what());
		exit(1);
	}

	stmt = con->createStatement();


	//char st[256] = { 0 };

	//sprintf_s(st, "SELECT min(id) FROM %s WHERE val < 0", table_name);


	sql::ResultSet* res;

	try
	{
		res = stmt->executeQuery("SELECT min(id) FROM origin WHERE val < 0");
	}
	catch (sql::SQLException e)
	{
		printf("Error message: %s", e.what());
		exit(1);
	}
	res->next();
	int dev_idx = res->getInt(1);
	printf("id %d\n", dev_idx);



	try
	{
		res = stmt->executeQuery("SELECT COUNT(*) FROM origin");
	}
	catch (sql::SQLException e)
	{
		printf("Error message: %s", e.what());
		exit(1);
	}
	res->next();
	int all_size = res->getInt(1);
	printf("all_size %d\n", all_size);
	int size1 = dev_idx -1;
	int size2 = all_size - dev_idx;

	int* arr1 = new int[size1];
	int* arr2 = new int[size2];

	char st[256] = { 0 };
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
	int idx = 1;

	while (res->next())
	{
		printf("%d ", idx);
		int val = res->getInt(1);
		printf(" = %d\n", val);
		if (idx < dev_idx)
			arr1[idx - 1] = val;
		else
			arr2[idx - 1 - size1] = val;

		idx++;
	}

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

	delete con;

}


int main()
{
	int arr[] = { 4, 2, 0, 5, 1, 6, 3, 7, 8, 9 };
	//int* marr;

	read_arr_from_db( (char*)"practice_task_5", (char*)"origin");
	system("pause");


	for (int i = 0; i < 10; i++)
	{
		printf("%d ", arr[i]);
	}

	printf("\n");

	msort(arr, 0, 10);

	printf("\n");
	for (int i = 0; i < 10; i++)
	{
		printf("%d ", arr[i]);
	}



	return 0;
}