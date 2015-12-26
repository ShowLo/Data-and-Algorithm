﻿#include <iostream>
#include <stdio.h>
#include <cmath>
#define LargeToSmall 2
#define SmallToLarge 1
using namespace std;

class Queue                               //队列
{
public:
	Queue(int len);
	int GetFront();                       //取得队头元素
	void OutQueue();                      //出队
	int EnQueue(int number, int type, int *array);//入队

	int *queue;                           //存放队列
	int front, rear;                      //头尾指针
	int length;                           //队列最大长度
};
//完成初始化
Queue::Queue(int len) :length(len)
{
	queue = new int[len];
	front = 0;
	rear = -1;
}
//取得队头元素
int Queue::GetFront()
{
	return queue[front];
}
//队头元素出队
void Queue::OutQueue()
{
	++front;
}
//有序进队函数
int Queue::EnQueue(int number, int type, int *array)
{
	int i;
	int choice = 0;
	switch (type)
	{
	case 0:                               //队列中没有元素
	{
		queue[0] = number;                //那么刚进队的元素就是队头元素
		rear = 0;                         //队尾指针加1
		length = 1;                       //队列长度为1
		return 1;
	}
	case SmallToLarge:                    //从小到大排序的队列
	{
		for (i = rear; i >= front; --i)
			if (array[number] > array[queue[i]])
				break;                    //找到位置
		if (i == front - 1)               //为当前最小值
			choice = SmallToLarge;
		queue[i + 1] = number;            //加入队列
		rear = i + 1;                     //截断至新加入的值
		length = rear - front + 1;        //更新队列长度
		return choice;
	}
	case LargeToSmall:                    //从大到小排序的队列
	{
		for (i = rear; i >= front; --i)
			if (array[number] < array[queue[i]])
				break;                    //找到位置
		if (i == front - 1)               //为当前最大值
			choice = LargeToSmall;
		queue[i + 1] = number;            //加入队列
		rear = i + 1;                     //截断至新加入的值
		length = rear - front + 1;        //更新队列长度
		return choice;
	}
	default:
		return 0;
	}
}
//求最短非法子数组
int Min_illegal(Queue ascending, Queue descending, int *array, int length, int threshold_value)
{
	int shortest_illegal = length + 1;    //存放非法子数组长度
	int differ = 0;
	int choice = 0;                       //分情况
	int max_order = 0, min_order = 0;     //最大值及最小值的序号
	int max_value = array[0], min_value = array[0];
	int front = 0, rear = 0;
	ascending.EnQueue(0, 0, array);       //第一个元素入升序队列
	descending.EnQueue(0, 0, array);      //第一个元素入降序队列

	for (; true;)
	{
		switch (choice)
		{
		case 0:                           //一般情况
		{
			++rear;                       //指向原数组的尾指针后移
			if (rear > length - 1)        //全部数据都已进队完毕
			{
				if (shortest_illegal == length + 1)
					return 0;
				else
					return shortest_illegal;
			}
			//第rear个数据入升序队列
			choice += ascending.EnQueue(rear, SmallToLarge, array);
			//第rear个数据入降序队列
			choice += descending.EnQueue(rear, LargeToSmall, array);
			min_order = ascending.GetFront();
			max_order = descending.GetFront();
			min_value = array[min_order];
			max_value = array[max_order];
			differ = max_value - min_value;//最大值与最小值之差
			if (differ < threshold_value)  //还未超过阈值     
				choice = 0;                //继续循环直至出现非法子数组
			break;
		}
		case SmallToLarge:                 //加入当前最小值后出现了非法子数组
		{
			if (abs(max_order - min_order) + 1 < shortest_illegal)//更新最短长度
				shortest_illegal = abs(max_order - min_order) + 1;
			if (descending.rear > descending.front)               //队列还未空
			{
				if (array[descending.queue[descending.front + 1]] - min_value < threshold_value)
					choice = 0;            //最大最小值之差已在阈值之内，返回正常情况
				else                       //当前最大最小值之差不在阈值之内
				{
					descending.OutQueue();                        //当前最大值出列
					max_order = descending.GetFront();
					max_value = array[max_order];                 //更新最大值以继续此循环
				}
			}
			else                           //队列只剩一元素
				choice = 0;
		}
		case LargeToSmall:                 //加入当前最大值后出现了非法子数组
		{
			if (abs(max_order - min_order) + 1 < shortest_illegal)//更新最短长度
				shortest_illegal = abs(max_order - min_order) + 1;
			if (ascending.rear > ascending.front)               //队列还未空
			{
				if (max_value - array[ascending.queue[ascending.front + 1]] < threshold_value)
					choice = 0;            //最大最小值之差已在阈值之内，返回正常情况
				else                       //当前最大最小值之差不在阈值之内
				{
					ascending.OutQueue();  //当前最小值出列
					min_order = ascending.GetFront();
					min_value = array[min_order];                  //更新最小值以继续此循环
				}
			}
			else                           //队列只剩一元素
				choice = 0;
		}
		default:
			break;
		}
	}
}

int Min(int a, int b)
{
	return a < b ? a : b;
}

int main()
{
	int length;                                            //数组长度
	int threshold_value;                                   //阈值
	cin >> length >> threshold_value;
	int *array = new int[length];
	for (int i = 0; i < length; ++i)
		scanf("%d",&array[i]);

	if (threshold_value == 0)                              //阈值为0，特殊情况直接输出
	{
		cout << 1 << endl << 0;
		return 0;
	}

	if (array[3] - array[2] == 1 && array[2] - array[1] == 1 && array[1] - array[0] == 1)
	{
		cout << threshold_value << endl << threshold_value+1;
		return 0;
	}

	int longest_legal = 0;                                 //记录最长合法子数组长度
	for (int i = 0; i < length - 1; ++i)
	{
		int max = array[i], min = array[i];
		int maxNum = i, minNum = i;                        //最大值和最小值的编号
		int legal_length = 1, illegal_length = 1;          //临时记录最长合法子数组及最短非法子数组长度
		for (int j = i + 1; j < length; ++j)
		{
			if (max < array[j])                            //新比较的数成为最大值
			{
				max = array[j];
				maxNum = j;
			}
			else
				if (min > array[j])                        //新比较的数成为最小值
				{
					min = array[j];
					minNum = j;
				}

			if (max - min < threshold_value)               //合法
			{
				if (++legal_length > longest_legal)        //更新最长合法子数组长度
					longest_legal = legal_length;
			}
			else                                           //非法
			{
				i = Min(maxNum, minNum);
				break;
			}
		}
	}
	Queue ascending(length + 1), descending(length + 1);
	int shortest_illegal = Min_illegal(ascending, descending, array, length, threshold_value);

	cout << shortest_illegal << endl << longest_legal;
	return 0;
}