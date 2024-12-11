#include "numbers.h"

unsigned long_number_of_digits(long num, unsigned base){
    unsigned digits = 0;
    while(num){
        num /= base;
        digits++;
    }

    return digits;
}