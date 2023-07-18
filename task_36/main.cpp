#include "stdio.h"
#include "math.h"

#define BUF_SIZE_MAX 5
#define MAX_ASK BUF_SIZE_MAX - 1

class number
{
public:
	// sign 01.234
	bool sign;
	int w[BUF_SIZE_MAX];

	number()
	{
		sign = false;
		for (int i = 0; i < BUF_SIZE_MAX; i++)
			w[i] = 0;
	};


	number(bool s, int w0, int w1, int w2, int w3, int w4)
	{
		sign = s;
		for (int i = 0; i < BUF_SIZE_MAX; i++)
			w[i] = 0;
		w[0] = w0;
		w[1] = w1;
		w[2] = w2;
		w[3] = w3;
		w[4] = w4;
		//print();
	}

	bool is_zero()
	{
		for (int i = 0; i < BUF_SIZE_MAX; i++)
		{
			if (w[i] != 0)
				return false;
		}
		return true;
	}



	// this > that
	bool operator > (const number& ptr) const
	{
		// this is -, that is +
		if (this->sign == true && ptr.sign == false)
		{
			return false;
		}
		// this is +, that is -
		if (this->sign == false && ptr.sign == true)
		{
			return true;
		}

		bool res = false;
		for (int i = 0; i < BUF_SIZE_MAX; i++)
		{
			if (this->w[i] >= ptr.w[i])
			{
				res = true;
				if (ptr.w[i]!=0)
				break;
			}
			else
			{
				res = false;
				if (ptr.w[i] != 0)
				break;
			}
		}

		if (this->sign == false)
			return res;
		else
			return !res;

	}

	number* cpy(const number& ptr)
	{
		return new number(ptr.sign, ptr.w[0], ptr.w[1], ptr.w[2], ptr.w[3], ptr.w[4]);
	}

	number sub(number* max, number* min)
	{
		number res;

		number* tmp_max = cpy(*max);
		number* tmp_min = cpy(*min);

		for (int i = MAX_ASK; i >= 0; i--)
		{
			// can substract
			if (tmp_max->w[i] >= tmp_min->w[i])
			{
				res.w[i] = tmp_max->w[i] - tmp_min->w[i];
			}
			else
			{

				// find next nonzero
				for (int j = i - 1; j >= 0; j--)
				{
					if (w[j] != 0)
					{
						tmp_max->w[j]--;

						// set 9 between j and i
						for (int k = j + 1; k < i; k++)
							tmp_max->w[k] = 9;
						tmp_max->w[i] += 10;

						res.w[i] = tmp_max->w[i] - tmp_min->w[i];
						break;
					}

				}
			}
		}


		return res;
	}

	number operator + (number& ptr)
	{
		number res;
		
		for (int i = MAX_ASK; i >= 0; i--)
		{
			int sum = w[i] + ptr.w[i] + res.w[i];
			res.w[i] = sum % 10 ;
			if (i != 0)
			{
				res.w[i - 1] += sum / 10;
			}
		}

		return res;
	}

	// only for two positive numbers
	number operator - (number& ptr) 
	{
		number res;

		if (*this > ptr)
		{
			res = sub(this, &ptr);
		}
		else
		{
			res = sub(&ptr, this);
			res.sign = true;
		}
		return res;
	}

	void print()
	{
		if (!sign) printf("+");
		else
			printf("-");
		for (int i = 0; i < 2; i++) printf("%d", w[i]);
		printf(".");
		for (int i = 2; i < 5; i++) printf("%d", w[i]);

	}

	number dev_by_2()
	{
		number res;

		for (int i = 0; i < BUF_SIZE_MAX; i++)
		{
			res.w[i] += w[i] / 2;
			if (w[i] % 2 && i != MAX_ASK)
			{	
				res.w[i + 1] += 5;
			}
		}
		return res;
	}


	void move_for_1()
	{
		if (w[MAX_ASK] >= 5)
			w[MAX_ASK - 1] ++;
		for (int i = MAX_ASK; i > 0; i--)
		{
			w[i] = w[i - 1];
		}
		w[0] = 0;
	}

	number square()
	{
		number res;
		number* tmp = cpy(*this);
		
		bool flag_hit_2 = false;
		int delta = 0;
		for (int j = MAX_ASK; j >= 0; j--)
		{
			for (int i = MAX_ASK; i >= 0; i--)
			{
				
				int idx = j - (MAX_ASK - i);
				
				idx += delta;
				
				int s = tmp->w[i] * tmp->w[j];
				int proc = s % 10;
				int dev = s / 10;
				
				if (idx >= 0)
				{
					res.w[idx] += proc;
					int v = res.w[idx];
					if (v >= 10)
					{
						res.w[idx] = v % 10;
						res.w[idx - 1] += v / 10;
					}
					if (s / 10 && (idx) != 0)
					{
						res.w[idx - 1] += dev;

					}
				}

				
			}
			
			if (delta < 3)
			{
				delta++;
				
				res.move_for_1();
				
			}
		}
		
		res.sign = false;
		return res;

	}

	number calc()
	{
		number res;
		number five(false, 0, 5, 0, 0, 0);

		res = square();
		res.print();
		res = res - five;

		return res;
	}


};


int main()
{
	
	number min(false, 0, 2, 0, 0, 0);
	number max(false, 0, 3, 0, 0, 0);
	number zero(false, 0, 0, 0, 0, 0);
	number calc_res;
	number target;
	number five(false, 0, 5, 0, 0, 0);

	bool flag = false;
	printf("     :  max    --  min\n");

	while (true)
	{		
		printf("serch: ");
		max.print();
		printf(" -- ");
		min.print(); 
		printf("\n");

		target = (max - min);

		target = target.dev_by_2();
		target = target + min;
	
		calc_res = target.square() - five;

		if (zero > calc_res)
			min = target;				
		else
			max = target;
		
		if (flag == true)
			break;
		if (calc_res.is_zero())
			flag = true;
	}

	printf("\nANSWER is between: ");
	min.print();
	printf(" and ");
	max.print();
	printf("\n");
	return 0;
}