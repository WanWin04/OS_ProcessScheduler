#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <fstream>
#include <functional>

#include "Process.hpp"

struct CompareProcess {
    bool operator()(const Process* a, const Process* b) const {
        return a->CPUBurst[0] > b->CPUBurst[0];
    }
};

struct CompareProcessD {
    bool operator()(const Process* a, const Process* b) const {
        return a->CPUBurst[0] >= b->CPUBurst[0];
    }
};

class Scheduler {
public:
    Scheduler();
    Scheduler(std::vector<Process*> processes);

    // void setComparisonFunction(std::function<bool(const Process*, const Process*)> comparisonFunction);

    void exportData(const std::string& filename);
    virtual void execute() = 0;

protected:
    std::vector<Process*> _processes;
    std::priority_queue<Process*, std::vector<Process*>, CompareProcess> _readyQueue;
    std::priority_queue<Process*, std::vector<Process*>, CompareProcessD> _readyQueueD;
    // std::priority_queue<Process*, std::vector<Process*>, std::function<bool(const Process*, const Process*)>> _readyQueue;
    std::queue<Process*> _blockedQueue;
    std::vector<int> _CPU;
    std::vector<int> _R;
};

#endif