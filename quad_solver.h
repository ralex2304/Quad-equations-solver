#ifndef SOLVER_H_
#define SOLVER_H_

#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>

#include "input.h"

/**
 * @brief Specifies functions status
 */
struct Status {
    enum Statuses {
        NO_ERROR     = -2,  ///< Poison value
        NORMAL_WORK  = -1,  ///< Normal mode system value (isn't returned in main())
        OK_EXIT      =  0,  ///< OK
        ARGS         =  1,  ///< Console arguments error
        COEFFS_INPUT =  2,  ///< User input error
        TEST_INPUT   =  3,  ///< Test file input error
        END_OF_FILE  =  4   ///< End of file reached unexpectedly
    };

    /**
     * @brief Prints and returns given status
     *
     * @param[in] status
     * @return Statuses
     */
    static Statuses raise(const Statuses status);
};

/**
 * @brief Specifies number of soludions of the equation
 */
enum Solutions {
    NAN_SOLUTIONS      = -2,    ///< Poison value
    INFINITE_SOLUTIONS = -1,    ///< Infinite number of solutions
    NO_SOLUTIONS       =  0,    ///< 0 solutions
    ONE_SOLUTION       =  1,    ///< 1 solutions
    TWO_SOLUTIONS      =  2     ///< 2 solutions
};

/**
 * @brief Contains input and output data for solver
 */
struct EqSolverData {
    static const int COEFF_NUM = 3;         ///< Number of equation coefficients

    double coeffs[COEFF_NUM] = {};          ///< Coeffs array
    double roots[COEFF_NUM - 1] = {};       ///< Roots array
    Solutions roots_num = NAN_SOLUTIONS;    ///< Number of solutions
};

/**
 * @brief Inits EqSolverData struct
 *
 * @param[in] data pointer
 */
inline void EqSolverData_init(EqSolverData* data) {
    data->roots_num = NAN_SOLUTIONS;
    for (int i = 0; i < EqSolverData::COEFF_NUM; i++)
        data->coeffs[i] = NAN;
    for (int i = 0; i < EqSolverData::COEFF_NUM - 1; i++)
        data->roots[i] = NAN;
}

/**
 * @brief Main proccess (read, solve and print)
 *
 * @return Status::Statuses
 */
Status::Statuses solver_proccess();

/**
 * @brief Reads coefficients from input to data->coeffs, starting with name 'a'
 *
 * @param[in] data
 * @return InputStatus
 */
InputStatus enter_coeffs(EqSolverData* data);

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
 * @return bool (a == b)
 */
inline bool is_double_equal(const double a, const double b) {
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

#endif // #ifndef SOLVER_H_
