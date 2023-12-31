#include "quad_solver.h"

/**
 * @brief Reads coefficient double from input
 *
 * @param[in] c coefficient name
 * @param[in] x
 * @return int success
 */
static InputStatus enter_coeff(const char c, double* x);


Status::Statuses solver_proccess() {
    EqSolverData data = {};
    EqSolverData_init(&data);

    switch (enter_coeffs(&data)) {
        case InputStatus::OK:
            break;
        case InputStatus::WRONG_DATA:
            return Status::COEFFS_INPUT;
        case InputStatus::END_OF_FILE:
            return Status::END_OF_FILE;
        default:
            assert(0 && "enter_coeffs() returned wrong InputStatus");
            break;
    }

    for (int i = 0; i < EqSolverData::COEFF_NUM; i++)
        assert(isfinite(data.coeffs[i]));

    solve_quad(&data);

    print_roots(&data);

    return Status::NO_ERROR;
}

static InputStatus enter_coeff(const char c, double* x) {
    assert(x);
    assert(isalpha(c));

    static const int ENTER_COEFF_TRIES = 5;

    for (int tries = ENTER_COEFF_TRIES; tries > 0; tries--) {
        assert(1 <= tries && tries <= ENTER_COEFF_TRIES);

        printf("Enter coefficient %c: ", c);

        InputStatus res = read_num(x);
        if (res != InputStatus::WRONG_DATA)
            return res;

        printf("Coefficient entered incorrectly. Try again\n");
    }

    printf("You tried to enter coefficient for %d times!"
           "Oh, come on, what's wrong with you?!\n", ENTER_COEFF_TRIES);
    return InputStatus::WRONG_DATA;
}

InputStatus enter_coeffs(EqSolverData* data) {
    assert(data);

    for (int i = 0; i < EqSolverData::COEFF_NUM; i++) {
        InputStatus res = enter_coeff('a' + (char)i, data->coeffs + i);
        if (res != InputStatus::OK)
            return res;
    }
    return InputStatus::OK;
}

void solve_quad(EqSolverData* data){
    assert(data);
    assert(EqSolverData::COEFF_NUM >= 3);

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
        double D_sqrt = NAN;
        if (is_double_equal(c, 0))
            D_sqrt = b;
        else
            D_sqrt = sqrt(D);
        assert(isfinite(D_sqrt));

        double double_a = a * 2;
        data->roots[0] = valid_root((-b - D_sqrt) / double_a);
        data->roots[1] = valid_root((-b + D_sqrt) / double_a);
        data->roots_num = TWO_SOLUTIONS;
    }
    bubble_sort(data->roots, data->roots_num);
}

void solve_lin(EqSolverData* data) {
    assert(data);
    assert(EqSolverData::COEFF_NUM >= 2);

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

Status::Statuses Status::raise(const Statuses status) {
    switch (status) {
        case NORMAL_WORK:
            assert(0 && "Status::raise(): NORMAL_WORK mustn't be raised");
            break;
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
    return status;
}
