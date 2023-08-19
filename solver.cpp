#include "solver.h"

int input_flush(FILE* stream) {
    int c = 0;
    int cnt = 0;
    do {
        cnt++;
    } while ((c = fgetc(stream)) != '\n' && c != EOF && !feof(stream) && !ferror(stream));
    
    return cnt;
}

int read_double(double* x, FILE* stream) {
    assert(x);

    int res = fscanf(stream, "%lf", x);
    return input_flush(stream) == 1 && res == 1 && res != EOF && !isnan(*x) && !isinf(*x);    // check input errors and flush input
}

int read_int(int* x, FILE* stream) {
    assert(x);

    int res = fscanf(stream, "%d", x);
    return input_flush(stream) == 1 && res == 1 && res != EOF && !isnan(*x) && !isinf(*x);    // check input errors and flush input
}

int enter_coeffs(SolverData* data) {
    assert(data);

    for (int i = 0; i < data->COEFF_NUM; i++) {
        if (!enter_coeff('a' + (char)i, data->coeffs + i))
            return 0;
    }
    return 1;
}

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