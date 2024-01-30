#include "SRTN.hpp"

SRTN::SRTN() {}

SRTN::SRTN(InputHandler &input) : Scheduler(input.processes) {}

void SRTN::execute() {
    int currentTime = 0;
    std::vector<Process*> currentProcesses = _processes;

    std::sort(currentProcesses.begin(), currentProcesses.end(), [](const Process* a, const Process* b) {
        return a->arrivalTime < b->arrivalTime;
    });

    while ( true ) {
        while (!currentProcesses.empty() && currentProcesses.front()->arrivalTime == currentTime) {
            _readyQueueD.push(currentProcesses.front());
            currentProcesses.erase(currentProcesses.begin());
        }

        int currentID = 0;
        if (!_readyQueueD.empty()) {
            Process* currentProcess = _readyQueueD.top();

            currentProcess->CPUBurst[0]--;
            currentID = currentProcess->ID;
            _CPU.push_back(currentProcess->ID);

            if (currentProcess->CPUBurst[0] == 0) {
                currentProcess->CPUBurst.erase(currentProcess->CPUBurst.begin());

                if (!currentProcess->resourceBurst.empty()) {
                    _blockedQueue.push(currentProcess);
                }
                _readyQueueD.pop();
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

            currentProcess->resourceBurst[0]--;
            _R.push_back(currentProcess->ID);

            if (currentProcess->resourceBurst[0] == 0) {
                currentProcess->resourceBurst.erase(currentProcess->resourceBurst.begin());

                if (!currentProcess->CPUBurst.empty()) {
                    _readyQueueD.push(currentProcess);
                }
                _blockedQueue.pop();
            }
        }
        else {
            _R.push_back(-1);
        }

        ++currentTime;

        if (currentProcesses.empty() && _readyQueueD.empty() && _blockedQueue.empty()) {
            break;
        }
    }
}