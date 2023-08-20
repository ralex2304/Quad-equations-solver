#ifndef SOLVER_H_
#define SOLVER_H_

#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>

/**
 * @brief Specifies number of soludions of the equation
 */
enum SOLUTIONS {
    NAN_SOLUTIONS = -2,
    INFINITE_SOLUTIONS = -1,
    NO_SOLUTIONS = 0,
    ONE_SOLUTION = 1,
    TWO_SOLUTIONS = 2
};

/**
 * @brief Contains input and output data for solver
 */
struct EqSolverData {
    static const int COEFF_NUM = 3;
    double coeffs[COEFF_NUM] = {};
    double roots[COEFF_NUM - 1] = {};
    SOLUTIONS roots_num = NAN_SOLUTIONS;
};

/**
 * @brief Reads coefficients from input to data->coeffs, starting with name 'a'
 * 
 * @param[in] data 
 * @return int success
 */
int enter_coeffs(EqSolverData* data);

/**
 * @brief Solves linear equations
 * 
 * @param[in] data 
 * @return SOLUTIONS number of solutions
 */
SOLUTIONS solve_lin(EqSolverData* data);

/**
 * @brief Solves quad equations
 * 
 * @param data[in] 
 * @return SOLUTIONS number of solutions
 */
SOLUTIONS solve_quad(EqSolverData* data);

/**
 * @brief Prints roots
 * 
 * @param[in] data 
 */
void print_roots(const EqSolverData* data);


/**
 * @brief Flushes input
 * 
 * @return int number of flushed symbols
 */
int input_flush(FILE* stream = stdin);

/**
 * @brief Reads double from input to pointer
 * 
 * @param[in] x
 * @param[in] stream 
 * @return int success
 */
int read_num(double* x, FILE* stream = stdin);

/**
 * @brief Reads int from input to pointer
 * 
 * @param[in] x 
 * @param[in] stream 
 * @return int success
 */
int read_num(int* x, FILE* stream = stdin);

/**
 * @brief Reads coefficient double from input
 * 
 * @param[in] c coefficient name
 * @param[in] x 
 * @return int success
 */
int enter_coeff(const char c, double* x);

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
    return abs(a - b) < DOUBLE_COMPARE_PREC;
};

/**
 * @brief Tells if a double is NAN or infinite
 * 
 * @param a 
 * @return int 
 */
inline int is_double_nan_inf(const double a) {
    return isnan(a) || isinf(a);
}

#endif
