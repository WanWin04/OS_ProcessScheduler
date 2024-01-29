#ifndef SRTN_HPP
#define SRTN_HPP

#include "Scheduler.hpp"
#include "InputHandler.hpp"

class SRTN : public Scheduler {
public:
    SRTN();
    SRTN(InputHandler &input);

    void execute() override;
};

#endif