#include "libs/algorithms/tasks/transpose_matrix.h"
#include "libs/algorithms/tasks/convert_float_numbers.h"
#include "libs/algorithms/tasks/values_of_expressions.h"
#include "libs/algorithms/tasks/filter_words.h"
#include "libs/algorithms/tasks/longest_word_in_string.h"

void test() {
    test_matrix_transpose();
    test_convertFloatNumbers();
    test_valuesOfExpressions(); // выводит "unlnown operator" (3 тест)
    test_filterWords();
    test_longestWordInString();
}

int main() {
    test();

    return 0;
}