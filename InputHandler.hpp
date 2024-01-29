#ifndef INPUT_HPP
#define INPUT_HPP

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>

#include "Process.hpp"

class InputHandler {
public:
    int algorithmID;
    int timeQuantum; // time quantum for Round Robin algorithm
    std::vector<Process*> processes;

    InputHandler();
    InputHandler(const std::string& filename);

    void readInput(const std::string& filename);
    Process* readOneLine(std::string line, int id);
};

#endif