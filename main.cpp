#include <utility> // для std::move
#include <cctype> // для std::tolower
#include <iostream>
#include <vector>

#include "vertoker_string.h"

bool backAlphabetComparer(const vertoker::string& a, const vertoker::string& b) {
    if (a.data() == nullptr || b.data() == nullptr) return false;

    auto aLength = a.length();
    auto bLength = b.length();
    auto lengthCompare = aLength < bLength;
    auto length = lengthCompare ? aLength : bLength;

    // честно, возможно я некорретно понял условие сортировки, но вот моё решение
    for (auto i = 1; i <= length; i++)
    {
        auto letterA = std::tolower(a.at(aLength - i));
        auto letterB = std::tolower(b.at(bLength - i));
        if (letterA != letterB)
            return letterA > letterB;
    }
    return lengthCompare;
}

// Я изначально подумал использовать std::sort, но потом решил сам написать сортировку
// Можно было бы сделать просто bubbleSort, но я подумал, чтобы выпендриться, здесь будет mergeSort

template<typename T>
void merge(std::vector<T>& array, bool(*comparer)(const T& a, const T& b), 
    std::vector<T>& leftArray, std::vector<T>& rightArray, size_t start, size_t center, size_t end) {
    
    size_t leftSize = center - start + 1;
    size_t rightSize = end - center;

    // Ещё я везде использую std::move чтобы минимизировать копирования
    // Они всё ещё происходят, но уже лучше

    // Заполняем temp массивы данными массива
    for (auto i = 0; i < leftSize; i++)
        leftArray.emplace_back(std::move(array[start + i]));
    for (auto j = 0; j < rightSize; j++)
        rightArray.emplace_back(std::move(array[center + 1 + j]));

    size_t leftCounter = 0, rightCounter = 0;
    size_t arrayCounter = start;

    // Основная сортировка
    while (leftCounter < leftSize && rightCounter < rightSize) {
        if (comparer(leftArray[leftCounter], rightArray[rightCounter])) {
            array[arrayCounter] = std::move(leftArray[leftCounter]);
            leftCounter++;
        }
        else {
            array[arrayCounter] = std::move(rightArray[rightCounter]);
            rightCounter++;
        }
        arrayCounter++;
    }

    // Копирование оставшихся элементов в array (если осталось что-то)
    while (leftCounter < leftSize) {
        array[arrayCounter] = std::move(leftArray[leftCounter]);
        leftCounter++;
        arrayCounter++;
    }
    while (rightCounter < rightSize) {
        array[arrayCounter] = std::move(rightArray[rightCounter]);
        rightCounter++;
        arrayCounter++;
    }

    leftArray.clear();
    rightArray.clear();
}
template<typename T>
void divide(std::vector<T>& array, bool(*comparer)(const T& a, const T& b), 
    std::vector<T>& leftArray, std::vector<T>& rightArray, size_t start, size_t end) {
    
    if (start >= end) return;

    size_t center = start + (end - start) / 2;
    divide(array, comparer, leftArray, rightArray, start, center);
    divide(array, comparer, leftArray, rightArray, center + 1, end);

    merge(array, comparer, leftArray, rightArray, start, center, end);
}

template<typename T>
void mergeSort(std::vector<T>& array, bool(*comparer)(const T& a, const T& b), size_t tempArraysCapacity = 4) {
    std::vector<T> leftArray;
    std::vector<T> rightArray;
    // стандартный capacity я выбрал случайно, думаю тут есть место для оптимизации
    leftArray.reserve(tempArraysCapacity);
    rightArray.reserve(tempArraysCapacity);

    divide(array, comparer, leftArray, rightArray, 0, array.size() - 1);
}

int main() {
    // Общие тесты
    vertoker::string test0{};

    vertoker::string test1{"data1"};
    vertoker::string test2{"data2"};
    vertoker::string test3{test0}; // copy null
    vertoker::string test4{test2}; // copy
    vertoker::string test5{std::move(test2)}; // move

    vertoker::string operator1 = test1 + test5; // data1data2
    vertoker::string operator2 = test1 + "data3"; // data1data3
    vertoker::string operator3 = "data3" + test1; // data3data1
    vertoker::string operator4 = operator1; // data1data2
    operator4 += "data3"; // data1data2data3
    //std::cout << operator4 << std::endl;

    // Обратная сортировка
    size_t length;
    size_t max_size = 10; // стандартный размер строки
    std::cout << "Enter strings count: ";
    std::cin >> length;

    std::vector<vertoker::string> strings{};
    strings.reserve(length);

    for (size_t i = 0; i < length; i++)
    {
        strings.emplace_back(max_size);
        std::cout << "Enter " << i+1 << " string: ";
        std::cin >> strings[i];
    }

    std::cout << "\nSource container";
    for (size_t i = 0; i < length; i++)
        std::cout << " : " << strings[i];
    std::cout << '\n';
    
    std::cout << "\nMake back alphabet merge sort\n";
    mergeSort(strings, backAlphabetComparer);

    std::cout << "\nSorted container";
    for (size_t i = 0; i < length; i++)
        std::cout << " : " << strings[i];
    std::cout << '\n';
    std::cin.ignore();

    return 0;
}