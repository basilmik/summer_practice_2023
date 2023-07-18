#include "stdio.h"
#include "math.h"

class number
{
public:
	// sign 01.234
	bool sign;
	int w[5];

	number()
	{
		sign = false;
		w[0] = 0;
		w[1] = 0;
		w[2] = 0;
		w[3] = 0;
		w[4] = 0;
	};


	number(bool s, int w0, int w1, int w2, int w3, int w4)
	{
		sign = s;
		w[0] = w0;
		w[1] = w1;
		w[2] = w2;
		w[3] = w3;
		w[4] = w4;
	}

	bool is_zero()
	{
		for (int i = 0; i < 4; i++)
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
		for (int i = 0; i < 5; i++)
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

		for (int i = 4; i >= 0; i--)
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
		
		for (int i = 4; i >= 0; i--)
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
		if (sign)
			printf("-");
		else
			printf("+");
		for (int i = 0; i < 2; i++) printf("%d", w[i]);
		printf(".");
		for (int i = 2; i < 5; i++) printf("%d", w[i]);
		printf("\n");
	}

	number dev_by_2()
	{
		number res;

		for (int i = 0; i < 5; i++)
		{
			res.w[i] += w[i] / 2;
			if (w[i] % 2 && i != 4)
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
		while (w[4] == 0)
		{
			for (int i = 4; i > 0; i--)
			{
				
				w[i] = w[i - 1];
			}
			move_idx++;
		}
	}

	void move_left()
	{
		if (is_zero())
			return;
		while (move_idx)
		{
			for (int i = 0; i < 3; i++)
			{
				
				w[i] = w[i + 1];
			}
			move_idx--;
		}
	}



	number square()
	{
		number res;
		number* tmp = cpy(*this);
		tmp->move_right();
		for (int j = 4; j >= 0; j--)
		{		
			for (int i = 4; i >= 0; i--)
			{
				//printf("i: %d j: %d\n", i, j);
				int idx = j - (4 - i);
				//printf(" j - (4 - i)  %d - (4 - %d) =  %d\n", j, i, idx);
				
				int s = tmp->w[i] * tmp->w[j];
				int proc = s % 10;
				int dev = s / 10;
				//printf("s: %d  proc: %d  dev: %d\n", s, proc, dev);
				
				if (idx >= 0)
				{
					res.w[j - (4 - i)] += proc;
					if (s / 10 && (j - (4 - i)) != 0)
					{
						res.w[j - (4 - i) - 1] += dev;
					}
				}
				//res.print();
			}
		}
		tmp->move_left();
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
	number t(false, 0, 0, 2, 2, 5);
	number r =t.square();
	r.print();

	number min(false, 0, 2, 0, 0, 0);
	number max(false, 0, 3, 0, 0, 0);
	number eps(false, 0, 0, 0, 0, 1);
	number calc_res;
	number target;

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
		printf("try: ");
		target.print();
		

		calc_res = target.calc();
		printf("calc_res: ");
		calc_res.print();
		printf("target: ");
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