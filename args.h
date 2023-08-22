#ifndef ARGS_H_
#define ARGS_H_

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "solver.h"

/**
 * @brief Specifies int main() returns
 */
enum class MAIN_RETURNS {
    OK = 0,
    COEFFS_INPUT_ERROR = 1,
    TEST_INPUT_ERROR = 2
};

const char ARGS_HELP[] = "-h";
const char ARGS_TEST_FILE_PATH[] = "-t";

/**
 * @brief Parses console arguments
 * 
 * @param argc 
 * @param argv 
 * @param filename for test mode
 */
void args_parse(int argc, char* argv[], char** filename);

#endif