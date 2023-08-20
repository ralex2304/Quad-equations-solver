#include "test.h"

int test_read(FILE** file, EqSolverData* data, const char* filename) {
    if (!test_open_file(file, filename))
        return 0;
    if (!test_enter_coeffs(data, file))
        return 0;
    return 1;
}

int test_open_file(FILE** file, const char* filename) {
    *file = fopen(filename, "r");
    if (*file == NULL) {
        printf("Error opening test file %s\n", filename);
        perror("Message: ");
        fclose(*file);
        return 0;
    }
    return 1;
}

int test_enter_coeffs(EqSolverData* data, FILE** file) {
    assert(data && file);

    for (int i = 0; i < EqSolverData::COEFF_NUM; i++) {
        if (!read_num(data->coeffs + i, *file)) {
            printf("Error reading coefficient from test file\n");
            fclose(*file);
            return 0;
        } 
    }
    return 1;
}

void test_read_roots(const EqSolverData* data, EqSolverData* correct_data, FILE** file) {
    assert(data && correct_data && file);
    
    if (!read_num(((int*)&correct_data->roots_num), *file)) {
        printf("Error reading number of solutions from test file\n");
        fclose(*file);
        exit(0);
    }

    for (int i = 0; i < (int)correct_data->roots_num; i++) {
        if(!read_num(&correct_data->roots[i], *file)) {
            printf("Error reading solution from test file\n");
            fclose(*file);
            exit(0);
        }
    }
}

void test_check(const EqSolverData* data, FILE** file) {
    EqSolverData correct_data = {};
    for (int i = 0; i < EqSolverData::COEFF_NUM - 1; i++)
        correct_data.roots[i] = NAN;
    test_read_roots(data, &correct_data, file);

    fclose(*file);

    test_compare_data(data, &correct_data);
}

void test_compare_data(const EqSolverData* data, const EqSolverData* correct_data) {
    assert(data && correct_data);

    if (data->roots_num != correct_data->roots_num) {
        printf("Test failed. Incorrect number of solutions\n");
        return;
    } else {
        printf("Number of solutions is correct: %d\n", (int)correct_data->roots_num);
    }

    // Тут конечно по-хорошему надо отсортировать корни, но это TODO
    int success = 1;
    for (int i = 0; i < (int) correct_data->roots_num; i++) {
        assert(!is_double_nan_inf(data->roots[i]) && !is_double_nan_inf(correct_data->roots[i]));
        if (!is_double_equal(data->roots[i], correct_data->roots[i])) {
            printf("Test failed. Incorrect root %d\n", (i+1));
            printf("Correct root:  %lf\n", correct_data->roots[i]);
            printf("Received root: %lf\n" , data->roots[i]);
            success = 0;
        } else {
            printf("Root %d is correct\n", (i+1));
        }
    }
    if (!success) return;

    printf("Test completed successfully!\n");
}