#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define True 1
// seven
int compare(const void *x, const void *y){
    return *(int *)y - *(int *)x;
}

int main(void){
    int n, k, i, last, m, tag;
    long long int sum;
    while(scanf("%d %d", &n, &k) != EOF){
        sum = 0;
        m = k - 1;
        tag = 0;
        long long num[n], tmp;
        for(i = 0; i < n; i++)
            scanf("%lld", num+i);
        qsort(num, n, sizeof(long long), compare); // sort
        if (n <= k){
            for(i = 0; i < n; i++)
                sum += num[i];
            n = 1;
        }
        else{
            last = n % m;
            if (last && last != 1){ // this if's goal: after this operation, n % m == 1
                for(n=n-last+1, i = 0; i < (last-1); i++)
                    num[n-1] += num[n+i];
                sum += num[n-1];
                tag = 1;
            }
            else if(m != 1 && !last){
                for(n=n-m+1, i = 0; i < (m-1); i++)
                    num[n-1] += num[n+i];
                sum += num[n-1];
                tag = 1;
            }
        }
        while(n > 1){
            if (tag){
                for(i = 0; i < n; i++) // insertion sort
                    if (num[i] < num[n-1]){
                        tmp = num[n-1];
                        for(last = n-1; last != i; last--)
                            num[last] = num[last-1];
                        num[last] = tmp;
                        break;
                    }
                tag = 0;
            }
            for(n-=m, i=0; i < m; i++){
                num[n-1] += num[n+i];
                tag = 1;
            }
            sum += num[n-1];
        }
        printf("%lld\n", sum);
    }
    return 0;
}
