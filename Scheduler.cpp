#include "Scheduler.hpp"

Scheduler::Scheduler() {}

Scheduler::Scheduler(std::vector<Process *> processes, int timeQuantum) : _processes(processes), timeQuantum(timeQuantum) {}

void Scheduler::exportData(const std::string &filename)
{
    std::ofstream ofs(filename);

    for (int i = 0; i < _CPU.size(); ++i)
    {
        if (_CPU[i]->ID == 0)
        {
            ofs << "_";
        }
        else
        {
            ofs << _CPU[i]->ID;
        }
        ofs << " ";
    }

    ofs << std::endl;

    for (int i = 0; i < _R.size(); ++i)
    {
        if (_R[i]->ID == 0)
        {
            ofs << "_";
        }
        else
        {
            ofs << _R[i]->ID;
        }
        ofs << " ";
    }

    ofs << std::endl;

    for (int i = 0; i < _processes.size(); ++i)
    {
        ofs << _processes[i]->turnAroundTime << " ";
    }

    ofs << std::endl;

    for (int i = 0; i < _processes.size(); ++i)
    {
        ofs << _processes[i]->waitingTime << " ";
    }

    ofs.close();
}

bool Scheduler::isTerminated(std::vector<Process *> processes, std::vector<Process *> readyQueue, std::vector<Process *> blockedQueue)
{
    return (processes.size() == 0 && readyQueue.size() == 0 && blockedQueue.size() == 0);
}