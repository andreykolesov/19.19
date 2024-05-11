cmake_minimum_required(VERSION 3.26)
project(untitled9 C)

set(CMAKE_C_STANDARD 11)

add_executable(untitled9 main.c
        libs/data_structures/matrix/matrix.h
        libs/data_structures/matrix/matrix.c
        libs/data_structures/ordered_array_set/ordered_array_set.c
        libs/data_structures/unordered_array_set/unordered_array_set.c
        libs/data_structures/vector/vector.c
        libs/data_structures/vectorVoid/vectorVoid.c
        libs/data_structures/bitset/bitset.c
        libs/data_structures/string/string_.h
        libs/data_structures/string/string_.c
        libs/algorithms/algorithm.c
        libs/algorithms/algorithm.h
        libs/algorithms/tasks/transpose_matrix.h
        libs/algorithms/array/array.c
        libs/algorithms/tasks/convert_float_numbers.h
        libs/algorithms/tasks/values_of_expressions.h
        libs/algorithms/tasks/filter_words.h
        libs/algorithms/tasks/longest_word_in_string.h)
