#include <iostream>
using namespace std;
//树结点类
class TreeNode
{
public:
	TreeNode();
	TreeNode &operator =(const TreeNode& tree);      //重载运算符"="
	TreeNode *LeftNode;                              //左孩子结点
	TreeNode *RightNode;                             //右孩子结点
	int value;                                       //结点值
};
//定义成员函数
TreeNode::TreeNode()
{
	LeftNode = NULL;                                 //初始化
	RightNode = NULL;
	value = -1;
}
//重载"="运算符
TreeNode& TreeNode::operator=(const TreeNode& tree)
{
	this->LeftNode = tree.LeftNode;
	this->RightNode = tree.RightNode;
	this->value = tree.value;
	return *this;
}
void FormTree(TreeNode **result, int *Preorder, int *Inorder, int NodeNum)
{
flag:
	if (NodeNum == 0)                                //结束标志，树已建完
	{
		*result = NULL;
		return;
	}
	TreeNode *node = new TreeNode;                   //新建树结点
	node->value = *Preorder;                         //初始化为先序遍历结果序列中位置靠前的结点值
	*result = node;
	int RootIndex = 0;
	for (; RootIndex < NodeNum; ++RootIndex)
	{
		if (Inorder[RootIndex] == *Preorder)         //在中序遍历结果序列中找到对应的结点,RootIndex为其位置
			break;
	}
	//递归调用，建立左子树
	FormTree(&node->LeftNode, Preorder + 1, Inorder, RootIndex);
	//改递归为循环，建立右子树
	result = &node->RightNode; 
	Preorder += RootIndex + 1; 
	Inorder += RootIndex + 1;
	NodeNum -= RootIndex + 1;
	goto flag;                                       //循环
}
//判断第一棵树中以node1为根节点的子树是否与第二棵树在形态结构上一致
bool IsSame(TreeNode *node1, TreeNode *node2)
{
	if (node1 == NULL)                               //递归结束
	{
		if (node2 == NULL)                           //同时到达叶子结点
			return true;
		else                                         //不一致
			return false;
	}
	if (node2 == NULL)
	{
		if (node1 == NULL)
			return true;
		else
			return false;
	}
	//递归调用本身，判断在形态结构上是否一致
	return IsSame(node1->LeftNode, node2->LeftNode) && IsSame(node1->RightNode, node2->RightNode);
}
//判断是否子树
void SubTree(TreeNode *tree1, TreeNode *tree2, int NodeNum2, int *value, bool *result)
{
flag:
	if (tree1 == NULL)                                //确定不是子树
	{
		*result = false;
		return;                                       //退出
	}
	*result = false;
	*result = IsSame(tree1, tree2);
	if (*result)                                      //确定是子树
	{
		*value = tree1->value;
		*result = true;
		return;                                       //退出
	}
	//如果上一个result为false，递归调用，指向左结点
	SubTree(tree1->LeftNode, tree2, NodeNum2, value, result);
	if (*result)                                      //确定是子树，退出
		return;
	//如果上一个result为false，改递归为循环，指向右结点，继续判断
	tree1 = tree1->RightNode;
	goto flag;                                        //循环
}
//主函数
int main()
{
	int NodeNum1, NodeNum2;
	cin >> NodeNum1;                                 //第一棵树的结点数
	int *Tree1_Pre = new int[NodeNum1];
	int *Tree1_In = new int[NodeNum1];
	for (int i = 0; i < NodeNum1; i++)               //前序遍历结果序列
		cin >> Tree1_Pre[i];
	for (int i = 0; i < NodeNum1; i++)               //中序遍历结果序列
		cin >> Tree1_In[i];

	cin >> NodeNum2;                                 //第二棵树的结点数
	int *Tree2_Pre = new int[NodeNum2];
	int *Tree2_In = new int[NodeNum2];
	for (int i = 0; i < NodeNum2; i++)               //前序遍历结果序列
		cin >> Tree2_Pre[i];
	for (int i = 0; i < NodeNum2; i++)               //中序遍历结果序列
		cin >> Tree2_In[i];

	TreeNode *tree1, *tree2;
	FormTree(&tree1,Tree1_Pre, Tree1_In, NodeNum1); //重建第一棵树
	FormTree(&tree2,Tree2_Pre, Tree2_In, NodeNum2); //重建第二棵树
	
	int value = -1;
	bool result = false;
	SubTree(tree1, tree2, NodeNum2,&value,&result); //判断是否子树
	cout << value;
	return 0;
}