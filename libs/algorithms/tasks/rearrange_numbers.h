#ifndef UNTITLED9_REARRANGE_NUMBERS_H
#define UNTITLED9_REARRANGE_NUMBERS_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "../../data_structures/vector/vector.h"
#include "../../data_structures/string/string_.h"

void rearrangeNumbers(const char *filename){
    vector pos_numbers = createVector(2);
    vector neg_numbers = createVector(2);

    FILE *file = fopen(filename, "rb");

    if (file == NULL) {
        printf("file reading error\n");
        exit(1);
    }

    int current_numbers;

    while (fread(&current_numbers, sizeof(int), 1, file) == 1){
        if (current_numbers >= 0)
            pushBack(&pos_numbers, current_numbers);
        else
            pushBack(&neg_numbers, current_numbers);
    }

    fclose(file);

    file = fopen(filename, "wb");

    if (file == NULL) {
        printf("file reading error\n");
        exit(1);
    }

    for (int i = 0; i < pos_numbers.size; i++)
        fwrite(pos_numbers.data + i, sizeof(int), 1, file);

    for (int i = 0; i < neg_numbers.size; i++)
        fwrite(neg_numbers.data + i, sizeof(int), 1, file);

    deleteVector(&pos_numbers);
    deleteVector(&neg_numbers);
    fclose(file);
}

void test_rearrangeNumbers_1_empty_file() {
    const char filename[] = "C:\\Users\\Andrey\\Desktop\\19.19\\task_7_test_1.txt";

    FILE* file = fopen(filename, "wb");
    fclose(file);

    rearrangeNumbers(filename);

    file = fopen(filename, "rb");

    char data[10] = "";
    fread(data, sizeof(data), 1, file);

    fclose(file);

    assert(strcmp_(data, "") == 0);
}


void test_rearrangeNumbers_2_only_negative_numbers() {
    const char filename[] = "C:\\Users\\Andrey\\Desktop\\19.19\\task_7_test_2.txt";

    int x1 = -1;
    int x2 = -2;
    int x3 = -3;

    FILE* file = fopen(filename, "wb");

    fwrite(&x1, sizeof(int), 1, file);
    fwrite(&x2, sizeof(int), 1, file);
    fwrite(&x3, sizeof(int), 1, file);

    fclose(file);

    rearrangeNumbers(filename);

    file = fopen(filename, "rb");

    int res_x1, res_x2, res_x3;
    fread(&res_x1, sizeof(int), 1, file);
    fread(&res_x2, sizeof(int), 1, file);
    fread(&res_x3, sizeof(int), 1, file);

    fclose(file);

    assert(x1 == res_x1);
    assert(x2 == res_x2);
    assert(x3 == res_x3);
}


void test_rearrangeNumbers_3_only_positive_numbers() {
    const char filename[] = "C:\\Users\\Andrey\\Desktop\\19.19\\task_7_test_3.txt";

    int x1 = 1;
    int x2 = 2;
    int x3 = 3;

    FILE* file = fopen(filename, "wb");

    fwrite(&x1, sizeof(int), 1, file);
    fwrite(&x2, sizeof(int), 1, file);
    fwrite(&x3, sizeof(int), 1, file);

    fclose(file);

    rearrangeNumbers(filename);

    file = fopen(filename, "rb");

    int res_x1, res_x2, res_x3;
    fread(&res_x1, sizeof(int), 1, file);
    fread(&res_x2, sizeof(int), 1, file);
    fread(&res_x3, sizeof(int), 1, file);

    fclose(file);

    assert(x1 == res_x1);
    assert(x2 == res_x2);
    assert(x3 == res_x3);
}


void test_rearrangeNumbers_4_mixed_numbers() {
    const char filename[] = "C:\\Users\\Andrey\\Desktop\\19.19\\task_7_test_4.txt";

    int x1 = -1;
    int x2 = 2;
    int x3 = -3;
    int x4 = 3;

    FILE* file = fopen(filename, "wb");

    fwrite(&x1, sizeof(int), 1, file);
    fwrite(&x2, sizeof(int), 1, file);
    fwrite(&x3, sizeof(int), 1, file);
    fwrite(&x4, sizeof(int), 1, file);

    fclose(file);

    rearrangeNumbers(filename);

    file = fopen(filename, "rb");

    int res_x1, res_x2, res_x3, res_x4;
    fread(&res_x1, sizeof(int), 1, file);
    fread(&res_x2, sizeof(int), 1, file);
    fread(&res_x3, sizeof(int), 1, file);
    fread(&res_x4, sizeof(int), 1, file);

    fclose(file);

    assert(res_x1 == x2);
    assert(res_x2 == x4);
    assert(res_x3 == x1);
    assert(res_x4 == x3);
}


void test_rearrangeNumbers() {
    test_rearrangeNumbers_1_empty_file();
    test_rearrangeNumbers_2_only_negative_numbers();
    test_rearrangeNumbers_3_only_positive_numbers();
    test_rearrangeNumbers_4_mixed_numbers();
}

#endif //UNTITLED9_REARRANGE_NUMBERS_H
