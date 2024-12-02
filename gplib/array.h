#ifndef GPLIB_ARRAY
#define GPLIB_ARRAY

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
int str_to_int_array(char *s, int *arr, char *sep);

#endif