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
    std::vector<Process *> _CPU;
    std::vector<Process *> _R;
};

#endif