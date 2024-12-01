#include <stdio.h>
#include <stdlib.h>

//Compare function for qsort
int compare(const void *a, const void *b) {
    return *(unsigned*)a - *(unsigned*)b;
}

#define HEURISTIC_SIZE 1000

int main(){
    unsigned a[HEURISTIC_SIZE], b[HEURISTIC_SIZE];
    unsigned n = 0;
    unsigned solution1 = 0;
    unsigned repetitions;
    unsigned solution2 = 0;
    
    while(scanf("%d %d\n", &a[n], &b[n]) != EOF) n++;

    qsort(a, n, sizeof(unsigned), compare);
    qsort(b, n, sizeof(unsigned), compare);

    for(unsigned i = 0; i < n; i++){
        solution1 += abs((int)a[i] - (int)b[i]);
    }

    //Can be optimized with binary search
    for(unsigned i = 0; i < n; i++){
        repetitions = 0;
        for(unsigned j = 0; j < n; j++){
            if(b[j] == a[i]) repetitions++;
        }
        solution2 += a[i] * repetitions;
    }
    
    printf("part 1: %d\npart 2: %d\n", solution1, solution2);
}