#include<iostream>
#include<random>
#include<queue>

struct Process {
	long int serv;
	int memReq;
	int IDn;
  long int remaining; // service time - attained time
  unsigned long long int completedAt = 0; // which cycle processed completed on
};

struct Processor {
	long int speed;
	int mem;
	int memAvail;
};

int main() {
	int x = 0; // seed for rng
	std::queue<Process> plist;
	std::queue<Process> completed;
	std::mt19937_64 randNum(x);
	struct Processor p[4];
	struct Process temp;
	unsigned long long int cycles = 0;
	long int q = 1000000000; // RR Quantum
	bool flag = false;

	// generate processors
	p[0].speed = 2000000000;
	p[1].speed = 2000000000;
	p[2].speed = 3000000000;
	p[3].speed = 4000000000;
	for(int i = 0; i < 4; i++) {
		p[i].mem = 8;
		p[i].memAvail = 8;
	}

	// generate processes here
	for (int i = x; i < x+40; i++) {
		std::uniform_int_distribution<long int> randST(10000000, 10000000000000);
		long int serviceTime = randST(randNum);

		std::uniform_int_distribution<int> randTime(1,8);
		int memory = randTime(randNum);;

		temp.serv = serviceTime;
		temp.memReq = memory;
    temp.completedAt = 0;
    temp.remaining = serviceTime;
		temp.IDn = i;
		plist.push(temp);
	}

	// start RR
  while(!flag) {
		temp = plist.front(); // set temp to the next process in line
		plist.pop(); // pop from queue

		for(int i = 0; i < 4; i++) {
			if(p[i].memAvail >= temp.memReq) { // are there enough resources?
				p[i].memAvail -= temp.memReq; // set resources aside
				if(temp.remaining > q) {
					cycles += q; // progress by q cycles
					temp.remaining -= q; // deduct q to get remaining service time
					plist.emplace(temp); // put back in at the end of the line
					//std::cout << "Process ID " << temp.IDn << " requeued. Remaining cycles: " << temp.remaining << std::endl;
				} else if(temp.remaining <= q) {
					cycles += temp.remaining; // progress by remaining cycle
					temp.remaining = 0; // remaining service time is complete
					temp.completedAt = cycles;
					completed.push(temp); // push completed process to queue
					std::cout << "Process ID " << temp.IDn << " completed.\n";
				}
				p[i].memAvail += temp.memReq; // free up resources
				flag = plist.empty(); // test for an empty list
				break;
			}
		}
  }

	// RESULTS
	std::cout << completed.size() << " processes complete!\n";

	unsigned long long int totalWait = 0;
	unsigned long long int totalTurn = 0;
	for(int i = 0; i < 40; i++) {
		temp = completed.front();
		completed.pop();
		totalWait += (temp.completedAt - temp.serv);
		totalTurn += temp.completedAt;
	}

	std::cout << "Average Wait Time: " << (totalWait / 40) << std::endl;
	std::cout << "Average Turnaround Time: " << (totalTurn / 40) << std::endl;
}
