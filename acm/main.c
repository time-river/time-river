#include <stdio.h>
#define True 1

// three
#include <string.h>
#include <stdlib.h>

int main(void){
    int n;
    char *string, *current;
    char *substr = "wanshen";
    int size = 7;
    string = malloc(sizeof(char) * 10000000);
    while(scanf("%d", &n) != EOF){
        int i, start, sum=0;
        if (string == NULL)
            exit(-1);
        for(i=0, start=0; i < n; i++, start=strlen(string)){
            scanf("%s", &string[start]);
        }
        current = string;
        while (True) {
            current = strstr(current, substr);
            if (current != NULL){
                current += size;
                sum += 1;
                if(strlen(current) < size)
                    break;
            }
            else
                break;
        }
        printf("%d\n", sum);
    }
    free(string);
    return 0;
}
/*
// one
int main(void){
    long long x=0, y=0, a=0, b=0;
    while(scanf("%lld+%lldi %lld+%lldi", &x, &y, &a, &b) != EOF) {
        printf("%lld+%lldi\n", x+a, y+b);
    }
    return 0;
}
*/

/*
// two
void result(long long total){
    long long position=0, reminder; // position is a's position
    long long a=0, b=1, tmp=0, sum=1; // sum: b <<
    if (total < 4){
        printf("1 1\n");
        return;
    }
    while(sum < total){
        position += 1;
        tmp = a + b;
        a = b;
        b = tmp;
        sum += b;
    }
    reminder = total - (sum -b);
    if (reminder > a)
        position += 1;
    else
        reminder = a;
    printf("%lld %lld\n", position, reminder);
    return;
}

int main(void){
    long long sum;
    while(scanf("%lld", &sum) !=EOF){
        result(sum);
    }
    return 0;
}
*/
