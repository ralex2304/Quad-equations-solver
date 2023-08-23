#ifndef ARGS_PARSER_H_
#define ARGS_PARSER_H_

#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "quad_solver.h"

/**
 * @brief Specifies int main() returns
 */
enum class ArgsMode {
    ERROR    = -1,    ///< Error
    EXIT     =  0,    ///< Continue reading args, but then normal exit
    CONTINUE =  1,    ///< Continue reading args
};

/**
 * @brief Specifies test mode parameters
 */
struct ArgsTest {
    bool is_enabled = false;        ///< TEST is defined
    const char* filename = nullptr; ///< test file name
};

/**
 * @brief Specifies console argument parametres: name, function and description
 *
 */
struct Argument {
    const char* arg;                                                              ///< Argument name
    ArgsMode (*func) (int* arg_i, int argc, char* argv[], ArgsTest* args_test);   ///< Function
    const char* description;                                                      ///< Description
};

/**
 * @brief Prints help
 *
 * @param arg_i number of current argument
 * @param argc  int main() argc
 * @param argv  int main() argv
 * @param args_test
 * @return ArgsMode
 */
ArgsMode print_help(int* arg_i, int argc, char* argv[], ArgsTest* args_test);

/**
 * @brief Reads test file name from console
 *
 * @param arg_i number of current argument
 * @param argc  int main() argc
 * @param argv  int main() argv
 * @param args_test
 * @return ArgsMode
 */
ArgsMode read_test_filename(int* arg_i, int argc, char* argv[], ArgsTest* args_test);

/**
 * @brief Specifies console arguments types number
 */
const int ARGS_STRUCT_COUNT = 2;

/**
 * @brief This array contains console options, their functions and descriptions
 */
const Argument args[ARGS_STRUCT_COUNT] = {
    {"-h", print_help,          "#   -h - prints help information\n"}, ///< Help option

    {"-t", read_test_filename, "#   -t - specify test file name after this (works only if test mode enabled)\n"
                                "# Test file format (there might be several such sections):\n"
                                "# <coeff a> <coeff b> <coeff c>\n"
                                "# <solutions number>\n"
                                "# <solution 1 (if exists)> <solution 2 (if exists)>\n"
                                "# \n"
                                "# <Next test>\n"}                     ///< Test option
};

/**
 * @brief Parses console arguments
 *
 * @param argc
 * @param argv
 * @param filename for test mode
 * @return Status::Statuses
 */
Status::Statuses args_parse(int argc, char* argv[], ArgsTest* test);

#endif // #ifndef ARGS_PARSER_H_
