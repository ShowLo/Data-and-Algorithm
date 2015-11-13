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

bool compare(gNode &node1, gNode &node2)
{
	return node1.weight > node2.weight;
}

int RealWeight(int weight)                               //返回真实权重
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
	vector<bool>visited(size);                           //访问数组记录顶点访问记录
	for (int i = 0; i < size; ++i)                       //初始化为未访问
		visited[i] = false;
	vector<int> grid(size);                              //存放输入的权重
	vector <gNode> Maze(size);                           //迷宫数组
	vector <gNode> path(1);                              //最短路径数组
	for (int i = 0; i < size; ++i)
	{
		cin >> grid[i];
		if (grid[i] == 0)
		{
			cin >> grid[i];
			grid[i] = -grid[i];
		}
		else if (grid[i] == -1)
			grid[i] = 0;
	}

	if (start == end)
	{
		cout << 0;
		return 0;
	}

	int times = 0;                                       //记录访问的点数
	path[0].vertex = start;                              //初始化最短路径起点
	path[0].weight = RealWeight(grid[start]);
	make_heap(path.begin(), path.end(), compare);        //生成最小堆
	
	while (true)
	{
		if (path.begin() + times >= path.end())
			break;

		if (grid[path[times].vertex] < 0)                //为具有瞬间移动功能的格子
		{
			int jump = -grid[path[times].vertex] - 1;    //跳转到的点
			if (grid[jump] != 0 && !visited[jump])       //不是墙也未被访问过
			{
				if (jump == end)
				{
					cout << path[times].weight;
					return 0;
				}
				visited[jump] = true;                    //置为已访问
				Maze[jump].vertex = jump;
				//加入点的权重置为原来的路径长度加上自身权重
				Maze[jump].weight = path[times].weight + RealWeight(grid[jump]);
				path.push_back(Maze[jump]);              //加入到路径中去
				//维护堆
				push_heap(path.begin() + times + 1, path.end(), compare);
			}
		}

		if (path[times].vertex - N >= 0)                 //不在迷宫第一行
		{
			if (grid[path[times].vertex - N] != 0 && !visited[path[times].vertex - N])
			{                                            //加入上边的点
				if (path[times].vertex - N == end)
				{
					cout << path[times].weight;
					return 0;
				}
				visited[path[times].vertex - N] = true;
				Maze[path[times].vertex - N].vertex = path[times].vertex - N;
				Maze[path[times].vertex - N].weight = path[times].weight + RealWeight(grid[path[times].vertex - N]);
				path.push_back(Maze[path[times].vertex - N]);
				push_heap(path.begin() + times + 1, path.end(), compare);
			}
		}

		if (path[times].vertex + N < size)               //不在迷宫最后一行  
		{
			if (grid[path[times].vertex + N] != 0 && !visited[path[times].vertex + N])
			{
				if (path[times].vertex + N == end)
				{
					cout << path[times].weight;
					return 0;
				}
				visited[path[times].vertex + N] = true;
				Maze[path[times].vertex + N].vertex = path[times].vertex + N;
				Maze[path[times].vertex + N].weight = path[times].weight + RealWeight(grid[path[times].vertex + N]);
				path.push_back(Maze[path[times].vertex + N]);
				push_heap(path.begin() + times + 1, path.end(), compare);
			}
		}

		if (path[times].vertex % N != 0)             //不在迷宫最左一列
		{
			if (grid[path[times].vertex - 1] != 0 && !visited[path[times].vertex - 1])
			{
				if (path[times].vertex - 1 == end)
				{
					cout << path[times].weight;
					return 0;
				}
				visited[path[times].vertex - 1] = true;
				Maze[path[times].vertex - 1].vertex = path[times].vertex - 1;
				Maze[path[times].vertex - 1].weight = path[times].weight + RealWeight(grid[path[times].vertex - 1]);
				path.push_back(Maze[path[times].vertex - 1]);
				push_heap(path.begin() + times + 1, path.end(), compare);
			}
		}

		if ((path[times].vertex + 1) % N != 0)       //不在迷宫最右一列
		{
			if (grid[path[times].vertex + 1] != 0 && !visited[path[times].vertex + 1])
			{
				if (path[times].vertex + 1 == end)
				{
					cout << path[times].weight;
					return 0;
				}
				visited[path[times].vertex + 1] = true;
				Maze[path[times].vertex + 1].vertex = path[times].vertex + 1;
				Maze[path[times].vertex + 1].weight = path[times].weight + RealWeight(grid[path[times].vertex + 1]);
				path.push_back(Maze[path[times].vertex + 1]);
				push_heap(path.begin() + times + 1, path.end(), compare);
			}
		}

		++times;                                         //访问的点数加1
	}
	cout << INF;
	return 0;
}