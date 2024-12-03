#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../gplib/array.h"

#define LINE_HEURISTIC_MAX_SIZE 1000
#define LEVEL_HEURISTIC_MAX_SIZE 100

typedef enum{increasing, decreasing} trend;

bool is_safe(int *level, int size){
    trend trend;
    int i;

    if(level[0] < level[1] && level[1] <= level[0] + 3){
        trend = increasing;
    }else if(level[0] - 3 <= level[1] && level[1] < level[0]){
        trend = decreasing;
    }else{
        return false;
    }

    i = 2;
    if(trend == increasing){
        while(i < size){
            if(!(level[i-1] < level[i] && level[i] <= level[i-1] + 3)) return false;
            i++;
        }
    }else{
        while(i < size){
            if(!(level[i-1] - 3 <= level[i] && level[i] < level[i-1])) return false;
            i++;
        }
    }

    return true;
}

int main(){
    char line[LINE_HEURISTIC_MAX_SIZE];
    char *number_str;
    int level[LEVEL_HEURISTIC_MAX_SIZE];
    int sublevel[LEVEL_HEURISTIC_MAX_SIZE];
    int size;
    unsigned solution1 = 0;
    unsigned solution2 = 0;

    while(fgets(line, LINE_HEURISTIC_MAX_SIZE, stdin) != NULL){
        size = str_to_int_array(line,level, " ");

        //Part 1
        if(is_safe(level,size)){
            solution1++;
        }

        //Part 2 - Try all level combinations removing 1 number
        for(unsigned i = 0; i < size; i++){
            for(unsigned j = 0; j < i; j++){
                sublevel[j] = level[j];
            }
            for(unsigned j = i; j < size - 1; j++){
                sublevel[j] = level[j+1];
            }
            if(is_safe(sublevel,size - 1)){
                solution2++;
                break;
            }
        }
    }

    printf("part 1: %d\npart 2: %d\n", solution1, solution2);
}