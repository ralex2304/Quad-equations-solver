#ifndef TEST_H_
#define TEST_H_

#include "../solver.h"

/**
 * @brief Tells if there are tests for solving.
 *        If there aren't any, enters normal mode
 * 
 * @param[in] file test file pointer
 * @param[in] data
 * @param[in] filename
 * @return MODE
 */
MODE have_tests(FILE** file, EqSolverData* data, char* filename);

/**
 * @brief Opens test file by filename
 * 
 * @param file - pointer 
 * @param filename - name of file
 * @return int success
 */
int test_open_file(FILE** file, const char* filename);

/**
 * @brief Reads coeffs from test file
 * 
 * @param[in] data 
 * @param[in] file 
 * @return MODE
 */
MODE test_enter_coeffs(EqSolverData* data, FILE** file);

/**
 * @brief Reads correct roots from test file
 * 
 * @param[in] data 
 * @param[in] correct_data 
 * @param[in] file 
 * @return int success
 */
int test_read_roots(const EqSolverData* data, EqSolverData* correc_data, FILE** file);

/**
 * @brief calls test_read_roots and test_compare_data
 * 
 * @param data 
 * @param file
 * @return int success 
 */
int test_check(const EqSolverData* data, FILE** file);

/**
 * @brief Compares solutinons number and roots
 * 
 * @param[in] data 
 * @param[in] correct_data 
 */
void test_compare_data(const EqSolverData* data, const EqSolverData* correct_data);

#endif
