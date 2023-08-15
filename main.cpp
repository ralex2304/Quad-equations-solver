#include <stdio.h>
#include <assert.h>

#define BUF_LEN 100

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
  int solutions = solve_to_ptr(a, b, c, &x1, &x2);
  if (solutions == 0){
    printf("No solutions\n");
  } else if (solutions == 1){
    printf("1 solution:\nx = %lf\n", x1);
  } else if (solutions == 2){
    printf("2 solutions:\nx1 = %lf\nx2 = %lf\n", x1, x2);
  } else if(solutions == -1){
    wprintf(L"Infinite number of solutions:\nx belongs to the set (-inf; +inf)\n");
  } else {
    assert(0);
  }
  printf("Bye!");
  return 0;
}

//Reads double from input to pointer. Returns 0 if fails
int read_double_to_ptr(double* x) {
  assert(x != NULL);
  char c = '\0';
  char str[BUF_LEN];
  int str_len = 0;
  int dot_cnt = 0;
  while ((c=getchar()) != '\n') {
    if (c == ' ') continue;
    if ((c=='-' && str_len!=0) || (c=='.' && dot_cnt!=0) || !('0'<=c && c<='9' || c=='-' || c=='.'))
      return 0;
    if (c == '.') dot_cnt++;
    str[str_len] = c;
    str_len++;
  }
  str[str_len] = '\0';
  // if str is emty, strtod returns 0.0 (it's not a bug, it's a feature ^-^ )
  *x = strtod(str, NULL);
  return 1;
}

//Reads coefficients from input
void enter_coeff_to_ptr(char c, double* x) {
  assert(x != NULL);
  while (1) {
    printf("Enter coefficient %c: ", c);
    if (read_double_to_ptr(x)) break;                         //exit if entered correctly
    printf("Coefficient entered incorrectly. Try again\n");
    while(getchar() != '\n') {}                               //clear input buffer
  }
  return;
}

//Solves quad equation to pointers x1, x2. Returns number of solutions (-1 if infinite)
int solve_to_ptr(const double a, const double b, const double c, double* x1, double* x2){
  assert(x1!=NULL && x2!=NULL);
  if (a == 0) {                   //check if equation is quad (zero division check)
    if (b == 0)
      if (c == 0)
        return -1;                //infinite number of solutions
      else
        return 0;
    *x1 = -c / b;
    return 1;
  }
  double D = b*b - 4*a*c;         //discriminant
  if (D < 0) {                    //check if there are solutions
    return 0;
  } else if (D == 0) {
    *x1 = (-b) / (2*a);
    return 1;
  } else {
    *x1 = (-b - D) / (2*a);
    *x2 = (-b + D) / (2*a);
    return 2;
  }
  assert(0);
  return 0;
}