#include<iostream>
#include<random>				
#include<ctime>	//get a diff seed for number generator
using namespace std;

int main()
{

	mt19937_64 randNum(time(0));
	uniform_int_distribution<int> randTime(1, 8);
	cout<<"test - "<<randTime(randNum)<<endl;
	
	/*
	//creates the same random numbers if seed not created
	default_random_engine randNum(time(0));	
	//uniform integer distribution class
	uniform_int_distribution<int> randTime();	
	uniform_int_distribution<int> randMem(1, 8);
	
	cout<<"test1 - "<< randMem(randNum) <<endl;
	cout<<"test2 - "<< randMem(randNum) <<endl;
	cout<<"test3 - "<< randMem(randNum) <<endl;
	
	int x;
	x = mersenne_twister_engine<std::uint_fast64_t, 64, 312, 156, 31,
                             0xb5026f5aa96619e9, 29,
                             0x5555555555555555, 17,
                             0x71d67fffeda60000, 37,
                             0xfff7eee000000000, 43, 6364136223846793005>;	
                      
    cout<<x; 
    */
            
	return 0;
}