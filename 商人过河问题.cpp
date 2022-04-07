#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
class Condi
{
public:
	int pos[4];
	vector<Condi*> pcon;
	Condi() {}
	bool operator==(Condi& c)
	{
		for (int i = 0; i < 3; ++i)
		{
			if (pos[i] != c.pos[i])
				return false;
		}
		if (pcon.size() != c.pcon.size())
			return false;
		else
		{
			for (int i = 0; i < pcon.size(); ++i)
			{
				if (pcon[i] != c.pcon[i])
					return false;
			}
		}
		return true;
	}
};
typedef vector<vector<Condi>> vvcondi;
typedef vector<Condi> vcondi;
vvcondi search_net(Condi start, Condi end);
bool find_pcon_in_chain(Condi* pcd, vcondi chain);
int main()
{
	vector<Condi> a_side;
	vector<Condi> b_side;
	for (int i = 0; i <= 3; ++i)
	{
		for (int j = 0; j <= 3; ++j)
		{
			if (i == 0 || i == 3 || i == j)
			{
				Condi tempcd;
				tempcd.pos[0] = i;
				tempcd.pos[1] = j;
				tempcd.pos[2] = 1;
				a_side.push_back(tempcd);
				tempcd.pos[2] = 0;
				b_side.push_back(tempcd);
			}
		}
	}
	for (auto & x : a_side)
	{
		for (auto & y : b_side)
		{
			if ((x.pos[0] - y.pos[0]) >= 0 && (x.pos[1] - y.pos[1]) >= 0 &&
				abs(x.pos[0] + x.pos[1] - y.pos[0] - y.pos[1]) <= 2 &&
				(x.pos[0] != y.pos[0] || x.pos[1] != y.pos[1]))
			{
				x.pcon.push_back(&y);
				y.pcon.push_back(&x);
			}
		}
	}
	for (int i = 0; i < 10; ++i)
	{
		a_side[i].pos[3] = 10 - i;
		b_side[i].pos[3] = 20 - i;
	}
	vvcondi result = search_net(a_side.back(),b_side.front());

	for (vcondi chain : result)
	{
		for (Condi condi : chain)
		{
			cout << "(" << condi.pos[3] << ")-";
		}
		cout << endl;
	}
}
//构建以node类为节点的网络，给定两点作为起始和终止点，返回从起始点到终止点的所有路径（不重复不交叉）
//Condi为类类型，需要对==进行重载，且与Node有类似的结构
vvcondi search_net(Condi start, Condi end)
{
	vvcondi result_menu;  //存储所有路线
	vvcondi result_list;  //存储最终结果清单

	vcondi start_chain;
	start_chain.push_back(start);
	result_menu.push_back(start_chain);

	while (result_menu.size() != 0)
	{
		int original_size = result_menu.size(); //上一级所有节点的数量

		for (int i = 0; i < original_size; ++i) //循环original_size次，遍历所有上一级节点，找出下一级的所有节点
		{
			//对当前上一级chain进行处理前判断其是否已经到达end，是则加入result_list，并跳过接下来的处理，使其随上一级chain删除
			if (result_menu[i].back() == end)
			{
				result_list.push_back(result_menu[i]);
				continue;
			}

			for (Condi* pcondi : result_menu[i].back().pcon)
			{
				//无效的chain将不会产生新的chain，在遍历完成后将随所有上一级chain被删除
				if (!find_pcon_in_chain(pcondi, result_menu[i])) //避免回撤，排除反向的可能性
				{
					vcondi new_chain = result_menu[i];
					new_chain.push_back(*pcondi);
					result_menu.push_back(new_chain);
				}
			}
		}
		for (int i = 0;i < original_size;++i)
			result_menu.erase(result_menu.begin()); //删除当前的上一级节点所属的chain
	}
	return result_list;
}
//从所给chain中找出pcd指向的Condi，未找到返回false
bool find_pcon_in_chain(Condi* pcd, vcondi chain)
{
	for (Condi x : chain)
		if (x == *pcd)
		{
			return true;
		}
	return false;
}
