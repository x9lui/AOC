#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define LINE_HEURISTIC_SIZE 10000
#define NUMBER_CHARS_HEURISTIC_SIZE 10

int main(){

    char regex_str[] = "mul\\(([0-9]+),([0-9]+)\\)"; 
    //Using [0-9] instead of \d (\\d if escaped) because isn't working
    regex_t regex;
    regmatch_t mul_matches[3]; //3 because index 0 is the full capture
    char line[LINE_HEURISTIC_SIZE];
    char *line_cursor;
    char n1_str[NUMBER_CHARS_HEURISTIC_SIZE];
    char n2_str[NUMBER_CHARS_HEURISTIC_SIZE];
    unsigned solution1 = 0;
    int regex_ret;

    bool mul_enabled = true;
    char *regex2_str = "do\\(\\)|don't\\(\\)";
    regex_t regex2;
    regmatch_t do_matches[1];
    unsigned solution2 = 0;
    int regex2_ret;

    regcomp(&regex, regex_str, REG_EXTENDED);
    regcomp(&regex2, regex2_str, REG_EXTENDED);

    while(fgets(line, sizeof(line), stdin) != NULL){
        line_cursor = line;
        regex_ret = regexec(&regex, line_cursor, 3, mul_matches, 0);
        regex2_ret = regexec(&regex2, line_cursor, 1, do_matches, 0);

        /*Cant put functions inside while condition because the "||" 
        operator evaluates in short-circuit*/
        while (regex_ret == 0 || regex2_ret == 0){ 

            
            if((mul_matches[0].rm_so < do_matches[0].rm_so && regex_ret == 0) ||
                regex2_ret == REG_NOMATCH){ 
                //"mul" found before "do" or "dont"

                //copy numbers to strings
                memset(n1_str,'\0', sizeof(n1_str));
                memset(n2_str,'\0', sizeof(n2_str));
                memcpy(n1_str, line_cursor + mul_matches[1].rm_so, 
                    sizeof(char) * (mul_matches[1].rm_eo - mul_matches[1].rm_so));
                memcpy(n2_str, line_cursor + mul_matches[2].rm_so,
                    sizeof(char) * (mul_matches[2].rm_eo - mul_matches[2].rm_so));

                solution1 += atoi(n1_str) * atoi(n2_str);
                
                if(mul_enabled) solution2 += atoi(n1_str) * atoi(n2_str);

                line_cursor += mul_matches[0].rm_eo;
            }else{ //"do" or "dont" found before mul
                if(strncmp("do()", line_cursor + do_matches[0].rm_so, 4) == 0){ 
                    mul_enabled = true;
                }else{
                    mul_enabled = false;
                }
                line_cursor += do_matches[0].rm_eo;
            }
            regex_ret = regexec(&regex, line_cursor, 3, mul_matches, 0);
            regex2_ret = regexec(&regex2, line_cursor, 1, do_matches, 0);
        }
        
    }
    regfree(&regex);
    regfree(&regex2);

    printf("part 1: %u\npart 2: %u\n", solution1, solution2);
}