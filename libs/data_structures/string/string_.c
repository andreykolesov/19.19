#include "string_.h"

size_t strlen_(const char *begin) {
    char *end = begin;

    while (*end != '\0')
        end++;

    return end - begin;
}

char *find(char *begin, char *end, int ch) {
    while (begin != end && *begin != ch)
        begin++;

    return begin;
}

char *findNonSpace(char *begin) {
    while (*begin != '\0' && isspace((unsigned char) *begin))
        begin++;

    return begin;
}

char *findSpace(char *begin) {
    while (*begin != '\0' && !isspace((unsigned char) *begin))
        begin++;

    return begin;
}

char *findNonSpaceReverse(char *r_begin, const char *r_end) {
    while (r_begin != r_end && isspace((unsigned char) *r_begin))
        r_begin--;

    return r_begin;
}

char *findSpaceReverse(char *r_begin, const char *r_end) {
    while (r_begin != r_end && !isspace((unsigned char) *r_begin))
        r_begin--;

    return r_begin;
}

int strcmp(const char *lhs, const char *rhs) {
    while (*lhs != '\0' && *rhs != '\0' && *lhs == *rhs) {
        lhs++;
        rhs++;
    }

    return *(const unsigned char *) lhs - *(const unsigned char *) rhs;
}

char *copy(const char *begin_source, const char *end_source, char *begin_destination) {
    while (begin_source != end_source) {
        *begin_destination = *begin_source;
        ++begin_source;
        ++begin_destination;
    }
    return begin_destination;
}

char *copyIf(char *beginSource, const char *endSource, char *beginDestination, int (*f)(int)) {
    char *start = beginSource;

    while (start != endSource) {
        if (f(*start)) {
            *beginDestination = *start;
            beginDestination++;
        }

        start++;
    }

    return beginDestination;
}

char *copyIfReverse(char *r_beginSource, const char *r_endSource, char *beginDestination, int (*f)(int)) {
    char *start = r_beginSource;

    while (start != r_endSource) {
        if (f(*start)) {
            *beginDestination = *start;
            beginDestination++;
        }

        start--;
    }

    return beginDestination;
}