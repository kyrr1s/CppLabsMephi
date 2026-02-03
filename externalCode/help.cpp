#include "dialog.h"

template <typename T>
void getValue(T& value, std::istream& c) {
    c >> value;
    if (c.fail()) {
        c.clear();
        c.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw std::invalid_argument("Invalid input argument.");
    }
    if (c.eof()) {
        c.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw std::runtime_error("End of file!");
    }
}

void erase_spaces(std::string& str){
    std::string::iterator end_pos = std::remove(str.begin(), str.end(), ' ');
    str.erase(end_pos, str.end());
}

void menu_stream(size_t& ans, const std::string& str) {
    std::string errmsg = "";
    do {
        std::cout << errmsg << std::endl;
        std::cout << str << std::endl;
        getValue(ans, std::cin);
        errmsg = "Wrong answer. Try again!";
    } while (ans < 0 || ans > 1);
}

bool isNoOperators(const std::string& str) {
    for (const auto& item: str)
        if (item == '+' || item == '-' || item == '(' || item == ')')
            return false;

    return true;
}

bool isBrackets(const std::string& str) {
    std::string::difference_type first = std::count(str.begin(), str.end(), '(');
    std::string::difference_type second = std::count(str.begin(), str.end(), ')');
    if (first == second)
        return false;
    return true;
}

bool isOnlyOperators(const std::string& str) {
    for (const auto& item: str)
        if (std::isdigit(item))
            return false;
    return true;
}

bool isWrongExpression(const std::string& str) {
    if (isNoOperators(str) || isBrackets(str) || isOnlyOperators(str))
        return true;
    return false;

    //строчка не является выражением, если:
    //1. Не содержит операторов - функция isNoOperators()
    //2. Не содержит одинаковое количество ( и ) - функция isBrackets()
    //3. Содержит лишь операторы - функция isOnlyOperators()
    //Остальные проверки - в функции solve_opz()
}
