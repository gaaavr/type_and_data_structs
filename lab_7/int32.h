//
// Created by ssgavrilin on 10.05.2024.
//

#include <iostream>

#define BIT_16_MAX_SIZE 65535

#ifndef LAB_7_INT32_H
#define LAB_7_INT32_H

using namespace std;

class Int32 {
    uint16_t low;  // младшие биты
    uint16_t high; // старшие биты
public:
    // Конструктор по умолчанию
    Int32() {
        low = 0;
        high = 0;
    }

    // Конструктор из int32
    Int32(int32_t value) {
        high = static_cast<uint16_t>(value >> 16); // отбрасываем младшие 16 бит и на их место ставим старшие
        low = static_cast<uint16_t>(value &
                                   BIT_16_MAX_SIZE); // отбрасываем старшие 16 бит и оставляем только младшие 16 бит
    }

    // Оператор "="
    Int32 &operator=(int32_t value) {
        high = static_cast<uint16_t>(value >> 16);
        low = static_cast<uint16_t>(value & BIT_16_MAX_SIZE);
        return *this;
    }

    // Оператор "="
    Int32 &operator=(Int32 value) {
        high = value.high;
        low = value.low;
        return *this;
    }

    // Оператор "+"
    Int32 operator+(const Int32 &other) const {
        int32_t result = static_cast<int32_t>(high) << 16 | low; // сдвигаем старшие биты в правую часть и через логическое ИЛИ добавляем младшие биты
        result += static_cast<int32_t>(other.high) << 16 | other.low;
        return Int32(result);
    }

    // Оператор "-"
    Int32 operator-(const Int32 &other) const {
        int32_t result = static_cast<int32_t>(high) << 16 | low;
        result -= static_cast<int32_t>(other.high) << 16 | other.low;
        return Int32(result);
    }

    // Оператор "*"
    Int32 operator*(const Int32 &other) const {
        int32_t result = static_cast<int32_t>(high) << 16 | low;
        result *= static_cast<int32_t>(other.high) << 16 | other.low;
        return Int32(result);
    }

    // Оператор сравнения ">"
    bool operator>(const Int32 &other) const {
        int32_t this_value = static_cast<int32_t>(high) << 16 | low;
        int32_t other_value = static_cast<int32_t>(other.high) << 16 | other.low;
        return this_value > other_value;
    }

    // Оператор сравнения "<"
    bool operator<(const Int32 &other) const {
        int32_t this_value = static_cast<int32_t>(high) << 16 | low;
        int32_t other_value = static_cast<int32_t>(other.high) << 16 | other.low;
        return this_value < other_value;
    }

    // Оператор сравнения "<="
    bool operator<=(const Int32 &other) const {
        int32_t this_value = static_cast<int32_t>(high) << 16 | low;
        int32_t other_value = static_cast<int32_t>(other.high) << 16 | other.low;
        return this_value <= other_value;
    }

    // Оператор сравнения ">="
    bool operator>=(const Int32 &other) const {
        int32_t this_value = static_cast<int32_t>(high) << 16 | low;
        int32_t other_value = static_cast<int32_t>(other.high) << 16 | other.low;
        return this_value >= other_value;
    }

    // Оператор сравнения "=="
    bool operator==(const Int32 &other) const {
        int32_t this_value = static_cast<int32_t>(high) << 16 | low;
        int32_t other_value = static_cast<int32_t>(other.high) << 16 | other.low;
        return this_value == other_value;
    }

    // Оператор сравнения "!="
    bool operator!=(const Int32 &other) const {
        int32_t this_value = static_cast<int32_t>(high) << 16 | low;
        int32_t other_value = static_cast<int32_t>(other.high) << 16 | other.low;
        return this_value != other_value;
    }

    // Оператор стандартного вывода
    friend ostream &operator<<(ostream &out, const Int32 &value) {
        out << (static_cast<int32_t>(value.high) << 16 | value.low);

        return out;
    };
};

#endif //LAB_7_INT32_H
