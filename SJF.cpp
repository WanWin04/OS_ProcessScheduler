#include "SJF.hpp"

SJF::SJF() : Scheduler() {}

SJF::SJF(InputHandler &input) : Scheduler(input.processes) {}

void SJF::execute() {
    int currentTime = 0;
    std::vector<Process*> currentProcesses = _processes;

    while ( true ) {
        // push process into queue
        while (!currentProcesses.empty() && currentProcesses.front()->arrivalTime == currentTime) {
            _readyQueue.push(currentProcesses.front());
            currentProcesses.front()->isWaiting = true;
            currentProcesses.erase(currentProcesses.begin());
        }

        // CPU burst 
        int currentID = -INT_MAX;
        if (!_readyQueue.empty()) {
            // execute CPU burst
            Process* currentProcess = _readyQueue.top();

            // calculate waiting time
            if (currentProcess->isWaiting) {
                currentProcess->waitingTime += (currentTime - currentProcess->startReadyQueue);
                currentProcess->isWaiting = false;
            }

            currentProcess->CPUBurst[0]--;
            currentID = currentProcess->ID;
            _CPU.push_back(currentProcess->ID);

            if (currentProcess->CPUBurst[0] == 0) {
                currentProcess->CPUBurst.erase(currentProcess->CPUBurst.begin());

                if (!currentProcess->resourceBurst.empty()) {
                    _blockedQueue.push(currentProcess);
                }
                _readyQueue.pop();
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
            
            currentProcess->resourceBurst[0]--;
            _R.push_back(currentProcess->ID);

            if (currentProcess->resourceBurst[0] == 0) {
                currentProcess->resourceBurst.erase(currentProcess->resourceBurst.begin());

                if (!currentProcess->CPUBurst.empty()) {
                    _readyQueue.push(currentProcess);
                    currentProcess->startReadyQueue = (currentTime + 1);
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

        if (currentProcesses.empty() && _readyQueue.empty() && _blockedQueue.empty()) {
            break;
        }
    }
}