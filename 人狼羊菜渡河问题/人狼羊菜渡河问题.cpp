#include "Nodenet.h"
using namespace namespace_Nodenet;
int main()
{
	vnetnode a_side,b_side;
	for (int i = 0;i < 2;++i)
		for (int j = 0;j < 2;++j)
			for (int k = 0; k < 2; ++k)
			{
				int person = 1;
				netnode tempcondi;
				if (!((i == j && i != person) || (j == k && j != person)))
				{
					tempcondi.item.push_back(person);
					tempcondi.item.push_back(i);
					tempcondi.item.push_back(j);
					tempcondi.item.push_back(k);
					a_side.push_back(tempcondi);
				}
				person = 0;
				if (!((i == j && i != person) || (j == k && j != person)))
				{
					if (tempcondi.item.size() != 0)
						tempcondi.item[0] = person;
					else
					{
						tempcondi.item.push_back(person);
						tempcondi.item.push_back(i);
						tempcondi.item.push_back(j);
						tempcondi.item.push_back(k);
					}
					b_side.push_back(tempcondi);
				}
			}
	for (int i = 0; i < a_side.size(); ++i)
	{
		for (int j = 0; j < b_side.size(); ++j)
		{
			bool judge = true;
			int change = 0;
			for (int ii = 0; ii < 4; ++ii)
			{
				if (a_side[i].item[ii] < b_side[j].item[ii])
				{
					judge = false;
					break;
				}
				change += a_side[i].item[ii] - b_side[j].item[ii];
			}
			if (judge && abs(change) <= 2)
			{
				a_side[i].pnode.push_back(&b_side[j]);
				b_side[j].pnode.push_back(&a_side[i]);
			}
		}
	}
	netnode start, end;
	start.item = {1,1,1,1};
	end.item = {0,0,0,0};
	for (int i = 0;i < a_side.size();++i)
	{
		if (equal_node_initem(start, a_side[i]))
			start = a_side[i];
		if (equal_node_initem(end, b_side[i]))
			end = b_side[i];
	}

	Nodenet solution;
	solution.search_net(start, end);
	solution.show_result();
	return 0;
}