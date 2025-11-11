# c-tools

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
| Expression evaluation    | Complex expressions with `+ - * / x :` operators and parentheses. Supports floating-point operations. |
| Number-base conversion   | Accepts binary (`0b`), decimal, and hexadecimal (`0x`) inputs and converts between them; sign handling included. |
| Divisor search           | Produces a sorted list of positive divisors for any integer (except 0). |

## Helpful tips

- In the calculator menu, type `back` to return to the algebraic input mode.

## Contribution

Feel free to submit issues or pull requests!
- The `x` and `:` symbols are interpreted as multiplication and division, respectively, to match common Hungarian input conventions.
- The number-base menu accepts numbers prefixed with `0b` or `0x`.
