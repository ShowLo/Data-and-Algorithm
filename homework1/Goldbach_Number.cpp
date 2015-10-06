#include <iostream>
#include <memory.h>
using namespace std;
bool JudgePrime(bool *isPrime, int n)                   //�ж��Ƿ�Ϊ����
{
	return isPrime[n];
}
int main()
{
	int inNumber;
	cin >> inNumber;
	int length = 2 * inNumber;                          //��N����°ͺ������ᳬ��2N
	bool *isPrime = new bool[length + 1];
	memset(isPrime, true, length + 1);                  //��ʼ��Ϊtrue
	for (int i = 2; i <= inNumber + 1; i++)             //ɸ��ɸѡ����
		if (isPrime[i])
			for (int j = 2; i*j <= length; j++)
			{
				if (isPrime[i*j])
				{
					isPrime[i*j] = false;
				}
			}
	int GoldbachNumber = 2;                             //��°ͺ�������
	if (inNumber == 1)
		cout << 4;
	if (inNumber == 2)
		cout << 5;
	int n;
	bool prime;
	for (n = 7; GoldbachNumber < inNumber; n += 2)      //ż���ض�����Ҫ��
	{
		prime = false;
		GoldbachNumber++;
		if (JudgePrime(isPrime, n - 2))                 //����������Ҫ�󣬷ֽ�֮���Ϊ2����һ������
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