#include<iostream>
#include<random>
using namespace std;

struct Processes
{
	long int st [40];
	int mem [40];
};

int main()
{	
	struct Processes P;
	int x = 0;
	//generates random service and memory for 40 processes
	for (int i = x; i < x+40; i++)
	{
		long int sTime[7] = {10000000, 100000000, 1000000000, 10000000000, 100000000000, 1000000000000, 10000000000000};
		mt19937_64 randNum(i);					//change to x
		uniform_int_distribution<int> randST(0,6);
		int index = randST(randNum);
		long int serviceTime = sTime[index];		
		//cout<<serviceTime<<endl;	//service time
		
		uniform_int_distribution<int> randTime(1,8);
		int memory = randTime(randNum);
		//cout<<memory<<" GB"<<endl;	//memory requirement
		
		P.st[i] = serviceTime;
		P.mem[i] = memory;
	}
	
	for (int i = 0; i < 40; i++)
	{
		cout<<"Process "<<i+1<<" has: "<<P.st[i]<<" as Service Time."<<endl;
		cout<<"Process "<<i+1<<" has: "<<P.mem[i]<<" GB"<<endl;
	}
	return 0;
}