#include "SJF.hpp"

SJF::SJF() : Scheduler() {}

SJF::SJF(InputHandler &input) : Scheduler(input.processes) {}

void SJF::execute() {
    int currentTime = 0;

    while (true) {
        // push process into queue
        while (!_processes.empty() && _processes.front()->arrivalTime == currentTime) {
            _readyQueue.push(_processes.front());
            _processes.erase(_processes.begin());
        }

        // CPU burst 
        int currentID = -INT_MAX;
        if (!_readyQueue.empty()) {
            // execute CPU burst
            Process* currentProcess = _readyQueue.top();

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
        } 
        else {
            _CPU.push_back(-1);
        }

        // resource burst
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
                    _readyQueue.push(currentProcess);
                }
                _blockedQueue.pop();
            }
        }
        else {
            _R.push_back(-1);
        }

        ++currentTime;

        if (_processes.empty() && _readyQueue.empty() && _blockedQueue.empty()) {
            break;
        }
    }
}