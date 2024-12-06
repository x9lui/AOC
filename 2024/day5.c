#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../gplib/array.h"

#define LINE_HEURISTIC_MAX_SIZE 1000
#define HEURISTIC_MAX_N_LINES 10000
#define HEURISTIC_ARRAY_MAX_SIZE 1000

//index < dest_index
void array_move(unsigned index, unsigned dest_index, unsigned *arr){
    unsigned el = arr[index];
    for(unsigned i = index; i < dest_index; i++){
        arr[i] = arr[i+1];
    }
    arr[dest_index] = el;
}

bool update_is_valid(unsigned *update, unsigned update_size,
 unsigned rules[LINE_HEURISTIC_MAX_SIZE][2], unsigned n_rules){
    unsigned match_index1;
    unsigned match_index2;
    unsigned valid = false;

    //Test each rule in the update
    for(unsigned i = 0; i < n_rules; i++){
        match_index1 = 0;
        match_index2 = 0;

        //finding the first rule number
        while(match_index1 < update_size && update[match_index1] != rules[i][0]) match_index1++;

        //Rule only applicable if the number is found (found only if match_index < update_size)
        if(match_index1 == update_size) continue;
        
        //finding the second rule number
        while(match_index2 < update_size && update[match_index2] != rules[i][1]) match_index2++;

        //Rule only applicable if the number is found (found only if match_index < update_size)
        if(match_index2 == update_size) continue;

        //Are pages in order?
        if(match_index1 > match_index2){
            return false;
        }
    }

    return true;

}

void sort_update(unsigned *update, unsigned update_size,
 unsigned rules[LINE_HEURISTIC_MAX_SIZE][2], unsigned n_rules){
    unsigned match_index1;
    unsigned match_index2;
    unsigned valid = false;
    

    //Sort until the update becomes valid
    while(valid == false){
        valid = true;

        //Test each rule in the update
        for(unsigned i = 0; i < n_rules; i++){
            match_index1 = 0;
            match_index2 = 0;

            //finding the first rule number
            while(match_index1 < update_size && update[match_index1] != rules[i][0]) match_index1++;

            //Rule only applicable if the number is found (found only if match_index < update_size)
            if(match_index1 == update_size) continue;
            
            //finding the second rule number
            while(match_index2 < update_size && update[match_index2] != rules[i][1]) match_index2++;

            //Rule only applicable if the number is found (found only if match_index < update_size)
            if(match_index2 == update_size) continue;

            //Are pages in order?
            if(match_index1 > match_index2){
                array_move(match_index2, match_index1, update);
                valid = false;
            }
        }
    } 
}

int main(){
    char line[LINE_HEURISTIC_MAX_SIZE];
    unsigned rules[HEURISTIC_MAX_N_LINES][2];
    unsigned n_rules = 0;
    unsigned update[HEURISTIC_ARRAY_MAX_SIZE];
    unsigned update_size;
    unsigned match_index1;
    unsigned match_index2;
    bool valid;
    unsigned solution1 = 0;
    unsigned solution2 = 0;

    //Load all rules in our rules array
    while(strcmp(fgets(line, sizeof(line), stdin), "\n") != 0){
        sscanf(line,"%u|%u", &rules[n_rules][0], &rules[n_rules][1]);
        n_rules++;
    }

    //Loop for every update
    while(fgets(line, sizeof(line), stdin) != NULL){
        valid = true;
        update_size = str_to_unsigned_array(line, update, ",");

        if(update_is_valid(update, update_size, rules, n_rules)){
            solution1 += update[update_size/2];
        }else{
            sort_update(update, update_size, rules, n_rules);
            solution2 += update[update_size/2];
        }
    }

    printf("part 1: %u\npart 2: %u\n", solution1, solution2);

}