#ifndef INPUT_H_
#define INPUT_H_

#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <assert.h>

/**
 * @brief Specifies input errors
 */
enum class InputStatus {
    END_OF_FILE = -1, ///< End of file reached
    WRONG_DATA  =  0, ///< Input error
    OK          =  1  ///< OK
};

/**
 * @brief Reads double from input to pointer
 *
 * @param[in] x
 * @param[in] stream
 * @param[in] flush enables input_flush() at the end
 * @return int success
 */
InputStatus read_num(double* x, FILE* stream = stdin, bool flush = true);

/**
 * @brief Reads int from input to pointer
 *
 * @param[in] x
 * @param[in] stream
 * @param[in] flush enables input_flush() at the end
 * @return int success
 */
InputStatus read_num(int* x, FILE* stream = stdin, bool flush = true);

/**
 * @brief Flushes input
 * @param[in] stream
 *
 * @return bool false - if there are non space symbols in stream left
 */
bool input_flush(FILE* stream = stdin);

#endif // #ifndef INPUT_H_
