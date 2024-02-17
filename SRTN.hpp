#ifndef SRTN_HPP
#define SRTN_HPP

#include <algorithm>

#include "Scheduler.hpp"
#include "InputHandler.hpp"

class SRTN : public Scheduler {
public:
    SRTN();
    SRTN(InputHandler &input);

    void execute() override;

private:
    Process* currentProcessOnCPU;
    Process* currentProcessOnR;

    void deleteProcess(std::vector<Process *> &processes, Process *process);

    void insertionSort(std::vector<Process*>& readyQueue, int currentTime);
};

#endif