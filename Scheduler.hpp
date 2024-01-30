#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <fstream>
#include <functional>

#include "Process.hpp"

const static int CPU_BURST_INDEX = 0;

struct CompareProcess {
    bool operator()(const Process* a, const Process* b) const {
        return a->CPUBurst[CPU_BURST_INDEX] > b->CPUBurst[CPU_BURST_INDEX];
    }
};

struct CompareProcessD {
    bool operator()(const Process* a, const Process* b) const {
        return a->CPUBurst[CPU_BURST_INDEX] >= b->CPUBurst[CPU_BURST_INDEX];
    }
};

class Scheduler {
public:
    Scheduler();
    Scheduler(std::vector<Process*> processes);

    void exportData(const std::string& filename);
    virtual void execute() = 0;

protected:
    std::vector<Process*> _processes;
    std::priority_queue<Process*, std::vector<Process*>, CompareProcess> _readyQueue;
    std::priority_queue<Process*, std::vector<Process*>, CompareProcessD> _readyQueueD;
    std::queue<Process*> _blockedQueue;
    std::vector<int> _CPU;
    std::vector<int> _R;
};

#endif