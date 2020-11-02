/*
 *
 *	Keila Cressman, Sam Roberts, Sam Farinacci
 *	Operating Systems -- Fall 2020
 *	Project 1
 *	11/1/2020
 *
*/

#include<iostream>
#include<random>
#include<queue>

struct Process {
	long int serv;
	int memReq;
	int IDn;
  long int remaining; // service time - attained time
  unsigned long long int completedAt = 0; // which cycle processed completed on
	unsigned long long int wait; // wait time
};

struct Processor {
	long int speed;
	int mem;
	int memAvail;
};

// Processor Scenarios
void s1(Processor p[4]);
void s2(Processor p[4]);
void s3(Processor p[4]);

// Process Stuff
void generateProcesses(std::queue<Process>& plist);
void RR(int option);
void FIFO(int option);

void mainMenu();

int main() {
	mainMenu();

	return 0;
}

void s1(Processor p[4]) {
	for(int i = 0; i < 4; i++) {
		p[i].speed = 3000000000;
		p[i].mem = 8;
		p[i].memAvail = 8;
	}
}

void s2(Processor p[4]) {
	p[0].mem = 2;
	p[1].mem = 2;
	p[2].mem = 4;
	p[3].mem = 8;
	for(int i = 0; i < 4; i++) {
		p[i].speed = 3000000000;
		p[i].memAvail = 8;
	}
}

void s3(Processor p[4]) {
	p[0].speed = 2000000000;
	p[1].speed = 2000000000;
	p[2].speed = 3000000000;
	p[3].speed = 4000000000;
	for(int i = 0; i < 4; i++) {
		p[i].mem = 8;
		p[i].memAvail = 8;
	}
}

void generateProcesses(std::queue<Process>& plist) {
	int x = 0;
	std::mt19937_64 randNum(x);
	struct Process temp;

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
}

void RR(int option) {
	struct Processor p[4];
	std::queue<Process> plist;
	std::queue<Process> completed;
	struct Process temp;
	unsigned long long int cycles = 0;
	long int q = 1000000000; // RR Quantum
	bool flag = false;

	// generate processors and processes
	switch(option) {
		case 1:
			s1(p);
			break;
		case 2:
			s2(p);
			break;
		case 3:
			s3(p);
			break;
		default:
			std::cout << "You shouldn't be seeing this message. If you are, you def goofed up.\n";
			break;
	}
	generateProcesses(plist);

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
					//std::cout << "Process ID " << temp.IDn << " completed.\n";
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

void FIFO(int option) {
	struct Processor p[4];
	std::queue<Process> plist;
	std::queue<Process> completed;
	struct Process temp;
	unsigned long long int cycles = 0;
	long int q = 1000000000; // RR Quantum
	bool flag = false;

	// generate processors and processes
	switch(option) {
		case 1:
			s1(p);
			break;
		case 2:
			s2(p);
			break;
		case 3:
			s3(p);
			break;
		default:
			std::cout << "You shouldn't be seeing this message either.\n";
			break;
	}
	generateProcesses(plist);

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

void mainMenu() {
	int pscenario;
	int strategy;
	bool cont = false;

	std::cout << "Hello!" << std::endl;
	std::cout << "Please choose from the following scenarios...\n";

	while(!cont) {
		std::cout << "1) All processors @ 3gHz speed and 8GB memory" << std::endl;
		std::cout << "2) Same speed, different memory" << std::endl;
		std::cout << "3) Same memory, different speed" << std::endl;
		std::cin >> pscenario;

		if(pscenario > 3 || pscenario < 0) {
			std::cout << "Please choose a valid option.\n";
		} else {
			cont = true;
		}
	}

	cont = false;

	while(!cont) {
		std::cout << "Thanks! Choose a scheduling strategy\n";

		std::cout << "1) First in, First out" << std::endl;
		std::cout << "2) Round Robin" << std::endl;

		std::cin >> strategy;

		if(strategy > 2 || strategy < 0) {
			std::cout << "Please choose a valid option.\n";
		} else {
			cont = true;
		}
	}

	std::cout << "Thank you! Continuing with your options...\n";

	if(strategy == 1) {
		FIFO(pscenario);
	} else {
		RR(pscenario);
	}
}
