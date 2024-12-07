#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "../gplib/array.h"

#define HEURISTIC_LINE_MAX_SIZE 1000
#define HEURISTIC_MAX_N_LINES 1000

typedef enum{up, right, down, left}direction;

//For part 2
typedef struct{
    unsigned x;
    unsigned y;
    direction direction;
}point_mark;

direction rotate(direction direction){
    switch(direction){
        case up:
    return right;

        case right:
    return down;

        case down:
    return left;

        case left:
    return up;
    }
}

void new_position(int x, int y, int *new_x, 
 int *new_y, direction direction){
    switch(direction){
        case up: 
            *new_x = x - 1;     
            *new_y = y;
    return;
        case right:
            *new_x = x;
            *new_y = y + 1;
    return;
        case down:
            *new_x = x + 1;
            *new_y = y;
    return;
        case left:
            *new_x = x;
            *new_y = y - 1;
    return;
    }
}

bool is_marked(unsigned x, unsigned y, direction direction,
 point_mark *marks, unsigned n_marks){
    for(unsigned i = 0; i < n_marks; i++){
        if(marks[i].x == x && marks[i].y == y && marks[i].direction == direction){
            return true;
        }
    }
    return false;
}

bool is_loop(int x, int y, 
 char grid[HEURISTIC_MAX_N_LINES][HEURISTIC_LINE_MAX_SIZE],
 unsigned rows, unsigned columns, direction direction){
    int new_x, new_y;
    //static to avoid segmentation fault in the stack
    static point_mark marks[HEURISTIC_LINE_MAX_SIZE * HEURISTIC_LINE_MAX_SIZE];
    unsigned n_marks = 0;
    point_mark new_mark;

    new_position(x, y, &new_x, &new_y, direction);
    while(index_in_range_2darray(new_x, new_y, rows, columns)){

        if(grid[new_x][new_y] == '#'){
            /*Only checking marks and marking next to obstacles ('#'s),
            for better efficiency. */

            //Check mark
            if(is_marked(x, y, direction, marks, n_marks)){
                return true;
            } 

            //Create mark
            new_mark.x = x;
            new_mark.y = y;
            new_mark.direction = direction;
            marks[n_marks] = new_mark;
            n_marks++;

            direction = rotate(direction);
        }else{
            x = new_x;
            y = new_y;
        }
        new_position(x, y, &new_x, &new_y, direction);
    }    
    return false;
}

int main(){
    char initial_grid[HEURISTIC_MAX_N_LINES][HEURISTIC_LINE_MAX_SIZE];
    char grid[HEURISTIC_MAX_N_LINES][HEURISTIC_LINE_MAX_SIZE];
    unsigned rows = 0;
    unsigned columns = 0;

    int initial_x, initial_y;
    direction initial_direction;

    int x, y, new_x, new_y;
    direction direction;

    unsigned solution1 = 0;
    unsigned solution2 = 0;

    
    //Load grid
    while(fgets(initial_grid[rows], HEURISTIC_LINE_MAX_SIZE, stdin) != NULL) rows++;
    while(initial_grid[0][columns] != '\n') columns++;

    memcpy(grid, initial_grid, sizeof(initial_grid));

    //Find the guard
    for(unsigned i = 0; i < rows; i++){
        for(unsigned j = 0; j < columns; j++){

            if(grid[i][j] == '^' || grid[i][j] == '>' ||
             grid[i][j] == 'v' || grid[i][j] == '<'){

                switch(grid[i][j]){
                    case '^':
                        initial_direction = up; 
                break;
                    case '>':
                        initial_direction = right;
                break;
                    case 'v':
                        initial_direction = down;
                break;
                    case '<':
                        initial_direction = left;
                break;
                }
                grid[i][j] = 'X';
                solution1++;
                initial_x = i;
                initial_y = j;

                goto found;
            }
        }
    }

    found:
    
    //Part 1
    x = initial_x;
    y = initial_y;
    direction = initial_direction;
    new_position(x, y, &new_x, &new_y, direction);
    while(index_in_range_2darray(new_x, new_y, rows, columns)){
        if(grid[new_x][new_y] == '#'){
            direction = rotate(direction);
        }else{
            x = new_x;
            y = new_y;
            if(grid[x][y] != 'X'){
                grid[x][y] = 'X';
                solution1++;
            }
        }
        new_position(x, y, &new_x, &new_y, direction);
    }   

    //Part 2
    memcpy(grid, initial_grid, sizeof(initial_grid));
    for(unsigned i = 0; i < rows; i++){
        for(unsigned j = 0; j < columns; j++){

            if(initial_grid[i][j] != '.') continue;

            grid[i][j] = '#';

            if(is_loop(initial_x, initial_y, grid,
             rows, columns, initial_direction)) solution2++; 

            grid[i][j] = '.';
        }
    }

    printf("part 1: %d\npart 2: %d\n", solution1, solution2);
}