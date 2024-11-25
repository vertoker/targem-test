#pragma once
#include <stdint.h>
#include <malloc.h>
#include <string.h>

#include <assert.h>
#include <stdio.h>

// тупой способ тестирования работоспособности строки через макросы
#define USE_TEST_LOG 0

namespace vertoker { // ну раз это моя реализация, значит и namespace будет мой
class string {
private:
    #define TEST_LOG(str) USE_TEST_LOG ? printf(str) : 0;

public:
    string() : ptr{nullptr} { 
        TEST_LOG("Null constructor\n");
    }
    string(const char* str) {
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

    ~string() {
        TEST_LOG("Free deconstructor\n");
        free(ptr);
    }

private:
    void copy(const char* dst) {
        size_t length = strlen(dst);
        ptr = (char*)malloc(length + 1);
        strcpy(ptr, dst);
        ptr[length] = '\0';
    }

    char* ptr; // главный указатель
}; // string
} // vertoker