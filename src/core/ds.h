//
// Created by rama on 13.03.23.
//

#include <stdlib.h>
#include <stdio.h>

#ifndef S21_SMARTCALC_V1_0_DS_H
#define S21_SMARTCALC_V1_0_DS_H

/*
 * @brief
 */
typedef struct operator_stack {
    char val;
    struct operator_stack *next;
} operator_stack;

/*
 * @brief
 */
typedef struct operand_stack {
    double val;
    struct operand_stack *next;
} operand_stack;

operator_stack *init_operator_stack(char _operator);

operand_stack *init_operand_stack(double _operand);

size_t get_size_operator_stack(operator_stack *head);

operator_stack *push_operator_stack(operator_stack *head, char _operator);

operand_stack *push_operand_stack(operand_stack *head, double _operand);

operator_stack *pop_operator_stack(operator_stack *head);

operand_stack *pop_operand_stack(operand_stack *head);

char peek_operator_stack(operator_stack *head);

double peek_operand_stack(operand_stack *head);

#endif //S21_SMARTCALC_V1_0_DS_H
