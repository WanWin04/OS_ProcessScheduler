#ifndef _RR_HPP
#define _RR_HPP
#include "Scheduler.hpp"
#include "InputHandler.hpp"

class RR : public Scheduler
{
public:
    RR();
    RR(InputHandler &input);
    void execute() override;
};
#endif