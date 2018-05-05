#include <iostream>
#include <string>
#include <stdexcept>
#include "Module.hpp"

int fatalError(const std::string& message) {
    std::cerr << message << std::endl;
    return 1;
}

int fatalError(const std::string& message, const std::exception& exception) {
    std::cerr << message << ": " << exception.what() << std::endl;
    return 1;
}

int main(int argc, const char ** argv)
{
    Module* module;
    if (argc < 2) {
        module = new LogModule();
    } else {
        std::string xStr(argv[1]);
        double x;
        try {
            x = std::stod(xStr);
        } catch (std::exception& exception) {
            return fatalError("Error parsing argument", exception);
        }
        module = new LogModule(x);
    }

    try {
        module->run();
    } catch (std::exception& exception) {
        return fatalError("Error occured", exception);
    }
    delete module;
    return 0;
}
