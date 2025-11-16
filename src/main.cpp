#include <algorithm>
#include <cctype>
#include <cmath>
#include <complex>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <vector>

#include "divisors.hpp"

namespace {

void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::string readLine(const std::string& prompt) {
    std::cout << prompt;
    std::cin >> std::ws;
    std::string line;
    std::getline(std::cin, line);
    return line;
}

int readMenuChoice(int min, int max) {
    int choice;
    while (true) {
        std::cout << "Select option: ";
        if (std::cin >> choice && choice >= min && choice <= max) {
            return choice;
        }
        std::cout << "Invalid choice. Try again.\n";
        clearInput();
    }
}

long long readInteger(const std::string& prompt) {
    long long value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            return value;
        }
        std::cout << "That doesn't look like an integer. ";
        clearInput();
    }
}

double readDouble(const std::string& prompt) {
    double value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            return value;
        }
        std::cout << "That doesn't look like a valid number. ";
        clearInput();
    }
}

bool isApproximatelyZero(double value, double epsilon = 1e-9) {
    return std::abs(value) <= epsilon;
}

std::string trim(const std::string& text) {
    auto notSpace = [](unsigned char ch) { return !std::isspace(ch); };
    auto begin = std::find_if(text.begin(), text.end(), notSpace);
    if (begin == text.end()) {
        return "";
    }
    auto rbegin = std::find_if(text.rbegin(), text.rend(), notSpace);
    return {begin, rbegin.base()};
}

std::string normalizeForBase(const std::string& input, int base) {
    std::string trimmed = trim(input);
    if (trimmed.empty()) {
        throw std::invalid_argument("Empty input.");
    }

    std::string sign;
    std::size_t pos = 0;
    if (trimmed[0] == '+' || trimmed[0] == '-') {
        sign = trimmed.substr(0, 1);
        pos = 1;
    }

    std::string body = trimmed.substr(pos);
    auto hasPrefix = [](const std::string& value, char expected) {
        if (value.size() <= 1 || value[0] != '0') {
            return false;
        }
        char prefixChar = static_cast<char>(std::tolower(static_cast<unsigned char>(value[1])));
        return prefixChar == expected;
    };

    if (base == 2 && hasPrefix(body, 'b')) {
        body = body.substr(2);
    } else if (base == 16 && hasPrefix(body, 'x')) {
        body = body.substr(2);
    }

    if (body.empty()) {
        throw std::invalid_argument("No digits were provided.");
    }

    return sign + body;
}

long long parseInteger(const std::string& text, int base) {
    std::string normalized = normalizeForBase(text, base);
    std::size_t processed = 0;
    long long value = 0;
    try {
        value = std::stoll(normalized, &processed, base);
    } catch (const std::invalid_argument&) {
        throw std::invalid_argument("Invalid character among the digits.");
    } catch (const std::out_of_range&) {
        throw std::out_of_range("The provided number is too large to convert.");
    }

    if (processed != normalized.size()) {
        throw std::invalid_argument("Invalid character among the digits.");
    }

    return value;
}

std::string formatInteger(long long value, int base) {
    if (base == 10) {
        return std::to_string(value);
    }

    const char* digits = "0123456789ABCDEF";
    bool negative = value < 0;
    unsigned long long magnitude =
        negative ? static_cast<unsigned long long>(-(value + 1)) + 1ULL
                 : static_cast<unsigned long long>(value);

    if (magnitude == 0) {
        return "0";
    }

    std::string converted;
    while (magnitude > 0) {
        converted.push_back(digits[magnitude % base]);
        magnitude /= base;
    }

    std::reverse(converted.begin(), converted.end());

    std::string prefix;
    if (base == 2) {
        prefix = "0b";
    } else if (base == 16) {
        prefix = "0x";
    }

    return (negative ? "-" : "") + prefix + converted;
}

bool isOperatorChar(char ch) {
    ch = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
    return ch == '+' || ch == '-' || ch == '*' || ch == 'x' || ch == ':' || ch == '/';
}

char normalizeOperator(char ch) {
    ch = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
    if (ch == 'x') {
        return '*';
    }
    if (ch == ':') {
        return '/';
    }
    return ch;
}

double factorialOf(double operand) {
    double rounded = std::round(operand);
    if (!isApproximatelyZero(operand - rounded)) {
        throw std::invalid_argument("Factorial is only defined for integers.");
    }

    long long n = static_cast<long long>(rounded);
    if (n < 0) {
        throw std::invalid_argument("Factorial is not defined for negative numbers.");
    }
    if (n > 170) {
        throw std::overflow_error("Factorial result would overflow double precision.");
    }

    long double result = 1.0L;
    for (long long i = 2; i <= n; ++i) {
        result *= static_cast<long double>(i);
    }
    return static_cast<double>(result);
}

double applyFunction(const std::string& functionName, double value) {
    if (functionName == "sin") {
        return std::sin(value);
    }
    if (functionName == "cos") {
        return std::cos(value);
    }
    if (functionName == "log") {
        if (value <= 0.0) {
            throw std::domain_error("Logarithm undefined for non-positive values.");
        }
        return std::log(value);
    }
    if (functionName == "tan") {
        return std::tan(value);
    }
    if (functionName == "sqrt") {
        if (value < 0.0) {
            throw std::domain_error("Square root undefined for negative values.");
        }
        return std::sqrt(value);
    }
    if (functionName == "exp") {
        return std::exp(value);
    }
    if (functionName == "cot") {
        double tanValue = std::tan(value);
        if (isApproximatelyZero(tanValue)) {
            throw std::domain_error("Cotangent undefined for this value.");
        }
        return 1.0 / tanValue;
    }
    if (functionName == "asin") {
        if (value < -1.0 || value > 1.0) {
            throw std::domain_error("Arcsine undefined for this value.");
        }
        return std::asin(value);
    }
    if (functionName == "acos") {
        if (value < -1.0 || value > 1.0) {
            throw std::domain_error("Arccosine undefined for this value.");
        }
        return std::acos(value);
    }
    if (functionName == "atan") {
        return std::atan(value);
    }
    if (functionName == "sinh") {
        return std::sinh(value);
    }
    throw std::invalid_argument("Unknown function: " + functionName);
}

int chooseBase(const std::string& label) {
    while (true) {
        std::cout << label << '\n';
        std::cout << " 1) Decimal (10)\n";
        std::cout << " 2) Binary (2)\n";
        std::cout << " 3) Hexadecimal (16)\n";
        std::cout << " 0) Back\n";

        int choice = readMenuChoice(0, 3);
        switch (choice) {
            case 1:
                return 10;
            case 2:
                return 2;
            case 3:
                return 16;
            case 0:
                return 0;
            default:
                break;
        }
    }
}

struct Token {
    enum class Type { Number, Operator, Function, LeftParen, RightParen } type;
    double value{};
    char op{};
    std::string func;
};

double parseNumberToken(const std::string& expr, std::size_t& index) {
    std::size_t start = index;
    bool hasDigit = false;
    bool hasDot = false;
    while (index < expr.size()) {
        char c = expr[index];
        if (std::isdigit(static_cast<unsigned char>(c))) {
            hasDigit = true;
            ++index;
        } else if (c == '.') {
            if (hasDot) {
                throw std::invalid_argument("Multiple decimal separators found in number.");
            }
            hasDot = true;
            ++index;
        } else {
            break;
        }
    }
    if (!hasDigit) {
        throw std::invalid_argument("Expected a digit in the number.");
    }
    return std::stod(expr.substr(start, index - start));
}

std::vector<Token> tokenizeExpression(const std::string& expression) {
    std::vector<Token> tokens;
    std::size_t i = 0;
    bool expectValue = true;

    while (i < expression.size()) {
        char c = expression[i];
        if (std::isspace(static_cast<unsigned char>(c))) {
            ++i;
            continue;
        }

        if (expectValue) {
            if (c == '(') {
                tokens.push_back({Token::Type::LeftParen, 0.0, 0, ""});
                ++i;
                continue;
            }

            int sign = 1;
            bool sawUnarySign = false;
            if (c == '+' || c == '-') {
                sawUnarySign = true;
                sign = (c == '-') ? -1 : 1;
                ++i;
                while (i < expression.size() &&
                       std::isspace(static_cast<unsigned char>(expression[i]))) {
                    ++i;
                }
                if (i >= expression.size()) {
                    throw std::invalid_argument("Expression cannot end with a unary operator.");
                }
                c = expression[i];
                if (c == '(') {
                    if (sign == -1) {
                        tokens.push_back({Token::Type::Number, 0.0, 0, ""});
                        tokens.push_back({Token::Type::Operator, 0.0, '-', ""});
                    }
                    expectValue = true;
                    continue;
                }
            } else {
                sign = 1;
            }

            if (std::isdigit(static_cast<unsigned char>(c)) || c == '.') {
                double number = parseNumberToken(expression, i);
                tokens.push_back({Token::Type::Number, sign * number, 0, ""});
                expectValue = false;
                continue;
            }

            if (std::isalpha(static_cast<unsigned char>(c))) {
                std::size_t start = i;
                while (i < expression.size() &&
                       std::isalpha(static_cast<unsigned char>(expression[i]))) {
                    ++i;
                }
                std::string functionName = expression.substr(start, i - start);
                std::string lowered = functionName;
                std::transform(lowered.begin(), lowered.end(), lowered.begin(), [](unsigned char ch) {
                    return static_cast<char>(std::tolower(ch));
                });
                if (lowered != "sin" && lowered != "cos" && lowered != "log") {
                    throw std::invalid_argument("Unknown function: " + functionName);
                }
                if (sawUnarySign && sign == -1) {
                    tokens.push_back({Token::Type::Number, 0.0, 0, ""});
                    tokens.push_back({Token::Type::Operator, 0.0, '-', ""});
                }
                tokens.push_back({Token::Type::Function, 0.0, 0, lowered});

                std::size_t lookahead = i;
                while (lookahead < expression.size() &&
                       std::isspace(static_cast<unsigned char>(expression[lookahead]))) {
                    ++lookahead;
                }
                if (lookahead >= expression.size() || expression[lookahead] != '(') {
                    throw std::invalid_argument("Function '" + functionName +
                                                "' must be followed by parentheses.");
                }
                i = lookahead;
                continue;
            }

            throw std::invalid_argument("Expected a number or '(' in the expression.");
        } else {
            if (c == ')') {
                tokens.push_back({Token::Type::RightParen, 0.0, 0, ""});
                ++i;
                continue;
            }

            if (c == '!') {
                tokens.push_back({Token::Type::Operator, 0.0, '!', ""});
                ++i;
                continue;
            }

            if (isOperatorChar(c)) {
                tokens.push_back(
                    {Token::Type::Operator, 0.0, normalizeOperator(c), ""});
                ++i;
                expectValue = true;
                continue;
            }

            throw std::invalid_argument("Expected an operator or ')' in the expression.");
        }
    }

    if (expectValue) {
        throw std::invalid_argument("Expression ended unexpectedly. Operand missing.");
    }

    return tokens;
}

int precedence(char op) {
    if (op == '+' || op == '-') {
        return 1;
    }
    if (op == '*' || op == '/') {
        return 2;
    }
    if (op == '!') {
        return 3;
    }
    throw std::invalid_argument("Unknown operator encountered.");
}

std::vector<Token> toRpn(const std::vector<Token>& tokens) {
    std::vector<Token> output;
    std::vector<Token> stack;

    for (const Token& token : tokens) {
        switch (token.type) {
            case Token::Type::Number:
                output.push_back(token);
                break;
            case Token::Type::Function:
                stack.push_back(token);
                break;
            case Token::Type::Operator:
                while (!stack.empty() && stack.back().type == Token::Type::Operator &&
                       precedence(stack.back().op) >= precedence(token.op)) {
                    output.push_back(stack.back());
                    stack.pop_back();
                }
                stack.push_back(token);
                break;
            case Token::Type::LeftParen:
                stack.push_back(token);
                break;
            case Token::Type::RightParen:
                while (!stack.empty() && stack.back().type != Token::Type::LeftParen) {
                    output.push_back(stack.back());
                    stack.pop_back();
                }
                if (stack.empty() || stack.back().type != Token::Type::LeftParen) {
                    throw std::invalid_argument("Mismatched parentheses in expression.");
                }
                stack.pop_back();
                if (!stack.empty() && stack.back().type == Token::Type::Function) {
                    output.push_back(stack.back());
                    stack.pop_back();
                }
                break;
        }
    }

    while (!stack.empty()) {
        if (stack.back().type == Token::Type::LeftParen ||
            stack.back().type == Token::Type::RightParen) {
            throw std::invalid_argument("Mismatched parentheses in expression.");
        }
        output.push_back(stack.back());
        stack.pop_back();
    }

    return output;
}

double evaluateExpression(const std::string& expression) {
    std::vector<Token> tokens = tokenizeExpression(expression);
    std::vector<Token> rpn = toRpn(tokens);
    std::vector<double> stack;

    for (const Token& token : rpn) {
        switch (token.type) {
            case Token::Type::Number:
                stack.push_back(token.value);
                break;
            case Token::Type::Operator:
                if (token.op == '!') {
                    if (stack.empty()) {
                        throw std::invalid_argument("Factorial operator missing operand.");
                    }
                    double value = stack.back();
                    stack.back() = factorialOf(value);
                    break;
                }
                if (stack.size() < 2) {
                    throw std::invalid_argument("Invalid expression: insufficient operands.");
                }
                {
                    double rhs = stack.back();
                    stack.pop_back();
                    double lhs = stack.back();
                    stack.pop_back();
                    double result = 0.0;
                    switch (token.op) {
                        case '+':
                            result = lhs + rhs;
                            break;
                        case '-':
                            result = lhs - rhs;
                            break;
                        case '*':
                            result = lhs * rhs;
                            break;
                        case '/':
                            if (rhs == 0.0) {
                                throw std::runtime_error("Division by zero in expression.");
                            }
                            result = lhs / rhs;
                            break;
                        default:
                            throw std::invalid_argument("Unknown operator in expression.");
                    }
                    stack.push_back(result);
                }
                break;
            case Token::Type::Function:
                if (stack.empty()) {
                    throw std::invalid_argument("Function missing operand.");
                }
                {
                    double argument = stack.back();
                    stack.back() = applyFunction(token.func, argument);
                }
                break;
            default:
                break;
        }
    }

    if (stack.size() != 1) {
        throw std::invalid_argument("Invalid expression: leftover operands.");
    }

    return stack.back();
}

bool askToContinue(const std::string& prompt) {
    std::string answer;
    while (true) {
        std::cout << prompt;
        if (!(std::cin >> answer)) {
            clearInput();
            continue;
        }
        if (answer.empty()) {
            continue;
        }

        char first = static_cast<char>(std::tolower(static_cast<unsigned char>(answer[0])));
        if (first == 'y') {
            return true;
        }
        if (first == 'n') {
            return false;
        }
        std::cout << "Please answer with 'y' or 'n'.\n";
    }
}

void solveLinearEquation(double a, double b) {
    if (isApproximatelyZero(a)) {
        if (isApproximatelyZero(b)) {
            std::cout << "Every real number is a solution.\n";
        } else {
            std::cout << "No solution exists for this equation.\n";
        }
        return;
    }

    double result = -b / a;
    std::cout << "Solution: x = " << result << '\n';
}

void solveQuadraticEquation(double a, double b, double c) {
    if (isApproximatelyZero(a)) {
        std::cout << "Coefficient 'a' is zero; falling back to a linear equation.\n";
        solveLinearEquation(b, c);
        return;
    }

    double discriminant = b * b - 4.0 * a * c;
    constexpr double epsilon = 1e-9;

    if (discriminant > epsilon) {
        double sqrtDisc = std::sqrt(discriminant);
        double denom = 2.0 * a;
        std::cout << "Two real solutions:\n";
        std::cout << " x1 = " << (-b + sqrtDisc) / denom << '\n';
        std::cout << " x2 = " << (-b - sqrtDisc) / denom << '\n';
    } else if (isApproximatelyZero(discriminant, epsilon)) {
        double root = -b / (2.0 * a);
        std::cout << "One real solution (double root): x = " << root << '\n';
    } else {
        std::complex<double> sqrtDisc = std::sqrt(std::complex<double>(discriminant, 0.0));
        std::complex<double> denom(2.0 * a, 0.0);
        std::complex<double> x1 = (-b + sqrtDisc) / denom;
        std::complex<double> x2 = (-b - sqrtDisc) / denom;

        auto printComplex = [](const std::complex<double>& value) {
            double realPart = value.real();
            double imagPart = value.imag();
            std::cout << realPart;
            if (!isApproximatelyZero(imagPart)) {
                if (imagPart >= 0) {
                    std::cout << " + " << imagPart << "i";
                } else {
                    std::cout << " - " << std::abs(imagPart) << "i";
                }
            }
        };

        std::cout << "Two complex solutions:\n x1 = ";
        printComplex(x1);
        std::cout << "\n x2 = ";
        printComplex(x2);
        std::cout << '\n';
    }
}

void handleEquations() {
    while (true) {
        std::cout << "\n--- Equation Solver ---\n";
        std::cout << " 1) Linear (a * x + b = 0)\n";
        std::cout << " 2) Quadratic (a * x^2 + b * x + c = 0)\n";
        std::cout << " 0) Back\n";

        int choice = readMenuChoice(0, 2);
        switch (choice) {
            case 0:
                return;
            case 1: {
                double a = readDouble("Enter coefficient a: ");
                double b = readDouble("Enter coefficient b: ");
                solveLinearEquation(a, b);
                break;
            }
            case 2: {
                double a = readDouble("Enter coefficient a: ");
                double b = readDouble("Enter coefficient b: ");
                double c = readDouble("Enter coefficient c: ");
                solveQuadraticEquation(a, b, c);
                break;
            }
            default:
                break;
        }

        if (!askToContinue("Would you like to solve another equation? (y/n): ")) {
            return;
        }
    }
}

void handleArithmetic() {
    while (true) {
        std::cout << "\n--- Expression Evaluator ---\n";
        std::string expression = readLine("Enter an expression (type 'back' to return): ");
        std::string lowered = trim(expression);
        std::transform(lowered.begin(), lowered.end(), lowered.begin(),
                       [](unsigned char ch) { return static_cast<char>(std::tolower(ch)); });
        if (lowered == "back") {
            return;
        }
        try {
            double result = evaluateExpression(expression);
            std::cout << "Result: " << result << '\n';
        } catch (const std::exception& ex) {
            std::cout << "Error: " << ex.what() << '\n';
        }

        if (!askToContinue("Would you like to evaluate another expression? (y/n): ")) {
            return;
        }
    }
}

void handleConversions() {
    while (true) {
        std::cout << "\n--- Numeral System Conversion ---\n";
        int fromBase = chooseBase("Source base:");
        if (fromBase == 0) {
            return;
        }
        int toBase = chooseBase("Target base:");
        if (toBase == 0) {
            return;
        }
        if (fromBase == toBase) {
            std::cout << "Source and target base are identical; nothing to convert.\n";
            continue;
        }

        std::cout << "Enter the integer to convert: ";
        std::string rawValue;
        std::cin >> rawValue;

        try {
            long long decimalValue = parseInteger(rawValue, fromBase);
            std::string converted = formatInteger(decimalValue, toBase);
            std::cout << "Result: " << converted << '\n';
        } catch (const std::exception& ex) {
            std::cout << "Error: " << ex.what() << '\n';
        }

        if (!askToContinue("Would you like to convert another number? (y/n): ")) {
            return;
        }
    }
}

void handleDivisors() {
    while (true) {
        std::cout << "\n--- Divisor Finder ---\n";
        long long value = readInteger("Enter an integer (0 allowed): ");
        if (value == 0) {
            std::cout << "Zero has infinitely many divisors.\n";
        } else {
            try {
                std::vector<long long> divisors = calculateDivisors(value);
                std::cout << "Divisors: ";
                for (std::size_t idx = 0; idx < divisors.size(); ++idx) {
                    if (idx > 0) {
                        std::cout << ", ";
                    }
                    std::cout << divisors[idx];
                }
                std::cout << '\n';
            } catch (const std::exception& ex) {
                std::cout << "Error: " << ex.what() << '\n';
            }
        }

        if (!askToContinue("Would you like to check another number? (y/n): ")) {
            return;
        }
    }
}

}  // namespace

int main() {
    std::cout << "Welcome to the CLI calculator!" << '\n';

    while (true) {
        std::cout << "\n=== Main Menu ===\n";
        std::cout << " 1) Basic operations\n";
        std::cout << " 2) Numeral system conversion\n";
        std::cout << " 3) Divisor finder\n";
        std::cout << " 4) Equation solver\n";
        std::cout << " 5) Report a bug\n";
        std::cout << " 0) Exit\n";

        int choice = readMenuChoice(0, 5);
        switch (choice) {
            case 1:
                handleArithmetic();
                break;
            case 2:
                handleConversions();
                break;
            case 3:
                handleDivisors();
                break;
            case 4:
                handleEquations();
                break;
            case 5:
                std::cout << "Opened a browser to report a bug, if don't see it, please visit:\n";
                std::system("xdg-open https://github.com/Benedek553/cli-calculator/issues");
                std::cout << "https://github.com/Benedek553/cli-calculator/issues\n";
                break;
            case 0:
                std::cout << "Goodbye!\n";
                return 0;
            default:
                break;
        }
    }
}
