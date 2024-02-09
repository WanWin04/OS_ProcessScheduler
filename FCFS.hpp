#ifndef _FCFS_HPP
#define _FCFS_HPP
#include "Scheduler.hpp"
#include "InputHandler.hpp"

class FCFS : public Scheduler
{
private:
    Process *currentProcessOnCPU;
    Process *currentProcessOnR;
    
public:
    FCFS() {}
    FCFS(InputHandler &input) : Scheduler(input.processes) {}
    void execute() override
    {
        Process temp;
        std::vector<Process *> processes = _processes;
        std::sort(processes.begin(), processes.end(), [](Process *a, Process *b)
                  { return a->arrivalTime < b->arrivalTime; });
        currentProcessOnCPU = nullptr;
        currentProcessOnR = nullptr;
        int currentTime = 0;

        while (!isTerminated(processes, _readyQueue, _blockedQueue))
        {
            std::cout << "aaa";
            if (_readyQueue.size() == 0)
            {
                for (int i = 0; i < processes.size(); i++)
                {
                    if (processes[i]->arrivalTime == currentTime)
                    {
                        _readyQueue.push_back(processes[i]);
                    }
                    else if (processes[i]->arrivalTime > currentTime)
                    {
                        break;
                    }
                }
            }
            if (currentProcessOnCPU == nullptr && _readyQueue.size() != 0)
            {
                currentProcessOnCPU = _readyQueue.front();
                _readyQueue.erase(_readyQueue.begin());
                currentProcessOnCPU->waitingTime += currentTime - currentProcessOnCPU->startReadyQueue;
            }

            if (currentProcessOnR == nullptr && _blockedQueue.size() != 0)
            {
                currentProcessOnR = _blockedQueue.front();
                _blockedQueue.erase(_blockedQueue.begin());
            }

            if (currentProcessOnCPU != nullptr)
            {
                _CPU.push_back(currentProcessOnCPU);
                currentProcessOnCPU->run();

                if (currentProcessOnCPU->CPUBurst[0] == 0)
                {
                    // remove CPU burst done
                    currentProcessOnCPU->CPUBurst.erase(currentProcessOnCPU->CPUBurst.begin());
                    // if process has resource burst
                    if (currentProcessOnCPU->resourceBurst.size() != 0)
                    {
                        _blockedQueue.push_back(currentProcessOnCPU);
                    }
                    else
                    {
                        currentProcessOnCPU->turnAroundTime = currentTime + 1 - currentProcessOnCPU->arrivalTime;
                        if (currentProcessOnCPU->CPUBurst.size() == 0)
                        {
                            // delete process from the list processes
                            for (int i = 0; i < processes.size(); i++)
                            {
                                if (processes[i]->ID == currentProcessOnCPU->ID)
                                {
                                    processes.erase(processes.begin() + i);
                                    break;
                                }
                            }
                        }
                    }
                    currentProcessOnCPU = nullptr;
                }
            }
            else
            {
                _CPU.push_back(&temp);
            }

            if (currentProcessOnR != nullptr)
            {
                _blockedQueue.push_back(currentProcessOnR);
                currentProcessOnR->run();
                if (currentProcessOnR->resourceBurst[0] == 0)
                {
                    currentProcessOnR->resourceBurst.erase(currentProcessOnR->resourceBurst.begin());

                    if (currentProcessOnR->CPUBurst.size() != 0)
                    {
                        for (int i = 0; i < processes.size(); i++)
                        {
                            if (processes[i]->arrivalTime == currentTime + 1)
                            {
                                _readyQueue.push_back(processes[i]);
                            }
                            else if (processes[i]->arrivalTime > currentTime + 1)
                            {
                                break;
                            }
                        }
                        _readyQueue.push_back(currentProcessOnR);
                        currentProcessOnR->startReadyQueue = currentTime + 1;
                    }
                    else
                    {
                        currentProcessOnR->turnAroundTime = currentTime + 1 - currentProcessOnR->arrivalTime;
                        if (currentProcessOnR->resourceBurst.size() == 0)
                        {
                            // delete process from the list processes
                            for (int i = 0; i < processes.size(); i++)
                            {
                                if (processes[i]->ID == currentProcessOnR->ID)
                                {
                                    processes.erase(processes.begin() + i);
                                    break;
                                }
                            }
                        }
                    }
                    currentProcessOnR = nullptr;
                }
            }
            else
            {
                _R.push_back(&temp);
            }

            currentTime++;
        }
    }
};

#endif