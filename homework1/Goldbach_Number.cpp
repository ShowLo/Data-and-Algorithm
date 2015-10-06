#include <iostream>
#include <memory.h>
using namespace std;
int main()
{
	int inNumber;
	cin >> inNumber;
	int length = 2 * inNumber;                          //第N个哥德巴赫数不会超过2N
	bool *isPrime = new bool[length + 1];
	memset(isPrime, true, length + 1);                  //初始化为true
	for (int i = 2; i <= inNumber + 1; i++)             //筛法筛选质数
		if (isPrime[i])
			for (int j = 2; i*j <= length; j++)
			{
				if (isPrime[i*j])
				{
					isPrime[i*j] = false;
				}
			}
	int GoldbachNumber = 2;                             //哥德巴赫数个数
	if (inNumber == 1)
		cout << 4;
	if (inNumber == 2)
		cout << 5;
	int n;
	bool prime;
	for (n = 7; GoldbachNumber < inNumber; n += 2)      //偶数必定符合要求
	{
		prime = false;
		GoldbachNumber++;
		if (isPrime[n - 2])                             //若奇数符合要求，分解之后必为2和另一个奇数
		{
			GoldbachNumber++;
			prime = true;
		}
	}
	if (inNumber > 2)
	{
		if (inNumber == GoldbachNumber&&prime)
			cout << n - 2;
		else
			cout << n - 3;
	}
	delete[] isPrime;
	return 0;
}