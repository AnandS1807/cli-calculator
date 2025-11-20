#include "divisors.hpp"
#include "ansi_colors.hpp"

#include <cstddef>
#include <iostream>
#include <vector>

int main(int argc, char** argv) {
    // allow disabling colors with --no-color or -nc
    for (int i = 1; i < argc; ++i) {
        std::string arg(argv[i]);
        if (arg == "--no-color" || arg == "-nc") {
            setColorsEnabled(false);
            break;
        }
    }
    long long n;
    std::cout << BOLD << BLUE << "Enter an integer: " << RESET;
    if (!(std::cin >> n)) {
        std::cerr << RED << "Invalid input." << RESET << '\n';
        return 1;
    }

    if (n == 0) {
        std::cout << CYAN << "Zero has infinitely many divisors." << RESET << '\n';
        return 0;
    }

    std::vector<long long> divisors = calculateDivisors(n);

    std::cout << GREEN << "Divisors: " << RESET;
    for (std::size_t idx = 0; idx < divisors.size(); ++idx) {
        if (idx > 0) {
            std::cout << YELLOW << ", " << RESET;
        }
        std::cout << GREEN << divisors[idx] << RESET;
    }
    std::cout << '\n';

    return 0;
}
