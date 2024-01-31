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
    void insertionSort(std::vector<Process*>& readyQueue);
};

#endif