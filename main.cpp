/**
 * @file main.cpp
 * @author ralex2304
 * @brief Quad equations solver
 * @version 0.9
 * @date 2023-08-17
 */

#include "quad_solver.h"
#include "args_parser.h"

/**
 * @brief Enables test mode
 */
#define TEST

#ifdef TEST
#include "test/test.h"
#endif

int main(int argc, char* argv[]) {
    printf("# Hello!\n");

    // Parse console args
#ifdef TEST
    ArgsTest args_test = {true, nullptr};
#else // ifndef TEST
    ArgsTest args_test = {false, nullptr};
#endif //idfdef TEST
    switch (args_parse(argc, argv, &args_test)) {
        case ProgramMode::ERROR:
            return Error::raise(Error::ARGS);

        case ProgramMode::HELP:
            print_help(args_test.is_enabled);
            return Error::raise(Error::OK_EXIT);

        case ProgramMode::NORMAL:
            break;

        default:
            assert(0 && "args_parse() returned wrong ProgramMode");
            break;
    };

    // Proccess
#ifdef TEST
    Error::Errors proccessed = test_or_normal(args_test.filename);
#else // idndef TEST
    Error::Errors proccessed = solver_proccess();
#endif // ifdef TEST
    if (proccessed != Error::NO_ERROR)
        return Error::raise(proccessed);

    printf("# Bye!\n");
    return Error::raise(Error::OK_EXIT);
}
