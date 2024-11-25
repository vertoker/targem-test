#include <iostream>
#include <utility> // для std::move

#include "string.hpp"

int main() {
    vertoker::string test0{};
    vertoker::string test1{"test1"};
    vertoker::string test2{"test2"};
    vertoker::string test3{test1}; // copy null
    vertoker::string test4{test2}; // copy
    vertoker::string test5{std::move(test2)}; // move

    //vertoker::string operator1 = test1 + test2; // test1test2

    //std::cin.ignore();
    return 0;
}