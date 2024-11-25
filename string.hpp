#pragma once
#include <stdint.h>

namespace vertoker { // ну раз это моя реализация, значит и namespace будет мой
class string {
public:
    string() {
        
    }

private:
    uint32_t size; // аллоцированные байты
    uint32_t length; // текущая длина строки
    char* ptr;
}; // string
} // vertoker