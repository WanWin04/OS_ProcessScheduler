#include "Scheduler.hpp"

Scheduler::Scheduler() {}

Scheduler::Scheduler(std::vector<Process *> processes, int timeQuantum) : _processes(processes), timeQuantum(timeQuantum) {}

void Scheduler::deleteProcess(std::vector<Process *> &processes, Process *process)
{
    for (int i = 0; i < processes.size(); i++)
    {
        if (processes[i]->ID == process->ID)
        {
            processes.erase(processes.begin() + i);
            break;
        }
    }
}

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

    std::string line;

    for (int i = 0; i < _R.size(); ++i)
    {
        if (_R[i]->ID == 0)
        {
            line += "_";
        }
        else
        {
            line += std::to_string(_R[i]->ID);
        }
        line += " ";
    }

    int index = 0;
    for (int i = line.size() - 1; i >= 0; --i)
    {
        if (line[i] != '_' && line[i] != ' ')
        {
            index = i;
            break;
        }
    }

    line.erase(index + 1);

    if (!line.empty())
    {
        ofs << line;
    }
    else
    {
        std::cerr << "R is empty!";
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