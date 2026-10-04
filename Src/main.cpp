#include "PokemonApplication.hpp"

#include <exception>
#include <iostream>

// Program entry point: initializes the application and reports startup failures.
int main() {
    try {
        PokemonApplication application;
        return application.run();
    } catch (const std::exception& exception) {
        std::cerr << "Startup error: " << exception.what() << std::endl;
        return 1;
    }
}