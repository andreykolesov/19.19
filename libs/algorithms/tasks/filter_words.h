#ifndef UNTITLED9_FILTER_WORDS_H
#define UNTITLED9_FILTER_WORDS_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../../data_structures/string/string_.h"

int compare_letters(const void *s1, const void *s2) {
    return *(const unsigned char *) s1 - *(const unsigned char *) s2;
}

void sort_word_letters(WordDescriptor *word) {
    qsort(word->begin, word->end - word->begin + 1, sizeof(char), compare_letters);
}

bool lettersBelongString(WordDescriptor sub_word, WordDescriptor word) {
    bool include[26] = {0};

    char *begin = word.begin;
    char *end = word.end + 1;

    while (begin != end) {
        if (isalpha(*begin))
            include[*begin - 'a'] = true;

        begin++;
    }

    while (sub_word.begin <= sub_word.end) {
        if (!include[*sub_word.begin - 'a'])
            return false;

        sub_word.begin++;
    }

    return true;
}

void generateString(const char *filename, char *source_string) {
    FILE *file = fopen(filename, "w");

    if (file == NULL) {
        printf("file reading error\n");
        exit(1);
    }

    size_t string_length = strlen_(source_string);

    for (size_t i = 0; i < string_length; i++)
        fprintf(file, "%c", source_string[i]);

    fclose(file);
}

void filterWords(const char *filename, char *source_word) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("file reading error\n");
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    size_t len = ftell(file);
    fseek(file, 0, SEEK_SET);

    if (len == 0)
        return;

    fread(stringBuffer_, sizeof(char), len, file);
    stringBuffer_[len] = '\0';

    fclose(file);

    WordDescriptor word;
    getWordWithoutSpace(source_word, &word);
    sort_word_letters(&word);

    BagOfWords words = {.size = 0};
    char *begin_search = stringBuffer_;
    while (getWordWithoutSpace(begin_search, &words.words[words.size])) {
        begin_search = words.words[words.size].end + 1;
        words.size++;
    }

    file = fopen(filename, "w");

    if (file == NULL) {
        printf("reading error\n");
        exit(1);
    }

    for (size_t i = 0; i < words.size; i++) {
        if (lettersBelongString(word, words.words[i])) {
            while (words.words[i].begin <= words.words[i].end) {
                fprintf(file, "%c", *words.words[i].begin);
                words.words[i].begin++;
            }

            fprintf(file, " ");
        }
    }

    fprintf(file, "%c", '\0');

    freeString(stringBuffer_);
    freeBag(&words);

    fclose(file);
}

void test_filterWords_1_empty_file() {
    const char filename[] = "C:\\Users\\Andrey\\Desktop\\19.19\\task_4_test_1.txt";

    generateString(filename, "");
    char source_word[] = "source";
    filterWords(filename, source_word);

    FILE *file = fopen(filename, "r");
    char data[10] = "";
    fscanf(file, "%s", data);
    fclose(file);

    assert(strcmp_(data, "") == 0);
}


void test_filterWords_2_sequence_not_in_line() {
    const char filename[] = "C:\\Users\\Andrey\\Desktop\\19.19\\task_4_test_2.txt";

    generateString(filename, "abcd ghtsdf");
    char source_word[] = "seq";
    filterWords(filename, source_word);

    FILE *file = fopen(filename, "r");
    char data[10] = "";
    fscanf(file, "%s", data);
    fclose(file);

    assert(strcmp_(data, "") == 0);
}


void test_filterWords_3_sequence_in_line() {
    const char filename[] = "C:\\Users\\Andrey\\Desktop\\19.19\\task_4_test_3.txt";

    generateString(filename, "abcd word abc");
    char source_word[] = "abc";
    filterWords(filename, source_word);

    FILE *file = fopen(filename, "r");
    char data[40] = "";
    fgets(data, sizeof(data), file);
    fclose(file);

    assert(strcmp_(data, "abcd abc ") == 0);
}


void test_filterWords() {
    test_filterWords_1_empty_file();
    test_filterWords_2_sequence_not_in_line();
    test_filterWords_3_sequence_in_line();
}

#endif //UNTITLED9_FILTER_WORDS_H
