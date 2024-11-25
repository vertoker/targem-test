#include <iostream>
#include <utility> // для std::move

#include "string.hpp"

int main() {
    vertoker::string test1{};
    vertoker::string test2{"Hello in ASCII"};
    vertoker::string test3{test1}; // copy null
    vertoker::string test4{test2}; // copy
    vertoker::string test5{std::move(test2)}; // move

    //std::cin.ignore();
    return 0;
}