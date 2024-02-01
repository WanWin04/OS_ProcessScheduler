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

    bool isOnReady;
    bool isOnBloked;
    bool isOnCPU;
    bool isOnR;

    std::vector<int> CPUBurst; // store CPU bursts
    std::vector<int> resourceBurst; // store resource bursts
    
    int turnAroundTime;
    int waitingTime; 
};

#endif