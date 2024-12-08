#include "array.h"

#include <stdlib.h>
#include <string.h>

unsigned str_to_int_array(char *s, int *arr, char *sep){
    unsigned size = 0;
    char *number_str;

    number_str = strtok(s,sep);
    while(number_str != NULL){
        arr[size] = atoi(number_str);
        number_str = strtok(NULL, sep);
        size++;
    }

    return size;
}

unsigned str_to_unsigned_array(char *s, unsigned *arr, char *sep){
    unsigned size = 0;
    char *number_str;

    number_str = strtok(s,sep);
    while(number_str != NULL){
        arr[size] = (unsigned)atoi(number_str);
        number_str = strtok(NULL, sep);
        size++;
    }

    return size;
}

bool index_in_range_2darray(int x, int y, unsigned rows, unsigned columns){
    return 0 <= x && x < rows && 0 <= y && y < columns;
}