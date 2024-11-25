#include <iostream>
#include <utility> // для std::move

#include "vertoker_string.h"

int main() {
    vertoker::string test0{};

    vertoker::string test1{"data1"};
    vertoker::string test2{"data2"};
    vertoker::string test3{test0}; // copy null
    vertoker::string test4{test2}; // copy
    vertoker::string test5{std::move(test2)}; // move

    vertoker::string operator1 = test1 + test5; // data1data2
    vertoker::string operator2 = test1 + "test3"; // data1data3
    vertoker::string operator3 = "data3" + test1; // data3data1
    vertoker::string operator4 = operator1; // data1data2
    operator4 += "data3"; // data1data2data3
    std::cout << operator4 << std::endl;

    //std::cin.ignore();
    return 0;
}