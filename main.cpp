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
    Status::Statuses args_parse_res = args_parse(argc, argv, &args_test);
    if (args_parse_res != Status::NORMAL_WORK)
        return Status::raise(args_parse_res);

    // Proccess
#ifdef TEST
    Status::Statuses proccessed = test_or_normal(args_test.filename);
#else  // ifndef TEST
    Status::Statuses proccessed = solver_proccess();
#endif // ifdef TEST
    if (proccessed != Status::NORMAL_WORK)
        return Status::raise(proccessed);

    printf("# Bye!\n");
    return Status::raise(Status::OK_EXIT);
}
