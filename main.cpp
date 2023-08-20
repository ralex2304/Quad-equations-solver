/**
 * @file main.cpp
 * @author ralex2304
 * @brief Quad equations solver
 * @version 0.8
 * @date 2023-08-17
 */

#include "solver.h"

/**
 * @brief Enables test mode
 */
#define TEST
#ifdef TEST
#include "test/test.h"
#endif

int main() {
    printf("Hello! This program solves quad equations of the form a*x^2 + b*x + c = 0\n"
           "Where \"x\" is a variable and \"a\", \"b\", \"c\" are coefficients\n");

    // Read data
    EqSolverData data = {};
    for (int i = 0; i < EqSolverData::COEFF_NUM; i++)
        data.coeffs[i] = NAN;

    #ifndef TEST
    if (!enter_coeffs(&data)) return 0;
    #else
    FILE* file = NULL;
    if (!test_read(&file, &data, test_name)) return 0;
    #endif

    for (int i = 0; i < EqSolverData::COEFF_NUM; i++)
        assert(!is_double_nan_inf(data.coeffs[i]));


    // Solve data
    for (int i = 0; i < EqSolverData::COEFF_NUM - 1; i++)
        data.roots[i] = NAN;
    data.roots_num = solve_quad(&data);


    // Write data
    #ifndef TEST
    print_roots(&data);
    #else
    test_check(&data, &file);
    #endif

    printf("Bye!");
    return 0;
}
