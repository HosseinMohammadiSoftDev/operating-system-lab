#include <stdio.h>
#include <stdbool.h>

#define PRECESS_COUNT 4

#define UNVISITED 0
#define VISITING 1 
#define VISITED 2

int graph[PRECESS_COUNT][PRECESS_COUNT] = {
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {1, 0, 0, 0},
    {0, 0, 0, 0}
};

int state[PRECESS_COUNT] = {0};

bool dfs(int process) {
    state[process] = VISITING;

    for (int i = 0; i < PRECESS_COUNT; i++) {
        if (!graph[process][i]) {continue;}

        if (state[i] == VISITING) {return true;}

        if (state[i] == UNVISITED && dfs(i)) {return true;}
    }

    state[process] = VISITED;

    return false;
}

bool detect_dead_lock(void) {
    for (int i = 0; i < PRECESS_COUNT; i++) {
        if (state[i] == UNVISITED && dfs(i)) {return true;}
    }

    return false;
}


int main (void) {
    if(detect_dead_lock()) {printf("DeadLock detected! \n");} 

    printf("no dead lock");

    return 0;
}
