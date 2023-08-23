#include "test.h"

Status::Statuses test_or_normal(const char* filename) {
    FILE* file = nullptr;
    switch (test_open_file(&file, filename)) {
        case TestMode::INPUT_ERROR:
            return Status::TEST_INPUT;
        case TestMode::TESTS_LEFT: // TEST mode
            return test_proccess(file);
        case TestMode::NO_TESTS: // Normal mode
            return solver_proccess();
        default:
            assert(0 && "test_open_file() returned wrong TestMode");
            break;
    }
    return Status::NO_ERROR;
}

Status::Statuses test_proccess(FILE* file) {
    TestMode tests = TestMode::INPUT_ERROR;

    int test_num = 0;
    int passed_test_num = 0;

    EqSolverData data = {};
    EqSolverData_init(&data);

    while ((tests = test_enter_coeffs(&data, file)) != TestMode::NO_TESTS) {
        if (tests == TestMode::INPUT_ERROR)
            return Status::TEST_INPUT;

        for (int i = 0; i < EqSolverData::COEFF_NUM; i++)
            assert(isfinite(data.coeffs[i]));

        solve_quad(&data);

        test_num++;
        switch (test_read_and_compare(&data, file, test_num)) {
            case TestResult::ERROR:
                return Status::TEST_INPUT;
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

    return Status::NO_ERROR;
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
            case InputStatus::END_OF_FILE:
                return TestMode::NO_TESTS;
            case InputStatus::WRONG_DATA:
                printf("Error reading coefficient from test file\n");
                return TestMode::INPUT_ERROR;
            case InputStatus::OK:
                break;
            default:
                assert(0 && "read_num() returned wrong InputStatus");
                break;
        }
    }
    if (!input_flush(file)) {
        printf("Error reading coefficient from test file\n");
        return TestMode::INPUT_ERROR;
    }
    return TestMode::TESTS_LEFT;
}

bool test_read_roots(const EqSolverData* data, EqSolverData* correct_data, FILE* file) {
    assert(data && correct_data && file);

    if (read_num(((int*)&correct_data->roots_num), file) != InputStatus::OK) {
        printf("Error reading number of solutions from test file\n");
        fclose(file);
        return false;
    }

    for (int i = 0; i < (int)correct_data->roots_num; i++) {
        if(read_num(&correct_data->roots[i], file, false) != InputStatus::OK) {
            printf("Error reading solution from test file\n");
            fclose(file);
            return false;
        }
    }
    if (!input_flush(file)) {
        printf("Error reading solution from test file\n");
        return false;
    }

    bubble_sort(correct_data->roots, correct_data->roots_num);
    return true;
}

TestResult test_compare_data(const EqSolverData* data, const EqSolverData* correct_data, const int test_n) {
    assert(data && correct_data);

    printf("Test %d. ", test_n);

    if (data->roots_num != correct_data->roots_num) {
        printf("Incorrect number of solutions.\n"
               CONSOLE_RED("Test %d FAILED!\n"), test_n);
        return TestResult::FAILED;
    }

    bool passed = true;
    for (int i = 0; i < (int) correct_data->roots_num; i++) {
        assert(isfinite(data->roots[i]) && isfinite(correct_data->roots[i]));
        if (!is_double_equal(data->roots[i], correct_data->roots[i])) {
            printf("Incorrect root %d\n", (i+1));
            printf("    Correct root:  %lf\n", correct_data->roots[i]);
            printf("    Received root: %lf\n", data->roots[i]);
            passed = false;
        }
    }
    if (!passed) {
        printf(CONSOLE_RED("Test %d FAILED!\n"), test_n);
        return TestResult::FAILED;
    }

    printf("Passed\n");
    return TestResult::PASSED;
}

TestResult test_read_and_compare(const EqSolverData* data, FILE* file, const int test_n) {
    assert(data && file);

    EqSolverData correct_data = {};
    for (int i = 0; i < EqSolverData::COEFF_NUM - 1; i++)
        correct_data.roots[i] = NAN;

    if (!test_read_roots(data, &correct_data, file))
        return TestResult::ERROR;

    return test_compare_data(data, &correct_data, test_n);
}

void test_print_summary(const int test_num, const int passed_test_num){
    if (test_num == passed_test_num) {
        if (test_num == 1)
            printf(CONSOLE_GREEN("Test passed.") " Congrats!\n");
        else
            printf(CONSOLE_GREEN("All %d tests passed.") " Congrats!\n", test_num);
    } else {
        if (test_num == 1)
            printf(CONSOLE_RED("WARNING! ") "Test failed\n");
        else {
            double success_percent = (double)passed_test_num * 100 / (double)test_num;
            printf(CONSOLE_RED("WARNING! ") "Passed %d of %d tests. It's %.1f%%\n",
                passed_test_num, test_num, success_percent);
        }
    }
}
