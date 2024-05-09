#ifndef UNTITLED9_VALUES_OF_EXPRESSIONS_H
#define UNTITLED9_VALUES_OF_EXPRESSIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../../data_structures/string/string_.h"

void valuesOfExpressions(const char *filename) {
    FILE *file = fopen(filename, "r+");

    if (file == NULL) {
        printf("file reading error\n");
        exit(1);
    }

    int operand1, operand2;
    char operator;

    fscanf(file, "%d %c %d", &operand1, &operator, &operand2);

    int result;

    switch (operator) {
        case '+':
            result = operand1 + operand2;
            break;
        case '-':
            result = operand1 - operand2;
            break;
        case '*':
            result = operand1 * operand2;
            break;
        case '/':
            if (operand2 != 0) {
                result = operand1 / operand2;
            } else {
                printf("division by zero error\n");
                return;
            }
            break;
        default:
            printf("unknown operator\n");
            return;
    }

    fprintf(file, " = %d", result);

    fclose(file);
}

void test_valuesOfExpressions_1_addition() {
    const char *filename = "C:\\Users\\Andrey\\Desktop\\19.19\\task_3_test_1.txt";

    FILE *file = fopen(filename, "w");

    fprintf(file, "5 + 3");

    fclose(file);

    valuesOfExpressions(filename);

    file = fopen(filename, "r");

    char expected[] = "5 + 3 = 8";
    char actual[10];

    fgets(actual, 10, file);

    fclose(file);

    assert(strcmp_(actual, expected) == 0);
}

void test_valuesOfExpressions_2_division() {
    const char *filename = "C:\\Users\\Andrey\\Desktop\\19.19\\task_3_test_2.txt";

    FILE *file = fopen(filename, "w");

    fprintf(file, "8 / 2");

    fclose(file);

    valuesOfExpressions(filename);

    file = fopen(filename, "r");

    char expected[] = "8 / 2 = 4";
    char actual[10];

    fgets(actual, 10, file);

    fclose(file);

    assert(strcmp_(actual, expected) == 0);
}

void test_valuesOfExpressions_3_unknown_operator() {
    const char *filename = "C:\\Users\\Andrey\\Desktop\\19.19\\task_3_test_3.txt";

    FILE *file = fopen(filename, "w");

    fprintf(file, "5 # 3");

    fclose(file);

    valuesOfExpressions(filename);

    file = fopen(filename, "r");

    char expected[] = "5 # 3";
    char actual[10];

    fgets(actual, 10, file);

    fclose(file);

    assert(strcmp_(actual, expected) == 0);
}

void test_valuesOfExpressions() {
    test_valuesOfExpressions_1_addition();
    test_valuesOfExpressions_2_division();
    test_valuesOfExpressions_3_unknown_operator();
}

#endif //UNTITLED9_VALUES_OF_EXPRESSIONS_H
