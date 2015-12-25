#include <iostream>
#include <stdio.h>
#include <cmath>
#define N (1E200)
#define M (1E-50)
#define Y (1E100)
using namespace std;
//求最大值
double maxNum(double a, double b, double c)
{
	if (a >= b&&a >= c)
		return a;
	else 
		if (b >= a&&b >= c)
		return b;
	else 
		return c;
}

int main()
{
	double a, b, c;
	double x1, x2;
	cin >> a >> b >> c;

	if (fabs(a) < M || fabs(c) < M || fabs(b) < M)        //防止下溢，乘以一个常数
	{
		a = a * N;
		b = b * N;
		c = c * N;
	}
	if ((fabs(a) > Y && fabs(c) > Y) || fabs(b) > Y)
	{
		double max = maxNum(a, b, c);                     //都除以最大值
		a = a / max;
		b = b / max;
		c = c / max;
	}
	double delta = b * b - 4 * a * c;                     //delta判别式
	if (delta < 0)                                        //无根
		cout << 0 << endl << 0 << endl;
	else if (delta == 0)                                  //有重根
	{
		if (c == 0)
			cout << 0 << endl << 0 << endl;
		else
		{
			if (fabs(b)>fabs(c))
			{
				x1 = -2 * c / b;
			}
			else
			{
				x1 = -b / (2 * a);
			}
			printf("%.16e\n", x1);
			printf("%.16e\n", x1);
		}
	}
	else                                              //有两根
	{
		double differ1, differ2;
		differ1 = -b + sqrt(delta);
		differ2 = -b - sqrt(delta);
		//根据数据适当使用不同形式的求根公式
		if (fabs(differ1) < 1)
			x1 = 2 * c / differ2;
		else
			x1 = differ1 / (2 * a);


		if (fabs(differ2) < 1)

			x2 = 2 * c / differ1;
		else
			x2 = differ2 / (2 * a);

		printf("%.16e\n", x1);
		printf("%.16e\n", x2);
	}
	return 0;
}