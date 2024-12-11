#include <stdio.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include "../gplib/array.h"
#include "../gplib/numbers.h"


#define LINE_HEURISTIC_MAX_SIZE 1000
#define EQUATION_HEURISTIC_MAX_NUMBERS 100

typedef enum{add, mul}operators;

typedef enum{add2, mul2, concat2}operators2;

//Using binary counting to perform the operator variations
void next_ops_variation(operators *ops, unsigned size){

    for(unsigned i = 0; i < size; i++){
        if(ops[i] == add){
            ops[i] = mul;
            return;
        }else{
            ops[i] = add;
        }
    }
}

//Using ternary counting to perform the operator variations
void next_ops_variation2(operators2 *ops, unsigned size){

    for(unsigned i = 0; i < size; i++){
        if(ops[i] == concat2){
            ops[i] = add2;
        }else if(ops[i] == mul2){
            ops[i] = concat2;
            return;
        }else{
            ops[i] = mul2;
            return;
        }
    }
}

int main(){
    char line[LINE_HEURISTIC_MAX_SIZE];
    char *str_number_array_begin;

    long nums_array[EQUATION_HEURISTIC_MAX_NUMBERS];
    unsigned nums_array_size;
    long equation_result;
    long calculated_result;

    operators ops[EQUATION_HEURISTIC_MAX_NUMBERS - 1];
    unsigned ops_size;

    operators2 ops2[EQUATION_HEURISTIC_MAX_NUMBERS - 1];
    unsigned ops_size2;

    long solution1 = 0;
    long solution2 = 0;

    char sep[] = " ";


    while(fgets(line, sizeof(line), stdin) != NULL){
        sscanf(line,"%lu", &equation_result);

        //Load equation numbers into the array
        str_number_array_begin = line;
        while(str_number_array_begin[0] != ' ') str_number_array_begin += sizeof(char);
        nums_array_size = str_to_long_array(str_number_array_begin, nums_array, sep);

        //Part 1
        ops_size = nums_array_size - 1;
        for(unsigned i = 0; i < ops_size; i++){
            ops[i] = add;
        }

        //Iterate over all the operator variations
        for(unsigned i = 0; i < pow(2, ops_size); i++){
            calculated_result = nums_array[0];
            for(unsigned j = 0; j < ops_size; j++){
                if(ops[j] == add){
                    calculated_result += nums_array[j + 1];
                }else{
                    calculated_result *= nums_array[j + 1];
                }
            }

            if(calculated_result == equation_result){
                solution1 += equation_result;
                break;
            }

            next_ops_variation(ops, ops_size);
        }


        //Part 2
        ops_size2 = nums_array_size - 1;
        for(unsigned i = 0; i < ops_size2; i++){
            ops2[i] = add2;
        }

        //Iterate over all the operator variations
        for(unsigned i = 0; i < pow(3, ops_size2); i++){
            calculated_result = nums_array[0];
            for(unsigned j = 0; j < ops_size2; j++){
                if(ops2[j] == concat2){
                    calculated_result = calculated_result * 
                     pow(10, long_number_of_digits(nums_array[j + 1], 10)) + nums_array[j + 1]; 
                }else if(ops2[j] == add2){
                    calculated_result += nums_array[j + 1];
                }else{
                    calculated_result *= nums_array[j + 1];
                }
            }

            if(calculated_result == equation_result){
                solution2 += equation_result;
                break;
            }

            next_ops_variation2(ops2, ops_size2);
        }

    }

    printf("part 1: %lu\npart 2: %lu\n", solution1, solution2);
}