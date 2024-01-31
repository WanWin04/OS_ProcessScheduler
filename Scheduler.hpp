#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <fstream>

#include "Process.hpp"

const static int CPU_BURST_INDEX = 0;

class Scheduler {
public:
    Scheduler();
    Scheduler(std::vector<Process*> processes);

    // export data to output file 
    void exportData(const std::string& filename);

    // pure virtual function  
    virtual void execute() = 0;

protected:
    std::vector<Process*> _processes;
    std::vector<Process*> _readyQueue;
    std::queue<Process*> _blockedQueue;
    std::vector<int> _CPU;
    std::vector<int> _R;

    // pure virtual function 
    virtual void insertionSort(std::vector<Process*>& readyQueue, int currentTime) = 0;

    // chech if all process is terminated 
    bool isTerminatedAll(std::vector<Process*> processes, std::vector<Process*> readyQueue, std::queue<Process*> blockedQueue);
};

#endif