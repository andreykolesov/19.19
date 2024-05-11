#ifndef UNTITLED9_GET_BEST_TEAM_H
#define UNTITLED9_GET_BEST_TEAM_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "../../data_structures/string/string_.h"

#define MAX_AMOUNT_SPORTSMAN 20

typedef struct sportsman {
    char name[MAX_STRING_SIZE];
    double best_result;
} sportsman;

void sortSportsman(sportsman *sm, const int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (sm[j].best_result < sm[j + 1].best_result) {
                sportsman temp = sm[j];
                sm[j] = sm[j + 1];
                sm[j + 1] = temp;
            }
}

void getBestTeam(const char *filename, const int n){
    FILE *file = fopen(filename, "rb");

    if (file == NULL) {
        printf("file reading error\n");
        exit(1);
    }

    sportsman *team = (sportsman *) malloc(MAX_AMOUNT_SPORTSMAN * sizeof(sportsman));

    sportsman *rec_ptr = team;
    int amount_sportsman = 0;

    while (fread(rec_ptr, sizeof(sportsman), 1, file) == 1){
        rec_ptr++;
        amount_sportsman++;
    }

    fclose(file);

    file = fopen(filename, "wb");

    if (file == NULL) {
        printf("file reading error\n");
        exit(1);
    }

    sortSportsman(team, amount_sportsman);

    int amount_in_team = amount_sportsman >= n? n : amount_sportsman;

    for (int i = 0; i < amount_in_team; i++)
        fwrite(team + i, sizeof(sportsman), 1, file);

    free(team);
    fclose(file);
}

void test_getBestTeam_1_empty_file() {
    const char filename[] = "C:\\Users\\Andrey\\Desktop\\19.19\\task_9_test_1.txt";

    FILE* file = fopen(filename, "wb");
    fclose(file);

    getBestTeam(filename, 0);

    file = fopen(filename, "rb");

    char data[100] = "";
    fread(data, sizeof(data), 1, file);

    fclose(file);

    assert(strcmp_(data, "") == 0);
}


void test_getBestTeam_2_n_more_quantity() {
    const char filename[] = "C:\\Users\\Andrey\\Desktop\\19.19\\task_9_test_2.txt";

    FILE* file = fopen(filename, "wb");

    sportsman s1 = {.best_result = 10.3, .name="first"};
    sportsman s2 = {.best_result = 5.2,  .name="second"};

    fwrite(&s1, sizeof(sportsman), 1, file);
    fwrite(&s2, sizeof(sportsman), 1, file);

    fclose(file);

    getBestTeam(filename, 3);

    file = fopen(filename, "rb");

    sportsman res_s1, res_s2;
    fread(&res_s1, sizeof(sportsman), 1, file);
    fread(&res_s2, sizeof(sportsman), 1, file);

    fclose(file);

    assert(strcmp_(s1.name, res_s1.name) == 0 && fabs(s1.best_result - res_s1.best_result) <= 0.001);
    assert(strcmp_(s2.name, res_s2.name) == 0 && fabs(s2.best_result - res_s2.best_result) <= 0.001);
}


void test_getBestTeam_3_n_less_quantity() {
    const char filename[] = "C:\\Users\\Andrey\\Desktop\\19.19\\task_9_test_3.txt";

    FILE* file = fopen(filename, "wb");

    sportsman s1 = {.best_result = 10.3, .name="first"};
    sportsman s2 = {.best_result = 5.2,  .name="second"};

    fwrite(&s1, sizeof(sportsman), 1, file);
    fwrite(&s2, sizeof(sportsman), 1, file);

    fclose(file);

    getBestTeam(filename, 1);

    file = fopen(filename, "rb");

    sportsman res_s1;
    fread(&res_s1, sizeof(sportsman), 1, file);

    fclose(file);

    assert(strcmp_(s1.name, res_s1.name) == 0 && fabs(s1.best_result - res_s1.best_result) <= 0.001);
}


void test_getBestTeam() {
    test_getBestTeam_1_empty_file();
    test_getBestTeam_2_n_more_quantity();
    test_getBestTeam_3_n_less_quantity();
}

#endif //UNTITLED9_GET_BEST_TEAM_H
