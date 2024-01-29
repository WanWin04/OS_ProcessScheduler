#include "SRTN.hpp"

SRTN::SRTN() {}

SRTN::SRTN(InputHandler &input) : Scheduler(input.processes) {}

void SRTN::execute() {
    int currentTime = 0;
    std::vector<Process*> tempProcesses = _processes;

    while ( true ) {
        
    }
}