//
// Created by Stephan on 24.09.2022.
//

#ifndef LAB3_SEM3_BIGINT_H
#define LAB3_SEM3_BIGINT_H
#include <iostream>
#include <string>
#include <cstring>

class BigInt {
protected:
    size_t length = 0;
    unsigned char * arr = nullptr;

    void swap(BigInt & bi) {
        std::swap(length, bi.length);
        std::swap(arr, bi.arr);
    }

private:
    static bool is_integer(const std::string & s);
    [[nodiscard]] bool empty() const;
public:
    /// possible operations with BI
    typedef enum Funcs {
        EXIT,
        SIZE,
        TO_STRING,
        ADDITION,
        SUBTRACTING,
        MULTIPLY_10,
        DIVIDE_10,
        INCREMENT,
        DECREMENT,
    } Funcs;

    // constructors
    BigInt() {
        //std::cout << "constructor" << std::endl;
    }
    BigInt(const long & x) {
        //std::cout << "constructor" << std::endl;
        size_t l = std::to_string(std::abs(x)).length();

        length = l;
        arr = new unsigned char [length+1];
        arr[0] = (unsigned char) (x < 0);
        long y = std::abs(x);
        for (size_t i = 0; i < length; ++i, y/=10)
            arr[length-i] = y%10;
    }
    BigInt(const std::string & x) {
        //std::cout << "constructor" << std::endl;
        // проверка строки
        if (!is_integer(x))
            throw std::invalid_argument("your line to conversion in BI is not integer");

        size_t l = (x[0] == '-') ? x.size()-1 : x.size();
        length = l;
        // память под массив символов нового числа
        try {
            arr = new unsigned char [length+1];
        } catch (std::bad_alloc & ba) {
            std::cerr << ba.what() << std::endl;
            throw ba;
        }
        arr[0] = (unsigned char) (x[0] == '-');
        std::string s = x;
        if (isdigit(x[0]))
            s = "+" + x;
        // можно доработать
        for (size_t i = 1; i < s.length(); ++i)
            arr[i] = s[i]-'0';
    }

    // copy constructor
    BigInt(const BigInt & bi) : length(bi.length) {
        //std::cout << "copy constructor" << std::endl;
        try {
            arr = new unsigned char [length+1];
        } catch (std::bad_alloc & ba) {
            std::cerr << ba.what() << std::endl;
            delete[] arr;
            arr = nullptr;
            throw ba;
        }
        memmove(arr, bi.arr, (length+1) * sizeof(char));
    }
    // move constructor
    BigInt(BigInt && bi)  noexcept : length(bi.length), arr(bi.arr) {
        //std::cout << "move constructor" << std::endl;
        bi.length = 0;
        bi.arr = nullptr;
    }

    // destructor
    ~BigInt() {
        //std::cout << "destructor" << std::endl;
        delete[] arr;
    }

    // assignment operator for my Ints
    /*
    BigInt & operator=(BigInt bi) {
        swap(bi);
        return *this;
    }
    */
    BigInt & operator=(const BigInt & bi) {
        //std::cout << "assigment" << std::endl;
        if (&bi == this)
            return *this;
        length = bi.length;
        delete[] arr;
        arr = new unsigned char [length+1];
        memcpy(arr, bi.arr, length+1);
        return *this;
    }
    BigInt & operator=(BigInt && bi)  noexcept {
        //std::cout << "move assigment" << std::endl;
        if (this != &bi) {
            delete[] arr;
            this->arr = bi.arr;
            this->length = bi.length;

            bi.arr = nullptr;
            bi.length = 0;
        }
        return *this;
    }


    // public methods
    /// returns len of BI in symbols except sign
    [[nodiscard]] size_t size() const;
    /// convert number to string equivalent with +/- sign
    [[nodiscard]] std::string to_string() const;
    // перегрузка оператора >>
    /// read BI from istream
    friend std::istream & operator>>(std::istream &, BigInt &);
    // перегрузка оператора <<
    /// print BI in ostream
    friend std::ostream & operator<<(std::ostream &, const BigInt &);
    /// return additional BI
    [[nodiscard]] BigInt additional_BI() const;
    /// return string version of additional BI (with +/-) without prefix '0's
    [[nodiscard]] std::string additional_code() const;
    // перегрузка оператора +
    BigInt& operator+=(const BigInt & bi);
    // перегрузка оператора -
    BigInt& operator-=(const BigInt & bi);
    // деление на 10
    /// divide BI by 10. return nothing
    void devision_by_10();
    // умножение на 10
    /// multiply BI with 10. return nothing
    void multiplication_with_10();
    // перегруженное умножение на 10
    /// return BI multiplied with 10. doesn't change BI
    BigInt operator!() const;
    // префикс-постфикс инкримент
    // префикс
    BigInt& operator++();
    // постфикс
    BigInt operator++(int);
    // префикс-постфикс декримент
    // префикс
    BigInt& operator--();
    // постфикс
    BigInt operator--(int);

    friend bool operator<(const BigInt&, const BigInt&);
};

BigInt operator+(const BigInt&, const BigInt&);
BigInt operator-(const BigInt&, const BigInt&);
bool operator<(const BigInt&, const BigInt&);
bool operator>(const BigInt&, const BigInt&);
bool operator==(const BigInt&, const BigInt&);

#endif //LAB3_SEM3_BIGINT_H
