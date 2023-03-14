//
// Created by rama on 13.03.23.
//

#ifndef S21_SMARTCALC_V1_0_CORE_H
#define S21_SMARTCALC_V1_0_CORE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "ds.h"

#define SIZE 255

typedef enum {
    OK,
    INVALID,
    MEM,
    CALC
} _logger;

char *rpn(char *in, int *err);

void _catch_err(char *in, int *err);

int is_binary(char *ch);

int is_digit(char *ch);

int is_unary(char *ch);

void is_unary_minus_or_plus(char *ch, char **out, int *idx);


int get_operation_priority(char _operation);


#endif //S21_SMARTCALC_V1_0_CORE_H
