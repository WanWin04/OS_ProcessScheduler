#include "Scheduler.hpp"

Scheduler::Scheduler() {}

Scheduler::Scheduler(std::vector<Process*> processes) : _processes(processes) {}

void Scheduler::exportData(const std::string& filename) {
    std::ofstream ofs(filename);

    for (int i = 0; i < _CPU.size(); ++i) {
        if (_CPU[i] == -1) {
            ofs << "_";
        } else {
            ofs << _CPU[i];
        }
        ofs << " ";
    }

    ofs << std::endl;

    for (int i = 0; i < _R.size(); ++i) {
        if (_R[i] == -1) {
            ofs << "_";
        } else {
            ofs << _R[i];
        }
        ofs << " ";
    }

    ofs << std::endl;

    for (int i = 0; i < _processes.size(); ++i) {
        ofs << _processes[i]->turnAroundTime << " ";
    }

    ofs << std::endl;
    
    for (int i = 0; i < _processes.size(); ++i) {
        ofs << _processes[i]->waitingTime << " ";
    }

    ofs.close();
}

bool Scheduler::isTerminatedAll(std::vector<Process*> processes, std::vector<Process*> readyQueue, std::queue<Process*> blockedQueue) {
    return (processes.empty() && readyQueue.empty() && blockedQueue.empty());
}