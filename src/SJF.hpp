#ifndef SJF_HPP
#define SJF_HPP

#include "Scheduler.hpp"
#include "InputHandler.hpp"

class SJF : public Scheduler
{
public:
    SJF();
    SJF(InputHandler &input);

    void execute() override;

private:
    // function to arrange processes in ready queue
    void sortReadyQueue(std::vector<Process *> &readyQueue, int currentTime);
};

#endif