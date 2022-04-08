#include <iostream>
#include "Nodenet.h"
using namespace namespace_Nodenet;

int main()
{
	vector<netnode> a_side;
	vector<netnode> b_side;
	for (int i = 0; i <= 3; ++i)
	{
		for (int j = 0; j <= 3; ++j)
		{
			if (i == 0 || i == 3 || i == j)
			{
				netnode tempcd;
				tempcd.item.push_back(i);
				tempcd.item.push_back(j);
				tempcd.item.push_back(1);
				a_side.push_back(tempcd);
				tempcd.item[2] = 0;
				b_side.push_back(tempcd);
			}
		}
	}
	for (auto & x : a_side)
	{
		for (auto & y : b_side)
		{
			if ((x.item[0] - y.item[0]) >= 0 && (x.item[1] - y.item[1]) >= 0 &&
				abs(x.item[0] + x.item[1] - y.item[0] - y.item[1]) <= 2 &&
				(x.item[0] != y.item[0] || x.item[1] != y.item[1]))
			{
				x.pnode.push_back(&y);
				y.pnode.push_back(&x);
			}
		}
	}
	for (int i = 0; i < 10; ++i)
	{
		a_side[i].item.push_back(10 - i);
		b_side[i].item.push_back(20 - i);
	}
	
	Nodenet nodenet;
	nodenet.search_net(a_side.back(),b_side.front());
	nodenet.show_initem(3);
}

