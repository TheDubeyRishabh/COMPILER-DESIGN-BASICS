#include <iostream>
#include <sstream>
#include <cctype>

class Parser {
public:
    Parser(std::string input) : input(input), pos(0) {}
    double parse() { return expression(); }

private:
    std::string input;
    size_t pos;

    char peek() {
        while (pos < input.size() && isspace(input[pos])) ++pos;
        return (pos < input.size()) ? input[pos] : '\0';
    }

    char get() {
        char ch = peek();
        if (pos < input.size()) ++pos;
        return ch;
    }

    double number() {
        std::stringstream ss;
        while (isdigit(peek()) || peek() == '.') ss << get();
        double value;
        ss >> value;
        return value;
    }

    double factor() {
        if (peek() == '(') {
            get();
            double result = expression();
            get();
            return result;
        } else {
            return number();
        }
    }

    double term() {
        double result = factor();
        while (peek() == '*' || peek() == '/') {
            char op = get();
            if (op == '*')
                result *= factor();
            else
                result /= factor();
        }
        return result;
    }

    double expression() {
        double result = term();
        while (peek() == '+' || peek() == '-') {
            char op = get();
            if (op == '+')
                result += term();
            else
                result -= term();
        }
        return result;
    }
};

int main() {
    std::string input;
    std::cout << "Enter an arithmetic expression: ";
    std::getline(std::cin, input);
    Parser parser(input);
    std::cout << "Result: " << parser.parse() << std::endl;
    return 0;
}