[![cli-calculator](https://snapcraft.io/cli-calculator/badge.svg)](https://snapcraft.io/cli-calculator)
[![C++ CI Build & Draft Release](https://github.com/Benedek553/cli-calculator/actions/workflows/release.yml/badge.svg)](https://github.com/Benedek553/cli-calculator/actions/workflows/release.yml)
[![CodeQL](https://github.com/Benedek553/cli-calculator/actions/workflows/github-code-scanning/codeql/badge.svg)](https://github.com/Benedek553/cli-calculator/actions/workflows/github-code-scanning/codeql)
[![Lint](https://github.com/Benedek553/cli-calculator/actions/workflows/lint.yml/badge.svg)](https://github.com/Benedek553/cli-calculator/actions/workflows/lint.yml)
[![pages-build-deployment](https://github.com/Benedek553/cli-calculator/actions/workflows/pages/pages-build-deployment/badge.svg)](https://github.com/Benedek553/cli-calculator/actions/workflows/pages/pages-build-deployment)
# cli-calculator

Simple C++ project providing two command-line tools:

- `calculator`: a full CLI calculator that
  - can read expressions of arbitrary length (e.g. `2 x 4 : 16 + (3-1)`),
  - can convert between number bases (binary, decimal, hexadecimal),
  - and includes an integrated divisors-finder.
- `divisors`: a standalone program that lists the positive divisors of an integer.
## Quickstart

[![Get it from the Snap Store](https://snapcraft.io/en/light/install.svg)](https://snapcraft.io/cli-calculator)

### Option 1: Install from the Snap Store

Install the snap package directly:

```bash
sudo snap install cli-calculator
```

Run the calculator:

```bash
cli-calculator
```
### Option 2: Download the Latest Release (Manual Installation)

1. Download the latest prebuilt binary from the **Releases** page.
2. Make it executable:

   ```bash
   chmod +x calculator
   ```
3. Move it to your system path:

   ```bash
   sudo mv calculator /usr/local/bin/
   ```
4. Verify installation:

   ```bash
   calculator --help
   ```

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

## CLI flags

- `--no-color` / `-nc`: disable ANSI colors in all outputs.
- `--eval <expression>` / `-e <expression>`: evaluate and print the result, then exit.
- `--square-root <value>` / `-sqrt <value>`: compute a single square root (fails for negative inputs).

## Supported functions in expressions

`sin`, `cos`, `tan`, `cot`, `asin`, `acos`, `atan`, `log`, `exp`, `sqrt`, `sinh`, and factorial `!`. Expressions also accept `x` and `:` as multiplication and division.

## Helpful tips

- In the calculator menu, type `back` to return to the algebraic input mode.
- The `x` and `:` symbols are interpreted as multiplication and division, respectively, to match common Hungarian input conventions.
- The number-base menu accepts numbers prefixed with `0b` or `0x`.
- Trigonometric/logarithmic functions expect radians and must be written with parentheses (e.g. `sin(0.5)`).


## Contribution

Feel free to submit issues or pull requests!
