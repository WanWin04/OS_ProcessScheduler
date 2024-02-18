#include "InputHandler.hpp"

InputHandler::InputHandler() {}

InputHandler::InputHandler(const std::string &filename)
{
    readInput(filename);
}

void InputHandler::readInput(const std::string &filename)
{
    std::ifstream ifs(filename);
    if (!ifs.is_open())
    {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }

    int numProcess;

    ifs >> algorithmID;

    if (algorithmID == 2)
    {
        ifs >> timeQuantum;
    }

    ifs >> numProcess;

    ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    int id = 1;
    while (numProcess)
    {
        std::string line;
        if (!std::getline(ifs, line))
        {
            std::cerr << "Error: Invalid format in input file." << std::endl;
            return;
        }

        // read each line data process
        std::stringstream ss(line);
        int arrTime;
        ss >> arrTime;
        Process *process = new Process();
        process->ID = id++;
        process->arrivalTime = arrTime;
        process->startReadyQueue = arrTime;

        int temp;
        int index = 0;
        while (ss >> temp)
        {
            if (index % 2 == 0)
            {
                process->CPUBurst.push_back(temp);
            }
            else
            {
                process->resourceBurst.push_back(temp);
            }

            ++index;
        }

        processes.push_back(process);
        --numProcess;
    }

    ifs.close();
}

InputHandler::~InputHandler()
{
    for (int i = 0; i < processes.size(); ++i)
    {
        delete processes[i];
    }
}
