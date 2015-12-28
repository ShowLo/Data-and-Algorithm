#include <iostream>
#include <stdlib.h>
#include <time.h>
#define N 100
#define M 1000
#define IMITATE_TIMES 66666                     //这个数可以过，不过还是有较小的概率过不了，这个数一般来说要适当取大一点
using namespace std;

int main()
{
	int *Array_0 = new int[N];
	int *Array_1 = new int[N];
	int **result = new int*[M];
	for (int i = 0; i < M; ++i)
	{
		result[i] = new int[N];
	}

	for (int i = 0; i < N; ++i)
		cin >> Array_0[i];
	for (int i = 0; i < N; ++i)
		cin >> Array_1[i];
	for (int i = 0; i < M; ++i)
		for (int j = 0; j < N; ++j)
			cin >> result[i][j];

	int choice;
	int *probablity_0 = new int[M + 1];         //数组序号即得到的介于10到1000的自然数，其中存放由数组一随机模拟得到此数的次数
	int *probablity_1 = new int[M + 1];         //数组序号即得到的介于10到1000的自然数，其中存放由数组二随机模拟得到此数的次数
	for (int i = 0; i < M + 1; ++i)             //初始化
	{
		probablity_0[i] = 0;
		probablity_1[i] = 0;
	}

	srand((unsigned)time(NULL));                //随机数种子
	int sum_0, sum_1;
	int i, j, k, times;

	for (j = 0; j < IMITATE_TIMES; ++j)         //进行多次模拟
	{
		sum_0 = 0, sum_1 = 0;
		for (i = 0; i < 10; ++i)                //模拟10次放回取样
		{
			choice = rand() % N;
			sum_0 += Array_0[choice];           //计算这10个数的和
			sum_1 += Array_1[choice];
		}
		++probablity_0[sum_0];                  //次数加一
		++probablity_1[sum_1];
	}
	
	int *imitate_output = new int[M];           //记录模拟输出的结果
	double pro_0, pro_1;
	for (int j = 0; j < M; ++j)                 //遍历1000组数据
	{
		pro_0 = 1, pro_1 = 1;
		for (int i = 0; i < N; ++i)             //遍历每组数据的100个数据并将其在两个数组的出现次数
			                                    //（可认为是概率）相乘，为避免溢出要除以一个数
		{
			pro_0 *= probablity_0[result[j][i]] / 100.0;
			pro_1 *= probablity_1[result[j][i]] / 100.0;
		}
		if (pro_0 > pro_1)                      //在Array_0出现概率更大
			imitate_output[j] = 0;
		else                                    //在Array_1出现概率更大
			imitate_output[j] = 1;
	}

	for (int i = 0; i < M; ++i)
		cout << imitate_output[i] << endl;  
	
	delete[]imitate_output;                     //删除动态申请空间
	delete[]probablity_0;
	delete[]probablity_1;
	delete[]Array_0;
	delete[]Array_1;
	for (int i = 0; i < N; ++i)
	{
		delete result[i];
		result[i] = NULL;
	}
	delete[]result;
	return 0;
}