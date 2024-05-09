#ifndef UNTITLED9_TRANSPOSE_MATRIX_H
#define UNTITLED9_TRANSPOSE_MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include "../../data_structures/matrix/matrix.h"

void generateMatrix(const char *filename, size_t n) {
    srand(time(NULL));

    FILE *file = fopen(filename, "w");

    if (file == NULL) {
        printf("file reading error\n");
        exit(1);
    }

    fprintf(file, "%lld\n", n);

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            fprintf(file, "%d ", rand() % 10);
        }

        fprintf(file, "\n");
    }

    fclose(file);
}

void transposeMatrixInFile(const char *filename) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("file reading error\n");
        exit(1);
    }

    size_t n;
    fscanf(file, "%lld", &n);

    matrix matrix = getMemMatrix((int) n, (int) n);

    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < n; j++)
            fscanf(file, "%d", &matrix.values[i][j]);

    fclose(file);

    transposeSquareMatrix(&matrix);

    file = fopen(filename, "w");

    if (file == NULL) {
        printf("file reading error\n");
        exit(1);
    }

    fprintf(file, "%lld\n", n);

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            fprintf(file, "%d ", matrix.values[i][j]);
        }

        fprintf(file, "\n");
    }

    fclose(file);

    freeMemMatrix(&matrix);
}

void test_transposeMatrixInFile_1_one_element_matrix() {
    const char *filename = "C:\\Users\\Andrey\\Desktop\\19.19\\task_1_test_1.txt";
    size_t n = 1;

    generateMatrix(filename, n);

    transposeMatrixInFile(filename);

    FILE *file = fopen(filename, "r");

    assert(file != NULL);

    fclose(file);
}

void test_transposeMatrixInFile_2_unit_symmetric_matrix() {
    const char *filename = "C:\\Users\\Andrey\\Desktop\\19.19\\task_1_test_1.txt";
    int n = 3;
    matrix m = createMatrixFromArray((int[]) {1, 0, 0,
                                                 0, 1, 0,
                                                 0, 0, 1}, 3, 3);

    FILE* file = fopen(filename, "w");

    fprintf(file, "%d\n", n);

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            fprintf(file, "%d ", m.values[i][j]);
        }

        fprintf(file, "\n");
    }

    fclose(file);


    transposeMatrixInFile(filename);


    int n_result;
    matrix result_m = getMemMatrix(n, n);

    file = fopen(filename, "r");

    fscanf(file, "%d\n", &n_result);

    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < n; j++)
            fscanf(file, "%d", &result_m.values[i][j]);

    fclose(file);

    assert(areTwoMatricesEqual(&m, &result_m));

    freeMemMatrix(&m);
    freeMemMatrix(&result_m);
}

void test_transposeMatrixInFile_3_matrix() {
    const char filename[] = "C:\\Users\\Andrey\\Desktop\\19.19\\task_1_test_1.txt";
    int n = 3;
    matrix m = createMatrixFromArray((int[]) {1, 2, 3,
                                                 4, 5, 6,
                                                 7, 8, 9}, 3, 3);

    matrix check_matrix = createMatrixFromArray((int[]) {1, 4, 7,
                                                            2, 5, 8,
                                                            3, 6, 9}, 3, 3);

    FILE* file = fopen(filename, "w");

    fprintf(file, "%d\n", n);

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            fprintf(file, "%d ", m.values[i][j]);
        }

        fprintf(file, "\n");
    }

    fclose(file);

    transposeMatrixInFile(filename);

    int n_result;
    matrix result_m = getMemMatrix(n, n);

    file = fopen(filename, "r");

    fscanf(file, "%d\n", &n_result);

    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < n; j++)
            fscanf(file, "%d", &result_m.values[i][j]);

    fclose(file);

    assert(areTwoMatricesEqual(&check_matrix, &result_m));

    freeMemMatrix(&m);
    freeMemMatrix(&result_m);
    freeMemMatrix(&check_matrix);
}

void test_matrix_transpose() {
    test_transposeMatrixInFile_1_one_element_matrix();
    test_transposeMatrixInFile_2_unit_symmetric_matrix();
    test_transposeMatrixInFile_3_matrix();
}

#endif //UNTITLED9_TRANSPOSE_MATRIX_H
