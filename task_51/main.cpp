#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"

class node
{
public:

	int val;
	node* left;
	node* right;
	node* parent;

	node()
	{
		left = nullptr;
		right = nullptr;
		parent = nullptr;
		val = -1;
	}

	node(int v)
	{
		left = nullptr;
		right = nullptr;
		parent = nullptr;
		val = v;
	}

	node(int v, node* par)
	{
		left = nullptr;
		right = nullptr;
		parent = par;
		val = v;
	}
	void add_left(node* _n)
	{
		//printf("add left %d to %d\n", _n->val, val);
		left = _n;
	}
	void add_right(node* _n)
	{
		//printf("add right %d to %d\n", _n->val, val);
		right = _n;
	}

	void set_val(int v)
	{
		val = v;
	}

	void printCLR()
	{
		printf("%d ", val);

		if (left != nullptr)
		{
			
			left->printCLR();
		}
		if (right != nullptr)
		{
			
			right->printCLR();
		}
	}
	void printLRC()
	{
		if (left != nullptr)
		{
			left->printLRC();
		}
		if (right != nullptr)
		{
			right->printLRC();
		}
		printf("%d\n", val);
	}


};


int main()
{
	node* root = new node();
	
	node* ptr = root;

	int input = 105;
	scanf("%d", &input);

	ptr->set_val(input);

	int linput = input;
	while (true)
	{
		if (scanf("%d", &input) == 0)
			break;
		
		if (linput > input)
		{
			node* add = new node(input, ptr);
			ptr->add_left(add);
			ptr = add;
		}
		else
		{
			int read = -1;
			int max_read = -1;
			node* max_read_ptr = nullptr;
			node* tmp = ptr;
			
			while (read < input && tmp != nullptr)
			{
				read = tmp->val;
				if (read >= input)
				{
					tmp = tmp->left;
					break;
				}

				if (read > max_read)
				{
					max_read = read;
					max_read_ptr = tmp;
				}
				tmp = tmp->parent;
			}

			tmp = max_read_ptr;
			if (tmp == nullptr)
				tmp = root;
			node* add = new node(input, tmp);
			tmp->add_right(add);
			ptr = add;
		}

		linput = input;
	}

	root->printLRC();

	return 0;
}