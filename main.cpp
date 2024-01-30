#include "SJF.hpp"
#include "SRTN.hpp"
#include "InputHandler.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <INPUT_FILE> <OUTPUT_FILE>" << std::endl;
        return 1;
    }
    
    InputHandler input(argv[1]);
    
    int algorithmID = input.algorithmID;

    Scheduler* scheduler = nullptr;

    switch (algorithmID) {
    case 1:
        
        break;
    case 2:
        
        break;
    case 3:
        scheduler = new SJF(input);
        break;
    case 4:
        scheduler = new SRTN(input);
        break;
    default:
        std::cerr << "Unknown algorithm ID." << std::endl;
        return 1;
    }

    if (scheduler) {
        scheduler->execute();
        scheduler->exportData(argv[2]);
        std::cout << "Build Successfully!" << std::endl;
        delete scheduler;
    }

    return EXIT_SUCCESS;
}
