cmake_minimum_required(VERSION 3.10)

# Build the executables from the sources in this directory
set(DIVISOR_SOURCES
    divisors.cpp
    divisors_lib.cpp
)

add_executable(divisors ${DIVISOR_SOURCES})
add_executable(calculator main.cpp divisors_lib.cpp)

target_include_directories(divisors PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(calculator PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

if(MSVC)
  target_compile_options(divisors PRIVATE /W4)
  target_compile_options(calculator PRIVATE /W4)
endif()
