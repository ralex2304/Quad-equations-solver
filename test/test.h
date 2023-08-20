#ifndef TEST_H_
#define TEST_H_

#include "../solver.h"

const char test_name[] = "test/test.txt"; // test file name

int test_read(FILE** file, EqSolverData* data, const char* filename);

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
 * @return int success
 */
int test_enter_coeffs(EqSolverData* data, FILE** file);

/**
 * @brief Reads correct roots from test file
 * 
 * @param[in] data 
 * @param[in] correct_data 
 * @param[in] file 
 */
void test_read_roots(const EqSolverData* data, EqSolverData* correc_data, FILE** file);

/**
 * @brief 
 * 
 * @param data 
 * @param file 
 */
void test_check(const EqSolverData* data, FILE** file);

/**
 * @brief Compares solutinons number and roots
 * 
 * @param[in] data 
 * @param[in] correct_data 
 */
void test_compare_data(const EqSolverData* data, const EqSolverData* correct_data);

#endif
