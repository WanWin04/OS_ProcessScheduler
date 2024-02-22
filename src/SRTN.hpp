#ifndef SRTN_HPP
#define SRTN_HPP

#include <algorithm>

#include "Scheduler.hpp"
#include "InputHandler.hpp"

class SRTN : public Scheduler
{
public:
    SRTN();
    SRTN(InputHandler &input);

    void execute() override;

private:
    // function to arrange processes in ready queue
    void sortReadyQueue(std::vector<Process *> &readyQueue, int currentTime);
};

#endif