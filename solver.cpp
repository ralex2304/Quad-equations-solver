#include "solver.h"

int enter_coeffs(EqSolverData* data) {
    assert(data);

    for (int i = 0; i < EqSolverData::COEFF_NUM; i++) {
        if (!enter_coeff('a' + (char)i, data->coeffs + i))
            return 0;
    }
    return 1;
}

int enter_coeff(char c, double* x) {
    assert(x && isalpha(c));

    static const int ENTER_COEFF_TRIES = 5;

    for (int tries = ENTER_COEFF_TRIES; tries > 0; tries++) {
        printf("Enter coefficient %c: ", c);
        if (read_num(x))
            return 1;           // exit if entered correctly
        printf("Coefficient entered incorrectly. Try again\n");
    }

    printf("You tried to enter coefficient for %d times!"
           "Oh, come on, what's wrong with you?!\n", ENTER_COEFF_TRIES);
    return 0;
}

void solve_quad(EqSolverData* data){
    assert(data && EqSolverData::COEFF_NUM >= 3);
    
    double a = data->coeffs[EqSolverData::COEFF_NUM - 3];
    double b = data->coeffs[EqSolverData::COEFF_NUM - 2];
    if (is_double_equal(b, 0)) b = -0.0;
    double c = data->coeffs[EqSolverData::COEFF_NUM - 1];

    if (is_double_equal(a, 0)) {        // check if equation is quad (zero division check)
        solve_lin(data);
        return;
    }

    double D = b*b - 4*a*c;             // discriminant
    if (is_double_equal(D, 0)) {        // check if there are solutions
        data->roots[0] = (-b) / (2*a);
        data->roots_num = ONE_SOLUTION;
    } else if (D < 0) {
        data->roots_num = NO_SOLUTIONS;
    } else {
        double D_sqrt = sqrt(D);
        data->roots[0] = (-b - D_sqrt) / (2*a);
        data->roots[1] = (-b + D_sqrt) / (2*a);
        data->roots_num = TWO_SOLUTIONS;
    }
    bubble_sort(data->roots, data->roots_num);
}

void solve_lin(EqSolverData* data) {
    assert(data && EqSolverData::COEFF_NUM >= 2);

    double a = data->coeffs[EqSolverData::COEFF_NUM - 2];
    double b = data->coeffs[EqSolverData::COEFF_NUM - 1];
    if (is_double_equal(b, 0)) b = -0.0;

    if (is_double_equal(a, 0)) {
        data->roots_num = is_double_equal(b, 0) ? INFINITE_SOLUTIONS : NO_SOLUTIONS;
        return;
    }

    data->roots[0] = b / -a;
    data->roots_num = ONE_SOLUTION;
}

void print_roots(const EqSolverData* data){
    assert(data);

    switch (data->roots_num) {
        case NO_SOLUTIONS:
            printf("No solutions\n");
            break;
        case ONE_SOLUTION:
            assert(isfinite(data->roots[0]));
            printf("1 solution:\nx = %lf\n", data->roots[0]);
            break;
        case TWO_SOLUTIONS:
            assert(isfinite(data->roots[0]) && isfinite(data->roots[1]));
            printf("2 solutions:\nx1 = %lf\nx2 = %lf\n", data->roots[0], data->roots[1]);
            break;
        case INFINITE_SOLUTIONS:
            printf("Infinite number of solutions:\nx belongs to the set (-inf; +inf)\n");
            break;
        case NAN_SOLUTIONS:
        default:
            assert(0 && "Incorrect solutions number");
            break;
    }
}

void print_help() {
    printf("# This program solves quad equations of the form a*x^2 + b*x + c = 0\n"
           "# Where \"x\" is a variable and \"a\", \"b\", \"c\" are coefficients\n"
           "# Console args\n"
           "#   -h - prints help information\n"
           "#   -t - specify test file name after this (works only if test mode enabled)\n"
           "# Test file format (there might be several such sections):\n"
           "# <coeff a>\n"
           "# <coeff b>\n"
           "# <coeff c>\n"
           "# <solutions number>\n"
           "# <solution 1 (if exists)>\n"
           "# <solution 2 (if exists)>\n");
}