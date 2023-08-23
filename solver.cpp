#include "solver.h"

/**
 * @brief Reads coefficient double from input
 * 
 * @param[in] c coefficient name
 * @param[in] x 
 * @return int success
 */
static InputError enter_coeff(const char c, double* x);

Error::Errors solver_proccess() {
    EqSolverData data = {};
    EqSolverData_init(&data);

    switch (enter_coeffs(&data)) {
        case InputError::OK:
            break;
        case InputError::WRONG_DATA:
            return Error::COEFFS_INPUT;
        case InputError::END_OF_FILE:
            return Error::END_OF_FILE;
        default:
            assert(0 && "enter_coeffs() returned wrong InputError");
            break;
    }
    
    for (int i = 0; i < EqSolverData::COEFF_NUM; i++)
        assert(isfinite(data.coeffs[i]));

    solve_quad(&data);

    print_roots(&data);
    return Error::NO_ERROR;
}

static InputError enter_coeff(const char c, double* x) {
    assert(x && isalpha(c));

    static const int ENTER_COEFF_TRIES = 5;

    for (int tries = ENTER_COEFF_TRIES; tries > 0; tries--) {
        printf("Enter coefficient %c: ", c);

        InputError res = read_num(x);
        if (res != InputError::WRONG_DATA)
            return res;
        
        printf("Coefficient entered incorrectly. Try again\n");
    }

    printf("You tried to enter coefficient for %d times!"
           "Oh, come on, what's wrong with you?!\n", ENTER_COEFF_TRIES);
    return InputError::WRONG_DATA;
}

InputError enter_coeffs(EqSolverData* data) {
    assert(data);

    for (int i = 0; i < EqSolverData::COEFF_NUM; i++) {
        InputError res = enter_coeff('a' + (char)i, data->coeffs + i);
        if (res != InputError::OK)
            return res;
    }
    return InputError::OK;
}

void solve_quad(EqSolverData* data){
    assert(data && EqSolverData::COEFF_NUM >= 3);
    
    double a = data->coeffs[EqSolverData::COEFF_NUM - 3];
    double b = data->coeffs[EqSolverData::COEFF_NUM - 2];
    double c = data->coeffs[EqSolverData::COEFF_NUM - 1];

    if (is_double_equal(a, 0)) {        // check if equation is quad (zero division check)
        solve_lin(data);
        return;
    }

    double D = b*b - 4*a*c;             // discriminant
    if (is_double_equal(D, 0)) {        // check if there are solutions
        data->roots[0] = valid_root((-b) / (2*a));
        data->roots_num = ONE_SOLUTION;
    } else if (D < 0) {
        data->roots_num = NO_SOLUTIONS;
    } else {
        double D_sqrt = sqrt(D);
        data->roots[0] = valid_root((-b - D_sqrt) / (2*a));
        data->roots[1] = valid_root((-b + D_sqrt) / (2*a));
        data->roots_num = TWO_SOLUTIONS;
    }
    bubble_sort(data->roots, data->roots_num);
}

void solve_lin(EqSolverData* data) {
    assert(data && EqSolverData::COEFF_NUM >= 2);

    double a = data->coeffs[EqSolverData::COEFF_NUM - 2];
    double b = data->coeffs[EqSolverData::COEFF_NUM - 1];

    if (is_double_equal(a, 0)) {
        data->roots_num = is_double_equal(b, 0) ? INFINITE_SOLUTIONS : NO_SOLUTIONS;
        return;
    }

    data->roots[0] = valid_root(b / -a);
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

void print_help(const bool hepl_en) {
    printf("# This program solves quad equations of the form a*x^2 + b*x + c = 0\n"
           "# Where \"x\" is a variable and \"a\", \"b\", \"c\" are coefficients\n"
           "# Console args:\n"
           "#   -h - prints help information\n");
    if (hepl_en)
        printf("#   -t - specify test file name after this (works only if test mode enabled)\n"
               "# Test file format (there might be several such sections):\n"
               "# <coeff a> <coeff b> <coeff c>\n"
               "# <solutions number>\n"
               "# <solution 1 (if exists)> <solution 2 (if exists)>\n"
               "# \n"
               "# <Next test>\n");
    printf("# End of help. Good luck using this program!\n");
}

Error::Errors Error::raise(const Errors err) {
    switch (err) {
        case ARGS:
            printf("Exiting. Args error\n");
            break;
        case COEFFS_INPUT:
            printf("Exiting. Coefficients input error");
            break;
        case TEST_INPUT:
            printf("Exiting. Test file input error");
            break;
        case END_OF_FILE:
            printf("Exiting. End of file reached");
        case OK_EXIT:
        case NO_ERROR:
            break;
        default:
            assert(0 && "Error::raise(): wrong error");
            break;
    };
    return err;
}