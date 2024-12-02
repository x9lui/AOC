#include "array.h"

#include <stdlib.h>
#include <string.h>

int str_to_int_array(char *s, int *arr, char *sep){
    int size = 0;
    char *number_str;

    number_str = strtok(s," ");
    while(number_str != NULL){
        arr[size] = atoi(number_str);
        number_str = strtok(NULL, sep);
        size++;
    }

    return size;
}