/*
 * Group 6: Keila Cressman, Sam F, Sam Roberts
 * Project 1: Scheduling
 * 10/30/2020
 */

#include<iostream>
#include<random>
#include<vector>
#include<queue>
using namespace std;

struct Pcess
{
	long int st [40];
	int mem [40];
};

struct PcorS1
{
	long int speed[4] = {3000000000, 3000000000, 3000000000, 3000000000};
	int pcormem[4] = {2, 2, 4, 8};
};

void randPcess(struct Pcess pcess, struct PcorS1 ps1);

int main() {

	struct Pcess pcess;
	struct PcorS1 ps1;
	int x = 0;

	//generates random service and memory for 40 processes
	mt19937_64 randNum(x);

	for (int i = x; i < x+40; i++) {

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

} // End of main().

void randPcess(struct Pcess pcess, struct PcorS1 ps1) {

	long int count = 0;

	long int entry[40];

	entry[0] = 0;//start of wait time

	//start of turnaround time
	for (int i = 1; i < 41; i++) {

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

	for (int i = 1; i < 40; i++) {

		//loop through processors
		for (int j = i; j < i+4; j++) {

			cout<<"ID Number: "<<j+1<<endl;

			cout<<"  Service Time: "<<pcess.st[j]<<" Cycles"<<endl;

			cout<<"  Memory Requirement: "<<pcess.mem[j]<< "GB"<<endl;

			cout<<"  Wait Time: "<<entry[j]<<" Cycles"<<endl;

			cout<<"  Total Time in System: "<<pcess.st[j]<<" Cycles"<<endl;

		} // End of inner for-loop.

		i+=4;

	} // End of outer for-loop in FIFO.

	cout<<" "<<endl;

	cout<<"Total Turnaround Time: "<<entry[40]<<endl;

	cout<<"Average Wait Time: "<<entry[40]/40<<endl;

	// End of FIFO.

	// Round Robin

	//rr takes things as they come in, inserts them into a ready queue and processess them in that order in bits of time

	queue <int> ready;

	queue <int> complete;

	ready.push(1);

	int slice;

	//loop that starts at quantum 0 and increases by 10{
	for (slice = 0; ready.empty() == true; slice + 10*10^9) {

		int count = 0;

		while (count < 40) {

			if (pcess.st[count] <= slice && pcess.st[count] > 0) {

				ready.push(count);

			}

			else if (pcess.st[count] == 0) {

				ready.pop(count);
				complete.push(count);

			}

			else {

				count++;

			}

			for (int i = 0; i <= ready.size() + 1; i++) {

				pcess.st[i] = pcess.st[i] - 1;

			} // End of for-loop.

		} // End of while-loop.

	} // End of RR outer for-loop.


} // End of randPcess().

