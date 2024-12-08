#ifndef GPLIB_ARRAY
#define GPLIB_ARRAY

#include <stdbool.h>

/*
*   Converts an string represented array to an int array,
*   the numbers in the string are separated by a SEP
*   character
*   
*   @param s the string represented array
*   @param sep the separators between the numbers
*
*   @return The number of elements in the array
*/
unsigned str_to_int_array(char *s, int *arr, char *sep);

/*
*   Converts an string represented array to an unsigned array,
*   the numbers in the string are separated by a SEP
*   character
*   
*   @param s the string represented array
*   @param sep the separators between the numbers
*
*   @return The number of elements in the array
*/
unsigned str_to_unsigned_array(char *s, unsigned *arr, char *sep);


bool index_in_range_2darray(int x, int y, unsigned rows, unsigned columns);

#endif
