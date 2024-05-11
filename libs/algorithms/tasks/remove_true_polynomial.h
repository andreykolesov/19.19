#ifndef UNTITLED9_REMOVE_TRUE_POLYNOMIAL_H
#define UNTITLED9_REMOVE_TRUE_POLYNOMIAL_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <memory.h>

typedef struct {
    int degree;
    double coefficient;
} Polynomial;

int isRoot(Polynomial *poly, int degree, double x) {
    double result = 0.0;

    for (int i = 0; i < degree; i++) {
        result += poly[i].coefficient * pow(x, poly[i].degree);
    }

    return result == 0.0;
}

void removeTruePolynomial(const char *filename, double x) {
    FILE *file = fopen(filename, "rb");

    if (file == NULL) {
        printf("file reading error\n");
        exit(1);
    }

    Polynomial poly[100];
    int count = fread(poly, sizeof(Polynomial), 100, file);
    fclose(file);

    file = fopen(filename, "wb");

    if (file == NULL) {
        printf("file reading error\n");
        exit(1);
    }

    for (int i = 0; i < count; i++) {
        if (!isRoot(poly, count, x)) {
            fwrite(&poly[i], sizeof(Polynomial), 1, file);
        }
    }

    fclose(file);
}

void test_removeTruePolynomial_1_with_root() {
    const char* filename = "C:\\Users\\Andrey\\Desktop\\19.19\\task_6_test_1.txt";
    FILE* file = fopen(filename, "wb");

    fprintf(file, "2 1.0\n");

    fclose(file);

    removeTruePolynomial(filename, 0.0);

    file = fopen(filename, "rb");
    int result = fgetc(file);

    assert(result == EOF);
    fclose(file);
}

void test_removeTruePolynomial_2_without_root() {
    const char* filename = "C:\\Users\\Andrey\\Desktop\\19.19\\task_6_test_2.txt";
    FILE* file = fopen(filename, "wb");

    Polynomial poly = {2, 1.0};
    fwrite(&poly, sizeof(Polynomial), 1, file);

    fclose(file);

    removeTruePolynomial(filename, 1.0);

    file = fopen(filename, "rb");
    Polynomial readPoly;
    fread(&readPoly, sizeof(Polynomial), 1, file);

    assert(memcmp(&poly, &readPoly, sizeof(Polynomial)) == 0);

    fclose(file);
}

void test_removeTruePolynomial_3_empty_file() {
    const char* filename = "C:\\Users\\Andrey\\Desktop\\19.19\\task_6_test_3.txt";
    FILE* file = fopen(filename, "wb");
    fclose(file);

    removeTruePolynomial(filename, 1.0);

    file = fopen(filename, "rb");
    assert(fgetc(file) == EOF);
}

void test_removeTruePolynomial() {
    test_removeTruePolynomial_1_with_root();
    test_removeTruePolynomial_2_without_root();
    test_removeTruePolynomial_3_empty_file();
}

#endif //UNTITLED9_REMOVE_TRUE_POLYNOMIAL_H
