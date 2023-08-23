#ifndef TEST_H_
#define TEST_H_

#include <assert.h>
#include "../solver.h"
#include "../args_parser.h"

/**
 * @brief Specifies test modes
 */
enum class TestMode {
    INPUT_ERROR = -1,
    NO_TESTS    =  0,
    TESTS_LEFT  =  1
};

/**
 * @brief Opens test file by filename
 * 
 * @param file - pointer 
 * @param filename - name of file
 * @return TestMode
 */
TestMode test_open_file(FILE** file, const char* filename);

/**
 * @brief Reads coeffs from test file
 * 
 * @param[in] data 
 * @param[in] file 
 * @return TestMode
 */
TestMode test_enter_coeffs(EqSolverData* data, FILE* file);

/**
 * @brief Opens test file and decides: solver_proccess() or test_proccess()
 * 
 * @param data 
 * @param filename 
 * @return Error::Errors 
 */
Error::Errors test_or_normal(const char* filename);

/**
 * @brief Main test proccess (read, test)
 * 
 * @param data 
 * @param file 
 * @return Error::Errors 
 */
Error::Errors test_proccess(FILE* file);

/**
 * @brief Reads correct roots from test file
 * 
 * @param[in] data 
 * @param[in] correct_data 
 * @param[in] file 
 * @return int success
 */
int test_read_roots(const EqSolverData* data, EqSolverData* correc_data, FILE* file);

/**
 * @brief Specifies test results
 * 
 */
enum class TestResult {
    ERROR  = -1,
    FAILED =  0,
    PASSED =  1
};

/**
 * @brief Compares solutinons number and roots
 * 
 * @param[in] data 
 * @param[in] correct_data 
 */
TestResult test_compare_data(const EqSolverData* data, const EqSolverData* correct_data, const int test_n);

/**
 * @brief calls test_read_roots and test_compare_data
 * 
 * @param data 
 * @param file
 * @return int success 
 */
TestResult test_check(const EqSolverData* data, FILE* file, const int test_n);

/**
 * @brief Prints summary about all tests
 * 
 * @param test_num 
 * @param passed_test_num 
 */
void test_print_summary(const int test_num, const int passed_test_num);

#endif
