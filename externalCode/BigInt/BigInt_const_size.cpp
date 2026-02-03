//
// Created by Stephan on 24.09.2022.
//
#include <iostream>
#include <cstring>
#include <string>

#include "BigInt_const_size.h"

size_t BigInt_const_size::size() const {
    return length;
}
std::string BigInt_const_size::to_string() const {
    std::string s = (arr[0])? "-": "+";
    for (size_t i = 1; i <= length; ++i) {
        s += std::to_string(arr[MAX_SIZE-length+i-1]);
    }
    return s;
}

bool BigInt_const_size::is_integer(std::string s) {
    if (s.empty())
        return false;
    char sign = s[0];
    bool sign_is_real = false;
    if (sign == '+' || sign == '-') {
        if (s.size() == 1)
            return false;
        sign_is_real = true;
    }
    else if (std::isdigit(sign))
        sign_is_real = false;
    else
        return false;

    for (size_t i = sign_is_real; i < s.size(); ++i)
        if (!std::isdigit(s[i]))
            return false;

    return true;
}

BigInt_const_size BigInt_const_size::additional_BI() const {
    BigInt_const_size bi;
    bi.length = length;
    bi.arr[0] = (length == 1 && !arr[MAX_SIZE - 1]) ? 0 : arr[0];

    if (!arr[0]) {
        memcpy(bi.arr+1, arr+1, (MAX_SIZE-1) * sizeof(char));
        return bi;
    }
    for (size_t i = 1; i < MAX_SIZE; ++i) {
        bi.arr[i] = 9-arr[i];
    }
    size_t i = 1;
    if (arr[0]) {
        unsigned char buf = 1;
        unsigned char sum = 0;
        for (i = MAX_SIZE-1; i > 0; --i) {
            sum = buf+bi.arr[i];
            bi.arr[i] = sum % 10;
            buf = sum / 10;
        }
    }
    i = 1;
    while (bi.arr[i] == 0 && i < MAX_SIZE)
        ++i;
    bi.length = MAX_SIZE-i;
    if (!(bi.length)) {
        bi.arr[0] = 0;
        bi.length = 1;
    }
    return bi;
}

std::string BigInt_const_size::additional_code() const {
    BigInt_const_size bi = this->additional_BI();
    return bi.to_string();
}

// деление на 10
void BigInt_const_size::devision_by_10() {
    std::memmove(arr + MAX_SIZE - length+1, arr + MAX_SIZE - length, (length-1) * sizeof(char));
    arr[MAX_SIZE - length] = 0;
    length = (length==1) ? 1 : length-1;
    if (length == 1 && arr[MAX_SIZE-1] == 0)
        arr[0] = 0;
}
// умножение на 10
void BigInt_const_size::multiplication_with_10() {
    if (length == MAX_SIZE-1)
        throw std::runtime_error("you try to do this number too big");
    std::memmove(arr + MAX_SIZE - length-1, arr + MAX_SIZE - length, length * sizeof(char));
    // возможны проблемки при MAX_SIZE == 2
    if (length != 1 || arr[MAX_SIZE-2])
        ++length;
    arr[MAX_SIZE-1] = 0;
}
BigInt_const_size BigInt_const_size::operator!() const {
    BigInt_const_size copy = *this;
    if (length == MAX_SIZE-1)
        throw std::runtime_error("you try to do this number too big");
    std::memmove(copy.arr + MAX_SIZE - length-1, copy.arr + MAX_SIZE - length, length * sizeof(char));
    // возможны проблемки при MAX_SIZE == 2
    if (length != 1 || arr[MAX_SIZE-2])
        ++copy.length;
    copy.arr[MAX_SIZE-1] = 0;
    return copy;
}


// перегрузка оператора +=
BigInt_const_size& BigInt_const_size::operator+=(const BigInt_const_size bi) {
    BigInt_const_size a = this->additional_BI();
    BigInt_const_size b = bi.additional_BI();
    unsigned char buf = 0;
    unsigned char sum = 0;
    BigInt_const_size res;
    for (size_t i = MAX_SIZE-1; i > 0; --i) {
        sum = a.arr[i] + b.arr[i] + buf;
        res.arr[i] = sum % 10;
        buf = sum / 10;
    }
    size_t i = 1;
    while (res.arr[i] == 0 && i < MAX_SIZE)
        ++i;
    if (a.arr[0]) {
        if (b.arr[0]) {
            if (!buf || (buf==1 && (0 == MAX_SIZE-i)))
                throw std::runtime_error("you try to create too large number");
            res.arr[0] = 1;
        } else {
            if (buf) {
                res.arr[0] = 0;
            } else {
                res.arr[0] = 1;
            }
        }
    } else {
        if (b.arr[0]) {
            if (buf) {
                res.arr[0] = 0;
            } else {
                res.arr[0] = 1;
            }
        } else {
            if (buf)
                throw std::runtime_error("you try to create too large number");
            res.arr[0] = 0;
        }
    }
    i = 1;
    while (res.arr[i] == 0 && i < MAX_SIZE)
        ++i;
    res.length = MAX_SIZE-i;
    if (!(res.length)) {
        res.arr[0] = 0;
        res.length = 1;
    }
    if (res.arr[0]) {
        res = res.additional_BI();
    }
    *this = res;
    return *this;
}
BigInt_const_size operator+(const BigInt_const_size& a, const BigInt_const_size& b) {
    BigInt_const_size copy = a;
    copy += b;
    return copy;
}

// перегрузка оператора -=
BigInt_const_size& BigInt_const_size::operator-=(const BigInt_const_size bi) {
    BigInt_const_size _copy = bi;
    if (bi.length == 1 && !bi.arr[MAX_SIZE-1])
        _copy.arr[0] = 0;
    else
        _copy.arr[0] = !_copy.arr[0];
    return *this += _copy;
}
BigInt_const_size operator-(const BigInt_const_size& a, const BigInt_const_size& b) {
    BigInt_const_size copy = a;
    copy -= b;
    return copy;
}

// перегрузка оператора >>
std::istream & operator>>(std::istream & istream, BigInt_const_size & bi) {
    std::string s;
    istream >> s;
    bi = BigInt_const_size(s);
    return istream;
}
// перегрузка оператора <<
std::ostream & operator<<(std::ostream & ostream, const BigInt_const_size & bi) {
    return ostream << bi.to_string();
}

// префикс
BigInt_const_size& BigInt_const_size::operator++() {
    *this += 1;
    return *this;
}
// постфикс
BigInt_const_size BigInt_const_size::operator++(int) {
    BigInt_const_size copy = *this;
    ++*this;
    return copy;
}
// префикс
BigInt_const_size& BigInt_const_size::operator--() {
    *this -= 1;
    return *this;
}
// постфикс
BigInt_const_size BigInt_const_size::operator--(int) {
    BigInt_const_size copy = *this;
    --*this;
    return copy;
}