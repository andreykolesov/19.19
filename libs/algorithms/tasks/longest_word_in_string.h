#ifndef UNTITLED9_LONGEST_WORD_IN_STRING_H
#define UNTITLED9_LONGEST_WORD_IN_STRING_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../../data_structures/string/string_.h"

void longestWordInString(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("file reading error\n");
        exit(1);
    }

    char buff[MAX_STRING_SIZE] = "";
    char* rec_ptr = stringBuffer_;

    fgets(buff, sizeof(buff), file);

    size_t length = strlen_(buff);
    length = length == 0 ? 1 : length;

    rec_ptr = copy(buff, buff + length - 1, rec_ptr);
    *rec_ptr++ = ' ';

    size_t amount_word_in_line = 0;
    char* begin_search = stringBuffer_;

    while (getWordWithoutSpace(begin_search, &_bag.words[_bag.size])) {
        begin_search = _bag.words[_bag.size].end + 1;
        amount_word_in_line++;
        _bag.size++;
    }

    while (fgets(buff, sizeof(buff), file)) {
        rec_ptr = copy(buff, buff + strlen_(buff) - 1, rec_ptr);
        *rec_ptr++ = ' ';

        while (getWordWithoutSpace(begin_search, &_bag.words[_bag.size])) {
            begin_search = _bag.words[_bag.size].end + 1;
            _bag.size++;
        }
    }

    fclose(file);

    file = fopen(filename, "w");
    if (file == NULL) {
        printf("file reading error\n");
        exit(1);
    }

    for (size_t i = 0; i < _bag.size; i += amount_word_in_line) {
        WordDescriptor word_max_length = _bag.words[i];
        size_t max_length = word_max_length.end - word_max_length.begin + 1;

        for (size_t j = i + 1; j < i + amount_word_in_line; j++) {
            size_t current_length = _bag.words[j].end - _bag.words[j].begin + 1;

            if (current_length > max_length) {
                word_max_length = _bag.words[j];
                max_length = current_length;
            }
        }

        char* write_ptr = word_max_length.begin;
        while (write_ptr <= word_max_length.end) {
            fprintf(file, "%c", *write_ptr);
            write_ptr++;
        }

        fprintf(file, "\n");
    }

    freeBag(&_bag);
    fclose(file);
}


void test_leave_longest_word_1_empty_file() {
    const char filename[] = "C:\\Users\\Andrey\\Desktop\\19.19\\task_5_test_1.txt";


    FILE* file = fopen(filename, "w");
    fclose(file);

    longestWordInString(filename);

    file = fopen(filename, "r");

    char data[100] = "";
    fprintf(file, "%s", data);

    fclose(file);

    assert(strcmp_(data, "") == 0);
}


void test_leave_longest_word_2_one_element_in_line() {
    const char filename[] = "C:\\Users\\Andrey\\Desktop\\19.19\\task_5_test_2.txt";

    char line1[] = "abcd";
    char line2[] = "efg";
    char line3[] = "hi";

    FILE* file = fopen(filename, "w");

    fprintf(file, "%s \n", line1);
    fprintf(file, "%s \n", line2);
    fprintf(file, "%s \n", line3);

    fclose(file);

    longestWordInString(filename);

    file = fopen(filename, "r");

    char res_line1[10] = "";
    fscanf(file, "%s\n", res_line1);

    char res_line2[10] = "";
    fscanf(file, "%s\n", res_line2);

    char res_line3[10] = "";
    fscanf(file, "%s\n", res_line3);

    fclose(file);

    assert(strcmp_(line1, res_line1) == 0);
    assert(strcmp_(line2, res_line2) == 0);
    assert(strcmp_(line3, res_line3) == 0);
}


void test_leave_longest_word_3_more_element_in_line() {
    const char filename[] = "C:\\Users\\Andrey\\Desktop\\19.19\\task_5_test_3.txt";

    char line1[] = "kkalsdf ssss ";
    char line2[] = "efg qweqw ";
    char line3[] = "hi my to ";

    FILE* file = fopen(filename, "w");

    fputs(line1, file);
    fprintf(file, "\n");
    fputs(line2, file);
    fprintf(file, "\n");
    fputs(line3, file);
    fprintf(file, "\n");

    fclose(file);

    longestWordInString(filename);

    file = fopen(filename, "r");

    char res_line1[10] = "";
    fscanf(file, "%s\n", res_line1);

    char res_line2[10] = "";
    fscanf(file, "%s\n", res_line2);

    char res_line3[10] = "";
    fscanf(file, "%s\n", res_line3);

    fclose(file);

    char check1[] = "kkalsdf";
    char check2[] = "qweqw";
    char check3[] = "hi";

    assert(strcmp_(check1, res_line1) == 0);
    assert(strcmp_(check2, res_line2) == 0);
    assert(strcmp_(check3, res_line3) == 0);
}


void test_longestWordInString() {
    test_leave_longest_word_1_empty_file();
    test_leave_longest_word_2_one_element_in_line();
    test_leave_longest_word_3_more_element_in_line();
}

#endif //UNTITLED9_LONGEST_WORD_IN_STRING_H
