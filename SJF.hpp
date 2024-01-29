#ifndef SJF_HPP
#define SJF_HPP

#include "Scheduler.hpp"
#include "InputHandler.hpp"

class SJF : public Scheduler {
public:
    SJF();
    SJF(InputHandler &input);

    void execute() override;
};

#endif