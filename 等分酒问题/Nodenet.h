//状态转移模型-网络路径搜索算法实现
#ifndef NODENET_H_
#define NODENET_H_
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
namespace namespace_Nodenet
{
	struct netnode
	{
		vector<int> item;
		vector<netnode*> pnode;
	};
	//判断两节点的item是否相等，便于确定起始点和终止点
	bool equal_node_initem(netnode na, netnode nb)
	{
		if (na.item.size() != nb.item.size())
			return false;
		else
		{
			for (int i = 0; i < na.item.size(); ++i)
			{
				if (na.item[i] != nb.item[i])
					return false;
			}
		}
		return true;
	}
	bool equal_node(netnode & na, netnode & nb)
	{
		if (na.item.size() != nb.item.size())
			return false;
		else
		{
			for (int i = 0; i < na.item.size(); ++i)
			{
				if (na.item[i] != nb.item[i])
					return false;
			}
		}
		if (na.pnode.size() != nb.pnode.size())
			return false;
		else
		{
			for (int i = 0; i < na.pnode.size(); ++i)
			{
				if (na.pnode[i] != nb.pnode[i])
					return false;
			}
		}
		return true;
	}
	typedef vector<vector<netnode>> vvnetnode;
	typedef vector<netnode> vnetnode;
	class Nodenet
	{
	private:
		vvnetnode result;
	public:
		Nodenet() {}
		//构建以netnode为节点的网络，给定两点作为起始和终止点，返回从起始点到终止点的所有路径（不重复不交叉）
		vvnetnode search_net(netnode start, netnode end)
		{
			vvnetnode result_menu;  //存储所有路线

			vnetnode start_chain;
			start_chain.push_back(start);
			result_menu.push_back(start_chain);

			while (result_menu.size() != 0)
			{
				int original_size = result_menu.size(); //上一级所有节点的数量

				for (int i = 0; i < original_size; ++i) //循环original_size次，遍历所有上一级节点，找出下一级的所有节点
				{
					//对当前上一级chain进行处理前判断其是否已经到达end，是则加入result，并跳过接下来的处理，使其随上一级chain删除
					if (equal_node(result_menu[i].back(), end))
					{
						result.push_back(result_menu[i]);
						continue;
					}
					for (netnode* pcondi : result_menu[i].back().pnode)
					{
						//无效的chain将不会产生新的chain，在遍历完成后将随所有上一级chain被删除
						if (!find_pnode_in_chain(pcondi, result_menu[i])) //避免回撤，排除反向的可能性
						{
							vnetnode new_chain = result_menu[i];
							new_chain.push_back(*pcondi);
							result_menu.push_back(new_chain);
						}
					}
				}
				for (int i = 0; i < original_size; ++i)
					result_menu.erase(result_menu.begin()); //删除当前的上一级节点所属的chain
			}
			return result;
		}
		//从所给chain中找出pcd指向的netnode，未找到返回false
		bool find_pnode_in_chain(netnode* pcd, vnetnode chain)
		{
			for (netnode x : chain)
				if (equal_node(x, *pcd))
				{
					return true;
				}
			return false;
		}
		void show_result()
		{
			int count = 1;
			for (vnetnode chain : result)
			{
				cout << "Solution #" << count++ << ": ";
				for (netnode condi : chain)
				{
					cout << "( ";
					for (int num : condi.item)
						cout << num << " ";
					cout << ")-";
				}
				cout << "end" << endl;
			}
		}
		//以item中指定的元素打印结果
		void show_initem(int index)
		{
			int count = 1;
			for (vnetnode chain : result)
			{
				cout << "Solution #" << count << ": ";
				for (netnode node : chain)
				{
					cout << "(" << node.item[index % node.item.size()] << ")-";
				}
				cout << "end" << endl;
			}
		}
	};
}

#endif