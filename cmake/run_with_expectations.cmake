cmake_minimum_required(VERSION 3.10)

# Validate required variables
foreach(var IN ITEMS cmd args expected_exit_code pattern)
  if(NOT DEFINED ${var})
    message(FATAL_ERROR "Missing required variable: ${var}")
  endif()
endforeach()

# Execute the command with the provided arguments
execute_process(
  COMMAND ${cmd} ${args}
  RESULT_VARIABLE actual_exit_code
  OUTPUT_VARIABLE cmd_stdout
  ERROR_VARIABLE cmd_stderr
  OUTPUT_STRIP_TRAILING_WHITESPACE
  ERROR_STRIP_TRAILING_WHITESPACE
)

# Check exit code
if(NOT actual_exit_code EQUAL expected_exit_code)
  message(FATAL_ERROR "Expected exit code ${expected_exit_code}, got ${actual_exit_code}.\nStdout: ${cmd_stdout}\nStderr: ${cmd_stderr}")
endif()

# Validate output pattern in combined stdout and stderr
string(JOIN "\n" combined_output "${cmd_stdout}" "${cmd_stderr}")
string(REGEX MATCH "${pattern}" matched_output "${combined_output}")
if(NOT matched_output)
  message(FATAL_ERROR "Expected pattern '${pattern}' not found in output.\nStdout: ${cmd_stdout}\nStderr: ${cmd_stderr}")
endif()
