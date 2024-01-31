#include "SRTN.hpp"

SRTN::SRTN() {}

SRTN::SRTN(InputHandler &input) : Scheduler(input.processes) {}

void SRTN::execute() {
    int currentTime = 0;
    std::vector<Process*> currentProcesses = _processes;

    // sort processes with increasing arrival time
    std::sort(currentProcesses.begin(), currentProcesses.end(), [](const Process* a, const Process* b) {
        return a->arrivalTime < b->arrivalTime;
    });

    while ( true ) {
        while (!currentProcesses.empty() && currentProcesses.front()->arrivalTime == currentTime) {
            // _readyQueueD.push(currentProcesses.front());
            _readyQueue.push_back(currentProcesses.front());
            currentProcesses.erase(currentProcesses.begin());
        }

        std::sort(_readyQueue.begin(), _readyQueue.end(), [](const Process* a, const Process* b) {
            return a->CPUBurst[CPU_BURST_INDEX] >= b->CPUBurst[CPU_BURST_INDEX];
        });

        int currentID = 0;
        if (!_readyQueue.empty()) {
            // Process* currentProcess = _readyQueueD.top();
            Process* currentProcess = _readyQueue.front();

            currentProcess->CPUBurst[CPU_BURST_INDEX]--;
            currentID = currentProcess->ID;
            _CPU.push_back(currentProcess->ID);

            if (currentProcess->CPUBurst[CPU_BURST_INDEX] == 0) {
                currentProcess->CPUBurst.erase(currentProcess->CPUBurst.begin());

                if (!currentProcess->resourceBurst.empty()) {
                    _blockedQueue.push(currentProcess);
                }
                // _readyQueueD.pop();
                _readyQueue.erase(_readyQueue.begin());
            }
        }
        else {
            _CPU.push_back(-1);
        }

        if (!_blockedQueue.empty()) {
            Process* currentProcess = _blockedQueue.front();

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
                    // _readyQueueD.push(currentProcess);
                    _readyQueue.push_back(currentProcess);
                }
                _blockedQueue.pop();
            }
        }
        else {
            _R.push_back(-1);
        }

        ++currentTime;

        // if (currentProcesses.empty() && _readyQueueD.empty() && _blockedQueue.empty()) {
        //     break;
        // }

        if (currentProcesses.empty() && _readyQueue.empty() && _blockedQueue.empty()) {
            break;
        }
    }
}