#include "libs/algorithms/tasks/transpose_matrix.h"
#include "libs/algorithms/tasks/convert_float_numbers.h"
#include "libs/algorithms/tasks/values_of_expressions.h"
#include "libs/algorithms/tasks/filter_words.h"

void test() {
    test_matrix_transpose();
    test_convertFloatNumbers();
    test_valuesOfExpressions(); // выводит "unlnown operator" (3 тест)
    test_filterWords();
}

int main() {
    test();

    return 0;
}