#include <iostream>
#include <string>
#include <stdexcept>
#include "math_functions.h"

int main(int argc, const char ** argv)
{
    if (argc < 2) {
        std::cout << "Expected 1 argument of type double" << std::endl;
        return 0;
    }

    std::string xStr(argv[1]);
    double x = std::stod(xStr);

    try {
        double lnx = ln(x);

        std::cout << "Ln(x) = ";
        std::cout.precision(8);
        std::cout << lnx << std::endl;
    } catch (std::exception& exception) {
        std::cout << "Error occured: " << exception.what() << std::endl;
        return 1;
    }
    return 0;
}
