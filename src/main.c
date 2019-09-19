#include "../include/functions.h"

#define N 7
#define M 8

int main(){
    team t;
    int ages[N] = {21, 33, 34, 18, 42, 22, 26};
    int src[M] = {1, 1, 2, 3, 6, 4, 4, 6};
    int dest[M] = {2, 3, 5, 5, 3, 6, 7, 7};
    make_empty_team(&t, N);

    for(int i = 0; i < N; i++)
        set_age(&t, i, ages[i]);

    for(int i = 0; i < M; i++)
        insert_edge(&t, dest[i]-1, src[i]-1);

    meeting(&t);
    free_team(&t);

    return 0;
}