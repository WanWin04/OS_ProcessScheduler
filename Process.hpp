#ifndef PROCESS_HPP
#define PROCESS_HPP

#include <vector>
#include <cmath>
#include <algorithm>

class Process {
public:
    Process();
    ~Process();

    int ID;
    int arrivalTime;

    bool isWaiting; // waiting on ready queue
    bool isPriority; // store state of process is old
    int startReadyQueue; // time index of ready queue

    std::vector<int> CPUBurst; // store CPU bursts
    std::vector<int> resourceBurst; // store resource bursts

    int turnAroundTime;
    int waitingTime; 

    void run() {
        CPUBurst.front()--;
        isPriority = false;
    }
};

#endif