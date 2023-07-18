#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "string.h"
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>


int prop[5] = { 0 };
bool is_h_good = false;
bool is_w_good = false;

void set_prop_zero()
{
	for (int i = 0; i < 5; i++)
		prop[i] = 0;
}


int get_category(int min, int max, int value)
{
	if (value < min)
		return 0;

	if (value > max)
		return 3;

	if (value < (max - min) / 2)
		return 1;
	else
		return 2;

}


int get_cat()
{
	if (is_h_good && is_w_good && prop[3] >= 3)
		return 0;
	if (prop[3] >= 2 && prop[2] >= 1)
		return 1;
	if (prop[0] == 0 && prop[2] >= 3)
		return 1;
	if (prop[3] >= 1 && prop[2] >= 1)
		return 2;
	if (prop[2] >= 3)
		return 2;
	return 3;
}


int main()
{
	const char* server = "tcp://127.0.0.1:3306";
	const char* username = "root";
	const char* password = "11323";

	sql::Driver* driver;
	sql::Connection* con;
	sql::Statement* stmt;

	try
	{
		driver = get_driver_instance();
		con = driver->connect(server, username, password);
		con->setSchema("draft_db");
	}
	catch (sql::SQLException e)
	{
		printf("Error message: %s", e.what());
		system("pause");
		exit(1);
	}

	stmt = con->createStatement();

	sql::ResultSet* res;
	res = stmt->executeQuery("SELECT * FROM players");

	printf(" )\th\tw\ts\tr\tp\tDRAFT\n");
	int counter = 1;

	while (res->next())
	{
		set_prop_zero();
		is_h_good = false;
		is_w_good = false;

		int h = res->getInt(1);
		prop[get_category(190, 220, h)] += 1;
		if (get_category(190, 220, h) == 3)
			is_h_good = true;

		int w = res->getInt(2);
		prop[get_category(200, 250, w)] += 1;
		if (get_category(200, 250, w) == 3)
			is_w_good = true;

		int s = res->getInt(3);
		prop[get_category(10, 20, s)] += 1;

		int r = res->getInt(4);
		prop[get_category(2, 6, r)] += 1;

		int p = res->getInt(5);
		prop[get_category(3, 7, p)] += 1;

		int cat = get_cat();

		printf("%d)\t%d\t%d\t%d\t%d\t%d\t%d\n", counter++, h, w, s, r, p, cat);
	}

	free(con);
	free(stmt);
}