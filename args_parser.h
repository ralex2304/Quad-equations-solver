#ifndef ARGS_H_
#define ARGS_H_

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "solver.h"

/**
 * @brief Specifies int main() returns
 */
enum class ProgramMode {
    ERROR  = -1,
    HELP   =  0,
    NORMAL =  1,
};

const char ARGS_HELP[] = "-h";
const char ARGS_TEST_FILE_PATH[] = "-t";

struct ArgsTest {
    bool en = false;
    const char* filename;
};

/**
 * @brief Parses console arguments
 * 
 * @param argc 
 * @param argv 
 * @param filename for test mode
 * @return int success
 */
ProgramMode args_parse(int argc, char* argv[], ArgsTest* test);

#endif