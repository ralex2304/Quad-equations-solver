/**
 * @file main.cpp
 * @author ralex2304
 * @brief Quad equations solver
 * @version 0.7
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
    SolverData data = {};
    for (int i = 0; i < data.COEFF_NUM; i++)
        data.coeffs[i] = NAN;
    #ifndef TEST
        if (!enter_coeffs(&data)) exit(0);
    #else
        FILE* file = NULL;
        test_open_file(&file, test_name);

        if (!test_enter_coeffs(&data, file)) exit(0);
    #endif
    for (int i = 0; i < data.COEFF_NUM; i++)
        assert(!isnan(data.coeffs[i]));
    
    // Solve data
    for (int i = 0; i < data.COEFF_NUM - 1; i++)
        data.roots[i] = NAN;
    data.roots_num = solve_quad(&data);

    // Write data
    #ifndef TEST
        print_roots(&data);
    #else
        SolverData correct_data = {};
        for (int i = 0; i < correct_data.COEFF_NUM - 1; i++)
            correct_data.roots[i] = NAN;
        test_read_roots(&data, &correct_data,file);

        fclose(file);

        test_check_data(&data, &correct_data);
    #endif
    
    printf("Bye!");
    return 0;
}
