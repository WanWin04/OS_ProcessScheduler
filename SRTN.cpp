#include "SRTN.hpp"

SRTN::SRTN() {}

SRTN::SRTN(InputHandler &input) : Scheduler(input.processes, input.timeQuantum) {}

// insertion sort
void SRTN::insertionSort(std::vector<Process *> &readyQueue, int currentTime)
{
    int n = readyQueue.size();
    for (int i = 1; i < n; ++i)
    {
        Process* key = readyQueue[i];
        int j = i - 1;

        while (j >= 0 && readyQueue[j]->CPUBurst[CPU_BURST_INDEX] >= key->CPUBurst[CPU_BURST_INDEX])
        {
            readyQueue[j + 1] = readyQueue[j];
            j = j - 1;
        }

        readyQueue[j + 1] = key;
    }
}

void SRTN::deleteProcess(std::vector<Process *> &processes, Process *process)
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

void printReadyQueue1(const std::vector<Process *> &readyQueue)
{
    std::cout << "Ready Queue Information:\n";

    for (int i = 0; i < readyQueue.size(); ++i)
    {
        std::cout << readyQueue[i]->ID << " - " << readyQueue[i]->CPUBurst[0] << std::endl;
    }
    std::cout << "-----------------------------------------\n";
}

void SRTN::execute()
{
    bool isPriority = false;
    std::vector<Process* > processes = _processes;

    std::sort(processes.begin(), processes.end(), [](Process *a, Process *b)
              { return a->arrivalTime < b->arrivalTime; });

    currentProcessOnCPU = nullptr;
    currentProcessOnR = nullptr;
    int currentTime = 0;

    while (!isTerminated(processes, _readyQueue, _blockedQueue))
    {
        if (!isPriority)
        {
            for (int i = 0; i < processes.size(); ++i)
            {
                if (processes[i]->arrivalTime == currentTime)
                {
                    processes[i]->startReadyQueue = currentTime;
                    _readyQueue.push_back(processes[i]);
                }
            }
        }
        else
        {
            isPriority = false;
        }

        insertionSort(_readyQueue, currentTime);

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
            if (!_readyQueue.empty() && currentProcessOnCPU->CPUBurst[0] >= _readyQueue.front()->CPUBurst[0])
            {
                currentProcessOnCPU->startReadyQueue = currentTime;
                _readyQueue.push_back(currentProcessOnCPU);
                currentProcessOnCPU = _readyQueue.front();
                _readyQueue.erase(_readyQueue.begin());
            }

            _CPU.push_back(currentProcessOnCPU);
            currentProcessOnCPU->CPUBurst.front()--;

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
            _CPU.push_back(&temp);
        }

        // execute on R
        if (currentProcessOnR != nullptr)
        {
            _R.push_back(currentProcessOnR);
            currentProcessOnR->resourceBurst.front()--;

            if (currentProcessOnR->resourceBurst[0] == 0)
            {
                currentProcessOnR->resourceBurst.erase(currentProcessOnR->resourceBurst.begin());

                if (currentProcessOnR->CPUBurst.size() != 0)
                {
                    for (int i = 0; i < processes.size(); ++i)
                    {
                        if (processes[i]->arrivalTime == (currentTime + 1))
                        {
                            processes[i]->startReadyQueue = currentTime + 1;
                            _readyQueue.push_back(processes[i]);
                        }
                    }
                    
                    currentProcessOnR->startReadyQueue = currentTime + 1;
                    _readyQueue.push_back(currentProcessOnR);

                    isPriority = true;
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
            _R.push_back(&temp);
        }

        ++currentTime;
    }
}
