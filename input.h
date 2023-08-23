#ifndef INPUT_H_
#define INPUT_H_

#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>

/**
 * @brief Specifies input errors
 */
enum class InputError {
    END_OF_FILE = -1,
    WRONG_DATA  =  0,
    OK          =  1
};

/**
 * @brief Reads double from input to pointer
 * 
 * @param[in] x
 * @param[in] stream 
 * @return int success
 */
InputError read_num(double* x, FILE* stream = stdin, bool flush = true);

/**
 * @brief Reads int from input to pointer
 * 
 * @param[in] x 
 * @param[in] stream 
 * @return int success
 */
InputError read_num(int* x, FILE* stream = stdin, bool flush = true);

/**
 * @brief Flushes input
 * @param[in] stream
 * 
 * @return int 0 - if there are non space symbols in stream left
 */
int input_flush(FILE* stream = stdin);

#endif