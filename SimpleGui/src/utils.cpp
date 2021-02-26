#include "utils.h"
#include <iostream>
#include <cstdarg>

void Debug(std::string str,std::string info)
{
    #ifdef DEBUG
        std::cout << str << " " << info << std::endl;
    #endif // DEBUG
}