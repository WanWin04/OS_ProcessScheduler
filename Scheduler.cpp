#include "Scheduler.hpp"

Scheduler::Scheduler() {}

Scheduler::Scheduler(std::vector<Process*> processes) : _processes(processes) {}

void Scheduler::exportData(const std::string& filename) {
    std::ofstream os(filename);

    for (int i = 0; i < _CPU.size(); ++i) {
        if (_CPU[i] == -1) {
            os << "_";;
        } else {
            os << _CPU[i];
        }
        os << " ";
    }

    os << std::endl;

    for (int i = 0; i < _R.size(); ++i) {
        if (_R[i] == -1) {
            os << "_";
        } else {
            os << _R[i];
        }
        os << " ";
    }

    os << std::endl;

    for (int i = 0; i < _processes.size(); ++i) {
        os << _processes[i]->turnAroundTime << " ";
    }

    os << std::endl;
    
    for (int i = 0; i < _processes.size(); ++i) {
        os << _processes[i]->waitingTime << " ";
    }

    os.close();
}

