#include "string.hpp"

#include <iostream>

int main() {
    vertoker::string test1{};
    vertoker::string test2{"Hello in ASCII"};
    vertoker::string test3{test1}; // copy null
    vertoker::string test4{test2}; // copy

    std::cin.ignore();
    return 0;
}