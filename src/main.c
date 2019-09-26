#include "../include/functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


int main(int argc, char const *argv[]) {
    team t;
    list l;
    FILE *file;
    int team_size, team_relations, n_instructions, age, src, dest;
    char instruction[20], command;
    clock_t start_time, end_time;

    if(argc < 2) {
        printf("Favor inserir o arquivo de entrada.\n");
        exit(0);
    }

    start_time = clock();
    file = fopen(argv[1], "r");
    fscanf(file, "%d %d %d\n", &team_size, &team_relations, &n_instructions);
    make_empty_team(&t, team_size);
    for(int i = 0; i < team_size; i++) {
        fscanf(file, "%d", &age);
        set_age(&t, i, age);
    }
    for(int i = 0; i < team_relations; i++) {
        fscanf(file, "%d %d\n", &src, &dest);
        insert_edge(&t, src, dest);
    }
    for(int i = 0; i < n_instructions; i++) {
        fgets(instruction, 20, file);
        command = instruction[0];
        strtok(instruction, " ");
        switch (command) {
            case 'C':
                src = atoi(strtok(NULL, " "));
                dest = commander(&t, src-1);
                if(dest == -1)
                    printf("C *\n");
                else
                    printf("C %d\n", dest);
                break;
            case 'M':
                printf("M ");
                l = meeting(&t);
                print_list(&l);
                break;
            case 'S':
                src = atoi(strtok(NULL, " "));
                dest = atoi(strtok(NULL, " "));
                if(swap(&t, src, dest))
                    printf("S T\n");
                else
                    printf("S N\n");
                break;
        }
    }
    fclose(file);
    free_team(&t);
    end_time = clock();
    printf("%f\n", (end_time - start_time) * 1000.0 / CLOCKS_PER_SEC);
    return 0;
}