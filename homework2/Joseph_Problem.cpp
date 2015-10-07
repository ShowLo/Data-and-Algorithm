#include <iostream>
#include <list>
using namespace std;
int main()
{
	int total_num;                     //总人数
	int circle_num;                    //围成圈的人数
	int start_num;                     //从1开始报数的人的编号
	int count_num;                     //数到的第count_num个人
	int i, number;                     //number记录未入圈的人中的最小标号
	cin >> total_num >> circle_num >> start_num >> count_num;
	list<int> circle;
	list<int>::iterator iter;
	//给圈中的人编号
	for (i = 1; i <= circle_num; i++)
		circle.push_back(i);
	number = circle_num;               //已入圈的最大编号
	//定位到第start_num个报数的人，start_num<circle_num
	for (i = 1, iter = circle.begin(); i < start_num; i++)
	{
			++iter;
	}
	//将剩下的未入圈的人全部入圈
	for (i = 1; i <= total_num - circle_num; i++)
	{
		for (int j = 1; j <= count_num; j++)
		{
			if (iter == --circle.end())
				iter = circle.begin();
			else
				++iter;
		}
		circle.insert(iter, ++number);  //将编号最小的插入圈中
		--iter;
	}
	//交换及出列操作
	for (; total_num > 1; --total_num)  //只剩一个人时停止
	{
		for (i = 1; i < count_num; i++)
		{
			if (iter == --circle.end())
				iter = circle.begin();
			else
				++iter;
		}
		if (iter == circle.begin())     //特殊情况，报到count_num的刚好是第一个人，等同于令最后一个人出列
		{
			circle.erase(--circle.end());
			iter = ++circle.begin();
		}
		else
		{
			--iter;                     //一般情况，等同于令报数为count_num-1的人出列
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