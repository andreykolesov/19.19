#include "libs/algorithms/tasks/transpose_matrix.h"
#include "libs/algorithms/tasks/convert_float_numbers.h"
#include "libs/algorithms/tasks/values_of_expressions.h"

void test() {
    test_matrix_transpose();
    test_convertFloatNumbers();
    test_valuesOfExpressions(); // выводит "unlnown operator" (3 тест)
}

int main() {
    test();

    return 0;
}