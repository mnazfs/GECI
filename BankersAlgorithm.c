#include<stdio.h>

#define MAX_P 3
#define MAX_R 3

int need[MAX_P][MAX_R];
int avail[MAX_R];
int allo[MAX_P][MAX_R];
int finish[MAX_P];

int is_safe(){
    int work[MAX_R];
    for(int i = 0; i < MAX_R; i++)
        work[i] = avail[i];

    for(int i = 0; i < MAX_P; i++) {
        if(finish[i] == 0) {
            int j;
            for(j = 0; j < MAX_R; j++) {
                if(need[i][j] > work[j])
                    break;
            }
            if(j == MAX_R) {
                for(int k = 0; k < MAX_R; k++)
                    work[k] += allo[i][k];
                finish[i] = 1;
                i = -1;
            }
        }
    }
    for(int i = 0; i < MAX_P; i++) {
        if(finish[i] == 0)
            return 0;
    }
    return 1;
}

int main() {
    printf("Enter the allocation matrix :\n");
    for(int i = 0; i < MAX_P; i++) {
        for(int j = 0; j < MAX_R; j++) {
            scanf("%d", &allo[i][j]);
        }
    }
    printf("Enter the need matrix :\n");
    for(int i = 0; i < MAX_P; i++) {
        for(int j = 0; j < MAX_R; j++) {
            scanf("%d", &need[i][j]);
        }
    }
    printf("Enter the available matrix :\n");
    for(int i = 0; i < MAX_R; i++) {
        scanf("%d", &avail[i]);
    }

    if(is_safe() == 1) {
        printf("System in safe state\n");
    } else {
        printf("The system is in an unsafe state\n");
    }
    return 0;
}
