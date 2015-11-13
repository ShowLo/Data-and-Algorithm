#include <iostream>
#include <algorithm>
#include <vector>
#define INF 2147483647
using namespace std;
//ͼ�����
class gNode
{
public:
	int vertex;                                          //�������
	int weight;                                          //Ȩ��
};
//������С��ʱ�õ��ıȽϺ���
bool compare(gNode &node1, gNode &node2)
{
	return node1.weight > node2.weight;
}
//������ʵȨ�غ���
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

	int size = N*N;                                      //�ܵĶ�����
	bool *visited = new bool[size];                      //���������¼������ʼ�¼
	for (int i = 0; i < size; ++i)                       //��ʼ��Ϊδ����
		visited[i] = false;
	vector <gNode> Maze(size);                           //�Թ�����
	vector <gNode> path(1);                              //���·������
	for (int i = 0; i < size; ++i)
	{
		Maze[i].vertex = i;
		cin >> Maze[i].weight;
		if (Maze[i].weight == 0)                         //����˲���ƶ����ܵĸ���
		{
			cin >> Maze[i].weight;
			Maze[i].weight = -Maze[i].weight;
		}
		else if (Maze[i].weight == -1)                   //ǽ�ڸ���
			Maze[i].weight = 0;
	}

	if (start == end)                                    //������յ��غ�
	{
		cout << 0;
		return 0;
	}

	int times = 0;                                       //��¼���ʵĵ���
	path[0].vertex = start;                              //��ʼ�����·�����
	path[0].weight = RealWeight(Maze[start].weight);
	//visited[0] = true;
	make_heap(path.begin(), path.end(), compare);        //������С��

	while (true)
	{
		if (path.begin() + times >= path.end())          //û��·��
			break;

		if (Maze[path[times].vertex].weight < 0)         //Ϊ����˲���ƶ����ܵĸ���
		{
			int jump = -Maze[path[times].vertex].weight - 1;    //���͵��ĵ�����
			if (Maze[jump].weight != 0 && !visited[jump])//��ת�㲻��ǽ��δ���ʹ�
			{
				if (jump == end)                         //�����յ�
				{
					cout << path[times].weight;
					return 0;
				}
				visited[jump] = true;                    //��Ϊ�ѷ���
				path.push_back(Maze[jump]);              //���͵��ĵ�������·����ȥ
				//������Ȩ����Ϊ��㵽˲���ƶ����·��ֵ���ϴ��͵��ĵ㱾��Ȩ��
				(path.end() - 1)->weight = path[times].weight + RealWeight(Maze[jump].weight);
				//ά����
				push_heap(path.begin() + times + 1, path.end(), compare);
			}
			Maze[path[times].vertex].weight = 0;
		}

		if (path[times].vertex - N >= 0)                 //�����Թ���һ��
		{
			if (Maze[path[times].vertex - N].weight != 0 && !visited[path[times].vertex - N])
			{                                            //�����ϱߵĵ�
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

		if (path[times].vertex + N < size)               //�����Թ����һ��
		{
			if (Maze[path[times].vertex + N].weight != 0 && !visited[path[times].vertex + N])
			{                                            //�����±ߵĵ�
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

		if (path[times].vertex % N != 0)                 //�����Թ�����һ��
		{
			if (Maze[path[times].vertex - 1].weight != 0 && !visited[path[times].vertex - 1])
			{                                            //������ߵĵ�
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

		if ((path[times].vertex + 1) % N != 0)           //�����Թ�����һ��
		{
			if (Maze[path[times].vertex + 1].weight != 0 && !visited[path[times].vertex + 1])
			{                                            //�����ұߵĵ�
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

		++times;                                         //���ʵĵ�����1
	}
	cout << INF;
	return 0;
}