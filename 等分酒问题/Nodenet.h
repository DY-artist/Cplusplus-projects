//״̬ת��ģ��-����·�������㷨ʵ��
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
	//�ж����ڵ��item�Ƿ���ȣ�����ȷ����ʼ�����ֹ��
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
		//������netnodeΪ�ڵ�����磬����������Ϊ��ʼ����ֹ�㣬���ش���ʼ�㵽��ֹ�������·�������ظ������棩
		vvnetnode search_net(netnode start, netnode end)
		{
			vvnetnode result_menu;  //�洢����·��

			vnetnode start_chain;
			start_chain.push_back(start);
			result_menu.push_back(start_chain);

			while (result_menu.size() != 0)
			{
				int original_size = result_menu.size(); //��һ�����нڵ������

				for (int i = 0; i < original_size; ++i) //ѭ��original_size�Σ�����������һ���ڵ㣬�ҳ���һ�������нڵ�
				{
					//�Ե�ǰ��һ��chain���д���ǰ�ж����Ƿ��Ѿ�����end���������result���������������Ĵ���ʹ������һ��chainɾ��
					if (equal_node(result_menu[i].back(), end))
					{
						result.push_back(result_menu[i]);
						continue;
					}
					for (netnode* pcondi : result_menu[i].back().pnode)
					{
						//��Ч��chain����������µ�chain���ڱ�����ɺ���������һ��chain��ɾ��
						if (!find_pnode_in_chain(pcondi, result_menu[i])) //����س����ų�����Ŀ�����
						{
							vnetnode new_chain = result_menu[i];
							new_chain.push_back(*pcondi);
							result_menu.push_back(new_chain);
						}
					}
				}
				for (int i = 0; i < original_size; ++i)
					result_menu.erase(result_menu.begin()); //ɾ����ǰ����һ���ڵ�������chain
			}
			return result;
		}
		//������chain���ҳ�pcdָ���netnode��δ�ҵ�����false
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
		//��item��ָ����Ԫ�ش�ӡ���
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