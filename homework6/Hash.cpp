#include <iostream>
#include <string>
#define Prime 1000099                                //宏定义一个大质数（此大质数是测试出来的能通过OJ测试的一个质数之一）
using namespace std;
//链表类
class LinkList
{
public:
	LinkList(int num=-1,LinkList *Next=NULL);
	void add(int num);
	void setNum(int num);
	void outputNum();
	LinkList *NextNode();
private:
	int number;
	LinkList *Next;
	LinkList *tail;
};
//默认构造函数
LinkList::LinkList(int num,LinkList *Next):number(num),Next(Next)
{
	tail = this;
}
//在尾部加结点，保存字符串序号
void LinkList::add(int num)
{
	LinkList *NewNode = new LinkList(num);
	tail->Next = NewNode;
	tail = NewNode;
}
//设置字符串序号
void LinkList::setNum(int num)
{
	number = num;
}
//输出字符串序号
void LinkList::outputNum()
{
	cout << number;
}
//返回下个结点地址
LinkList* LinkList::NextNode()
{
	return Next;
}

//BKDR方法得到哈希值
long long BKDRHash(string str, int size)
{
	long long hash=0;
	for (int i = 0; i < size; ++i)
		hash = (hash * 31 + int(str[i]))%Prime;
	return hash;
}

//RS方法得到哈希值
long long RSHash(string str, int size)
{
	long long hash = 0;
	long long magic = 63689;
	for (int i = 0; i < size; ++i)
	{
		hash = (hash*magic + int(str[i])) % Prime;
		magic = (magic * 378551) % Prime;
	}
	return hash;
}

int main()
{
	int num;
	cin >> num;

	long long *Hash1 = new long long[num];           //哈希表1
	long long *Hash2 = new long long[num];           //哈希表2
	LinkList *NumList = new LinkList[Prime];         //储存相同字符串序号
	string *str = new string[num];                   //储存输入字符串
	int *list = new int[Prime];                      //作比较时用
	for (int i = 0; i < Prime; ++i)
		list[i] = -2;

	for (int i = 0; i < num; ++i)                    //每输入一个字符串，对应得到两个哈希值
	{
		cin >> str[i];
		Hash1[i] = BKDRHash(str[i], str[i].length());
		Hash2[i] = RSHash(str[i], str[i].length());
		if (list[Hash1[i]] == -2)                    //哈希值1还没有出现过
		{
			list[Hash1[i]] = i;
			//设置头结点
			NumList[list[Hash1[i]]].setNum(list[Hash1[i]]);
		}
		else if (Hash2[list[Hash1[i]]] == Hash2[i])  //哈希值2相等
			NumList[list[Hash1[i]]].add(i);          //加点
	}

	bool output = false;                             //判断是否有相同字符串
	LinkList *p;
	for (int i = 0; i < Prime; ++i)
	{
		p = &NumList[i];
		if (p->NextNode() != NULL)
		{
			output = true;                           //有相同字符串
			for (; p != NULL; p = p->NextNode())
			{
				p->outputNum();                      //输出
				cout << " ";
			}
			cout << endl;
		}
	}

	if (!output)                                     //没有相同字符串
		cout << -1;
	return 0;
}