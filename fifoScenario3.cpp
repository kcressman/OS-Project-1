#include<iostream>
#include<random>
#include<queue>

struct Process {
	long int serv;
	int memReq;
	int IDn;
  long int remaining; // service time - attained time
  unsigned long long int wait; // wait time
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
    temp.wait = 0;
    temp.remaining = serviceTime;
		temp.IDn = i;
		plist.push(temp);
	}

	// start FIFO
	for(int i = 0; i < 40; i++) {
		temp = plist.front(); // set temp to next process in line
		plist.pop(); // pop from queue

		// find an open processor
		for(int j = 0; j < 4; j++) {
			if(p[j].memAvail >= temp.memReq) {
				p[j].memAvail -= temp.memReq; // consume resource
				temp.wait += cycles; // set wait time

				while(temp.remaining > 0) { // start working on the process
					if(temp.remaining > p[j].speed) {
						cycles += p[j].speed; // move forward based on processor speed
						temp.remaining -= p[j].speed; // remove cycles progressed from remaining
					} else if(temp.remaining <= p[j].speed) {
						cycles += temp.remaining; // progress by remaining cycles
						temp.remaining = 0; // set remaining to 0 to exit processor
						completed.push(temp); // it's done, push it to the completed queue
					}
				}
				p[j].memAvail += temp.memReq; // free up resource
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
		totalWait += temp.wait;
		totalTurn += (temp.wait + temp.serv);
	}

	std::cout << "Average Wait Time: " << (totalWait / 40) << std::endl;
	std::cout << "Average Turnaround Time: " << (totalTurn / 40) << std::endl;
}
