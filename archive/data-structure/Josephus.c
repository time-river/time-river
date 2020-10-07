#include <stdio.h>
#include <stdlib.h>

typedef struct LNode {
    int data[2];
    struct LNode *next;
}List, *LinkList;

void InitList(LinkList *L); //构造一个空的线性表L
int  ListLength(LinkList L); //返回L中数据元素个数
int  ListDelete(LinkList *L, int i, int *e); //删除L的第i个元素，并由e返回其值(从1计数)
int  ListAppend(LinkList *L, int *e); //在L最后一个元素后追加一个元素
LinkList Input(int n);
LinkList Output(LinkList *L, int code);

int main(void) {
    int m, n;
    LinkList L = NULL;

    scanf("%d %d", &n, &m);
    if (n) { //非空传入
        L = Input(n);
        L = Output(&L, m);
    }

    return 0;
}
LinkList Input(int n) {
    int i, status, e[2];
    LinkList L = NULL;

    for (i = 0; i < n; ++i) {
		scanf ("%d", e+1);
        e[0] = i+1;
 		status = ListAppend(&L, e);
        if (status == 0)
            exit(-1);
	}
    return L;
}

LinkList Output(LinkList *L, int code) {
    int e[2];
    int len = ListLength(*L);

    while (len != 0) {
        code = code % len;
        ListDelete(L, code?code:len, e);
        printf("%d ", e[0]);
        code = e[1];
        len = ListLength(*L);
    }

    return NULL;
}

int  ListLength(LinkList L) {
    int i;
    LinkList tmp = L;

    if (tmp == NULL)
        return 0;
    for (i = 1, L = L->next; L != tmp; i++)
        L = L->next;

    return i;
}

int  ListDelete(LinkList *L, int i, int *e) {
    LinkList tmp = *L;
    LinkList next;
    int len = ListLength(*L);
    int j = 1;

    if (i < 1 || i > len) {
        e = NULL;
        return 0;
    }
    if(i == 1) { //第一个结点
        e[0] = tmp->data[0];
        e[1] = tmp->data[1];
        if (len == 1) {
            free (tmp);
            *L = NULL;
        }
        else {
            while (tmp->next != *L)
            tmp = tmp->next;
            tmp->next = (*L)->next;
            tmp = *L;
            *L = tmp->next;
            free(tmp);
        }
    }
    else { //非第一个结点
        for (j = 2; j < i; j++)
            tmp = tmp->next;
        next = tmp->next;
        e[0] = next->data[0];
        e[1] = next->data[1];
        tmp->next = next->next;
        *L = next->next;
        free(next);
    }
    return 1;
}
int  ListAppend(LinkList *L, int *e) {
    LinkList tmp = *L;
    LinkList node = (LinkList)malloc(sizeof(List));

    node->data[0] = e[0];
    node->data[1] = e[1];

   if (tmp == NULL) {
        node->next = node;
        *L = node;
    }
    else {
        while (tmp != NULL && tmp->next != *L)
            tmp = tmp->next;
        node->next = tmp->next;
        tmp->next = node;
    }
    return 1;
}
