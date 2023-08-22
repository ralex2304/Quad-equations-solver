#include "input.h"

int input_flush(FILE* stream) {
    int c = 0;
    int cnt = 0;
    do {
        cnt++;
    } while ((c = fgetc(stream)) != '\n' && c != EOF && !feof(stream) && !ferror(stream));
    
    return cnt;
}

int read_num(double* x, FILE* stream) {
    assert(x);

    int res = fscanf(stream, "%lf", x);
    return input_flush(stream) == 1 && res == 1
           && isfinite(*x);  // check input errors and flush input
}

int read_num(int* x, FILE* stream) {
    assert(x);

    int res = fscanf(stream, "%d", x);
    return input_flush(stream) == 1 && res == 1 && res != EOF;    // check input errors and flush input
}