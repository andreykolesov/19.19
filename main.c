#include "libs/algorithms/tasks/transpose_matrix.h"
#include "libs/algorithms/tasks/convert_float_numbers.h"
#include "libs/algorithms/tasks/values_of_expressions.h"
#include "libs/algorithms/tasks/filter_words.h"
#include "libs/algorithms/tasks/longest_word_in_string.h"
#include "libs/algorithms/tasks/remove_true_polynomial.h"
#include "libs/algorithms/tasks/rearrange_numbers.h"
#include "libs/algorithms/tasks/transpose_non_symmetric_matrix.h"
#include "libs/algorithms/tasks/get_best_team.h"
#include "libs/algorithms/tasks/update_product.h"

void test() {
    test_matrix_transpose();
    test_convertFloatNumbers();
    test_valuesOfExpressions(); // выводит "unlnown operator" (3 тест)
    test_filterWords();
    test_longestWordInString();
    test_removeTruePolynomial();
    test_rearrangeNumbers();
    test_transposeNonSymmetricMatrix();
    test_getBestTeam();
    test_updateProduct();
}

int main() {
    test();

    return 0;
}