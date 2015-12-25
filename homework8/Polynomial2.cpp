#include <iostream>
#include <cmath>
using namespace std;


//求整数部分函数，遵循四舍五入原则
int integ(double a)
{
	int b = int(a);
	if (fabs(b - a) < 0.5)
		return b;
	else
		if (a > 0)
			return b + 1;
		else
			return b - 1;
}

int main()
{
	int n, m;
	cin >> n >> m;
	double *x = new double[n];
	double *y = new double[n];
	double *v = new double[n];
	double *a = new double[m];
	for (int i = 0; i < n; ++i)
		cin >> x[i] >> y[i];

	double **X = new double*[n];                //为矩阵申请空间
	for (int i = 0; i < n; ++i)
	{
		X[i] = new double[m];
	}

	//初始化
	for (int i = 0; i < n; ++i)
	{
		X[i][0] = 1.0;
		for (int j = 1; j < m; ++j)
		{
			X[i][j] = X[i][j - 1] * x[i];
		}
	}

	for (int i = 0; i < m; ++i)
	{
		long double alfa = 0.0, multi = 0.0;
		double vT_v = 0.0, vT_u = 0.0;

		for (int j = i; j < n; ++j)             //求单位向量前所加的系数
		{
			alfa += X[j][i] * X[j][i];
		}
		if (X[i][i] < 0)                        //判断正负
			alfa = sqrtl(alfa);
		else
			alfa = -sqrtl(alfa);

		for (int j = 0; j < i; ++j)             //求Household矢量v
			v[j] = 0;
		v[i] = X[i][i] - alfa;
		for (int j = i + 1; j < n; ++j)
			v[j] = X[j][i];

		vT_v = 0;
		for (int j = 0; j < n; ++j)             //求v^T*v
		{
			vT_v += v[j] * v[j];
		}

		for (int j = i; j < m; ++j)
		{
			vT_u = 0;
			for (int k = 0; k < n; ++k)         //求v^T*u
			{
				vT_u += v[k] * X[k][j];
			}
			multi = 2 * vT_u / vT_v;            //Household矢量v前面的系数
			for (int k = 0; k < n; ++k)         //逐列求解，对系数矩阵作Household变换
				X[k][j] = X[k][j] - multi * v[k];
		}

		vT_u = 0;
		for (int k = 0; k < n; ++k)             //求vT_y
		{
			vT_u += v[k] * y[k];
		}

		multi = 2 * vT_u / vT_v;
		for (int k = 0; k < n; ++k)             //对y进行Household变换
			y[k] = y[k] - multi * v[k];
	}

	double sum;
	for (int i = m - 1; i >= 0; --i)            //回代求解
	{
		sum = y[i];
		for (int j = i + 1; j < m; ++j)
			sum -= X[i][j] * a[j];
		a[i] = sum / X[i][i];
	}

	for (int i = 0; i < m; ++i)
		cout << integ(a[i]) << endl;
	return 0;
}