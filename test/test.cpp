#include "test.h"

Error::Errors test_or_normal(const char* filename) {
    FILE* file = nullptr;
    switch (test_open_file(&file, filename)) {
        case TestMode::INPUT_ERROR:
            return Error::TEST_INPUT;
        case TestMode::TESTS_LEFT: // TEST mode
            return test_proccess(file);
        case TestMode::NO_TESTS: // Normal mode
            return solver_proccess();
        default:
            assert(0 && "test_open_file() returned wrong TestMode");
            break;
    }
    return Error::NO_ERROR;
}

Error::Errors test_proccess(FILE* file) {
    TestMode tests = TestMode::INPUT_ERROR;

    int test_num = 0;
    int passed_test_num = 0;

    EqSolverData data = {};
    EqSolverData_init(&data);

    while ((tests = test_enter_coeffs(&data, file)) != TestMode::NO_TESTS) {
        if (tests == TestMode::INPUT_ERROR)
            return Error::TEST_INPUT;

        for (int i = 0; i < EqSolverData::COEFF_NUM; i++)
            assert(isfinite(data.coeffs[i]));

        solve_quad(&data);
        
        test_num++;
        switch (test_check(&data, file, test_num)) {
            case TestResult::ERROR:
                return Error::TEST_INPUT;
            case TestResult::FAILED:
                break;
            case TestResult::PASSED:
                passed_test_num++;
                break;
            default:
                assert(0 && "test_check() returned incorrect TestResult");
                break;
        }

        EqSolverData_init(&data);
    }

    test_print_summary(test_num, passed_test_num);

    return Error::NO_ERROR;
}

TestMode test_open_file(FILE** file, const char* filename) {
    assert(file);

    if (filename == nullptr)
        return TestMode::NO_TESTS;

    *file = fopen(filename, "r");
    if (*file == nullptr) {
        printf("Error opening test file %s\n", filename);
        perror("Message");
        fclose(*file);
        return TestMode::INPUT_ERROR;
    }
    return TestMode::TESTS_LEFT;
}

TestMode test_enter_coeffs(EqSolverData* data, FILE* file) {
    assert(data && file);

    for (int i = 0; i < EqSolverData::COEFF_NUM; i++) {
        switch (read_num(data->coeffs + i, file, false)) {
            case InputError::END_OF_FILE:
                return TestMode::NO_TESTS;
                break;
            case InputError::WRONG_DATA:
                printf("Error reading coefficient from test file\n");
                return TestMode::INPUT_ERROR;
                break;
            case InputError::OK:
                break;
            default:
                assert(0 && "read_num() returned wrong InputError");
                break;
        } 
    }
    if (!input_flush(file)) {
        printf("Error reading coefficient from test file\n");
        return TestMode::INPUT_ERROR;
    }
    return TestMode::TESTS_LEFT;
}

int test_read_roots(const EqSolverData* data, EqSolverData* correct_data, FILE* file) {
    assert(data && correct_data && file);
    
    if (read_num(((int*)&correct_data->roots_num), file) != InputError::OK) {
        printf("Error reading number of solutions from test file\n");
        fclose(file);
        return 0;
    }

    for (int i = 0; i < (int)correct_data->roots_num; i++) {
        if(read_num(&correct_data->roots[i], file, false) != InputError::OK) {
            printf("Error reading solution from test file\n");
            fclose(file);
            return 0;
        }
    }
    if (!input_flush(file)) {
        printf("Error reading solution from test file\n");
        return 0;
    }
    bubble_sort(correct_data->roots, correct_data->roots_num);
    return 1;
}

TestResult test_compare_data(const EqSolverData* data, const EqSolverData* correct_data, const int test_n) {
    assert(data && correct_data);

    printf("Test %d. ", test_n);

    if (data->roots_num != correct_data->roots_num) {
        printf("Failed. Incorrect number of solutions.");
        return TestResult::FAILED;
    } else {
        printf("Number of solutions is correct: %d. ", (int)correct_data->roots_num);
    }

    bool passed = true;
    for (int i = 0; i < (int) correct_data->roots_num; i++) {
        assert(isfinite(data->roots[i]) && isfinite(correct_data->roots[i]));
        if (!is_double_equal(data->roots[i], correct_data->roots[i])) {
            printf("Incorrect root %d\n", (i+1));
            printf("    Correct root:  %lf\n", correct_data->roots[i]);
            printf("    Received root: %lf\n" , data->roots[i]);
            passed = false;
        } else {
            printf("Root %d is correct. ", (i+1));
        }
    }
    if (!passed) {
        printf("\n");
        return TestResult::FAILED;
    }

    printf("Passed\n");
    return TestResult::PASSED;
}

TestResult test_check(const EqSolverData* data, FILE* file, const int test_n) {
    assert(data && file);

    EqSolverData correct_data = {};
    for (int i = 0; i < EqSolverData::COEFF_NUM - 1; i++)
        correct_data.roots[i] = NAN;
    if (!test_read_roots(data, &correct_data, file)) return TestResult::ERROR;

    return test_compare_data(data, &correct_data, test_n);
}

void test_print_summary(const int test_num, const int passed_test_num){
    if (test_num == passed_test_num) {
        printf("All %d tests passed. Congrats!\n", test_num);
    } else {
        double success_percent = (double)passed_test_num * 100 / (double)test_num;
        printf("WARNING! Passed %d of %d tests. It's %.1f%%\n",
               passed_test_num, test_num, success_percent);
    }
}