#include <stdio.h>
#include <math.h>
#include <assert.h>

#define INFINITE_SOLUTIONS -1
#define DOUBLE_COMPARE_PREC 0.000001

int is_double_equal(double a, double b);
int input_flush();
int read_double_to_ptr(double* x);
void enter_coeff_to_ptr(const char c, double* x);
int solve_to_ptr(const double a, const double b, const double c, double* x1, double* x2);

int main() {
  printf("Hello! This program solves quad equations of the form a*x^2 + b*x + c = 0\n");
  printf("Where \"x\" is a variable and \"a\", \"b\", \"c\" are coefficients\n");
  double a,b,c;
  enter_coeff_to_ptr('a', &a);
  enter_coeff_to_ptr('b', &b);
  enter_coeff_to_ptr('c', &c);
  double x1, x2;
  switch (solve_to_ptr(a, b, c, &x1, &x2)){
    case 0:
      printf("No solutions\n");
      break;
    case 1:
      printf("1 solution:\nx = %lf\n", x1);
      break;
    case 2:
      printf("2 solutions:\nx1 = %lf\nx2 = %lf\n", x1, x2);
      break;
    case INFINITE_SOLUTIONS:
      wprintf(L"Infinite number of solutions:\nx belongs to the set (-inf; +inf)\n");
      break;
    default:
      assert(0);
      break;
  }
  printf("Bye!");
  return 0;
}

//Returns 1 if two doubles are equal with precision of DOUBLE_COMPARE_PRECISION
int is_double_equal(double a, double b) {
  return abs(a - b) < DOUBLE_COMPARE_PREC;
}

//Flushes input. Returns number of flushed symbols
int input_flush() {
  int c;
  int cnt = 1;
  while ((c=getchar()) != '\n' && c != EOF) cnt++;
  return cnt;
}

//Reads double from input to pointer. Returns 0 if fails
int read_double_to_ptr(double* x) {
  assert(x != NULL);
  int res = scanf("%lf", x);
  if (input_flush() != 1 || res != 1 || res == EOF)   //check input errors and flush input
    return 0;
  return 1;
}

//Reads coefficients from input
void enter_coeff_to_ptr(char c, double* x) {
  assert(x != NULL);
  while (1) {
    printf("Enter coefficient %c: ", c);
    if (read_double_to_ptr(x)) break;                         //exit if entered correctly
    printf("Coefficient entered incorrectly. Try again\n");
  }
  return;
}

//Solves quad equation to pointers x1, x2. Returns number of solutions (INFINITE_SOLUTIONS if infinite)
int solve_to_ptr(const double a, const double b, const double c, double* x1, double* x2){
  assert(x1!=NULL && x2!=NULL);
  if (is_double_equal(a, 0)) {        //check if equation is quad (zero division check)
    if (is_double_equal(b, 0)) {
      if (is_double_equal(c, 0))
        return INFINITE_SOLUTIONS;    //infinite number of solutions
      else
        return 0;
    }
    *x1 = -c / b;
    return 1;
  }
  double D = b*b - 4*a*c;             //discriminant
  if (is_double_equal(D, 0)) {        //check if there are solutions
    *x1 = (-b) / (2*a);
    return 1;
  } else if (D < 0) {
    return 0;
  } else {
    double D_sqrt = sqrt(D);
    *x1 = (-b - D_sqrt) / (2*a);
    *x2 = (-b + D_sqrt) / (2*a);
    return 2;
  }
  assert(0);
  return 0;
}