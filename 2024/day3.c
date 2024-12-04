#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#define LINE_HEURISTIC_SIZE 10000
#define NUMBER_CHARS_HEURISTIC_SIZE 10

int main(){

    char regex_str[] = "mul\\(([0-9]+),([0-9]+)\\)"; //Using [0-9] instead of \d (\\d if escaped) because isn't working
    regex_t regex;
    regmatch_t matches[3]; //3 because index 0 is full capture
    char line[LINE_HEURISTIC_SIZE];
    char *line_cursor;
    char n1_str[NUMBER_CHARS_HEURISTIC_SIZE];
    char n2_str[NUMBER_CHARS_HEURISTIC_SIZE];
    unsigned solution1 = 0;

    regcomp(&regex, regex_str, REG_EXTENDED);

    while(fgets(line, sizeof(line), stdin) != NULL){
        line_cursor = line;
        while (regexec(&regex, line_cursor, 3, matches, 0) == 0){
            memset(n1_str,'\0', sizeof(n1_str));
            memset(n2_str,'\0', sizeof(n2_str));
            memcpy(n1_str, line_cursor + matches[1].rm_so, sizeof(char) * (matches[1].rm_eo - matches[1].rm_so));
            memcpy(n2_str, line_cursor + matches[2].rm_so, sizeof(char) * (matches[2].rm_eo - matches[2].rm_so));

            solution1 += atoi(n1_str) * atoi(n2_str);

            line_cursor = line_cursor + matches[0].rm_eo;
        } 
    }
    regfree(&regex);

    printf("part 1: %u\n", solution1);
}