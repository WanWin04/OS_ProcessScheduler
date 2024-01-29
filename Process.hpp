#ifndef PROCESS_HPP
#define PROCESS_HPP

#include <vector>

class Process {
public:
    Process();
    ~Process();

    int ID;
    int arrivalTime;

    bool isWaiting; // waiting on ready queue
    int startReadyQueue; // time index of ready queue

    std::vector<int> CPUBurst; // store CPU bursts
    std::vector<int> resourceBurst; // store resource bursts

    int turnAroundTime;
    int waitingTime; 
};

#endif