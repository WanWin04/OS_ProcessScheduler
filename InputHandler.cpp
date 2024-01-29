#include "InputHandler.hpp"

InputHandler::InputHandler() {}

InputHandler::InputHandler(const std::string& filename) {
    readInput(filename);
}

Process* InputHandler::readOneLine(std::string line, int id) {
    std::stringstream ss(line);
    int arrTime;
    ss >> arrTime;
    Process* process = new Process();
    process->ID = id;
    process->arrivalTime = arrTime;
    process->startReadyQueue = arrTime;

    int temp;
    int index = 0;
    while (ss >> temp) {
        if (index % 2 == 0) {
            process->CPUBurst.push_back(temp);
        } else {
            process->resourceBurst.push_back(temp);
        }
        
        ++index;
    }
    return process;
}

void InputHandler::readInput(const std::string& filename) {
    std::ifstream is(filename);
    if (!is.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }
    
    int numProcess;
    
    is >> algorithmID;

    if (algorithmID == 2) {
        is >> timeQuantum;
    }
    
    is >> numProcess;

    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    int id = 1;
    while (numProcess) {
        std::string line;
        if (!std::getline(is, line)) {
            std::cerr << "Error: Invalid format in input file." << std::endl;
            return;
        }

        // read each line data process 
        Process* process = readOneLine(line, id++);

        processes.push_back(process);
        --numProcess;
    }

    is.close();
}
