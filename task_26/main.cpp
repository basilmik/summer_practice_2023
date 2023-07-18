#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include <list>

class word_class
{
public:
	std::list<char> word;
	bool has_number;

	void add(char c)
	{
		if (c >= '0' && c <= '9')
			has_number = true;
		word.push_back(c);
	}


	int print(FILE* fout)
	{
		if (word.size() == 0)
			return 0;
		else
		if (has_number)
		{
			while (word.size() != 0)
			{
				fprintf(fout, "%c", word.front());
				//printf("%c", word.front());
				word.pop_front();
			}
			has_number = false;
			return 1;
		}
		else
		{
			while (word.size() != 0)
			{
				fprintf(fout, "%c", word.back());
				//printf("%c", word.back());
				word.pop_back();
			}
			return 2;
		}		
	}
};


bool is_devider(char c)
{
	switch (c)
	{
	case ' ':
	case '.':
	case ',':
	case ';':
	case '-':
	case '+':
	case ':':
	case '!':
	case '?':
	case '\"':
	case '\n':
		return true;
	default:
		return false;
	}	
}


int main()
{
	FILE* fin = fopen("source.txt", "r");
	FILE* fout = fopen("output.txt", "w");
	
	if (fin == nullptr)
	{
		return -1;
	}
	char c;
	word_class word;

	int word_count = 0;
	int num_count = 0;
	int letter_count = 0;
	int symbol_count = 0;
	int space_count = 0;
	int punct_mark_count = 0;

	while ((c = fgetc(fin)) != EOF)
	{
		//printf("%c", c);
		symbol_count++;
		if (is_devider(c))
		{
			if (c == ' ')
				space_count++;
			else
				punct_mark_count++;

			int type = word.print(fout);
			if (type == 2)
				word_count++;
			if (type == 1)
				num_count++;

			//printf("%c", c);
			fprintf(fout, "%c", c);
		}
		else
		{
			word.add(c);
			if (c < '0' || c > '9')
				letter_count++;

		}

	}

	fclose(fin);
	fclose(fout);

	printf("\nCOUNT:\nwords\t\t%d\n\n", word_count);
	printf("numbers\t\t%d\n\n", num_count);
	printf("letters\t\t%d\n\n", letter_count);
	printf("symbols\t\t%d\n\n", symbol_count);
	printf("spaces\t\t%d\n\n", space_count);
	printf("punctuation\nmarks\t\t%d\n\n", punct_mark_count);

	return 0;
}