#ifndef PROCESS_HPP
#define PROCESS_HPP

#include <vector>
#include <cmath>
#include <algorithm>

class Process
{
public:
    Process();
    ~Process();

    int ID;
    int arrivalTime;

    bool isPrevent; // flag if can not swap
    bool backCPU; // flag if process from R to CPU
    int startReadyQueue; // time index of ready queue

    std::vector<int> CPUBurst;      // store CPU bursts
    std::vector<int> resourceBurst; // store resource bursts

    int turnAroundTime;
    int waitingTime;
};

#endif