#include<iostream>
#include<random>
#include<vector>
using namespace std;

struct Pcess
{
	long int st [40];
	int mem [40];
};

struct PcorS1
{
	long int speed[4] = {9000000000, 9000000000, 9000000000, 9000000000};
	int pcormem[4] = {8, 8, 8, 8};
};



void randPcess(struct Pcess pcess, struct PcorS1 ps1);

int main()
{	
	struct Pcess pcess;
	struct PcorS1 ps1;
	int x = 0;
	//generates random service and memory for 40 processes
	mt19937_64 randNum(x);
	for (int i = x; i < x+40; i++)
	{
		uniform_int_distribution<long int> randST(10000000, 10000000000000);
		long int serviceTime = randST(randNum);		
		//cout<<serviceTime<<endl;	//service time
		
		uniform_int_distribution<int> randTime(1,8);
		int memory = randTime(randNum);
		//cout<<memory<<" GB"<<endl;	//memory requirement
		
		pcess.st[i] = serviceTime;
		pcess.mem[i] = memory;
	}
	randPcess(pcess, ps1);
	
	return 0;
}

void randPcess(struct Pcess pcess, struct PcorS1 ps1)
{
	long int count = 0;
	long int entry[40];
	entry[0] = 0;//start of wait time
	//start of turnaround time
	for (int i = 1; i < 41; i++)
	{
		count += pcess.st[i-1];
		entry[i] = count;
	}
	entry[40] = entry[39] + pcess.st[39];
	
	//FIFO
	cout<<"ID Number: 1"<<endl;
		cout<<"  Service Time: "<<pcess.st[0]<<" Cycles"<<endl;
		cout<<"  Memory Requirement: "<<pcess.mem[0]<< "GB"<<endl;
		cout<<"  Wait Time: "<<entry[0]<<" Cycles"<<endl;
		cout<<"  Total Time in System: "<<pcess.st[0]<<" Cycles"<<endl;
	for (int i = 1; i < 40; i++)
	{
		//loop through processors
		for (int j = i; j < i+4; j++)
		{
			cout<<"ID Number: "<<j+1<<endl;
			cout<<"  Service Time: "<<pcess.st[j]<<" Cycles"<<endl;
			cout<<"  Memory Requirement: "<<pcess.mem[j]<< "GB"<<endl;
			cout<<"  Wait Time: "<<entry[j]<<" Cycles"<<endl;
			cout<<"  Total Time in System: "<<pcess.st[j]<<" Cycles"<<endl;
		}
		i+=4;
	}
	cout<<" "<<endl;
	cout<<"Total Turnaround Time: "<<entry[40]<<endl;
	cout<<"Average Wait Time: "<<entry[40]/40<<endl;
	
	
	
}























