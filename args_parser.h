#ifndef ARGS_H_
#define ARGS_H_

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "solver.h"

/**
 * @brief Specifies int main() returns
 */
struct Error {
    enum Errors {
        OK           = 0,
        ARGS         = 1,
        COEFFS_INPUT = 2,
        TEST_INPUT   = 3
    };
    static Errors raise(Errors err);
};

enum class ProgramMode {
    ERROR  = -1,
    HELP   =  0,
    NORMAL =  1,
};

const char ARGS_HELP[] = "-h";
const char ARGS_TEST_FILE_PATH[] = "-t";

/**
 * @brief Parses console arguments
 * 
 * @param argc 
 * @param argv 
 * @param filename for test mode
 * @return int success
 */
ProgramMode args_parse(int argc, char* argv[], char** filename);

#endif