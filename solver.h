#ifndef SOLVER_H_
#define SOLVER_H_

#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>

#include "input.h"

/**
 * @brief Specifies functions errors
 * 
 */
struct Error {
    enum Errors {
        NO_ERROR     = -1,
        OK_EXIT      =  0,
        ARGS         =  1,
        COEFFS_INPUT =  2,
        TEST_INPUT   =  3,
        END_OF_FILE  =  4
    };

    /**
     * @brief Prints and returns given error
     * 
     * @param err 
     * @return Errors 
     */
    static Errors raise(const Errors err);
};

/**
 * @brief Specifies number of soludions of the equation
 */
enum Solutions {
    NAN_SOLUTIONS      = -2,
    INFINITE_SOLUTIONS = -1,
    NO_SOLUTIONS       =  0,
    ONE_SOLUTION       =  1,
    TWO_SOLUTIONS      =  2
};

/**
 * @brief Contains input and output data for solver
 */
struct EqSolverData {
    static const int COEFF_NUM = 3;

    double coeffs[COEFF_NUM] = {};
    double roots[COEFF_NUM - 1] = {};
    Solutions roots_num = NAN_SOLUTIONS;
};

/**
 * @brief Inits EqSolverData struct
 * 
 * @param data pointer
 */
inline void EqSolverData_init(EqSolverData* data) {
    for (int i = 0; i < EqSolverData::COEFF_NUM; i++)
        data->coeffs[i] = NAN;
    for (int i = 0; i < EqSolverData::COEFF_NUM - 1; i++)
        data->roots[i] = NAN;
    data->roots_num = NAN_SOLUTIONS;
}

/**
 * @brief Main proccess (read, solve and print)
 * 
 * @param data 
 * @return Error::Errors 
 */
Error::Errors solver_proccess();

/**
 * @brief Reads coefficients from input to data->coeffs, starting with name 'a'
 * 
 * @param[in] data 
 * @return InputError
 */
InputError enter_coeffs(EqSolverData* data);

/**
 * @brief Solves linear equations
 * 
 * @param[in] data 
 */
void solve_lin(EqSolverData* data);

/**
 * @brief Solves quad equations
 * 
 * @param[in] data
 */
void solve_quad(EqSolverData* data);

/**
 * @brief Prints roots
 * 
 * @param[in] data 
 */
void print_roots(const EqSolverData* data);

/**
 * @brief Tells if two doubles are equal with precision of DOUBLE_COMPARE_PRECISION
 * 
 * @param[in] a First double
 * @param[in] b Second double
 * @return int (a == b)
 */
inline int is_double_equal(const double a, const double b) {
    assert(!isnan(a) && !isinf(a) && !isnan(b) && !isinf(b));

    static const double DOUBLE_COMPARE_PREC = 0.000001;
    return fabs(a - b) < DOUBLE_COMPARE_PREC;
};

/**
 * @brief Returns valid root (check for -0.0)
 * 
 * @param root 
 * @return double 
 */
inline double valid_root(double root) {
    if (is_double_equal(root, 0))
        return fabs(root);
    return root;
}

/**
 * @brief Swaps values of two pointers
 * 
 * @param a First pointer
 * @param b Second pointer
 */
inline void swap(double* a, double* b) {

    //      --------------
    //     |             |
    double c = *a; //    |
               *a = *b;//v
                    *b = c;
}

/**
 * @brief Bubble sorting algorithm
 * 
 * @param arr array
 * @param size array size
 */
inline void bubble_sort(double* arr, int size) {
    for (int i = 0; i < size - 1; i++)
        for (int j = 0; j < size - 1; j++)
            if (arr[j] > arr[j+1])
                swap(arr + j, arr + j + 1);
}

/**
 * @brief Prints help
 */
void print_help(const bool help_en);

#endif
