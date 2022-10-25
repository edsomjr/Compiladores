#include <iostream>
#include "error.h"

void erro(const std::string& message)
{
    std::cerr << message << '\n';
    exit(-1);
}
