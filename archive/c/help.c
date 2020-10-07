#include<stdio.h>

int main(void){
    int array[4][4], position[2]={0};
    int i, j;
    puts("Input the array");
    for(i=0; i<4; i++){
        for(j=0; j<4; j++)
            scanf("%d", array[j]+i);
    }
    puts("Elements of the main diagonal:");
    for(i=0; i< 4; i++)
        printf("%d ", array[i][i]);
    printf("\nElements of the upward-pointing triangle:\n");
    for(i=0; i<4; i++){
        for(j=0; j <4; j++){
            if(i<=j) 
                printf("%d ", array[j][i]);
            else
                printf("  ");
        }
        putchar('\n');
    }
    printf("\n%d %d %d %d\n", array[1][1], array[1][3], array[3][1], array[3][3]);
    for(i=0; i<4; i++){
        for(j=0; j<4; j++)
            if(array[i][j]>array[position[0]][position[1]]){
                position[0] = i;
                position[1] = j;
            }
    }
    printf("Max element: %d, position:%d %d\n", array[position[0]][position[1]], position[0], position[1]);
    return 0;
}
