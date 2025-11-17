# Contributing to CLI-Calculator

Thank you for your interest in contributing to **CLI-Calculator**! This project welcomes all contributions, whether they involve new features, bug fixes, documentation improvements, or general enhancements.

Please follow the guidelines below to ensure a smooth and efficient contribution process.

---

## 1. Getting Started

1. **Fork the repository** on GitHub.
2. **Clone your fork** locally:

   ```sh
   git clone https://github.com/<username>/cli-calculator
   ```
3. Create a build directory and compile the project:

   ```sh
   mkdir build && cd build
   cmake ..
   make
   ```
4. Run the calculator:

   ```sh
   ./cli-calculator
   ```

---

## 2. Branching Strategy

Please follow this branching approach:

* **main** – stable releases only
* **dev** – active development
* **feature/<name>** – new features
* **fix/<name>** – bug fixes

Example:

```sh
git checkout -b feature/add-tan-function
```

---

## 3. Coding Standards

To keep the project consistent, please follow these guidelines:

### **C++ Style Guidelines**

* Use modern C++ (C++17 or newer).
* Prefer `std::string`, `std::vector`, and other STL containers.
* Avoid raw pointers when possible.
* Use `const` correctness.
* Handle all user input defensively.
* Provide meaningful error messages.

### **Formatting**

* Use consistent indentation (4 spaces).
* Keep functions short and focused.
* Split large modules into separate `.cpp` / `.hpp` files when appropriate.

---

## 4. Commit Guidelines

* Write clear commit messages.
* Use conventional commit style when possible:

Examples:

* `feat: add quadratic equation solver`
* `fix: prevent crash on empty expression`
* `docs: update installation instructions`
* `refactor: simplify token parsing`

---

## 5. Adding New Features

If you plan to implement a new feature:

1. Open an Issue describing your idea.
2. Wait for feedback/approval.
3. Implement the feature in a feature branch.
4. Add tests if applicable.
5. Submit a Pull Request to the **dev** branch.

This keeps development organized and avoids duplicate work.

---

## 6. Pull Request Process

Before submitting a PR:

* Ensure the project compiles.
* Run basic tests manually.
* Keep PRs focused on a single change.
* Reference any related Issues.

Your PR will be reviewed, and feedback may be provided. Once approved, it will be merged.

---

## 7. Reporting Bugs

If you find a bug:

* Visit the Issue tracker: [https://github.com/Benedek553/cli-calculator/issues](https://github.com/Benedek553/cli-calculator/issues)
* Include:

  * A clear description
  * Steps to reproduce
  * Expected vs actual behavior
  * Platform / compiler information

---

## 8. Security

If you discover a security-related problem, please follow the instructions in **SECURITY.md**.

---

## 9. License

By contributing to this project, you agree that your contributions will be licensed under the
**Apache License 2.0**, the same license as the project.

---

Thank you for contributing to CLI-Calculator! Your time, effort, and interest are greatly appreciated.
