#ifndef TEST_H_
#define TEST_H_

#include "../solver.h"

/**
 * @brief Specifies test modes
 */
enum class TestMode {
    INPUT_ERROR = -1,
    NO_TESTS =  0,
    TESTS_LEFT  =  1
};

/**
 * @brief Opens test file by filename
 * 
 * @param file - pointer 
 * @param filename - name of file
 * @return MODE
 */
TestMode test_open_file(FILE** file, const char* filename);

/**
 * @brief Reads coeffs from test file
 * 
 * @param[in] data 
 * @param[in] file 
 * @return MODE
 */
TestMode test_enter_coeffs(EqSolverData* data, FILE** file);

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
