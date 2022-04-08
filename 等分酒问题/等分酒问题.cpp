#include "Nodenet.h"
using namespace namespace_Nodenet;
int main()
{
	vnetnode conditions;
	netnode start,end;
	start.item = { 8,0,0 };
	end.item = { 4,4,0 };
	int max[3] = { 8,5,3 };
	for (int i = 0;i <= 8;++i)
		for (int j = 0; j <= 5; ++j)
			for (int k = 0; k <= 3; ++k)
			{
				if (i + j + k != 8) //酒的体积恒定为8
					continue;
				netnode tempcondi;
				tempcondi.item.push_back(i);
				tempcondi.item.push_back(j);
				tempcondi.item.push_back(k);
				conditions.push_back(tempcondi);
			}

	for (int i = 0;i < conditions.size();++i)
		for (int j = i + 1; j < conditions.size(); ++j) //避免重复增加节点关系，减少运算量
		{
			//判断i->j,j->i是否可行
			int changes = 0;
			vector<int> index;
			for (int ii = 0; ii < 3; ++ii) //检查酒量发生变化的酒瓶数
			{
				if (conditions[i].item[ii] != conditions[j].item[ii])
				{
					++changes;
					index.push_back(ii);
				}
			}
			if (changes == 2) //一次操作只允许涉及两个酒瓶
			{
				if (conditions[i].item[index[0]] - conditions[j].item[index[0]] ==
					conditions[j].item[index[1]] - conditions[i].item[index[1]])//总共的装酒量恒定
				{
					//i->j
					//index[0]或index[1]代表的酒瓶酒量减少且变为0，或酒量增加且变为最大值
					if ((conditions[i].item[index[0]] > conditions[j].item[index[0]] && conditions[j].item[index[0]] == 0) ||
						(conditions[i].item[index[0]] < conditions[j].item[index[0]] && conditions[j].item[index[0]] == max[index[0]]) ||
						(conditions[i].item[index[1]] > conditions[j].item[index[1]] && conditions[j].item[index[1]] == 0) ||
						(conditions[i].item[index[1]] < conditions[j].item[index[1]] && conditions[j].item[index[1]] == max[index[1]]))
					{
						conditions[i].pnode.push_back(&conditions[j]);
					}
					//j->i
					//index[0]或index[1]代表的酒瓶酒量减少且变为0，或酒量增加且变为最大值
					if ((conditions[j].item[index[0]] > conditions[i].item[index[0]] && conditions[i].item[index[0]] == 0) ||
						(conditions[j].item[index[0]] < conditions[i].item[index[0]] && conditions[i].item[index[0]] == max[index[0]]) ||
						(conditions[j].item[index[1]] > conditions[i].item[index[1]] && conditions[i].item[index[1]] == 0) ||
						(conditions[j].item[index[1]] < conditions[i].item[index[1]] && conditions[i].item[index[1]] == max[index[1]]))
					{
						conditions[j].pnode.push_back(&conditions[i]);
					}
				}
			}
		}
	for (auto& x : conditions)
	{
		if (equal_node_initem(x, start))
			start = x;
		if (equal_node_initem(x, end))
			end = x;
	}
	Nodenet solution;
	solution.search_net(start, end);
	solution.show_result();
	return 0;
}