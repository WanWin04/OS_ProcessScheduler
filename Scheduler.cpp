#include "Scheduler.hpp"

Scheduler::Scheduler() {}

Scheduler::Scheduler(std::vector<Process*> processes) : _processes(processes) {}

void Scheduler::exportData(const std::string& filename) {
    std::ofstream ofs(filename);

    for (int i = 0; i < _CPU.size(); ++i) {
        if (_CPU[i] == nullptr) {
            ofs << "_";
        } else {
            ofs << _CPU[i]->ID;
        }
        ofs << " ";
    }

    ofs << std::endl;

    for (int i = 0; i < _R.size(); ++i) {
        if (_R[i] == nullptr) {
            ofs << "_";
        } else {
            ofs << _R[i]->ID;
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