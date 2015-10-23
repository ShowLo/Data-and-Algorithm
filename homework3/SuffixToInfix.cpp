#include <iostream>
#include <string>
using namespace std;
//结点类
class SNode                                                     
{
public:
	SNode();
	char item;                                                   //结点值
	SNode *m_next;                                               //结点后继，指向下一个结点的指针
};
//操作栈类
class Stack
{
public:
	Stack();
	void Bracket();                                              //加括号函数
	SNode *LeftNode;                                             //左结点
	SNode *RightNode;                                            //右结点
	int priority;                                                //优先级
};
//定义SNode类的构造函数
SNode::SNode()                                                   //结点类构造函数
{
	m_next = NULL;                                               //初始化
}
//定义Stack类的成员函数
Stack::Stack()
{
	LeftNode = NULL;                                             //初始化                        
	RightNode = NULL;
}
void Stack::Bracket()                                            //加括号
{
	SNode *bracket = new SNode[2];
	bracket[0].item = '(';
	bracket[1].item = ')';
	bracket[0].m_next = LeftNode; 
	LeftNode = &bracket[0];                                      //左括号为左结点
	RightNode->m_next = &bracket[1];
	RightNode = &bracket[1];                                     //右括号为右结点
}
//主函数
int main()
{
	enum prioitity{add_sub,mul_div,fac,oper};                    //枚举型变量，代表运算符优先级
	string suffix;
	cin >> suffix;
	int length = suffix.length();                                //输入后缀表达式长度
	SNode *Node=new SNode[length];                               //结点类存放后缀表达式
	for (int i = 0; i < length; ++i)
		Node[i].item = suffix[i];
	Stack *Infix=new Stack[length/2+1];                          //操作栈，长度不会超过后缀表达式长度的一半
	int stack_pos=0;                                             //记录操作的位置
	for (int i = 0; i < length; i++)
	{
		if (Node[i].item >= 'a'&&Node[i].item <= 'z')            //为操作数
		{
			Infix[stack_pos].LeftNode = &Node[i];                //栈顶的左右结点均设为操作数
			Infix[stack_pos].RightNode = &Node[i];
			Infix[stack_pos].priority = oper;                    //设置此栈的优先级
			++stack_pos;
		}
		else if (Node[i].item == '+' || Node[i].item == '-')     //加减操作符
		{
			if (Infix[stack_pos - 1].priority == add_sub)        //加括号
				Infix[stack_pos - 1].Bracket();
			(Infix[stack_pos - 2].RightNode)->m_next = &Node[i]; //操作符链接到第一个式子之后
			Node[i].m_next = Infix[stack_pos - 1].LeftNode;      //操作符链接到第二个式子之前
			Infix[stack_pos - 2].RightNode = Infix[stack_pos - 1].RightNode;//第二个式子退栈
			--stack_pos;
			Infix[stack_pos - 1].priority = add_sub;
		}
		else if (Node[i].item == '*' || Node[i].item == '/')     //乘除操作符
		{
			if (Infix[stack_pos - 1].priority <= mul_div)        
				Infix[stack_pos - 1].Bracket();
			if (Infix[stack_pos - 2].priority < mul_div)         
				Infix[stack_pos - 2].Bracket();
			(Infix[stack_pos - 2].RightNode)->m_next = &Node[i];
			Node[i].m_next = Infix[stack_pos - 1].LeftNode;
			Infix[stack_pos - 2].RightNode = Infix[stack_pos - 1].RightNode;
			--stack_pos;
			Infix[stack_pos - 1].priority = mul_div;
		}
		else                                                     //阶乘操作符，为单目操作符
		{
			if (Infix[stack_pos - 1].priority < fac)
				Infix[stack_pos - 1].Bracket();
			(Infix[stack_pos - 1].RightNode)->m_next = &Node[i]; //操作符链接到式子之后
			Infix[stack_pos - 1].RightNode= &Node[i];            //操作符为新的右结点
			Infix[stack_pos - 1].priority = fac;
		}
	}
	for (SNode *output = Infix[0].LeftNode; output != NULL; output = output->m_next)
		cout << output->item;
	return 0;
}