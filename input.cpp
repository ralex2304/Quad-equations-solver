#include "input.h"

InputError read_num(double* x, FILE* stream, bool flush) {
    assert(x && stream);

    int res = fscanf(stream, "%lf", x);
    if (res == EOF)
        return InputError::END_OF_FILE;
    else if (res == 1 && isfinite(*x) && (!flush || input_flush(stream))) {
        return InputError::OK;
    } else {
        return InputError::WRONG_DATA;
    }
}

InputError read_num(int* x, FILE* stream, bool flush) {
    assert(x && stream);

    int res = fscanf(stream, "%d", x);
    if (res == EOF)
        return InputError::END_OF_FILE;
    else if (res == 1 && (!flush || input_flush(stream))) {
        return InputError::OK;
    } else {
        return InputError::WRONG_DATA;
    }
}

bool input_flush(FILE* stream) {
    int c = ' ';
    bool non_space = true;

    do {
        if (!isspace(c))
            non_space = false;
    } while ((c = fgetc(stream)) != '\n' && c != EOF && !feof(stream) && !ferror(stream));

    return non_space;
}
