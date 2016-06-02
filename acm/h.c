#include <stdio.h>
#include <stdlib.h>
#define MOD 1000000007
#include <time.h>
typedef struct {
    long long int **array;
    int params[2];
} martix_, *martix;

// martix calculate
martix init(int flag);
void martix_sum(martix x, martix y);
void martix_mul(martix x, martix y);
void martix_des(martix x);

// Fast Matrices
long long int fast_matrices(long long int frequency);

int main(void){
    /*martix ones = init(1);
    martix factor = init(2);
    martix factor_ori = init(2);
    martix first = init(3);
    martix _result = init(3);
    martix_mul(factor, factor);
    martix_mul(factor, _result);
    for(int i=0; i < _result->params[0]; i++){
        for(int j=0; j < _result->params[1]; j++)
            printf("%lld ", _result->array[i][j]);
        putchar('\n');
    }*/
    long long int l, r, i, before_start_sum, end_sum, result;
    /*l = 0, r = 1;
    long long int start, end;
    for(int p=0; p < 10; p++){
        r*=10;
        start = clock();*/
    while(scanf("%lld %lld", &l, &r) != EOF){
        result = 0;
        if(r < 3){ // the first three item is 1, 1, 1
            for(i = l; l <= r && i <= r; i++)
                result += 1;
            //printf("result: %lld\n", result);
        }
        else{
            before_start_sum = 0;
            if(l < 3){
                for(i=0; i < l; i++)
                    before_start_sum +=1;
            }
            else{
                before_start_sum = fast_matrices(l-3); // frequency == l-3
            }
            //printf("before_start_sum: %lld-------------------\n", before_start_sum);
            end_sum = fast_matrices(r-2); // frequency == r-2
            result = end_sum - before_start_sum;
            if(result < 0)
                result = (end_sum + MOD) - before_start_sum;
        }
        printf("%lld\n", result);
        //end = clock();
        //printf("end-start: %lld\n", end-start);
    }
    return 0;
}

long long int fast_matrices(long long int frequency){
    martix result = init(3);
    martix factor = init(2);
    long long int ans;

   /*     int i, j;
    {// debug information
        for(i = 0; i < factor->params[0]; i++){
            for(j = 0; j < factor->params[1]; j++)
                printf("%lld ", factor->array[i][j]);
            putchar('\n');
        }
        for(i = 0; i < result->params[0]; i++){
            for(j = 0; j < result->params[1]; j++)
                printf("%lld ", result->array[i][j]);
            putchar('\n');
        }
    }
*/
    while(frequency){
        if(frequency & 1){ // frequency %= 2
            martix_mul(factor, result);
  /*          { //debug information
                for(i = 0; i < result->params[0]; i++)
                    for(j = 0; j < result->params[1]; j++)
                    printf("result[%d][%d]: %lld***\n", i, j, result->array[i][j]);
            }*/
        }
        martix_mul(factor, factor);
        frequency >>= 1; // frequency /= 2
    }
    martix_des(factor);
    ans = result->array[0][0];
  //  long long int ttt = result->array[1][0];
    martix_des(result);
//    printf("ans: %lld A[n]: %lld\n", ans, ttt);
    return ans;
}

martix init(int flag){
    long long int 
        ones[4][4] = {
            {1, 0, 0, 0},
            {0, 1, 0, 0},
            {0, 0, 1, 0},
            {0, 0, 0, 1}
        },
         factor[4][4] = {
             {1, 1, 1, 1},
             {0, 1, 1, 1},
             {0, 1, 0, 0},
             {0, 0, 1, 0}
         },
         first[4][1] = {
             {3},
             {1},
             {1},
             {1}
         };

    int params[2] = {4};
    switch(flag){
        case 1:
        case 2:
            params[1] = 4;
            break;
        case 3:
            params[1] = 1;
            break;
    }
    martix array = (martix)malloc(sizeof(martix_));
    if(array == NULL)
        exit(-1);
    array->params[0] = params[0];
    array->params[1] = params[1];
    //printf("****%d %d****\n", array->params[0], array->params[1]);
    array->array = (long long int **)malloc(params[0] * sizeof(long long int *));
    if (NULL == array->array)
        exit(-1);
    int i, j;
    for(i = 0; i < params[0]; i++){
        array->array[i] = (long long int *)malloc(params[1] * sizeof(long long int));
        if(array->array[i] == NULL)
            exit(-1);
        for(j = 0; j < params[1]; j++){
            switch(flag){
                case 1:
                    array->array[i][j] = ones[i][j];
                    break;
                case 2:
                    array->array[i][j] = factor[i][j];
                    break;
                case 3:
                    array->array[i][j] = first[i][j];
                    break;
            }
        }
    }
    return array;
}

void martix_sum(martix x, martix y){ // y = (x + y) % MOD = ((x % MOD) + (y % MOD)) % MOD
    int i, j;
    for(i = 0; i < x->params[0]; i++)
        for(j = 0; j < x->params[1]; j++)
            y->array[i][j] = (x->array[i][j] + y->array[i][j]) % MOD;
    return;
}

void martix_mul(martix x, martix y){ // y = (x * y) % MOD = ((x % MOD) * (y % MOD)) % MOD
    long long int tmp[x->params[0]][y->params[1]];
    int i, j, k;
    for(i = 0; i < x->params[0]; i++)
        for(j = 0; j < y->params[1]; j++){
            tmp[i][j] = 0;
            for(k = 0; k < x->params[1]; k++){
                tmp[i][j] += (x->array[i][k] * y->array[k][j]) % MOD;
            }
            tmp[i][j] %= MOD;
        }
    for(i = 0; i < x->params[0]; i++)
        for(j = 0; j < y->params[1]; j++){
            y->array[i][j] = tmp[i][j];
    //        printf("%lld ", y->array[i][j]);
        }
    y->params[0] = x->params[0];
    return;
}

void martix_des(martix x){
    int i;
    for(i = 0; i < x->params[0]; i++)
        free(x->array[i]);
    free(x->array);
    free(x);
    return;
}
