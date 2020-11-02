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
	long int speed[4] = {3000000000, 3000000000, 3000000000, 3000000000};
	int pcormem[4] = {8, 8, 8, 8};
};

struct gantt
{
	vector<long int> time;
	int pcorused[4] = {1,2,3,4};
};

void opt1(int x);
int opt2(int x);
int opt3(int x);
int opt4(int x);
vector<long int> rrfunc(vector<long int> gc, int n);

int main()
{
	cout<<"Choose from the following scenarios: "<<endl;
	cout<<"(1): Same speed and same memory same arrival time"<<endl;
	cout<<"(2): Same speeds and varying memory"<<endl;
	cout<<"(3): Varying speed and same memory"<<endl;
	cout<<"(4): Same speed and same memory different arrival times"<<endl;
	int user1;
	cin>>user1;
	
	if (user1 == 1)
	{
		cout<<"You chose to use same speed and same memory same arrival time"<<endl;
		opt1(user1);
	}	
	else if (user1 == 2)
	{
		cout<<"You chose to use same speed and varying memory"<<endl;
		opt2(user1);
	}
	else if (user1 == 3)
	{
		cout<<"You chose to use varying speed and same memory"<<endl;
		opt3(user1);
	}
	else if (user1 == 4)
	{
		cout<<"You chose to use same speed and same memory different arrival times"<<endl;
		opt4(user1);
	}
	
	return 0;
}

void opt1(int x)
{
	cout<<"Choose from the following scheduling algorithms: "<<endl;
	cout<<"(1): First In First Out (FIFO)"<<endl;
	cout<<"(2): Round Robin (RR)"<<endl;
	int user2;
	cin>>user2;
	struct Pcess pcess;
	x = 0;
	mt19937_64 randNum(x);
	//generates random service and memory for 40 processes
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
	long int count = 0;
	long int entry[40];

	entry[0] = 0;//start of wait time
	//start of turnaround time
	for (int i = 1; i < 41; i++)
	{
		count += pcess.st[i];
		entry[i] = count;
	}
	entry[40] = entry[39] + pcess.st[39];
	
	if (user2 == 1)
	{
		cout<<"You chose First In First Out (FIFO)"<<endl;
		cout<<"What seed would you like to start with(from, to): "<<endl;
		int seed1;
		//print out message
		for (int i = 0; i < 40; i++)
		{
			cout<<"ID Number: "<<i+1<<endl;
			cout<<"  Service Time: "<<pcess.st[i]<<" Cycles"<<endl;
			cout<<"  Memory Requirement: "<<pcess.mem[i]<< "GB"<<endl;
			cout<<"  Wait Time: "<<entry[i]<<" Cycles"<<endl;
			cout<<"  Total Time: "<<pcess.st[i]<<" Cycles"<<endl;
		}
		cout<<" "<<endl;
		cout<<"Total Turnaround Time: "<<entry[40]<<endl;
		cout<<"Average Wait Time: "<<entry[40]/40<<endl;
	}
	
	else if (user2 == 2)
	{
		cout<<"You chose Round Robin (RR)"<<endl;
		cout<<"What seed would you like to start with(from, to): "<<endl;
		int seed2;
		//print out message
		//RR
		//Quantum in between service times, not too big or small
		long int q = 1000000000000;
		struct gantt g;
		//fills array with starter service time to decrement from
		for (int i = 0; i < 40; i++)
		{
			g.time.push_back(pcess.st[i]);
		}
		for (int i = 0; i < g.time.size(); i++) 
		{
			if (g.time[i] != 0)
			{	//each processes is decremented by the quantum
				g.time[i] = g.time[i] - q;
				//service time is done
				if (g.time[i] <= 0)
				{
					g.time[i] = 0;
				}
				g.time.push_back(g.time[i]);
			}
		}
		vector<long int> gc;
		//new vector created to store a copy of original vector
		for (int i = 0; i < 40; i++) 
		{
			gc.push_back(g.time[i]);
		}
		int n = gc.size();			//start of decrements for recursion
		vector<long int> ng = rrfunc(gc, n);
		//printout of updated gantt chart
		long int count2 = 0;
		long int entry2[ng.size()];
		entry2[0] = 0;
		cout<<"ID Number: 1"<<endl;
			cout<<"  Service Time: "<<pcess.st[0]<<" Cycles"<<endl;
			cout<<"  Memory Requirement: "<<pcess.mem[0]<< "GB"<<endl;
			cout<<"  Wait Time: "<<entry2[0]<<" Cycles"<<endl;
			cout<<"  Total Time in System: "<<pcess.st[0]<<" Cycles"<<endl;
		long int gcCount = 0;//handle gc
		vector<long int> ngc;
		long int ngcCount = 0;
		for (int i = 0; i < gc.size(); i++)//update after used service time
		{//saves leftover service times
			if (gc[i] > 0)
			{
				ngc.push_back(gc[i]);
			}
		}
		for (int i = 1; i < 40; i++) 
		{ 
			count2 += pcess.st[i-1]-ng[i-1];	
			entry2[i] = count2;					//right of gantt before all processes
		}
		for (int i = 40; i < ng.size(); i++) 
		{ 
			count2 += ngc[ngcCount];	
			entry2[i] = count2;					//right of gantt after all processes
			ngcCount++;
		}
		entry2[ng.size()] = entry2[ng.size()-1];
	  	//loop through processors
	  	int arr = sizeof(entry2)/sizeof(entry2[0]);
		for (int i = 1; i < 40;i++)//before update of used service time
		{
			cout<<"ID Number: "<<i+1<<endl;
			cout<<"  Service Time: "<<pcess.st[i]<<" Cycles"<<endl;
			cout<<"  Memory Requirements: "<<pcess.mem[i]<<"GB"<<endl;
			cout<<"  Wait Time: "<<entry2[i]<<" Cycles"<<endl;
			cout<<"  Total Time in System: "<<pcess.st[i]<<" Cycles"<<endl;
		}
		for (int i = 40; i < arr; i++)//update after used service time
		{
			cout<<"ID Number: "<<i+1<<endl;
			cout<<"  Service Time: "<<ngc[gcCount]<<" Cycles"<<endl;
			cout<<"  Memory Requirements: "<<pcess.mem[gcCount]<<"GB"<<endl;
			cout<<"  Wait Time: "<<entry2[i]<<" Cycles"<<endl;
			cout<<"  Total Time in System: "<<pcess.st[gcCount]<<" Cycles"<<endl;
			gcCount++;
		}
		cout<<" "<<endl;
		cout<<"Total Turnaround Time: "<<entry2[ng.size()]<<endl;
		cout<<"Average Wait Time: "<<entry2[ng.size()]/ng.size()<<endl;
	}	
}

int opt2(int x)
{
	cout<<"Choose from the following scheduling algorithms: "<<endl;
	cout<<"(1): First In First Out (FIFO)"<<endl;
	cout<<"(2): Round Robin (RR)"<<endl;
	int user2;
	cin>>user2;
	if (user2 == 1)
	{
		cout<<"You chose First In First Out (FIFO)"<<endl;
		cout<<"What seed would you like to start with(from, to): "<<endl;
		int seed1;
	}
	else if (user2 == 2)
	{
		cout<<"You chose Round Robin (RR)"<<endl;
		cout<<"What seed would you like to start with(from, to): "<<endl;
		int seed2;
	}
	return 0;
}

int opt3(int x)
{
	cout<<"Choose from the following scheduling algorithms: "<<endl;
	cout<<"(1): First In First Out (FIFO)"<<endl;
	cout<<"(2): Round Robin (RR)"<<endl;
	int user2;
	cin>>user2;
	if (user2 == 1)
	{
		cout<<"You chose First In First Out (FIFO)"<<endl;
		cout<<"What seed would you like to start with(from, to): "<<endl;
		int seed1;
	}
	else if (user2 == 2)
	{
		cout<<"You chose Round Robin (RR)"<<endl;
		cout<<"What seed would you like to start with(from, to): "<<endl;
		int seed2;
	}
	return 0;
}

int opt4(int x)
{
	cout<<"Choose from the following scheduling algorithms: "<<endl;
	cout<<"(1): First In First Out (FIFO)"<<endl;
	cout<<"(2): Round Robin (RR)"<<endl;
	int user2;
	cin>>user2;
	if (user2 == 1)
	{
		cout<<"You chose First In First Out (FIFO)"<<endl;
		cout<<"What seed would you like to start with(from, to): "<<endl;
		int seed1;
	}
	else if (user2 == 2)
	{
		cout<<"You chose Round Robin (RR)"<<endl;
		cout<<"What seed would you like to start with(from, to): "<<endl;
		int seed2;
	}
	return 0;
}

int k;
vector<long int> rrfunc(vector<long int> gc, int n)
{
	long int q = 1000000000000;
	//copy of old service times
	vector<long int> gcopy;
	vector<long int> check;
	//basecase
	if(n == 0)
	{
		return gc;
	}
	//check if any processes have not finished their time
	for (int i = k; i < gc.size(); i++) 
	{
		if (gc[i] != 0)
		{
			gcopy.push_back(gc[i]);
			//k is global to keep track of where we stopped at arrival 
				//and what index to start when we enter again
			k = i;
		}
	}
	for (int i = 0; i < gcopy.size(); i++) 
	{
		gcopy[i] = gcopy[i] - q;
		//service time is done
		if (gcopy[i] <= 0)
		{
			gcopy[i] = 0;
		}
		//update copy
		gcopy[i] = gcopy[i];
		if(gcopy[i] > 0)
		{
			check.push_back(gcopy[i]);
		}
		gc.push_back(gcopy[i]);
	}
	n = check.size();
	return rrfunc(gc,n);
}