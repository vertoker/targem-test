#pragma once
#include <stdint.h>
#include <malloc.h>
#include <string.h>

#include <assert.h>
#include <stdio.h>

#include <iostream> // нужна только для переопределения оператора << для ostream

// тупой способ тестирования работоспособности строки через макросы
#define USE_TEST_LOG 0

namespace vertoker { // ну раз это моя реализация, значит и namespace будет мой
class string {
private:
    #define TEST_LOG(str) USE_TEST_LOG ? printf(str) : 0;

public: // constructors and destructors
    string() : ptr{nullptr} { 
        TEST_LOG("Null constructor\n");
    }
    string(const char* str) { // create
        if (str == nullptr) {
            TEST_LOG("Create constructor null\n");
            ptr = nullptr;
        }
        else {
            TEST_LOG("Create constructor\n");
            copy(str);
        }
    }
    string(const string& other) { // copy
        if (other.ptr == nullptr) {
            TEST_LOG("Copy constructor null\n");
            ptr = nullptr;
        }
        else {
            TEST_LOG("Copy constructor\n");
            copy(other.ptr);
        }
    }
    string(string&& other) { // move
        TEST_LOG("Move constructor\n");
        ptr = other.ptr;
        other.ptr = nullptr;
    }
    
    string(const char* str1, const char* str2) { // merge
        if (str1 == nullptr || *str1 == '\0') {
            TEST_LOG("+ constructor other empty\n");
            return;
        }
        else if (str2 == nullptr || *str2 == '\n') {
            TEST_LOG("+ constructor other copy\n");
            return;
        }
        else {
            TEST_LOG("+ constructor\n");
            merge(str1, str2);
        }
    }

    string(const string& a, const string& b) // merge 2
        : string{a.c_ptr(), b.c_ptr()} { } 

    ~string() {
        TEST_LOG("Free deconstructor\n");
        free(ptr);
    }

public: // operators

    void operator+=(const char* str) {
        if (str == nullptr || *str == '\0') {
            TEST_LOG("Operator += other empty\n");
            return;
        }
        else if (ptr == nullptr || *ptr == '\n') {
            TEST_LOG("Operator += other copy\n");
            copy(str);
        }
        else {
            TEST_LOG("Operator +=\n");
            append(str);
        }
    }
    void operator+=(const string& other) {
        this->operator+=(other.ptr);
    }

public: // other
    char* c_ptr() const { return ptr; }

private:
    void copy(const char* dst) noexcept {
        size_t length = strlen(dst);
        ptr = (char*)malloc(length + 1);

        strcpy(ptr, dst);
        ptr[length] = '\0';
    }
    void append(const char* dst) noexcept {
        size_t length1 = strlen(ptr);
        size_t length = length1 + strlen(dst);

        char* ptr1 = (char*)malloc(length + 1);
        char* ptr2 = ptr1 + length1;

        strcpy(ptr1, ptr);
        strcpy(ptr2, dst);
        ptr1[length] = '\0';

        ptr = ptr1;
    }
    void merge(const char* str1, const char* str2) noexcept {
        size_t length1 = strlen(str1);
        size_t length = length1 + strlen(str2);

        ptr = (char*)malloc(length + 1);
        char* ptr2 = ptr + length1;

        strcpy(ptr, str1);
        strcpy(ptr2, str2);
        ptr[length] = '\0';
    }

    char* ptr; // главный указатель
}; // string

vertoker::string operator+(const vertoker::string& a, const vertoker::string& b) {
    return vertoker::string{a, b};
}

std::ostream& operator<<(std::ostream& os, const vertoker::string& str) {
    auto ptr = str.c_ptr();
    if (ptr != nullptr)
        os << ptr;
    return os;
}

} // vertoker