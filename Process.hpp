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

    // function 
    friend void swap(Process* target1, Process* target2) noexcept {
        std::swap(target1->ID, target2->ID);
        std::swap(target1->arrivalTime, target2->arrivalTime);
        std::swap(target1->isWaiting, target2->isWaiting);
        std::swap(target1->startReadyQueue, target2->startReadyQueue);
        std::swap(target1->CPUBurst, target2->CPUBurst);
        std::swap(target1->resourceBurst, target2->resourceBurst);
        std::swap(target1->turnAroundTime, target2->turnAroundTime);
        std::swap(target1->waitingTime, target2->waitingTime);
    }
};

#endif