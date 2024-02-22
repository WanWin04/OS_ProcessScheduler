#include "SRTN.hpp"

SRTN::SRTN() {}

SRTN::SRTN(InputHandler &input) : Scheduler(input.processes, input.timeQuantum) {}

// insertion sort
void SRTN::sortReadyQueue(std::vector<Process *> &readyQueue, int currentTime)
{
    int n = readyQueue.size();
    for (int i = 1; i < n; ++i)
    {
        Process *key = readyQueue[i];
        int j = i - 1;

        while (j >= 0 && readyQueue[j]->CPUBurst[BURST_INDEX] > key->CPUBurst[BURST_INDEX])
        {
            readyQueue[j + 1] = readyQueue[j];
            j = j - 1;
        }

        readyQueue[j + 1] = key;
    }
}

void printReadyQueue(const std::vector<Process *> &readyQueue)
{
    std::cout << "Ready Queue Information:\n";

    for (const auto &process : readyQueue)
    {
        std::cout << process->ID << " - ";
        std::cout << process->CPUBurst.front() << std::endl;
    }

    std::cout << "-----------------------------------------\n";
}

void SRTN::execute()
{
    std::vector<Process *> tempReadyQueue;
    std::vector<Process *> processes = _processes;

    // sort processes by arrival time
    std::sort(processes.begin(), processes.end(), [](Process *a, Process *b)
              { return a->arrivalTime < b->arrivalTime; });

    int currentTime = 0;
    bool isPriority = true;

    while (!isTerminated(processes, _readyQueue, _blockedQueue))
    {
        for (int i = 0; i < processes.size(); ++i)
        {
            if (processes[i]->arrivalTime == currentTime)
            {
                tempReadyQueue.push_back(processes[i]);
            }
        }

        std::reverse(tempReadyQueue.begin(), tempReadyQueue.end());
        for (int i = 0; i < tempReadyQueue.size(); ++i)
        {
            _readyQueue.push_back(tempReadyQueue[i]);
        }
        tempReadyQueue.clear();

        // special case
        if (_readyQueue.size() == 2 && _readyQueue.front()->CPUBurst[BURST_INDEX] == _readyQueue.back()->CPUBurst[BURST_INDEX])
        {
            if ((_readyQueue.front()->backCPU == true && _readyQueue.back()->backCPU == false) || (_readyQueue.front()->backCPU == false && _readyQueue.back()->backCPU == true))
            {
                if (_readyQueue.front()->backCPU == true)
                {
                    _readyQueue.front()->isPrevent = true;
                }
                else
                {
                    _readyQueue.back()->isPrevent = true;
                }
            }
        }

        // sort readyQueue
        sortReadyQueue(_readyQueue, currentTime);

        // get process from readyQueue
        if (currentProcessOnCPU == nullptr && _readyQueue.size() != 0)
        {
            currentProcessOnCPU = _readyQueue.front();
            _readyQueue.erase(_readyQueue.begin());

            // calculate waiting time
            currentProcessOnCPU->waitingTime += currentTime - currentProcessOnCPU->startReadyQueue;
        }

        // get process from blockQueue
        if (currentProcessOnR == nullptr && _blockedQueue.size() != 0)
        {
            currentProcessOnR = _blockedQueue.front();
            _blockedQueue.erase(_blockedQueue.begin());
        }

        // execute on CPU
        if (currentProcessOnCPU != nullptr)
        {
            if ((!_readyQueue.empty() && currentProcessOnCPU->CPUBurst[BURST_INDEX] >= _readyQueue.front()->CPUBurst[BURST_INDEX]) && (currentProcessOnCPU->isPrevent == false && _readyQueue.front()->isPrevent == false))
            {
                currentProcessOnCPU->startReadyQueue = currentTime;
                tempReadyQueue.push_back(currentProcessOnCPU);
                currentProcessOnCPU = _readyQueue.front();
                _readyQueue.erase(_readyQueue.begin());

                // calculate waiting time
                currentProcessOnCPU->waitingTime += currentTime - currentProcessOnCPU->startReadyQueue;
            }

            _CPU.push_back(currentProcessOnCPU);
            currentProcessOnCPU->CPUBurst.front()--;

            if (currentProcessOnCPU->CPUBurst[BURST_INDEX] == 0)
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
                    // calculate turn around time
                    currentProcessOnCPU->turnAroundTime = (currentTime + 1) - currentProcessOnCPU->arrivalTime;

                    if (currentProcessOnCPU->CPUBurst.size() == 0)
                    {
                        // delete process from the list processes
                        deleteProcess(processes, currentProcessOnCPU);
                    }
                }
                currentProcessOnCPU = nullptr;
            }
        }
        else
        {
            // CPU is empty
            _CPU.push_back(&temp);
        }

        // execute on R
        if (currentProcessOnR != nullptr)
        {
            _R.push_back(currentProcessOnR);
            currentProcessOnR->resourceBurst.front()--;

            if (currentProcessOnR->resourceBurst[BURST_INDEX] == 0)
            {
                currentProcessOnR->resourceBurst.erase(currentProcessOnR->resourceBurst.begin());

                if (currentProcessOnR->CPUBurst.size() != 0)
                {
                    currentProcessOnR->startReadyQueue = currentTime + 1;
                    currentProcessOnR->backCPU = true;

                    tempReadyQueue.push_back(currentProcessOnR);
                }
                else
                {
                    // calculate turn around time
                    currentProcessOnR->turnAroundTime = (currentTime + 1) - currentProcessOnR->arrivalTime;

                    if (currentProcessOnR->resourceBurst.size() == 0)
                    {
                        // delete process from the list processes
                        deleteProcess(processes, currentProcessOnR);
                    }
                }
                currentProcessOnR = nullptr;
            }
        }
        else
        {
            // R is empty
            _R.push_back(&temp);
        }

        ++currentTime;
    }
}