#ifndef INPUT_H_
#define INPUT_H_

#include <stdio.h>
#include <math.h>
#include <assert.h>

/**
 * @brief Reads double from input to pointer
 * 
 * @param[in] x
 * @param[in] stream 
 * @return int success
 */
int read_num(double* x, FILE* stream = stdin);

/**
 * @brief Reads int from input to pointer
 * 
 * @param[in] x 
 * @param[in] stream 
 * @return int success
 */
int read_num(int* x, FILE* stream = stdin);

/**
 * @brief Flushes input
 * 
 * @return int number of flushed symbols
 */
int input_flush(FILE* stream = stdin);

#endif