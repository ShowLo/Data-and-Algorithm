#include <iostream>
#include <list>
using namespace std;
int main()
{
	int total_num;                     //������
	int circle_num;                    //Χ��Ȧ������
	int start_num;                     //��1��ʼ�������˵ı��
	int count_num;                     //�����ĵ�count_num����
	int i, number;                     //number��¼δ��Ȧ�����е���С���
	cin >> total_num >> circle_num >> start_num >> count_num;
	list<int> circle;
	list<int>::iterator iter;
	//��Ȧ�е��˱��
	for (i = 1; i <= circle_num; i++)
		circle.push_back(i);
	number = circle_num;               //����Ȧ�������
	//��λ����start_num���������ˣ�start_num<circle_num
	for (i = 1, iter = circle.begin(); i < start_num; i++)
	{
			++iter;
	}
	//��ʣ�µ�δ��Ȧ����ȫ����Ȧ
	for (i = 1; i <= total_num - circle_num; i++)
	{
		for (int j = 1; j <= count_num; j++)
		{
			if (iter == --circle.end())
				iter = circle.begin();
			else
				++iter;
		}
		circle.insert(iter, ++number);  //�������С�Ĳ���Ȧ��
		--iter;
	}
	//���������в���
	for (; total_num > 1; --total_num)  //ֻʣһ����ʱֹͣ
	{
		for (i = 1; i < count_num; i++)
		{
			if (iter == --circle.end())
				iter = circle.begin();
			else
				++iter;
		}
		if (iter == circle.begin())     //�������������count_num�ĸպ��ǵ�һ���ˣ���ͬ�������һ���˳���
		{
			circle.erase(--circle.end());
			iter = ++circle.begin();
		}
		else
		{
			--iter;                     //һ���������ͬ�����Ϊcount_num-1���˳���
			iter = circle.erase(iter);
			if (iter == --circle.end())
				iter = circle.begin();
			else
				++iter;
		}
	}
	cout << *circle.begin();

	return 0;
}