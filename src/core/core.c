//
// Created by rama on 13.03.23.
//

#include "core.h"

char *rpn(char *in, int *err) {
    *err = OK;
    operator_stack *operator_s = NULL;
    char *out = malloc(sizeof(char) * strlen(in) * 2);
    char *res = out;

    _catch_err(in, err);

    return res;
}

/**
 * @brief - A function for catching errors, if the errors fit the condition, then throw out "Input error!"
 * @param in - input line
 * @param err - error code
 */
void _catch_err(char *in, int *err) {
    int count_bracket = 0;
    if (*in == '\0' || strlen(in) > SIZE)
        *err = INVALID;

    if (in[0] == ')' || in[0] == '%' || in[0] == '.' ||
        in[0] == '*' || in[0] == '/' || in[0] == '^')
        *err = INVALID;

    for (int i = 0; i < in[i]; ++i) {
        if (is_binary(&in[i]) && is_binary(&in[i + 1]))
            *err = INVALID;
        if (is_binary(&in[i]) &&
            (in[i - 1] == '.' || in[i + 1] == '.'))
            *err = INVALID;
        if (is_digit(&in[i]) &&
            in[i + 1] == '.' && in[i + 2] == '.')
            *err = INVALID;
        if (is_digit(&in[i]) &&
            in[i + 1] == '.' && in[i - 1] == '.')
            *err = INVALID;
        if ((is_digit(&in[i]) || in[i] == 'x' || in[i] == '.') &&
            is_unary(&in[i + 1]))
            *err = INVALID;
        if (in[i] == 'x' && (is_digit(&in[i + 1]) || is_digit(&in[i - 1])))
            *err = INVALID;
        if (in[i] == '(') {
            if (is_digit(&in[i - 1]) || in[i - 1] == '.' ||
                in[i - 1] == 'x')
                *err = INVALID;
            ++count_bracket;
        } else if (in[i] == ')') {
            if (is_digit(&in[i + 1]) || in[i + 1] == '.' ||
                in[i + 1] == 'x')
                *err = INVALID;
            --count_bracket;
        }
    }
    if (count_bracket != 0)
        *err = INVALID;

}

/**
 * @brief - We check if the operator is binary ['+', '-', '*', '/', '^', '%'].
 *
 * @param ch
 * @return - We return the `true` if this is the case
 */
int is_binary(char *ch) {
    return *ch == '+' || *ch == '-' ||
           *ch == '*' || *ch == '/' ||
           *ch == '^' || *ch == '%';
}

/**
 * @brief - We check if the operand is a digit [0..9].
 *
 * @param ch
 * @return - We return the `true` if this is the case
 */
int is_digit(char *ch) {
    return *ch >= '0' && *ch <= '9';
}

/**
 * @brief - We check if the operator is unary [cos, sin, tan, acos, asin, atan, sqrt, ln, log].
 *
 * @param ch
 * @return - We return the `true` if this is the case
 */
int is_unary(char *ch) {
    return *ch == 'c' || *ch == 's' || *ch == 't' || *ch == 'a' ||
           *ch == 'g' || *ch == 'q' || *ch == 'l' ||
           *ch == 'C' || *ch == 'S' || *ch == 'T';
}