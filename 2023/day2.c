#include <stdio.h>
#include <string.h>

void part_one(FILE *f);
void part_two(FILE *f);

int main(int argc, char *argv[]){
    part_one(fopen(argv[1],"r"));
    part_two(fopen(argv[1],"r"));
    return 0;
}

void part_one(FILE *f){
    unsigned sum = 0;
    char color[6];
    unsigned game_id, number;
    unsigned blue_count = 0, green_count = 0, red_count = 0;
    unsigned red_max = 12, green_max = 13, blue_max = 14;
    char c;
    while(fscanf(f,"Game %u: ",&game_id) != EOF){
        do{
            fscanf(f," %u %5[^,;\n]",&number,color);
            c = fgetc(f);
            
            if(strcmp("red",color)==0){
                red_count += number;
            }else if(strcmp("blue",color)==0){
                blue_count += number;
            }else{
                green_count += number;
            }

            if(c == ';'){
                if(red_count>red_max || blue_count>blue_max || green_count>green_max){
                    char d;
                    do{
                        d = fgetc(f);
                    }while(d !='\n' && d!= EOF);
                    break;
                }else{
                    red_count = 0;
                    blue_count = 0;
                    green_count = 0;
                }
            }
        }while(c != '\n' && c!= EOF);
        
        if(red_count<=red_max && blue_count<=blue_max && green_count<=green_max){
            sum += game_id;
        }
        red_count = 0;
        blue_count = 0;
        green_count = 0;
    }   
    fclose(f);
    printf("%u\n",sum);
}

void part_two(FILE *f){
    unsigned sum = 0;
    char color[6];
    unsigned number;
    unsigned blue_count = 0, green_count = 0, red_count = 0;
    unsigned red_min = 0, green_min = 0, blue_min = 0;
    char c;
    while(fscanf(f,"Game %*u: ") != EOF){
        do{
            fscanf(f," %u %5[^,;\n]",&number,color);
            c = fgetc(f);

            if(strcmp("red",color)==0){
                red_count += number;
            }else if(strcmp("blue",color)==0){
                blue_count += number;
            }else{
                green_count += number;
            }

            if(c == ';'){
                if(green_min<green_count) green_min = green_count;
                if(red_min<red_count) red_min = red_count;
                if(blue_min<blue_count) blue_min = blue_count;
                red_count = 0;
                blue_count = 0;
                green_count = 0;
            }
        }while(c != '\n' && c!= EOF);
        if(green_min<green_count) green_min = green_count;
        if(red_min<red_count) red_min = red_count;
        if(blue_min<blue_count) blue_min = blue_count;

        sum += green_min * blue_min * red_min;
        red_min = 0;
        blue_min = 0;
        green_min = 0;
        red_count = 0;
        blue_count = 0;
        green_count = 0;
    }   
    fclose(f);
    printf("%u\n",sum);
}