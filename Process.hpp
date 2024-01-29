#ifndef PROCESS_HPP
#define PROCESS_HPP

#include <vector>

class Process {
public:
    Process();
    ~Process();

    int ID;
    int arrivalTime;

    std::vector<int> CPUBurst;
    std::vector<int> resourceBurst;

    int turnAroundTime;
    int waitingTime; 
};

#endif