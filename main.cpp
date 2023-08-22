/**
 * @file main.cpp
 * @author ralex2304
 * @brief Quad equations solver
 * @version 0.9
 * @date 2023-08-17
 */

#include "solver.h"
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

    char* filename = nullptr;
    switch (args_parse(argc, argv, &filename)) {
        case ProgramMode::ERROR:
            return Error::raise(Error::ARGS);

        case ProgramMode::HELP:
            return Error::OK;

        case ProgramMode::NORMAL:
            break;

        default:
            assert(0 && "args_parse() returned wrong ProgramMode");
            break;
    };

    // Read data
    EqSolverData data = {};
    EqSolverData_init(&data);
    
#ifdef TEST
    FILE* file = nullptr;
    switch (test_open_file(&file, filename)) {
        case TestMode::INPUT_ERROR:
            return Error::raise(Error::TEST_INPUT);

        case TestMode::TESTS_LEFT: // TEST mode
        {
            TestMode tests = TestMode::INPUT_ERROR;

            while ((tests = test_enter_coeffs(&data, &file)) != TestMode::NO_TESTS) {
                if (tests == TestMode::INPUT_ERROR) return Error::raise(Error::TEST_INPUT);

                for (int i = 0; i < EqSolverData::COEFF_NUM; i++)
                    assert(isfinite(data.coeffs[i]));

                solve_quad(&data);

                if (!test_check(&data, &file))
                    return Error::raise(Error::TEST_INPUT);

                EqSolverData_init(&data);
            }
            break;
        } 

        case TestMode::NO_TESTS: // Normal mode
#endif
            if (!enter_coeffs(&data)) return Error::raise(Error::COEFFS_INPUT);
            
            for (int i = 0; i < EqSolverData::COEFF_NUM; i++)
                    assert(isfinite(data.coeffs[i]));

            solve_quad(&data);

            print_roots(&data);
#ifdef TEST
        break;
        default:
            assert(0 && "test_open_file() returned wrong mode");
    };
#endif

    printf("# Bye!\n");
    return Error::OK;
}
