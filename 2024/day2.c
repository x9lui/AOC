#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define HEURISTIC_SIZE 1000
#define NUMBER_CHARACTERS_HEURISTIC_SIZE 100

typedef enum{increasing, decreasing} trend;

int main(){
    char line[HEURISTIC_SIZE];
    char *number_str;
    int last_number, current_number; //int to avoid underflow
    unsigned solution1 = 0;
    trend trend;

    while(fgets(line, HEURISTIC_SIZE, stdin) != NULL){
        number_str = strtok(line," ");
        last_number = atoi(number_str);

        number_str = strtok(NULL," ");
        current_number = atoi(number_str);

        if(last_number < current_number && current_number <= last_number + 3){
            trend = increasing;
        }else if(last_number - 3 <= current_number && current_number < last_number){
            trend = decreasing;
        }else{
            goto unsafe;
        }

        last_number = current_number;

        if(trend == increasing){
            while((number_str = strtok(NULL," ")) != NULL){
                current_number = atoi(number_str);
                if(!(last_number < current_number && current_number <= last_number + 3)) goto unsafe;
                last_number = current_number;
            }
        }else{
            while((number_str = strtok(NULL," ")) != NULL){
                current_number = atoi(number_str);
                if(!(last_number - 3 <= current_number && current_number < last_number)) goto unsafe;
                last_number = current_number;
            }
        }

        solution1++;

        unsafe:
    }

    printf("part 1: %d\n", solution1);
}