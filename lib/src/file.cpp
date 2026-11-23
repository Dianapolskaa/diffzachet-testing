#include "file.h"
#include <cctype>
#include <string>
#include <string_view>
#include <charconv> // Для std::from_chars
#include <stdexcept>

namespace mylib {

class Parser {
public:
    explicit Parser(const std::string& s) : str(s), pos(0) {}

    double parse() {
        skipWhitespace();
        if (pos >= str.length()) {
            throw std::invalid_argument("Empty expression");
        }
        double result = parseExpression();
        skipWhitespace();
        if (pos < str.length()) {
            throw std::invalid_argument("Unexpected characters after expression");
        }
        return result;
    }

private:
    std::string str;
    size_t pos;

    void skipWhitespace() {
        while (pos < str.length() && std::isspace(static_cast<unsigned char>(str[pos]))) {
            pos++;
        }
    }

    char peek() {
        return pos < str.length() ? str[pos] : '\0';
    }

    char get() {
        return pos < str.length() ? str[pos++] : '\0';
    }

    double parseExpression() {
        double result = parseTerm();
        while (true) {
            skipWhitespace();
            char op = peek();
            if (op == '+') {
                get();
                result += parseTerm();
            } else if (op == '-') {
                get();
                result -= parseTerm();
            } else {
                break;
            }
        }
        return result;
    }

    double parseTerm() {
        double result = parseFactor();
        while (true) {
            skipWhitespace();
            char op = peek();
            if (op == '*') {
                get();
                result *= parseFactor();
            } else if (op == '/') {
                get();
                double divisor = parseFactor();
                if (divisor == 0.0) {
                    throw std::invalid_argument("Division by zero");
                }
                result /= divisor;
            } else {
                break;
            }
        }
        return result;
    }

    double parseFactor() {
        skipWhitespace();
        char op = peek();
        if (op == '+') {
            get();
            return parseFactor();
        }
        if (op == '-') {
            get();
            return -parseFactor();
        }
        if (op == '(') {
            get(); // consume '('
            double result = parseExpression();
            skipWhitespace();
            if (peek() != ')') {
                throw std::invalid_argument("Mismatched parentheses");
            }
            get(); // consume ')'
            return result;
        }
        return parseNumber();
    }

    double parseNumber() {
        skipWhitespace();
        size_t start = pos;
        bool hasDot = false;
        while (pos < str.length()) {
            char c = str[pos];
            if (std::isdigit(static_cast<unsigned char>(c))) {
                pos++;
            } else if (c == '.' && !hasDot) {
                hasDot = true;
                pos++;
            } else {
                break;
            }
        }
        if (pos == start) {
            throw std::invalid_argument("Expected number");
        }

        // Используем std::from_chars: она НЕ зависит от локали системы
        // и всегда корректно парсит числа с точкой.
        std::string_view numStr(str.data() + start, pos - start);
        double result = 0.0;
        auto [ptr, ec] = std::from_chars(numStr.data(), numStr.data() + numStr.size(), result);

        if (ec == std::errc::invalid_argument || ec == std::errc::result_out_of_range) {
            throw std::invalid_argument("Invalid number format");
        }

        return result;
    }
};

double evaluateExpression(const std::string& expr) {
    Parser parser(expr);
    return parser.parse();
}

} // namespace mylib