#ifndef UNTITLED1_STRING__H
#define UNTITLED1_STRING__H

#include <stdlib.h>
#include <ctype.h>
#include <memory.h>

// возвращает количество символов в строке (не считая ноль-символ)
size_t strlen_(const char *begin);

// возвращает указатель на первый элемент с кодом ch, расположенным на ленте памяти между адресами begin и end не
// включая end. Если символ не найден, возращается значение end.
char *find(char *begin, char *end, int ch);

// возвращает указатель на первый символ, отличный от пробельных, расположенный на ленте памяти,
// начиная с begin и заканчивая ноль-символом. Если символ не найден, возвращается адрес первого ноль-символа.
char *findNonSpace(char *begin);

// возвращает указатель на первый пробельный символ, расположенный на ленте памяти начиная с адреса begin
// или на первый ноль-символ.
char *findSpace(char *begin);

// возвращает указатель на первый справа символ, отличный от пробельных, расположенный на ленте памяти, начиная с
// rbegin (последний символ строки, за которым следует ноль-символ) и заканчивая rend
// (адрес символа перед началом строки). Если символ не найден, возвращается адрес rend.
char *findNonSpaceReverse(char *r_begin, const char *r_end);

// возвращает указатель на первый пробельный символ справа, расположенный на ленте памяти, начиная с rbegin и заканчивая
// rend. Если символ не найден, возвращается адрес rend.
char *findSpaceReverse(char *r_begin, const char *r_end);

// Функция возвращает отрицательное значение, если lhs располагается до rhs в лексикографическом
// порядке (как в словаре), значение 0, если lhs и rhs равны, иначе – положительное значение
int strcmp(const char *lhs, const char *rhs);

// записывает по адресу beginDestination фрагмент памяти, начиная с адреса beginSource до endSource.
// Возвращает указатель на следующий свободный фрагмент памяти в destination.
char *copy(const char *beginSource, const char *endSource, char *beginDestination);

// записывает по адресу beginDestination элементы из фрагмента памяти начиная с beginSource заканчивая endSource,
// удовлетворяющие функции-предикату f. Функция возвращает указатель на
// следующий свободный для записи фрагмент в памяти.
char *copyIf(char *beginSource, const char *endSource, char *beginDestination, int (*f)(int));

// записывает по адресу beginDestination элементы из фрагмента памяти начиная с r_beginSource заканчивая r_endSource,
// удовлетворяющие функции-предикату f. Функция возвращает значение beginDestination по окончанию работы функции
char *copyIfReverse(char *r_beginSource, const char *r_endSource, char *beginDestination, int (*f)(int));

#endif
