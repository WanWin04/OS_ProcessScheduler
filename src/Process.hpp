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

    bool state; // flag if the process has entered the CPU (true/false)
    int startReadyQueue; // time index of ready queue

    std::vector<int> CPUBurst;      // store CPU bursts
    std::vector<int> resourceBurst; // store resource bursts

    int turnAroundTime;
    int waitingTime;
};

#endif