#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>

enum SOLUTIONS {
    NAN_SOLUTIONS = -2,
    INFINITE_SOLUTIONS = -1,
    NO_SOLUTIONS = 0,
    ONE_SOLUTION = 1,
    TWO_SOLUTIONS = 2
};

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

int input_flush();
int read_double(double* x);
int enter_coeff(const char c, double* x);
// Returns 1 if two doubles are equal with precision of DOUBLE_COMPARE_PRECISION
inline int is_double_equal(const double a, const double b) {
    assert(!isnan(a) && !isinf(a) && !isnan(b) && !isinf(b));

    static const double DOUBLE_COMPARE_PREC = 0.000001;
    return abs(a - b) < DOUBLE_COMPARE_PREC;
};

int main() {
    printf("Hello! This program solves quad equations of the form a*x^2 + b*x + c = 0\n"
           "Where \"x\" is a variable and \"a\", \"b\", \"c\" are coefficients\n");
    
    // Read data
    SolverData data;
    for (int i = 0; i < SolverData::COEFF_NUM; i++)
        data.coeffs[i] = NAN;
    if (!enter_coeffs(&data)) exit(0);
    for (int i = 0; i < SolverData::COEFF_NUM; i++)
        assert(!isnan(data.coeffs[i]));
    
    // Solve data
    for (int i = 0; i < SolverData::COEFF_NUM - 1; i++)
        data.roots[i] = NAN;
    data.roots_num = solve_quad(&data);

    // Write data
    print_roots(&data);
    
    printf("Bye!");
    return 0;
}

// Flushes input. Returns number of flushed symbols
int input_flush() {
    int c = 0;
    int cnt = 0;
    do {
        cnt++;
    } while ((c = getchar()) != '\n' && c != EOF);
    
    return cnt;
}

// Reads double from input to pointer. Returns 0 if fails
int read_double(double* x) {
    assert(x);

    int res = scanf("%lf", x);
    return input_flush() == 1 && res == 1 && res != EOF && !isnan(*x) && !isinf(*x);    // check input errors and flush input
}

// Reads COEFF_NUM coefficients from input, starting with 'a'
int enter_coeffs(SolverData* data) {
    assert(data);

    for (int i = 0; i < data->COEFF_NUM; i++) {
        if (!enter_coeff('a' + (char)i, data->coeffs + i))
            return 0;
    }
    return 1;
}

// Reads coefficient from input
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

// Solves quad equations of the form a*x^2 + b*x + c = 0 to pointers x1, x2.
// Returns number of solutions (INFINITE_SOLUTIONS if infinite)
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

// Solves equations of the form a*x + b = 0 to pointer x1.
// Returns number of solutions (INFINITE_SOLUTIONS if infinite)
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

// Prints roots
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
