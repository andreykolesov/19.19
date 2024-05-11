#ifndef UNTITLED9_TRANSPOSE_NON_SYMMETRIC_MATRIX_H
#define UNTITLED9_TRANSPOSE_NON_SYMMETRIC_MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../../data_structures/matrix/matrix.h"

bool isSymmetric(int n, int matrix[n][n]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (matrix[i][j] != matrix[j][i])
                return false;
    return true;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void transpose(int n, int matrix[n][n]) {
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            swap(&matrix[i][j], &matrix[j][i]);
}

void transposeNonSymmetricMatrix(const char *filename) {
    FILE *file = fopen(filename, "r+b");

    if (file == NULL) {
        printf("file reading error\n");
        exit(1);
    }

    int n;
    if (fread(&n, sizeof(int), 1, file) != 1) {
        printf("error when reading the order of the matrix.\n");
        fclose(file);
        return;
    }

    while (1) {
        int matrix[n][n];
        size_t read_count = fread(matrix, sizeof(int), n * n, file);
        if (read_count != n * n) {
            if (feof(file)) {
                break;
            } else {
                printf("error reading the matrix.\n");
                break;
            }
        }

        if (!isSymmetric(n, matrix)) {
            transpose(n, matrix);
            fseek(file, -(long int) read_count * sizeof(int), SEEK_CUR);
            fwrite(matrix, sizeof(int), read_count, file);
            fseek(file, (long int) read_count * sizeof(int), SEEK_CUR);
        }
    }

    fclose(file);
}

void test_transposeNonSymmetricMatrix_1_empty_matrix() {
    const char filename[] = "C:\\Users\\Andrey\\Desktop\\19.19\\task_8_test_1.txt";

    int n = 0;
    FILE *file = fopen(filename, "wb");

    fwrite(&n, sizeof(int), 1, file);

    fclose(file);

    file = fopen(filename, "rb");

    int res_n;
    fread(&res_n, sizeof(int), 1, file);

    fclose(file);

    assert(n == res_n);
}

void test_transposeNonSymmetricMatrix_2_one_matrices() {
    const char filename[] = "C:\\Users\\Andrey\\Desktop\\19.19\\task_8_test_2.txt";

    int n = 1;
    int x1 = 1;
    int x2 = 10;

    FILE *file = fopen(filename, "wb");

    fwrite(&n, sizeof(int), 1, file);
    fwrite(&x1, sizeof(int), 1, file);
    fwrite(&x2, sizeof(int), 1, file);

    fclose(file);

    int res_n, res_x1, res_x2;
    file = fopen(filename, "rb");

    fread(&res_n, sizeof(int), 1, file);
    fread(&res_x1, sizeof(int), 1, file);
    fread(&res_x2, sizeof(int), 1, file);

    fclose(file);

    assert(res_n == n);
    assert(res_x1 == x1);
    assert(res_x2 == x2);
}

void test_transposeNonSymmetricMatrix_3_symmetric_matrix() {
    const char filename[] = "C:\\Users\\Andrey\\Desktop\\19.19\\task_8_test_3.txt";

    FILE *file = fopen(filename, "wb");

    int n = 3;
    matrix m = createMatrixFromArray((int[]) {1, 0, 0,
                                              0, 1, 0,
                                              0, 0, 1}, 3, 3);

    fwrite(&n, sizeof(int), 1, file);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            fwrite(&m.values[i][j], sizeof(int), 1, file);

    fclose(file);

    transposeNonSymmetricMatrix(filename);

    file = fopen(filename, "rb");

    int res_n;
    fread(&res_n, sizeof(int), 1, file);
    matrix res_m = getMemMatrix(res_n, res_n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            fread(&res_m.values[i][j], sizeof(int), 1, file);

    fclose(file);

    assert(areTwoMatricesEqual(&res_m, &m));

    freeMemMatrix(&m);
    freeMemMatrix(&res_m);
}

void test_transposeNonSymmetricMatrix_4_non_symmetric_matrix() {
    const char filename[] = "C:\\Users\\Andrey\\Desktop\\19.19\\task_8_test_4.txt";

    FILE *file = fopen(filename, "wb");

    int n = 3;
    matrix m = createMatrixFromArray((int[]) {1, 2, 3,
                                              4, 5, 6,
                                              7, 8, 9}, 3, 3);

    fwrite(&n, sizeof(int), 1, file);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            fwrite(&m.values[i][j], sizeof(int), 1, file);

    fclose(file);

    transposeNonSymmetricMatrix(filename);

    file = fopen(filename, "rb");

    int res_n;
    fread(&res_n, sizeof(int), 1, file);
    matrix res_m = getMemMatrix(res_n, res_n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            fread(&res_m.values[i][j], sizeof(int), 1, file);

    fclose(file);

    matrix check = createMatrixFromArray((int[]) {1, 4, 7,
                                                  2, 5, 8,
                                                  3, 6, 9}, 3, 3);

    assert(res_n == n);
    assert(areTwoMatricesEqual(&res_m, &check));

    freeMemMatrix(&m);
    freeMemMatrix(&res_m);
}

void test_transposeNonSymmetricMatrix_5_mixed_matrix() {
    const char filename[] = "C:\\Users\\Andrey\\Desktop\\19.19\\task_8_test_5.txt";

    FILE *file = fopen(filename, "wb");

    int n = 3;
    matrix m1 = createMatrixFromArray((int[]) {1, 0, 0,
                                               0, 1, 0,
                                               0, 0, 1}, 3, 3);

    matrix m2 = createMatrixFromArray((int[]) {1, 2, 3,
                                               4, 5, 6,
                                               7, 8, 9}, 3, 3);

    fwrite(&n, sizeof(int), 1, file);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            fwrite(&m1.values[i][j], sizeof(int), 1, file);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            fwrite(&m2.values[i][j], sizeof(int), 1, file);

    fclose(file);

    transposeNonSymmetricMatrix(filename);

    file = fopen(filename, "rb");

    int res_n;
    matrix check1 = createMatrixFromArray((int[]) {1, 0, 0,
                                                   0, 1, 0,
                                                   0, 0, 1}, 3, 3);
    matrix check2 = createMatrixFromArray((int[]) {1, 4, 7,
                                                   2, 5, 8,
                                                   3, 6, 9}, 3, 3);

    fread(&res_n, sizeof(int), 1, file);

    matrix res_m1 = getMemMatrix(res_n, res_n);
    matrix res_m2 = getMemMatrix(res_n, res_n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            fread(&res_m1.values[i][j], sizeof(int), 1, file);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            fread(&res_m2.values[i][j], sizeof(int), 1, file);

    fclose(file);

    assert(res_n == n);
    assert(areTwoMatricesEqual(&res_m1, &check1));
    assert(areTwoMatricesEqual(&res_m2, &check2));

    freeMemMatrix(&m1);
    freeMemMatrix(&m2);
    freeMemMatrix(&res_m1);
    freeMemMatrix(&res_m2);
    freeMemMatrix(&check1);
    freeMemMatrix(&check2);
}

void test_transposeNonSymmetricMatrix() {
    test_transposeNonSymmetricMatrix_1_empty_matrix();
    test_transposeNonSymmetricMatrix_2_one_matrices();
    test_transposeNonSymmetricMatrix_3_symmetric_matrix();
    test_transposeNonSymmetricMatrix_4_non_symmetric_matrix();
    test_transposeNonSymmetricMatrix_5_mixed_matrix();
}

#endif //UNTITLED9_TRANSPOSE_NON_SYMMETRIC_MATRIX_H
