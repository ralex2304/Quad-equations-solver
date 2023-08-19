/**
 * @file main.cpp
 * @author ralex2304
 * @brief Quad equations solver
 * @version 0.7
 * @date 2023-08-17
 */

#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>

/**
 * @brief Enables test mode
 */
#define TEST
#ifdef TEST
    const char test_name[] = "tests/test.txt"; // test file name
#endif

/**
 * @brief Specifies number of soludions of the equation
 */
enum SOLUTIONS {
    NAN_SOLUTIONS = -2,
    INFINITE_SOLUTIONS = -1,
    NO_SOLUTIONS = 0,
    ONE_SOLUTION = 1,
    TWO_SOLUTIONS = 2
};

/**
 * @brief Contains input and output data for solver
 */
struct SolverData {
    static const int COEFF_NUM = 3;
    double coeffs[COEFF_NUM] = {};
    double roots[COEFF_NUM - 1] = {};
    SOLUTIONS roots_num = NAN_SOLUTIONS;
};

int enter_coeffs(SolverData* data);
SOLUTIONS solve_lin(SolverData* data);
SOLUTIONS solve_quad(SolverData* data);
void print_roots(const SolverData* data);

int input_flush(FILE* stream = stdin);
int read_double(double* x, FILE* stream = stdin);
int read_int(int* x, FILE* stream = stdin);
int enter_coeff(const char c, double* x);
/**
 * @brief Tells if two doubles are equal with precision of DOUBLE_COMPARE_PRECISION
 * 
 * @param[in] a First double
 * @param[in] b Second double
 * @return int (a == b)
 */
inline int is_double_equal(const double a, const double b) {
    assert(!isnan(a) && !isinf(a) && !isnan(b) && !isinf(b));

    static const double DOUBLE_COMPARE_PREC = 0.000001;
    return abs(a - b) < DOUBLE_COMPARE_PREC;
};

#ifdef TEST
    void test_open_file(FILE** file, const char* filename);
    int test_enter_coeffs(SolverData* data, FILE* file);
    void test_read_roots(const SolverData* data, SolverData* correc_data, FILE* file);
    void test_check_data(const SolverData* data, const SolverData* correct_data);
#endif

int main() {
    printf("Hello! This program solves quad equations of the form a*x^2 + b*x + c = 0\n"
           "Where \"x\" is a variable and \"a\", \"b\", \"c\" are coefficients\n");
    
    // Read data
    SolverData data = {};
    for (int i = 0; i < data.COEFF_NUM; i++)
        data.coeffs[i] = NAN;
    #ifndef TEST
        if (!enter_coeffs(&data)) exit(0);
    #else
        FILE* file = NULL;
        test_open_file(&file, test_name);
        if (!test_enter_coeffs(&data, file)) exit(0);
    #endif
    for (int i = 0; i < data.COEFF_NUM; i++)
        assert(!isnan(data.coeffs[i]));
    
    // Solve data
    for (int i = 0; i < SolverData::COEFF_NUM - 1; i++)
        data.roots[i] = NAN;
    data.roots_num = solve_quad(&data);

    // Write data
    #ifndef TEST
        print_roots(&data);
    #else
        SolverData correct_data = {};
        for (int i = 0; i < correct_data.COEFF_NUM - 1; i++)
            correct_data.roots[i] = NAN;
        test_read_roots(&data, &correct_data,file);
        for (int i = 0; i < correct_data.roots_num; i++)
            assert(!isnan(correct_data.roots[i]));
        fclose(file);
        test_check_data(&data, &correct_data);
    #endif
    
    printf("Bye!");
    return 0;
}

/**
 * @brief Flushes input
 * 
 * @return int number of flushed symbols
 */
int input_flush(FILE* stream) {
    int c = 0;
    int cnt = 0;
    do {
        cnt++;
    } while ((c = fgetc(stream)) != '\n' && c != EOF && !feof(stream) && !ferror(stream));
    
    return cnt;
}

// 
/**
 * @brief Reads double from input to pointer
 * 
 * @param[in] x
 * @param[in] stream 
 * @return int success
 */
int read_double(double* x, FILE* stream) {
    assert(x);

    int res = fscanf(stream, "%lf", x);
    return input_flush(stream) == 1 && res == 1 && res != EOF && !isnan(*x) && !isinf(*x);    // check input errors and flush input
}

// 
/**
 * @brief Reads int from input to pointer
 * 
 * @param[in] x 
 * @param[in] stream 
 * @return int success
 */
int read_int(int* x, FILE* stream) {
    assert(x);

    int res = fscanf(stream, "%d", x);
    return input_flush(stream) == 1 && res == 1 && res != EOF && !isnan(*x) && !isinf(*x);    // check input errors and flush input
}

// 
/**
 * @brief Reads coefficients from input to data->coeffs, starting with name 'a'
 * 
 * @param[in] data 
 * @return int success
 */
int enter_coeffs(SolverData* data) {
    assert(data);

    for (int i = 0; i < data->COEFF_NUM; i++) {
        if (!enter_coeff('a' + (char)i, data->coeffs + i))
            return 0;
    }
    return 1;
}

/**
 * @brief Reads coefficient double from input
 * 
 * @param[in] c coefficient name
 * @param[in] x 
 * @return int success
 */
int enter_coeff(char c, double* x) {
    assert(x && isalpha(c));
    static const int ENTER_COEFF_TRIES = 5;
    int tries = ENTER_COEFF_TRIES;

    while (tries--) {
        printf("Enter coefficient %c: ", c);
        if (read_double(x))
            return 1;           // exit if entered correctly
        printf("Coefficient entered incorrectly. Try again\n");
    }

    printf("You tried to enter coefficient for %d times! Oh, come on, what's wrong with you?!\n", ENTER_COEFF_TRIES);
    return 0;
}

/**
 * @brief Solves quad equations
 * 
 * @param data[in] 
 * @return SOLUTIONS number of solutions
 */
SOLUTIONS solve_quad(SolverData* data){
    assert(data && data->COEFF_NUM >= 3);
    
    double a = data->coeffs[data->COEFF_NUM - 3];
    double b = data->coeffs[data->COEFF_NUM - 2];
    double c = data->coeffs[data->COEFF_NUM - 1];

    if (is_double_equal(a, 0)) {        // check if equation is quad (zero division check)
        return solve_lin(data);
    }

    double D = b*b - 4*a*c;             // discriminant
    if (is_double_equal(D, 0)) {        // check if there are solutions
        data->roots[0] = (-b) / (2*a);
        return ONE_SOLUTION;
    } else if (D < 0) {
        return NO_SOLUTIONS;
    } else {
        double D_sqrt = sqrt(D);
        data->roots[0] = (-b - D_sqrt) / (2*a);
        data->roots[1] = (-b + D_sqrt) / (2*a);
        return TWO_SOLUTIONS;
    }
}

/**
 * @brief Solves linear equations
 * 
 * @param[in] data 
 * @return SOLUTIONS number of solutions
 */
SOLUTIONS solve_lin(SolverData* data) {
    assert(data && data->COEFF_NUM >= 2);

    double a = data->coeffs[data->COEFF_NUM - 2];
    double b = data->coeffs[data->COEFF_NUM - 1];

    if (is_double_equal(a, 0)) {
        return is_double_equal(b, 0) ? INFINITE_SOLUTIONS : NO_SOLUTIONS;
    }

    data->roots[0] = -b / a;
    return ONE_SOLUTION;
}

/**
 * @brief Prints roots
 * 
 * @param[in] data 
 */
void print_roots(const SolverData* data){
    switch (data->roots_num) {
        case NO_SOLUTIONS:
            printf("No solutions\n");
            break;
        case ONE_SOLUTION:
            assert(!isnan(data->roots[0]) && !isinf(data->roots[0]));
            printf("1 solution:\nx = %lf\n", data->roots[0]);
            break;
        case TWO_SOLUTIONS:
            assert(!isnan(data->roots[0]) && !isinf(data->roots[0]) && !isnan(data->roots[1]) && !isinf(data->roots[1]));
            printf("2 solutions:\nx1 = %lf\nx2 = %lf\n", data->roots[0], data->roots[1]);
            break;
        case INFINITE_SOLUTIONS:
            wprintf(L"Infinite number of solutions:\nx belongs to the set (-inf; +inf)\n");
            break;
        case NAN_SOLUTIONS:
        default:
            assert(0 && "Incorrect solutions number");
            break;
    }
}

#ifdef TEST
    /**
     * @brief Opens test file by filename
     * 
     * @param[in] file - pointer 
     * @param[in] filename - name of file
     */
    void test_open_file(FILE** file, const char* filename) {
        *file = fopen(filename, "r");
        if (*file == NULL) {
            printf("Error opening test file %s\n", filename);
            fclose(*file);
            exit(0);
        }
    }

    /**
     * @brief Reads coeffs from test file
     * 
     * @param[in] data 
     * @param[in] file 
     * @return int success
     */
    int test_enter_coeffs(SolverData* data, FILE* file) {
        assert(data && file);

        for (int i = 0; i < data->COEFF_NUM; i++) {
            if (!read_double(data->coeffs + i, file)) {
                printf("Error reading coefficient from test file\n");
                fclose(file);
                return 0;
            } 
        }
        return 1;
    }

    /**
     * @brief Reads correct roots from test file
     * 
     * @param[in] data 
     * @param[in] correct_data 
     * @param[in] file 
     */
    void test_read_roots(const SolverData* data, SolverData* correct_data, FILE* file) {
        assert(data && correct_data && file);
        
        if (!read_int(((int*)&correct_data->roots_num), file)) {
            printf("Error reading number of solutions from test file\n");
            fclose(file);
            exit(0);
        }

        for (int i = 0; i < (int)correct_data->roots_num; i++) {
            if(!read_double(&correct_data->roots[i], file)) {
                printf("Error reading solution from test file\n");
                fclose(file);
                exit(0);
            }
        }
    }

    /**
     * @brief Checks solutions number and roots
     * 
     * @param[in] data 
     * @param[in] correct_data 
     */
    void test_check_data(const SolverData* data, const SolverData* correct_data) {
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
#endif
