#include "input.h"

InputStatus read_num(double* x, FILE* stream, bool flush) {
    assert(x);
    assert(stream);

    int res = fscanf(stream, "%lf", x);
    if (res == EOF)
        return InputStatus::END_OF_FILE;
    else if (res == 1 && isfinite(*x) && (!flush || input_flush(stream))) {
        return InputStatus::OK;
    } else {
        return InputStatus::WRONG_DATA;
    }
}

InputStatus read_num(int* x, FILE* stream, bool flush) {
    assert(x);
    assert(stream);

    int res = fscanf(stream, "%d", x);
    if (res == EOF)
        return InputStatus::END_OF_FILE;
    else if (res == 1 && (!flush || input_flush(stream))) {
        return InputStatus::OK;
    } else {
        return InputStatus::WRONG_DATA;
    }
}

bool input_flush(FILE* stream) {
    assert(stream);

    int c = ' ';
    bool non_space = true;

    do {
        if (!isspace(c))
            non_space = false;
    } while ((c = fgetc(stream)) != '\n' && c != EOF && !feof(stream) && !ferror(stream));

    return non_space;
}
