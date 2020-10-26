#include<iostream>
#include<random>
#include<ctime>	//get a diff seed for number generator until user input
using namespace std;

int opt1(int x);
int opt2(int x);
int opt3(int x);
int opt4(int x);
int fifo(int x);
int rr(int x);
int printOut(int x);

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

int opt1(int x)
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
		cin>>seed1;
		fifo(seed1);
	}
	else if (user2 == 2)
	{
		cout<<"You chose Round Robin (RR)"<<endl;
		cout<<"What seed would you like to start with(from, to): "<<endl;
		int seed2;
		cin>>seed2;
		rr(seed2);
	}
	return 0;
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
		cin>>seed1;
		fifo(seed1);
	}
	else if (user2 == 2)
	{
		cout<<"You chose Round Robin (RR)"<<endl;
		cout<<"What seed would you like to start with(from, to): "<<endl;
		int seed2;
		cin>>seed2;
		rr(seed2);
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
		cin>>seed1;
		fifo(seed1);
	}
	else if (user2 == 2)
	{
		cout<<"You chose Round Robin (RR)"<<endl;
		cout<<"What seed would you like to start with(from, to): "<<endl;
		int seed2;
		cin>>seed2;
		rr(seed2);
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
		cin>>seed1;
		fifo(seed1);
	}
	else if (user2 == 2)
	{
		cout<<"You chose Round Robin (RR)"<<endl;
		cout<<"What seed would you like to start with(from, to): "<<endl;
		int seed2;
		cin>>seed2;
		rr(seed2);
	}
	return 0;
}

int fifo(int x)
{
	cout<<"Seed is "<<x<<endl;
	printOut(x);
	return 0;
}

int rr(int x)
{
	cout<<"Seed is "<<x<<endl;
	printOut(x);
	return 0;
}

int printOut(int x)
{
	//creates the pseudorandom number easier to replicate
	mt19937_64 randNum(x);
	uniform_int_distribution<int> randTime(1,8);
	cout<<"Random number using Mersenne Twister - "<<randTime(randNum)<<endl;
	
	long int sTime[7] = {10000000, 100000000, 1000000000, 10000000000, 100000000000, 1000000000000, 10000000000000};
	uniform_int_distribution<int> randST(0,6);
	cout<<"Generates random cycle - "<<sTime[randST(randNum)]<<" GHz"<<endl;
	  
	cout<<"Generates random memory - "<<randTime(randNum)<<" GB"<<endl; 
	 
	return 0;
}