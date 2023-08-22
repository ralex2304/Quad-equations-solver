/**
 * @file main.cpp
 * @author ralex2304
 * @brief Quad equations solver
 * @version 0.8
 * @date 2023-08-17
 */

#include "solver.h"
#include "args.h"
#include "test/test.h"

/**
 * @brief Enables test mode
 */
#define TEST

int main(int argc, char* argv[]) {
    printf("# Hello!\n");

    char* filename = NULL;
    args_parse(argc, argv, &filename);
    #ifndef TEST
    filename = NULL;
    #endif

    // Read data
    EqSolverData data;
    EqSolverData_init(&data);
    
    FILE* file = NULL;
    MODE tests = TESTS_ENDED_MODE;
    while ((int)(tests = have_tests(&file, &data, filename))) {
        if (tests == INPUT_ERROR_MODE) 
            return (int)MAIN_RETURNS::COEFFS_INPUT_ERROR;
        for (int i = 0; i < EqSolverData::COEFF_NUM; i++)
            assert(isfinite(data.coeffs[i]));
        
        // Solve data
        solve_quad(&data);
        
        // Write data
        if (tests == NORMAL_MODE) {
            print_roots(&data);
            break;
        }

        // Or check data if test mode
        if (!test_check(&data, &file)) return (int)MAIN_RETURNS::TEST_INPUT_ERROR;

        EqSolverData_init(&data);
    }

    printf("# Bye!\n");
    return (int)MAIN_RETURNS::OK;
}
