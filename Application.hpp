#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "InputHandler.hpp"
#include "SJF.hpp"
#include "SRTN.hpp"

#include <iostream>

class Application {
public:
    Application();

    void run(char* source, char* destination);
};

#endif