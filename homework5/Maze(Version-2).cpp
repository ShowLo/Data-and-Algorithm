#include <iostream>
#include <algorithm>
#include <vector>
#define INF 2147483647
using namespace std;
//图结点类
class gNode
{
public:
	int vertex;                                          //顶点序号
	int weight;                                          //权重
};
//构造最小堆时用到的比较函数
bool compare(gNode &node1, gNode &node2)
{
	return node1.weight > node2.weight;
}
//返回真实权重函数
int RealWeight(int weight)                               
{
	if (weight < 0)
		weight = 0;
	return weight;
}

int main()
{
	int N, start, end;
	cin >> N >> start >> end;
	start = start - 1;
	end = end - 1;

	int size = N*N;                                      //总的顶点数
	bool *visited = new bool[size];                      //访问数组记录顶点访问记录
	for (int i = 0; i < size; ++i)                       //初始化为未访问
		visited[i] = false;
	vector <gNode> Maze(size);                           //迷宫数组
	vector <gNode> path(1);                              //最短路径数组
	for (int i = 0; i < size; ++i)
	{
		Maze[i].vertex = i;
		cin >> Maze[i].weight;
		if (Maze[i].weight == 0)                         //具有瞬间移动功能的格子
		{
			cin >> Maze[i].weight;
			Maze[i].weight = -Maze[i].weight;
		}
		else if (Maze[i].weight == -1)                   //墙壁格子
			Maze[i].weight = 0;
	}

	if (start == end)                                    //起点与终点重合
	{
		cout << 0;
		return 0;
	}

	int times = 0;                                       //记录访问的点数
	path[0].vertex = start;                              //初始化最短路径起点
	path[0].weight = RealWeight(Maze[start].weight);
	//visited[0] = true;
	make_heap(path.begin(), path.end(), compare);        //生成最小堆

	while (true)
	{
		if (path.begin() + times >= path.end())          //没有路径
			break;

		if (Maze[path[times].vertex].weight < 0)         //为具有瞬间移动功能的格子
		{
			int jump = -Maze[path[times].vertex].weight - 1;    //传送到的点的序号
			if (Maze[jump].weight != 0 && !visited[jump])//跳转点不是墙且未访问过
			{
				if (jump == end)                         //到达终点
				{
					cout << path[times].weight;
					return 0;
				}
				visited[jump] = true;                    //置为已访问
				path.push_back(Maze[jump]);              //传送到的点加入最短路径中去
				//加入点的权重置为起点到瞬间移动点的路径值加上传送到的点本身权重
				(path.end() - 1)->weight = path[times].weight + RealWeight(Maze[jump].weight);
				//维护堆
				push_heap(path.begin() + times + 1, path.end(), compare);
			}
			Maze[path[times].vertex].weight = 0;
		}

		if (path[times].vertex - N >= 0)                 //不在迷宫第一行
		{
			if (Maze[path[times].vertex - N].weight != 0 && !visited[path[times].vertex - N])
			{                                            //加入上边的点
				if (path[times].vertex - N == end)
				{
					cout << path[times].weight;
					return 0;
				}
				visited[path[times].vertex - N] = true;
				path.push_back(Maze[path[times].vertex - N]);
				(path.end() - 1)->weight = path[times].weight + RealWeight(Maze[path[times].vertex - N].weight);
				push_heap(path.begin() + times + 1, path.end(), compare);
			}
		}

		if (path[times].vertex + N < size)               //不在迷宫最后一行
		{
			if (Maze[path[times].vertex + N].weight != 0 && !visited[path[times].vertex + N])
			{                                            //加入下边的点
				if (path[times].vertex + N == end)
				{
					cout << path[times].weight;
					return 0;
				}
				visited[path[times].vertex + N] = true;
				path.push_back(Maze[path[times].vertex + N]);
				(path.end() - 1)->weight = path[times].weight + RealWeight(Maze[path[times].vertex + N].weight);
				push_heap(path.begin() + times + 1, path.end(), compare);
			}
		}

		if (path[times].vertex % N != 0)                 //不在迷宫最左一列
		{
			if (Maze[path[times].vertex - 1].weight != 0 && !visited[path[times].vertex - 1])
			{                                            //加入左边的点
				if (path[times].vertex - 1 == end)
				{
					cout << path[times].weight;
					return 0;
				}
				visited[path[times].vertex - 1] = true;
				path.push_back(Maze[path[times].vertex - 1]);
				(path.end() - 1)->weight = path[times].weight + RealWeight(Maze[path[times].vertex - 1].weight);
				push_heap(path.begin() + times + 1, path.end(), compare);
			}
		}

		if ((path[times].vertex + 1) % N != 0)           //不在迷宫最右一列
		{
			if (Maze[path[times].vertex + 1].weight != 0 && !visited[path[times].vertex + 1])
			{                                            //加入右边的点
				if (path[times].vertex + 1 == end)
				{
					cout << path[times].weight;
					return 0;
				}
				visited[path[times].vertex + 1] = true;
				path.push_back(Maze[path[times].vertex + 1]);
				(path.end() - 1)->weight = path[times].weight + RealWeight(Maze[path[times].vertex + 1].weight);
				push_heap(path.begin() + times + 1, path.end(), compare);
			}
		}

		++times;                                         //访问的点数加1
	}
	cout << INF;
	return 0;
}