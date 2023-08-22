#include "test.h"

MODE have_tests(FILE** file, EqSolverData* data, char* filename) {
    assert(file && data);

    if (*file == NULL && (filename == NULL || !test_open_file(file, filename))) {
        if (!enter_coeffs(data))
            return TESTS_ENDED_MODE;
        return NORMAL_MODE;
    }

    if (!test_enter_coeffs(data, file)) return TESTS_ENDED_MODE;
    return TESTS_LEFT_MODE;
}

int test_open_file(FILE** file, const char* filename) {
    *file = fopen(filename, "r");
    if (*file == NULL) {
        printf("Error opening test file %s\n", filename);
        perror("Message");
        fclose(*file);
        free((void*)filename);
        printf("Entering normal mode\n");
        return 0;
    }
    free((void*)filename);
    return 1;
}

int test_enter_coeffs(EqSolverData* data, FILE** file) {
    assert(data && file);

    for (int i = 0; i < EqSolverData::COEFF_NUM; i++) {
        if (!read_num(data->coeffs + i, *file)) {
            int c = fgetc(*file);
            if (c != EOF)
                printf("Error reading coefficient from test file\n");
            ungetc(c, *file);
            fclose(*file);
            return 0;
        } 
    }
    return 1;
}

int test_read_roots(const EqSolverData* data, EqSolverData* correct_data, FILE** file) {
    assert(data && correct_data && file);
    
    if (!read_num(((int*)&correct_data->roots_num), *file)) {
        printf("Error reading number of solutions from test file\n");
        fclose(*file);
        return 0;
    }

    for (int i = 0; i < (int)correct_data->roots_num; i++) {
        if(!read_num(&correct_data->roots[i], *file)) {
            printf("Error reading solution from test file\n");
            fclose(*file);
            return 0;
        }
    }
    bubble_sort(correct_data->roots, correct_data->roots_num);
    return 1;
}

int test_check(const EqSolverData* data, FILE** file) {
    EqSolverData correct_data;
    for (int i = 0; i < EqSolverData::COEFF_NUM - 1; i++)
        correct_data.roots[i] = NAN;
    if (!test_read_roots(data, &correct_data, file)) return 0;

    test_compare_data(data, &correct_data);
    return 1;
}

void test_compare_data(const EqSolverData* data, const EqSolverData* correct_data) {
    assert(data && correct_data);

    static int test_num = 0;
    test_num++;

    if (data->roots_num != correct_data->roots_num) {
        printf("Test %d failed. Incorrect number of solutions\n", test_num);
        return;
    } else {
        printf("Number of solutions is correct: %d\n", (int)correct_data->roots_num);
    }

    int success = 1;
    for (int i = 0; i < (int) correct_data->roots_num; i++) {
        assert(isfinite(data->roots[i]) && isfinite(correct_data->roots[i]));
        if (!is_double_equal(data->roots[i], correct_data->roots[i])) {
            printf("Test %d failed. Incorrect root %d\n", test_num, (i+1));
            printf("Correct root:  %lf\n", correct_data->roots[i]);
            printf("Received root: %lf\n" , data->roots[i]);
            success = 0;
        } else {
            printf("Root %d is correct\n", (i+1));
        }
    }
    if (!success) return;

    printf("Test %d completed successfully!\n", test_num);
}