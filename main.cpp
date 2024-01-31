#include "Application.hpp"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <INPUT_FILE> <OUTPUT_FILE>" << std::endl;
        return EXIT_FAILURE;
    }
    
    Application app;
    app.run(argv[1], argv[2]);

    return EXIT_SUCCESS;
}
