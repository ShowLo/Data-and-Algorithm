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
	for (i = 1; i <= circle_num; ++i)
		circle.push_back(i);
	number = circle_num;               //已入圈的最大编号
	//定位到第start_num个报数的人，start_num<circle_num
	for (i = 1, iter = circle.begin(); i < start_num; ++i)
	{
		++iter;
	}
	//将剩下的未入圈的人全部入圈
	for (; number <= total_num - 1; )
	{
		for (int j = 1; j <= count_num; ++j)             //定位
		{
			if (iter == --circle.end())
				iter = circle.begin();
			else
				++iter;
		}
		iter=circle.insert(iter, ++number);              //将编号最小的插入圈中;
	}
	//交换及出列操作
	for (; total_num > 1; --total_num)                   //只剩一个人时停止
	{
		if (count_num > 1)
		{
			for (int i = 1; i < count_num - 1; ++i)      //定位到报count_num-1的人
			{
				++iter;
				if (iter == circle.end())
					iter = circle.begin();
			}
		}
		else if (count_num == 1)                         //特殊情况，定位到上一个人
		{
			if (iter == circle.begin())
				iter = --circle.end();
			else
				--iter;
		}
		iter = circle.erase(iter);                       //交换后删除第count_num个人等同直接删除第count_num-1人
		if (iter == circle.end())
			iter = circle.begin();
		++iter;                                          //指向删除后的下一个人
		if (iter == circle.end())
			iter = circle.begin();
	}
	cout << *circle.begin();
	return 0;
}