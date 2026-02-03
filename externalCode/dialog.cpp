#include "dialog.h"

BigInt solve_opz(const std::string& str) {
    std::stringstream s(str);
    std::stack<BigInt> opz;
    BigInt value;
    char sign;
    while (!s.eof()) {
        try {
            while (!s.eof() && s >> value) {
                opz.push(value);
            }
        }
        catch (const std::exception& ex) {
            s.unget();
            s>>sign;
            if (opz.size() < 2)
                throw std::runtime_error("The equation is not reverse polish notation. You should input more variables.");
            BigInt right = opz.top();
            opz.pop();
            BigInt left = opz.top();
            opz.pop();
            switch (sign) {
                case '+':   opz.push(right + left); break;
                case '-':   opz.push(left - right); break;
                default: throw std::runtime_error("Undefined operator in reverse polish notation.");
            }
            if (s>>sign)
                s.unget();
            else return opz.top();
        }
    }
    if (opz.size() != 1)
        throw std::runtime_error("The equation is not reverse polish notation. Need one more operator.");
    return opz.top();
}

BigInt solve(std::string& str, std::ostream& c) {
    ConvertToPN opn;
    opn.convert(str);
    BigInt res = solve_opz(opn.getStrOut());
    c << std::showpos << res;
    return res;
}

void menu() {
    std::fstream inf;
    std::fstream outf;

    size_t ansm;
    menu_stream(ansm, "Choose input stream: console (0) or file (1)");
    std::cin.ignore();

    std::string ans;
    std::string errmsg = "";
    do {
        std::cout << errmsg << std::endl;
        if (ansm == 1) {
            std::cout << "Input an input file name:" << std::endl;
            std::string inp_file_name;
            std::getline(std::cin, inp_file_name);
            inf.open(inp_file_name);
            if (!inf)
                throw std::runtime_error("Can not open input file.");
            inf >> ans;
        } else {
            std::cout << "Input an expression (it only can constist of '+', '-', '(' or ')' ):" << std::endl;
            std::getline(std::cin, ans);
        }
        erase_spaces(ans);
        errmsg = "Wrong expression. Try again.";
    } while (isWrongExpression(ans));

    menu_stream(ansm, "Choose output stream console (0) or file (1):");
    std::cin.ignore();

    if (ansm == 1) {
        std::cout << "Input an output file name: ";
        std::string out_file_name;
        std::getline(std::cin, out_file_name);
        std::cout << std::endl;
        outf.open(out_file_name);
        if (!outf)
            throw std::runtime_error("Can not open output file.");
        solve(ans, outf);
    }
    else solve(ans, std::cout);

    inf.close();
    outf.close();
    std::cout << std::endl;
}


