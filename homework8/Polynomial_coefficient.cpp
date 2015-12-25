#include <iostream>
#include <cmath>
using namespace std;

//矩阵乘法
void Multiply(int n, int m, double **M1, double **M2, double **M)
{
	for (int i = 0; i < m; ++i)                 //所有元素初始化为0
		for (int j = 0; j < m; ++j)
			M[i][j] = 0;
	for (int i = 0; i < m; i++)                 //一行一行地计算出所有元素
		for (int k = 0; k < n; ++k)
			if (M1[i][k])                       //M1[i][j]为0时不用进行相乘操作
				for (int j = 0; j < m; ++j)
					M[i][j] += M1[i][k] * M2[k][j];
}

//矩阵与向量的乘法
void Multiply_vector(int n, int m, double **M, float *y, double *b)
{
	for (int i = 0; i < m; ++i)
	{
		b[i] = 0;
		for (int j = 0; j < n; ++j)
			b[i] += M[i][j] * y[j];
	}
}

//转置函数
void Transposition(int n, int m, double **X, double **XT)
{
	for (int i = 0; i < m; ++i)
		for (int j = 0; j < n; ++j)
			XT[i][j] = X[j][i];
}
//求整数部分函数，遵循四舍五入原则
long integ(double a)
{
	long b = long(a);
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
	float *x = new float[n];
	float *y = new float[n];
	double *b = new double[m];
	for (int i = 0; i < n; ++i)
		cin >> x[i] >> y[i];

	double **X = new double*[n];                  //为矩阵申请空间
	for (int i = 0; i < n; ++i)
	{
		X[i] = new double[m];
	}
	double **XT = new double*[m];
	for (int i = 0; i < m; ++i)
	{
		XT[i] = new double[n];
	}
	double **XT_X = new double*[m];
	for (int i = 0; i < m; ++i)
	{
		XT_X[i] = new double[m];
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
	//求转置阵
	Transposition(n, m, X, XT);
	//作乘法运算
	Multiply(n, m, XT, X, XT_X);
	Multiply_vector(n, m, XT, y, b);

	double *v = new double[m];
	for (int i = 0; i < m; ++i)
	{
		double alfa = 0.0, multi = 0.0;
		double vT_v = 0.0, vT_u = 0.0;

		for (int j = i; j < m; ++j)             //求单位向量前所加的系数
		{
			alfa += XT_X[j][i] * XT_X[j][i];
		}
		if (XT_X[i][i] < 0)                     //判断正负
			alfa = sqrtl(alfa);
		else
			alfa = -sqrtl(alfa);

		for (int j = 0; j < i; ++j)             //求Household矢量v
			v[j] = 0;
		v[i] = XT_X[i][i] - alfa;
		for (int j = i + 1; j < m; ++j)
			v[j] = XT_X[j][i];

		vT_v = 0;
		for (int j = 0; j < m; ++j)             //求v^T*v
		{
			vT_v += v[j] * v[j];
		}

		for (int j = i; j < m; ++j)
		{
			vT_u = 0;
			for (int k = 0; k < m; ++k)         //求v^T*u
			{
				vT_u += v[k] * XT_X[k][j];
			}
			multi = (2 * vT_u) / vT_v;            //Household矢量v前面的系数
			for (int k = 0; k < m; ++k)         //逐列求解，对系数矩阵作Household变换
				XT_X[k][j] = XT_X[k][j] - 2 * vT_u *v[k] / vT_v;
		}

		vT_u = 0;
		for (int k = 0; k < m; ++k)
		{
			vT_u += v[k] * b[k];
		}

		multi = (2 * vT_u) / vT_v;
		for (int k = 0; k < m; ++k)
			b[k] = b[k] - 2 * vT_u*v[k]/ vT_v;
	}

	double sum;
	double *a = new double[m];
	for (int i = m - 1; i >= 0; --i)
	{
		sum = b[i];
		for (int j = i + 1; j < m; ++j)
			sum -= XT_X[i][j] * a[j];
		a[i] = sum / XT_X[i][i];
	}

	for (int i = 0; i < m; ++i)
		cout << integ(a[i]) << endl;
	return 0;
}