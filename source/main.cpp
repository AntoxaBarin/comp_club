#include <cstdlib>
#include <iostream>

#include "simulation.hpp"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <input-file>\n";
        return EXIT_FAILURE;
    }
    comp_club::simulate(argv[1]);
    return 0;
}
