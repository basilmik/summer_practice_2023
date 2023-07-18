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
		move_idx = 0;
		sign = false;
		for (int i = 0; i < BUF_SIZE_MAX; i++)
			w[i] = 0;
	};


	number(bool s, int w0, int w1, int w2, int w3, int w4)
	{
		move_idx = 0;
		sign = s;
		for (int i = 0; i < BUF_SIZE_MAX; i++)
			w[i] = 0;
		w[0] = w0;
		w[1] = w1;
		w[2] = w2;
		w[3] = w3;
		w[4] = w4;
		print();
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
				res = true;
			else
			{
				res = false;
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
				res.w[i] += sum / 10;
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

		for (int i = 0; i < 2; i++) printf("%d", w[i]);
		printf(".");
		for (int i = 2; i < 5; i++) printf("%d", w[i]);

		//for (int i = 0; i < BUF_SIZE_MAX; i++)
		//	//printf("%d] %d\n", i, w[i]);
		//	printf("%d", w[i]);
		printf("\n");
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

	int move_idx;
	void move_right()
	{
		move_idx = 0;
		if (is_zero())
			return;

		//int tmp = 100 * w[2] + 10 * w[3] + w[4];
		//if (w[3] == 0 && w[4] == 0)
		//	tmp /= 100;
		//else
		//if (w[4] == 0)
		//	tmp /= 10;
		//

		//if (tmp >= 100)
		//	move_idx = 6;
		//else
		//	if (tmp >= 10)
		//		move_idx = 4;
		//	else
		//		if (tmp != 0)
		//			move_idx = 2;


		while (w[MAX_ASK] == 0)
		{
			for (int i = MAX_ASK; i > 0; i--)
			{
				
				w[i] = w[i - 1];
			}
			//move_idx++;
		}


	}

	void move_left(int idx)
	{
		if (is_zero())
			return;
		int v = idx;
		for (int i = 0; i < MAX_ASK; i++)
		{
			w[i] = w[i + 1];
		}
		w[MAX_ASK] = 0;
		/*while (v)
		{
			for (int i = 0; i < MAX_ASK; i++)
			{	
				w[i] = w[i + 1];
			}
			w[MAX_ASK] = 0;
			print();
			v--;
		}*/
	}

	void move_for_3()
	{
		for(int j = 0; j <3; j++)
		{
			for (int i = MAX_ASK; i > 0; i--)
			{
				w[i] = w[i - 1];
			}
		}
	}
	void move_for_1()
	{
		
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
		//tmp->move_right();
		tmp->print();
		bool flag_hit_2 = false;
		int delta = 0;
		for (int j = MAX_ASK; j >= 0; j--)
		{
			for (int i = MAX_ASK; i >= 0; i--)
			{
				//printf("i: %d j: %d\n", i, j);
				int idx = j - (MAX_ASK - i);
				/*if (j == 2 && i == 4 && flag_hit_2 == false)
				{
					flag_hit_2 = true;
					res.print();
					res.move_for_3();
					res.print();
					printf("MOVE\n");
				}
				if (idx < 2 && flag_hit_2)
				{
					idx += 3;
				}*/
				idx += delta;
				//printf(" j - (4 - i)  %d - (4 - %d) =  %d\n", j, i, idx);

				int s = tmp->w[i] * tmp->w[j];
				int proc = s % 10;
				int dev = s / 10;
				printf("s: %d  proc: %d  dev: %d\n", s, proc, dev);

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

				res.print();
			}
			printf("%d done\n", j);
			res.print();
			if (delta < 3)
			{
				delta++;
				printf("MOVE\n");

				res.move_for_1();
				res.print();
			}
		}
		//res.print();
		//res.move_left(tmp->move_idx);
		res.print();
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


float calc(float _t)
{
	return (_t * _t - 5.0);
}

int main()
{
	//number t(false, 0, 0, 2, 2, 5);
	//number r =t.square();
	//r.print();

	number min(false, 0, 2, 0, 0, 0);
	number max(false, 0, 3, 0, 0, 0);
	number eps(false, 0, 0, 0, 0, 1);
	number calc_res;
	number target;
	number five(false, 0, 5, 0, 0, 0);

	while (true)
	{
		target = (max - min);
		printf("max: ");
		max.print();
		printf("min: ");
		min.print();
		
		//target.print();
		target = target.dev_by_2();
		//target.print();
		target = target + min;
		printf("mid: ");
		target.print();
		
		//target.square();
		//printf("mid^2: ");
		//target.print();

		calc_res = target.square() - five;
		printf("mid^2 - 5: ");
		calc_res.print();
		target.print();

		if (calc_res > eps)
		{
			min = target;
			
		}
		else
		{
			max = target;
		}

	}

	/*float min = 2;
	float max = 3;
	float eps = 0.001;
	float calc_res = 1;
	float test = 1;

	do
	{
		test = (max - min) / 2.0;
		test += min;

		calc_res = calc(test);
		if (calc_res * 1000 > eps * 1000)
		{
			max = test;
		}
		else
		{
			min = test;
		}

	} while (abs((int)(calc_res*1000) - (int)(eps*1000)) > 0);

	printf("%f\n", test);*/

	return 0;

}