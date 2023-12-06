#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include "../gplib/char.h"

void part_one(FILE *f);
void part_two(FILE *f);

int main(int argc, char *argv[]){
    part_one(fopen(argv[1],"r"));
    part_two(fopen(argv[1],"r"));
    return 0;
}

void part_one(FILE *f){
    char m[140][140];
    unsigned line = 0;
    while(fscanf(f,"%s\n",m[line]) != EOF) line++;
    fclose(f);

    bool valid = false;
    unsigned number = 0;
    unsigned sum = 0;
    for(unsigned i = 0; i<140; i++){
        for(unsigned j = 0; j<140; j++){
            while(isdigit(m[i][j]) && j != 140){
                number = number * 10 + char_to_short_unsigned(m[i][j]);
                for(int k = -1; k<2; k++){
                    for(int l = -1; l<2; l++){
                        if(i+k >= 0 && i+k<140 && j+l >= 0 && j+l < 140){
                            if(!isdigit(m[i+k][j+l]) && m[i+k][j+l] != '.'){
                                valid = true;
                            }
                        }
                    }
                }
                j++;
            }
            if(valid){
                sum += number;
            }
            valid = false;
            number = 0;
        }
    }
    printf("%d",sum);
}

void part_two(FILE *f){

}