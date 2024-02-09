#include "SJF.hpp"

SJF::SJF() : Scheduler() {}

SJF::SJF(InputHandler &input) : Scheduler(input.processes) {}

// insertion sort
void SJF::insertionSort(std::vector<Process*>& readyQueue, int currentTime) {
    int n = readyQueue.size();
    for (int i = 2; i < n; ++i) {
        Process* key = readyQueue[i];
        int j = i - 1;

        while (j >= 0 && readyQueue[j]->CPUBurst[CPU_BURST_INDEX] > key->CPUBurst[CPU_BURST_INDEX]) {
            readyQueue[j + 1] = readyQueue[j];
            j = j - 1;
        }

        // Kiểm tra ưu tiên
        while (j >= 0 && readyQueue[j]->CPUBurst[CPU_BURST_INDEX] == key->CPUBurst[CPU_BURST_INDEX] && !readyQueue[j]->isPriority) {
            readyQueue[j + 1] = readyQueue[j];
            j = j - 1;
        }
        readyQueue[j + 1] = key;
    }
}

void printReadyQueue(const std::vector<Process*>& readyQueue) {
    std::cout << "Ready Queue Information:\n";
    std::cout << "-----------------------------------------\n";

    for (const auto& process : readyQueue) {
        std::cout << process->ID << " - " << process->CPUBurst[0] << std::endl;
        std::cout << "\n";
    }
}

void SJF::execute() {
    int currentTime = 0;
    std::vector<Process*> currentProcesses = _processes;

    // sort processes with increasing arrival time
    std::sort(currentProcesses.begin(), currentProcesses.end(), [](const Process* a, const Process* b) {
        return a->arrivalTime < b->arrivalTime;
    });

    while ( true ) {
        // push process into queue
        while (!currentProcesses.empty() && currentProcesses.front()->arrivalTime == currentTime) {
            _readyQueue.push_back(currentProcesses.front());
            currentProcesses.front()->isWaiting = true;
            currentProcesses.erase(currentProcesses.begin());
        }

        // sort priority
        insertionSort(_readyQueue, currentTime);

        printReadyQueue(_readyQueue);

        // CPU burst 
        int currentID = 0;
        if (!_readyQueue.empty()) {
            // execute CPU burst
            Process* currentProcess = _readyQueue.front();

            // calculate waiting time
            if (currentProcess->isWaiting) {
                currentProcess->waitingTime += (currentTime - currentProcess->startReadyQueue);
                currentProcess->isWaiting = false;
            }

            currentProcess->CPUBurst[CPU_BURST_INDEX]--;          
            currentID = currentProcess->ID;
            _CPU.push_back(currentProcess->ID);

            if (currentProcess->CPUBurst[CPU_BURST_INDEX] == 0) {
                currentProcess->CPUBurst.erase(currentProcess->CPUBurst.begin());

                if (!currentProcess->resourceBurst.empty()) {
                    _blockedQueue.push(currentProcess);
                }
                _readyQueue.erase(_readyQueue.begin());
            }

            // calculate turnaround time 
            if (currentProcess->resourceBurst.empty() && currentProcess->CPUBurst.empty()) {
                currentProcess->turnAroundTime = (currentTime + 1) - currentProcess->arrivalTime;
            }
        } 
        else {
            // CPU is free 
            _CPU.push_back(-1);
        }

        // resource burst
        if (!_blockedQueue.empty()) {
            Process* currentProcess = _blockedQueue.front();

            // process on ready queue or CPU 
            if (currentID == currentProcess->ID) {
                _R.push_back(-1);
                ++currentTime;
                continue;
            }
            
            currentProcess->resourceBurst[CPU_BURST_INDEX]--;
            _R.push_back(currentProcess->ID);

            if (currentProcess->resourceBurst[CPU_BURST_INDEX] == 0) {
                currentProcess->resourceBurst.erase(currentProcess->resourceBurst.begin());

                if (!currentProcess->CPUBurst.empty()) {
                    _readyQueue.push_back(currentProcess);
                    currentProcess->startReadyQueue = (currentTime + 1);
                    currentProcess->isPriority = false;
                    currentProcess->isWaiting = true;
                }
                _blockedQueue.pop();
            }

            // calculate turnaround time 
            if (currentProcess->resourceBurst.empty() && currentProcess->CPUBurst.empty()) {
                currentProcess->turnAroundTime = (currentTime + 1) - currentProcess->arrivalTime;
            }
        }
        else {
            // Resource is free 
            _R.push_back(-1);
        }

        ++currentTime;

        if (isTerminatedAll(currentProcesses, _readyQueue, _blockedQueue)) {
            break;
        }
    }
}