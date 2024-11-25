#pragma once
#include <stdint.h>
#include <malloc.h>
#include <string.h>

#include <assert.h>
#include <stdio.h>

namespace vertoker { // ну раз это моя реализация, значит и namespace будет мой
class string {
public:
    string() : ptr{nullptr} { 
        //printf("Null constructor\n");
    }
    string(const char* str) {
        if (str == nullptr) {
            //printf("Create constructor null\n");
            ptr = nullptr;
        }
        else {
            //printf("Create constructor\n");
            size_t length = strlen(str);
            ptr = (char*)malloc(length + 1);
            strcpy(ptr, str);
            ptr[length] = '\0';
        }
    }

    string(const string& other) { // copy
        if (other.ptr == nullptr) {
            //printf("Copy constructor null\n");
            ptr = nullptr;
        }
        else {
            //printf("Copy constructor\n");
            size_t length = strlen(other.ptr);
            ptr = (char*)malloc(length + 1);
            strcpy(ptr, other.ptr);
            ptr[length] = '\0';
        }
    }
    string(string&& other) { // move
        //printf("Move constructor\n");
        ptr = other.ptr;
        other.ptr = nullptr;
    }

    ~string() {
        free(ptr);
    }

private:
    char* ptr; // главный указатель
}; // string
} // vertoker