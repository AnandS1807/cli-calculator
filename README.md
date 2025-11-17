# cli-calculator

[![Get it from the Snap Store](https://snapcraft.io/en/light/install.svg)](https://snapcraft.io/cli-calculator)

Simple C++ project providing two command-line tools:

- `calculator`: a full CLI calculator that
  - can read expressions of arbitrary length (e.g. `2 x 4 : 16 + (3-1)`),
  - can convert between number bases (binary, decimal, hexadecimal),
  - and includes an integrated divisors-finder.
- `divisors`: a standalone program that lists the positive divisors of an integer.

## Requirements

- CMake 3.10+
- Any C++17-compatible compiler (GCC, Clang, MSVC)

## Build (out-of-source)

```bash
cmake -S . -B build
cmake --build build --config Release
```

## Run

```bash
# Start the calculator
./build/src/calculator

# Run the divisors tool separately
./build/src/divisors
```

## Features (brief)

| Feature                  | Description |
| ------------------------ | ----------- |
| Expression evaluation    | Complex expressions with `+ - * / x :` operators, parentheses, `sin`, `cos`, `log`, and factorial (`!`). Supports floating-point operations. |
| Number-base conversion   | Accepts binary (`0b`), decimal, and hexadecimal (`0x`) inputs and converts between them; sign handling included. |
| Equation solver          | Solves linear (`a * x + b = 0`) and quadratic (`a * x^2 + b * x + c = 0`) equations, including complex roots. |
| Divisor search           | Produces a sorted list of positive divisors for any integer (except 0). |

## Helpful tips

- In the calculator menu, type `back` to return to the algebraic input mode.
- The `x` and `:` symbols are interpreted as multiplication and division, respectively, to match common Hungarian input conventions.
- The number-base menu accepts numbers prefixed with `0b` or `0x`.
- Trigonometric/logarithmic functions expect radians and must be written with parentheses (e.g. `sin(0.5)`).


## Contribution

Feel free to submit issues or pull requests!
