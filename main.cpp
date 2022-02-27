#include <iostream>
#include <memory>
#include "shared_ptr.h"

int main(int, char**)
{
    shared_ptr<std::string> test(new std::string("Hello, world!"));
    std::cout << *test << std::endl;
}
