#include <iostream>
#include <cstdlib>
#include <ctime>
#include "queue.h"
const int Min_per_hour = 60;
bool newguest(int guest_per_hour);
int main()
{
	using namespace std;
	srand(time(0));
	const int test_hours = 100000000;
	int test_mins = test_hours * Min_per_hour;
	int guest_per_hour;

	cout << "Please enter the number of guests per hour: ";
	cin >> guest_per_hour;

	Queue line; // create a wait line
	Customer inservingcust; // a guest in serving
	Customer newcust;		// a new customer
	int total_wait_time = 0; //所有顾客的等候总时间
	int wait_time = 0;		//每位顾客的等候时间
	int guest_served = 0;	//获得服务的顾客总数
	int guest_count = 0;	//进入排队的顾客总数
	int turnaways = 0;		//被拒绝入队的顾客数
	int serving_time = -1;			//minutes need to serve a guest

	
	for (int i = 0; i < test_mins; i++)
	{
		if (newguest(guest_per_hour))   //come a new guest
		{
			newcust.set(i);				// the time guest get into line(arrive time)
			if (!line.enqueue(newcust)) // failure to get into line
				turnaways++;
			else						//success to get into line
				guest_count++;
		}

		if (!line.isempty())     //line is not empty
		{
			if (serving_time == -1 || serving_time == 0)
			{
				line.dequeue(inservingcust);
				serving_time = inservingcust.ptime();
				serving_time--;
				if (serving_time == 0) //a guest's serving finished in this minute
				{
					guest_served++;
					wait_time = i + 1 - inservingcust.ptime() - inservingcust.when();
					total_wait_time += wait_time;
				}
			}
			else 
			{
				serving_time--;
				if (serving_time == 0) //a guest's serving finished in this minute
				{
					guest_served++;
					wait_time = i + 1 - inservingcust.ptime() - inservingcust.when();
					total_wait_time += wait_time;
				}
			}
		}
		else						//no guest in line, no next guest
		{
			if (serving_time > 0)
			{
				serving_time--;
				if (serving_time == 0)
				{
					guest_served++;
					wait_time = i + 1 - inservingcust.ptime() - inservingcust.when();
					total_wait_time += wait_time;
					serving_time = -1;
				}
			}

			else if (serving_time == 0)
			{
				serving_time = -1;
			}
		}

	}

	cout << "=======================================" << endl;
	cout << "Total customers get in line: " << guest_count << endl;
	cout << "Customers served: " << guest_served << endl;
	cout << "Customers remained in line: " << line.queuecount() << endl;
	cout << "Customers turnaway: " << turnaways << endl;
	cout << "Total wait time: " << total_wait_time << endl;
	cout << "Average wait minutes for every customer: " << double(total_wait_time) / double(guest_served) << endl;
	return 0;
}
bool newguest(int gph)
{
	double min_per_guest = double (Min_per_hour) / double (gph);
	return (rand() * min_per_guest / RAND_MAX < 1.0);
}
