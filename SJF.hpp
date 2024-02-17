#ifndef SJF_HPP
#define SJF_HPP

#include "Scheduler.hpp"
#include "InputHandler.hpp"

class SJF : public Scheduler {
public:
    SJF();
    SJF(InputHandler &input);

    void execute() override;

private:
    Process* currentProcessOnCPU;
    Process* currentProcessOnR;

    void deleteProcess(std::vector<Process *> &processes, Process *process);

    void insertionSort(std::vector<Process*>& readyQueue, int currentTime);
};

#endif