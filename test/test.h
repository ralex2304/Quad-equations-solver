#ifndef _TEST_H
#define _TEST_H

#include "../solver.h"

const char test_name[] = "test/test.txt"; // test file name

/**
 * @brief Opens test file by filename
 * 
 * @param[in] file - pointer 
 * @param[in] filename - name of file
 */
void test_open_file(FILE** file, const char* filename);

/**
 * @brief Reads coeffs from test file
 * 
 * @param[in] data 
 * @param[in] file 
 * @return int success
 */
int test_enter_coeffs(SolverData* data, FILE* file);

/**
 * @brief Reads correct roots from test file
 * 
 * @param[in] data 
 * @param[in] correct_data 
 * @param[in] file 
 */
void test_read_roots(const SolverData* data, SolverData* correc_data, FILE* file);

/**
 * @brief Checks solutions number and roots
 * 
 * @param[in] data 
 * @param[in] correct_data 
 */
void test_check_data(const SolverData* data, const SolverData* correct_data);

#endif
