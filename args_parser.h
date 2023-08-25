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
    ArgsMode (*func) (const Argument args_dict[], const int args_dict_len,
                      int* arg_i, int argc, char* argv[], ArgsTest* args_test);   ///< Function
    const char* description;                                                      ///< Description
    bool is_enabled = true;
};

/**
 * @brief Prints help
 *
 * @param[in] args_dict
 * @param[in] args_dict_len
 * @param[in] arg_i number of current argument
 * @param[in] argc  int main() argc
 * @param[in] argv  int main() argv
 * @param[in] args_test
 * @return ArgsMode
 */
ArgsMode print_help(const Argument args_dict[], const int args_dict_len,
                    int* arg_i, int argc, char* argv[], ArgsTest* args_test);

/**
 * @brief Reads test file name from console
 *
 * @param[in] args_dict
 * @param[in] args_dict_len
 * @param[in] arg_i number of current argument
 * @param[in] argc  int main() argc
 * @param[in] argv  int main() argv
 * @param[out] args_test
 * @return ArgsMode
 */
ArgsMode read_test_filename(const Argument args_dict[], const int args_dict_len,
                            int* arg_i, int argc, char* argv[], ArgsTest* args_test);

/**
 * @brief Parses console arguments
 *
 * @param[in] argc
 * @param[in] argv
 * @param[out] args_test
 * @return Status::Statuses
 */
Status::Statuses args_parse(int argc, char* argv[], ArgsTest* args_test);

/**
 * @brief Enables test mode args in args_dict
 *
 * @param[out] args_dict
 * @param[in] args_dict_len
 */
inline void enable_test_args(Argument args_dict[], const int args_dict_len) {
    assert(args_dict);

    for (int i = 0; i < args_dict_len; i++) {
        if (strcmp(args_dict[i].arg, "-t") == 0)
            args_dict[i].is_enabled = true;
    }
}

#endif // #ifndef ARGS_PARSER_H_
