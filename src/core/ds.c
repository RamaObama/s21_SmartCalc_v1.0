//
// Created by rama on 13.03.23.
//

#include "ds.h"

operator_stack *init_operator_stack(char _operator) {
    operator_stack *tmp = (operator_stack *) malloc(sizeof(operator_stack));
    tmp->val = _operator;
    tmp->next = NULL;
    return tmp;
}

operand_stack *init_operand_stack(double _operand) {
    operand_stack *tmp = (operand_stack *)malloc(sizeof(operand_stack));
    tmp->val = _operand;
    tmp->next = NULL;
    return tmp;
}

size_t get_size_operator_stack(operator_stack *head) {
    size_t res = 0;
    while (head) {
        ++res;
        head = head->next;
    }
    return res;
}

operator_stack *push_operator_stack(operator_stack *head, char _operator) {
    operator_stack *tmp = init_operator_stack(_operator);
    tmp->next = head;
    return tmp;
}

operand_stack *push_operand_stack(operand_stack *head, double _operand) {
    operand_stack *tmp = init_operand_stack(_operand);
    tmp->next = head;
    return tmp;
}

operator_stack *pop_operator_stack(operator_stack *head) {
    operator_stack *tmp = NULL;
    if (head != NULL) {
        tmp = head->next;
        free(head);
    }
    return tmp;
}

operand_stack *pop_operand_stack(operand_stack *head) {
    operand_stack *tmp = NULL;
    if (head != NULL) {
        tmp = head->next;
        free(head);
    }
    return tmp;
}

char peek_operator_stack(operator_stack *head) {
    return head->val;
}

double peek_operand_stack(operand_stack *head) {
    return head->val;
}
