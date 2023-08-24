#ifndef TEST_H_
#define TEST_H_

#include <assert.h>

#include "../quad_solver.h"
#include "../args_parser.h"
#include "../console.h"

/**
 * @brief Specifies test modes
 */
enum class TestMode {
    INPUT_ERROR = -1,   ///< Input error
    NO_TESTS    =  0,   ///< No tests left in file or user didn't dpecified test mode
    TESTS_LEFT  =  1    ///< There are tests left in the file
};

/**
 * @brief Opens test file by filename
 *
 * @param[out] file - pointer
 * @param[in] filename - name of file
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
 * @param[in] filename
 * @return Error::Errors
 */
Status::Statuses test_or_normal(const char* filename);

/**
 * @brief Main test proccess (read, test)
 *
 * @param[in] file
 * @return Error::Errors
 */
Status::Statuses test_proccess(FILE* file);

/**
 * @brief Reads correct roots from test file
 *
 * @param[in] data
 * @param[in] correct_data
 * @param[in] file
 * @return bool success
 */
bool test_read_roots(const EqSolverData* data, EqSolverData* correc_data, FILE* file);

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
 * @param[in] test_n number of test
 */
TestResult test_compare_data(const EqSolverData* data, const EqSolverData* correct_data, const int test_n);

/**
 * @brief calls test_read_roots and test_compare_data
 *
 * @param[in] data
 * @param[in] file
 * @param[in] test_n number of test
 * @return int success
 */
TestResult test_read_and_compare(const EqSolverData* data, FILE* file, const int test_n);

/**
 * @brief Prints summary about all tests
 *
 * @param[in] test_num
 * @param[in] passed_test_num
 */
void test_print_summary(const int test_num, const int passed_test_num);

#endif // #ifndef TEST_H_
