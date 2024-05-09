#ifndef UNTITLED9_CONVERT_FLOAT_NUMBERS_H
#define UNTITLED9_CONVERT_FLOAT_NUMBERS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include "../../data_structures/string/string_.h"

void generateFloat(const char *filename, int n){
    srand(time(NULL));

    FILE *file = fopen(filename, "w");

    if (file == NULL) {
        printf("file reading error\n");
        exit(1);
    }

    for (size_t i = 0; i < n; i++)
        fprintf(file, "%f ", 10.0 * rand() / RAND_MAX);

    fclose(file);
}

void convertFloatNumbers(const char *filename){
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("file reading error\n");
        exit(1);
    }

    double *numbers = malloc(sizeof(double));
    size_t count = 0;

    while (fscanf(file, "%lf", &numbers[count]) != EOF) {
        count++;
        numbers = realloc(numbers, (count + 1) * sizeof(double));
    }

    fclose(file);

    file = fopen(filename, "w");

    if (file == NULL) {
        printf("file reading error\n");
        exit(1);
    }

    for (size_t i = 0; i < count; i++)
        fprintf(file, "%.2lf ", numbers[i]);

    fclose(file);

    free(numbers);
}

void test_convertFloatNumbers_1_with_generated_float() {
    const char *filename = "C:\\Users\\Andrey\\Desktop\\19.19\\task_2_test_1.txt";
    int n = 5;

    generateFloat(filename, n);

    convertFloatNumbers(filename);

    FILE *file = fopen(filename, "r");

    assert(file != NULL);

    fclose(file);
}

void test_convertFloatNumbers_2_zero_quantity() {
    const char filename[] = "C:\\Users\\Andrey\\Desktop\\19.19\\task_2_test_2.txt";

    FILE* file = fopen(filename, "w");
    fclose(file);

    convertFloatNumbers(filename);

    file = fopen(filename, "r");

    char data[10] = "";
    int result = fscanf(file, "%s", data);

    fclose(file);

    assert(result == EOF);
}


void test_convertFloatNumbers_3_one_element() {
    const char filename[] = "C:\\Users\\Andrey\\Desktop\\19.19\\task_2_test_3.txt";

    float number = 10.123;

    FILE* file = fopen(filename, "w");

    fprintf(file, "%f", number);

    fclose(file);

    convertFloatNumbers(filename);

    file = fopen(filename, "r");

    char data[10] = "";
    fscanf_s(file, "%s", data);

    fclose(file);

    char check[10] = "10.12";

    assert(strcmp_(data, check) == 0);
}


void test_convertFloatNumbers_4_more_element() {
    const char filename[] = "C:\\Users\\Andrey\\Desktop\\19.19\\task_2_test_4.txt";

    float f1 = 1.123123;
    float f2 = 2.232323;
    float f3 = 3.343434;


    FILE* file = fopen(filename, "w");

    fprintf(file, "%f %f %f", f1, f2,f3);

    fclose(file);

    convertFloatNumbers(filename);

    file = fopen(filename, "r");

    char data[100] = "";
    fgets(data, sizeof(data), file);

    fclose(file);

    char check[100] = "1.12 2.23 3.34 ";

    assert(strcmp_(data, check) == 0);
}


void test_convertFloatNumbers() {
    test_convertFloatNumbers_1_with_generated_float();
    test_convertFloatNumbers_2_zero_quantity();
    test_convertFloatNumbers_3_one_element();
    test_convertFloatNumbers_4_more_element();
}

#endif //UNTITLED9_CONVERT_FLOAT_NUMBERS_H
