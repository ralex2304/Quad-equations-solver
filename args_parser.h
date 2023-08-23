#ifndef ARGS_PARSER_H_
#define ARGS_PARSER_H_

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "quad_solver.h"

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

/**
 * @brief Specifies test mode parameters
 */
struct ArgsTest {
    bool is_enabled = false;
    const char* filename = nullptr;
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

#endif // #ifndef ARGS_PARSER_H_
