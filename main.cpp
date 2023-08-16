#include <stdio.h>
#include <math.h>
#include <assert.h>

enum Solutions {INFINITE_SOLUTIONS = -1, NO_SOLUTIONS, ONE_SOLUTION, TWO_SOLUTIONS};
const int COEFF_NUM = 3;

int input_flush();
int read_double(double* x);
int enter_coeffs(double* coeffs);
int enter_coeff(const char c, double* x);

int is_double_equal(double a, double b);
Solutions solve_quad(const double a, const double b, const double c, double* x1, double* x2);
Solutions solve_lin(const double a, const double b, double* x1);


int main() {
    printf("Hello! This program solves quad equations of the form a*x^2 + b*x + c = 0\n"
           "Where \"x\" is a variable and \"a\", \"b\", \"c\" are coefficients\n");
    
    double coeffs[COEFF_NUM];
    for (int i = 0; i < COEFF_NUM; i++) coeffs[i] = NAN;
    if (!enter_coeffs(coeffs)) exit(0);
    for (int i = 0; i < COEFF_NUM; i++) assert(!isnan(coeffs[i]));
    
    double x1 = NAN, x2 = NAN;
    Solutions solustions_number = solve_quad(coeffs[0], coeffs[1], coeffs[2], &x1, &x2);
    switch (solustions_number) {
        case NO_SOLUTIONS:
            printf("No solutions\n");
            break;
        case ONE_SOLUTION:
            assert(!isnan(x1));
            printf("1 solution:\nx = %lf\n", x1);
            break;
        case TWO_SOLUTIONS:
            assert(!isnan(x1) && !isnan(x2));
            printf("2 solutions:\nx1 = %lf\nx2 = %lf\n", x1, x2);
            break;
        case INFINITE_SOLUTIONS:
            wprintf(L"Infinite number of solutions:\nx belongs to the set (-inf; +inf)\n");
            break;
        default:
            assert(0 && "Incorrect solutions number");
            break;
    }
    
    printf("Bye!");
    return 0;
}

//Flushes input. Returns number of flushed symbols
int input_flush() {
    int c = 0, cnt = 1;
    while ((c=getchar()) != '\n' && c != EOF) cnt++;
    return cnt;
}

//Reads double from input to pointer. Returns 0 if fails
int read_double(double* x) {
    assert(x);

    int res = scanf("%lf", x);
    if (input_flush() != 1 || res != 1 || res == EOF)   //check input errors and flush input
        return 0;
    return 1;
}

//Reads COEFF_NUM coefficients from input, starting with 'a'
int enter_coeffs(double* coeffs) {
    assert(coeffs);

    for (int i = 0; i < COEFF_NUM; i++) {
        if (!enter_coeff('a' + (char)i, coeffs + i))
            return 0;
    }
    return 1;
}

//Reads coefficient from input
int enter_coeff(char c, double* x) {
    assert(x && (('a'<=c && c<='z') || ('A'<=c && c<='Z')));

    static const int ENTER_COEFF_TRIES = 5;
    int tries = ENTER_COEFF_TRIES;

    while (tries--) {
        printf("Enter coefficient %c: ", c);
        if (read_double(x))
            return 1;                         //exit if entered correctly
        printf("Coefficient entered incorrectly. Try again\n");
    }

    printf("You tried to enter coefficient for %d times! Oh, come on, what's wrong with you?!\n", ENTER_COEFF_TRIES);
    return 0;
}

//Solves quad equations of the form a*x^2 + b*x + c = 0 to pointers x1, x2.
//Returns number of solutions (INFINITE_SOLUTIONS if infinite)
Solutions solve_quad(const double a, const double b, const double c, double* x1, double* x2){
    assert(x1 && x2);
    
    if (is_double_equal(a, 0)) {        //check if equation is quad (zero division check)
        return solve_lin(b, c, x1);
    }

    double D = b*b - 4*a*c;     //discriminant
    if (is_double_equal(D, 0)) {                                //check if there are solutions
        *x1 = (-b) / (2*a);
        return ONE_SOLUTION;
    } else if (D < 0) {
        return NO_SOLUTIONS;
    } else {
        double D_sqrt = sqrt(D);
        *x1 = (-b - D_sqrt) / (2*a);
        *x2 = (-b + D_sqrt) / (2*a);
        return TWO_SOLUTIONS;
    }
}

//Solves equations of the form a*x + b = 0 to pointer x1.
//Returns number of solutions (INFINITE_SOLUTIONS if infinite)
Solutions solve_lin(const double a, const double b, double* x1) {
    assert(x1);

    if (is_double_equal(a, 0)) {
        return is_double_equal(b, 0) ? INFINITE_SOLUTIONS : NO_SOLUTIONS;
    }

    *x1 = -b / a;
    return ONE_SOLUTION;
}

//Returns 1 if two doubles are equal with precision of DOUBLE_COMPARE_PRECISION
int is_double_equal(double a, double b) {
    static const double DOUBLE_COMPARE_PREC = 0.000001;
    return abs(a - b) < DOUBLE_COMPARE_PREC;
}
