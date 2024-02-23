#ifndef _FCFS_HPP
#define _FCFS_HPP
#include "Scheduler.hpp"
#include "InputHandler.hpp"

class FCFS : public Scheduler
{
public:
    FCFS();
    FCFS(InputHandler &input);
    void execute() override;
};

#endif