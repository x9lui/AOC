#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

void part_one(FILE*);
void part_two(FILE*);
char str_digit_start(const char*);

int main(int argc, char *argv[]){
    part_one(fopen(argv[1],"r"));
    part_two(fopen(argv[1],"r"));
    return 0;
}

void part_one(FILE *f){
    unsigned sum = 0;    
    bool found_first = false;
    unsigned short num1 = 0, num2 = 0;
    char c = fgetc(f);
    while(c != EOF){
        if(c != '\n'){
            if(isdigit(c)){
                if(!found_first){
                    num1 = char_to_unsigned(c);
                    found_first = true;
                }
                num2 = char_to_unsigned(c); 
            }
        }else{
            sum += num1*10 + num2;
            num1 = 0;
            num2 = 0;
            found_first = false;
        }
        c = fgetc(f);
    }
    fclose(f);
    sum += num1*10 + num2; //The sum isn't performed in the last iteration

    printf("%u\n",sum);
}

void part_two(FILE *f){
    FILE *parsed_file;
    parsed_file = fopen("day1_aux","w");
    char buffer[100];
    while(fscanf(f,"%s",buffer) != EOF){
        buffer[strlen(buffer)+1] = '\0';
        buffer[strlen(buffer)] = '\n';

        for(unsigned i = 0; i<strlen(buffer)-1; i++){
            if(isdigit(buffer[i])){
                fprintf(parsed_file,"%c",buffer[i]);
            }else{
                char digit = str_digit_start(buffer+i);
                if(digit != 'n'){
                    fprintf(parsed_file,"%c",digit);
                }
            }
        }
        fprintf(parsed_file,"\n");
    }

    fclose(f);
    fclose(parsed_file);
    parsed_file = fopen("day1_aux","r");
    part_one(parsed_file);
    remove("day1_aux");
}


/*
@brief Evalues if there is a digit in string format in the beggining of the string.

@param str The evalued string

@return Returns the number in character form if not returns the character 'n' 
*/
char str_digit_start(const char *str){
    char buffer[6];
    char digit = 'n';

    memcpy(buffer,str,5);
    buffer[5] = '\0';
    
    if(strcmp(buffer,"three") == 0) digit = '3';
    if(strcmp(buffer,"seven") == 0) digit = '7';
    if(strcmp(buffer,"eight") == 0) digit = '8';

    buffer[4] = '\0';

    if(strcmp(buffer,"zero") == 0) digit = '0';
    if(strcmp(buffer,"four") == 0) digit = '4';
    if(strcmp(buffer,"five") == 0) digit = '5';
    if(strcmp(buffer,"nine") == 0) digit = '9';

    buffer[3] = '\0';

    if(strcmp(buffer,"one") == 0) digit = '1';
    if(strcmp(buffer,"two") == 0) digit = '2';
    if(strcmp(buffer,"six") == 0) digit = '6';

    return digit;
}