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

    if (res != NULL) {
        for (int i = 0; i < in[i]; ++i) {
            is_unary_minus_or_plus(&in[i], &out, &i);
            if (in[i] == '(') {
                operator_s = push_operator_stack(operator_s, in[i]);
                is_unary_minus_or_plus(&in[i], &out, &i);
            } else if (in[i] == ')') {
                while (operator_s != NULL && peek_operator_stack(operator_s) != '(') {
                    *(out++) = peek_operator_stack(operator_s);
                    *(out++) = ' ';
                    operator_s = pop_operator_stack(operator_s);
                }
                operator_s = pop_operator_stack(operator_s);
            } else if (is_digit(&in[i]) || in[i] == '.' || in[i] == 'x') {
                *(out++) = in[i];
                if (!(is_digit(&in[i + 1]) || in[i + 1] == '.'))
                    *(out++) = ' ';
            } else if (is_binary(&in[i])) {
                // TODO: Parser for binary operations;
            } else if (is_unary(in[i])) {
                // TODO: Parser for unary operations;
            }
        }
    } else {
        *err = MEM;
    }

    // TODO:

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

/**
 * @brief - We replacing the unary sign. ['-' -> '~' | '+' -> '#']
 * @param ch
 * @param out
 * @param idx
 */
void is_unary_minus_or_plus(char *ch, char **out, int *idx) {
    char *tmp = *out;
    int index = *idx;

    if (*ch == '-' && (index == 0 || (index >= 1 && *(ch - 1) == '('))) {
        *(tmp++) = '~';
        ++index;
    } else if (*ch == '+' && (index == 0 || (index >= 1 && *(ch - 1) == '('))) {
        *(tmp++) = '#';
        ++index;
    }
    *out = tmp;
    *idx = index;
}


/**
 * @brief - Let's determine the priority of the operation.
 * @param _operation
 * @return - We return the priority number of the operation to be replenished.
 */
int get_operation_priority(char _operation) {
    int ret = 0;

    if (_operation == '+' || _operation == '-')
        ret = 1;
    else if (_operation == '*' || _operation == '/' || _operation == '%')
        ret = 2;
    else if (_operation == '^')
        ret = 3;
    else if (_operation == 'c' || _operation == 'C' || _operation == 't' ||
             _operation == 'T' || _operation == 's' || _operation == 'S' ||
             _operation == 'q' || _operation == 'l' || _operation == 'g')
        ret = 4;

    return ret;
}