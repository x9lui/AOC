#include <stdio.h>
#include <stdbool.h>

#define LINE_HEURISTIC_MAX_SIZE 1000
#define N_LINES_HEURISTIC_MAX_SIZE 1000

typedef struct{
    int x;
    int y;
}direction;

//Aux function to check if an index is valid
bool valid_matrix_index(int x, int y, unsigned rows, unsigned columns){
    return 0 <= x && x < rows && 0 <= y && y < columns;
}

//Call this function when m[x][y] == 'X'
unsigned count_xmas(unsigned x, unsigned y, char m[][LINE_HEURISTIC_MAX_SIZE],
 unsigned rows, unsigned columns){
    unsigned count = 0;
    char xmas[] = "XMAS";
    bool found = true;
    int look_x;
    int look_y;

    direction directions[] = {
        {-1,-1},{0,-1},{1,-1},
        {-1,0},        {1,0},
        {-1,1}, {0,1}, {1,1} 
    };
    
    //directions loop
    for(unsigned i = 0; i < 8; i++){
        found = true;

        //xmas characters loop
        for(unsigned j = 0; j < 4; j++){
            look_x = (int)x + directions[i].x * j;
            look_y = (int)y + directions[i].y * j;
            if(!(valid_matrix_index(look_x, look_y, rows, columns) &&
             m[look_x][look_y] == xmas[j])) found = false;
        }
        if(found) count++;
    }

    return count;
}


bool m_or_s(char c){
    return c == 'M' || c == 'S';
}

char m_s_opposite(char c){
    if(c == 'M') return 'S';
    return 'M';
}

//Call this function when m[x][y] == 'A'
bool check_cross_mass(unsigned x, unsigned y, char m[][LINE_HEURISTIC_MAX_SIZE],
 unsigned rows, unsigned columns){
    char c1, c2;

    if(x == 0 || x == rows -1 || y == 0 || y == columns - 1) return false;

    c1 = m[x - 1][y - 1];    
    c2 = m[x + 1][y - 1];
    if(m_or_s(c1) && m_s_opposite(c1) == m[x+1][y+1] && 
     m_or_s(c2) && m_s_opposite(c2) == m[x-1][y+1]) return true;

    return false;
}

int main(){
    char line[LINE_HEURISTIC_MAX_SIZE];
    unsigned columns;
    unsigned rows = 0;
    char matrix[LINE_HEURISTIC_MAX_SIZE][N_LINES_HEURISTIC_MAX_SIZE];
    unsigned row_index = 0;
    unsigned solution1 = 0;
    unsigned solution2 = 0;

    //fill matrix
    while(fgets(line, sizeof(line),stdin) != NULL){
        columns = 0;
        for(unsigned i = 0; line[i] != '\n' ; i++){
            matrix[row_index][i] = line[i];
            columns++;
        }
        row_index++;
        rows++;
    }

    for(unsigned i = 0; i < rows; i++){
        for(unsigned j = 0; j < columns; j++){

            //Part 1
            if(matrix[i][j] == 'X'){
                solution1 += count_xmas(i,j,matrix,rows,columns);
            }

            //Part2
            if(matrix[i][j] == 'A' && check_cross_mass(i,j,matrix,rows,columns)){
                solution2++;
            }
        }
    }

    printf("part 1: %d\npart 2: %d\n", solution1, solution2);


}