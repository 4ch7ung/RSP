#include <iostream>
#include <string>
#include <stdexcept>
#include "LogModule.h"
#include "LogAssembly.h"

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
    LogAssembly assembly = LogAssembly();
    LogModule* module;
    if (argc >= 2) {
        std::string xStr(argv[1]);
        double x;
        try {
            x = std::stod(xStr);
            module = assembly.createModule(&x);
        } catch (std::exception& exception) {
            delete module;
            return fatalError("Error parsing argument", exception);
        }
    } else {
        module = assembly.createModule();
    }

    try {
        module->run();
    } catch (std::exception& exception) {
        delete module;
        return fatalError("Error occured", exception);
    }
    delete module;
    return 0;
}
