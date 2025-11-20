cmake_minimum_required(VERSION 3.10)

project(c-tools VERSION 0.1 LANGUAGES CXX)

# Recommended: out-of-source builds
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include(CTest)

# Enable good warnings for GCC/Clang
if(CMAKE_CXX_COMPILER_ID MATCHES "(GNU|Clang)")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_subdirectory(src)

option(BUILD_TESTING "Enable testing" ON)

if(BUILD_TESTING)
  enable_testing()

  add_test(
    NAME calculator_eval_basic
    COMMAND ${CMAKE_COMMAND}
      -Dcmd=$<TARGET_FILE:calculator>
      "-Dargs=--no-color;--eval;1+2*3"
      -Dexpected_exit_code=0
      "-Dpattern=Result:[ ]7"
      -P ${CMAKE_SOURCE_DIR}/cmake/run_with_expectations.cmake)

  add_test(
    NAME calculator_eval_missing_expr
    COMMAND ${CMAKE_COMMAND}
      -Dcmd=$<TARGET_FILE:calculator>
      "-Dargs=--no-color;--eval"
      -Dexpected_exit_code=1
      "-Dpattern=missing expression"
      -P ${CMAKE_SOURCE_DIR}/cmake/run_with_expectations.cmake)

  add_test(
    NAME calculator_square_root_value
    COMMAND ${CMAKE_COMMAND}
      -Dcmd=$<TARGET_FILE:calculator>
      "-Dargs=--no-color;--square-root;9"
      -Dexpected_exit_code=0
      "-Dpattern=Result:[ ]3"
      -P ${CMAKE_SOURCE_DIR}/cmake/run_with_expectations.cmake)

  add_test(
    NAME calculator_square_root_negative
    COMMAND ${CMAKE_COMMAND}
      -Dcmd=$<TARGET_FILE:calculator>
      "-Dargs=--no-color;--square-root;-9"
      -Dexpected_exit_code=1
      "-Dpattern=square root undefined for negative values"
      -P ${CMAKE_SOURCE_DIR}/cmake/run_with_expectations.cmake)
endif()

install(TARGETS divisors calculator
        RUNTIME DESTINATION bin)
