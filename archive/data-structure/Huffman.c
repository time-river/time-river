#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 30

//string
typedef struct {
    char *string;
    int *weight;
    int n;
}String;
//huffman
typedef struct {
    unsigned int weight;
    unsigned int parent;
    unsigned int left_child;
    unsigned int right_child;
    char ch;
}HTNode, *HuffmanTree;
typedef char **HuffmanCode;
//queue
typedef struct Queue {
    int * data;
    int front;
    int rear;
    int size;
}Queue, *LinkQueue;

String Input(void); //Input the Str, return NULL if failing
//Huffman tree ADT
HuffmanTree Initialization(String string); // Initialization the huffman tree
void        Encoding(HuffmanTree tree, char *tree_fp, int n, char *string); //Encode the huffman tree, left is zero and right is one
void 		Decoding(HuffmanTree tree, char *tree_fp, int m, int n); //Decoding the buffer
void 		PrintHuffmanTree(HuffmanTree huffman_tree); //Print the huffman tree
void        Print(void); //Print CodeFile
//Select two element
void Select(HuffmanTree huffman_tree, int i, int *child_1, int *child_2); //select the tow smallest element from huffman_tree, the smaller is child_1
char *StringCopy(char *tmp, int start, int size); // copy tmp string starting the start position
//Find root in the tree
int FindRoot(HuffmanTree huffman_tree);
//Queue ADT
LinkQueue InitQueue(int size);
void	  InQueue(LinkQueue queue, int x);
int 	  OutQueue(LinkQueue queue);
int 	  IsEmpty(Queue queue);
LinkQueue DesQueue(LinkQueue queue);

int main(void){
    String string;
    HuffmanTree huffman_tree;
    HuffmanCode huffman_code;
    char str[] = "THIS PROMGAM IS MY FAVORITE";

    string = Input();
    huffman_tree = Initialization(string);
    Encoding(huffman_tree, '\0', string.n, str);
    Decoding(huffman_tree, '\0', FindRoot(huffman_tree), string.n);
    Print();
    PrintHuffmanTree(huffman_tree);
    return 0;
}

LinkQueue InitQueue(int size){
    LinkQueue queue = (LinkQueue)malloc(sizeof(Queue));
    if (NULL == queue)
        exit(-1);

    queue->data = (int *)malloc(size * sizeof(int));
    if (queue->data == NULL)
        exit(-1);
    queue->front = queue->rear = 0;
    queue->size = size;

    return queue;
}

void InQueue(LinkQueue queue, int x){
    //front指向第一个元素 rear指向最后一元素的下一元素
    int tmp;

    tmp = (queue->rear + 1) % queue->size;
    if (tmp == queue->front){
        printf("Queue is full.");
        return;
    }
    queue->data[queue->rear] = x;
    queue->rear = tmp;

    return;
}
int OutQueue(LinkQueue queue){
    int x;


    x = queue->data[queue->front];
    queue->front = (queue->front + 1) % queue->size;

    return x;
}
int IsEmpty(Queue queue){
    int tmp;

    if (queue.front == queue.rear)
        return 1; //队列空，返回1
    else
        return 0;
}
LinkQueue DesQueue(LinkQueue queue){
    free(queue->data);
    free(queue);

    return NULL;
}

void PrintHuffmanTree(HuffmanTree huffman_tree){
    int root = FindRoot(huffman_tree);
    LinkQueue queue = InitQueue(SIZE);
    //level-order traversal
    InQueue(queue, root);
    puts("(code|character|weight|left_child|right_child)");
    while(!IsEmpty(*queue)){
        root = OutQueue(queue);
        /***********************************************************************
         Output section
         ***********************************************************************/
        if (huffman_tree[root].ch != '\0')
            printf("(%d|%c|%d|%d %d)\n", root, huffman_tree[root].ch, huffman_tree[root].weight, huffman_tree[root].left_child, huffman_tree[root].right_child);
        else
            printf("(%d|None|%d|%d %d)\n", root, huffman_tree[root].weight, huffman_tree[root].left_child, huffman_tree[root].right_child);
        /***********************************************************************
         Output section
         ***********************************************************************/
        if(huffman_tree[root].left_child != -2)
            InQueue(queue, huffman_tree[root].left_child);
        if(huffman_tree[root].right_child != -2)
            InQueue(queue, huffman_tree[root].right_child);
    }
    DesQueue(queue);
    return;
}

int FindRoot(HuffmanTree huffman_tree){
    int root = 0;
    while(huffman_tree[root].parent != -1)
        root = huffman_tree[root].parent;

    return root;
}

void Print(void){
    FILE *fp, *print_fp;
    char str[51];

    fp = fopen("CodeFile.txt", "r");
    print_fp = fopen("CodePrin.txt", "w+");
    if (NULL == fp)
        exit(-1);
    while(!feof(fp)){
        str[50] = '\0';
        fread(str, sizeof(char), 50, fp);
        puts(str);
        fwrite(str, sizeof(char), 50, print_fp);
    }
    return;
}

void Decoding(HuffmanTree tree, char *tree_fp, int m, int n){
    int root = m, i;
    char buffer;
    HuffmanTree huffman_tree;
    FILE *fp, *tree_stream, *code_stream;

    if (tree == NULL){// if tree is NULL, read from file
        tree_stream = fopen(tree_fp, "r");
        if (NULL == tree_stream)
            exit(-1);
        for (i = 0; i < n; i++){
            fscanf(tree_stream, "%c %d %d %d %d\n", &huffman_tree[i].ch, &huffman_tree[i].weight, &huffman_tree[i].parent,
                   &huffman_tree[i].left_child, &huffman_tree[i].right_child);
        }
        fclose(tree_stream);
    }
    else
        huffman_tree = tree;

    fp = fopen("TextFile.txt", "w+");
    code_stream = fopen("CodeFile.txt", "r");
    if(NULL == fp || NULL == code_stream)
        exit(-1);
    for(buffer=fgetc(code_stream); buffer != EOF; buffer=fgetc(code_stream)){
        if(buffer == '0'){
            root = huffman_tree[root].left_child;
        }
        else
            root = huffman_tree[root].right_child;

        if(-2 == huffman_tree[root].left_child && -2 == huffman_tree[root].right_child){
            printf("%c", huffman_tree[root].ch);
            fprintf(fp, "%c", huffman_tree[root].ch);
            root = m;
        }
    }
    putchar('\n');
    fclose(fp);
    return;
}

char *StringCopy(char *tmp, int start, int size){
    char *string;
    int i;
    string = (char *)malloc(sizeof(char) * size);
    if (NULL == string)
        exit(-1);
    for(i = 0; tmp[start] != '\0'; start++, i++){
        string[i] = tmp[start];
    }
    string[i] = '\0';

    return string;
}

void Encoding(HuffmanTree tree, char *tree_fp, int n, char *string){
    HuffmanCode huffman_code;
    HuffmanTree huffman_tree;
    int i, cur, next, size, start;
    char *tmp;
    FILE *fp;

    if (tree == NULL){// if tree is NULL, read from file
        huffman_tree = (HuffmanTree)malloc(sizeof(HTNode) * n);
        if (NULL == huffman_tree)
            exit(-1);
        fp = fopen(tree_fp, "r");
        for (i = 0; i < n; i++){
             fscanf(fp, "%c %d %d %d %d\n", &huffman_tree[i].ch, &huffman_tree[i].weight, &huffman_tree[i].parent,
                   &huffman_tree[i].left_child, &huffman_tree[i].right_child);
        }
        fclose(fp);
    }
    else
        huffman_tree = tree;

    tmp = (char *)malloc(sizeof(char) * n);
    if (NULL == tmp)
        exit(-1);
    tmp[n-1] = '\0';

    huffman_code = (HuffmanCode)malloc(n * sizeof(char*));
    for(i = 0; i < n; i++){
        start = n - 1;
        for(cur = i, next=huffman_tree[cur].parent; huffman_tree[cur].parent != -1; cur=next, next=huffman_tree[next].parent){
            if(cur == huffman_tree[next].left_child)
                tmp[--start] = '0';
            else
                tmp[--start] = '1';
        }
        size = n - start;
        huffman_code[i] = (char *)malloc(size * sizeof(char));
        if(huffman_code[i] == NULL)
            exit(-1);
        huffman_code[i] = StringCopy(tmp, start, size);
    }//get huffman code

    //encode string and write in file
    fp = fopen("CodeFile.txt", "w+");
    if (NULL == fp)
        exit(-1);
    for (cur = 0; string[cur] != '\0'; ++cur){
        for(i = 0; i < n; i++){
            if(huffman_tree[i].ch == string[cur])
                fprintf(fp, "%s", huffman_code[i]);
        }
    }
    fclose(fp);
    return;
}

void Select(HuffmanTree huffman_tree, int len, int *child_1, int *child_2){
    int i, max, weight_1, weight_2;

    for (*child_1 = *child_2 = -1, i = 0; i < len; i++){
        if(huffman_tree[i].parent == -1){ //判断是否存在parent
            if(*child_1 == -1){
                *child_1 = i;
            }
            else if(*child_2 == -1){
                *child_2 = i;
            }
            else{ //找最小2结点
                weight_1 = huffman_tree[*child_1].weight;
                weight_2 = huffman_tree[*child_2].weight;
                max = weight_1 > weight_2 ? weight_1 : weight_2;
                if(max > huffman_tree[i].weight){
                    if(weight_1 == max){
                        *child_1 = i;
                    }
                    else
                        *child_2 = i;
                }
            }
        }
    }
    return;
}

HuffmanTree Initialization(String string){
    HuffmanTree huffman_tree;
    int i, size, child_1, child_2;
    FILE *fp;

    fp = fopen("hfmTree.txt", "w+");
    if (fp == NULL)
        exit(-1);
    size = string.n * 2 - 1;
    huffman_tree = (HuffmanTree)malloc(size * sizeof(HTNode));
    if (NULL == huffman_tree)
        return NULL;
    for(i = 0; i < string.n; i++){
        huffman_tree[i].weight = string.weight[i];
        huffman_tree[i].parent = -1;
        huffman_tree[i].left_child = -2;
        huffman_tree[i].right_child = -2;
        huffman_tree[i].ch = string.string[i];
    }
    for( ; i < size; i++){
        huffman_tree[i].weight = 0;
        huffman_tree[i].parent = -1; //set root parent -1
        huffman_tree[i].left_child = -2; //if no child, value is -2
        huffman_tree[i].right_child = -2;
        huffman_tree[i].ch = '\0';
    }
    for(i = string.n; i < size; i++){
        Select(huffman_tree, i, &child_1, &child_2);
        huffman_tree[child_1].parent = i;
        huffman_tree[child_2].parent = i;
        huffman_tree[i].right_child = child_1;
        huffman_tree[i].left_child = child_2;
        huffman_tree[i].weight = huffman_tree[child_1].weight + huffman_tree[child_2].weight;
        huffman_tree[i].ch = '\0';
    }

    puts("Huffman code:");
    puts("character weight parent left_child right_child");
    for (i = 0; i < size; i++){
        if ('\0' == huffman_tree[i].ch)
            printf("None %d %d %d %d\n", huffman_tree[i].ch, huffman_tree[i].weight, huffman_tree[i].parent,
                   huffman_tree[i].left_child, huffman_tree[i].right_child);
        else
            printf("%c %d %d %d %d\n", huffman_tree[i].ch, huffman_tree[i].weight, huffman_tree[i].parent,
                   huffman_tree[i].left_child, huffman_tree[i].right_child);
        fprintf(fp, "%c %d %d %d %d\n", huffman_tree[i].ch, huffman_tree[i].weight, huffman_tree[i].parent,
                huffman_tree[i].left_child, huffman_tree[i].right_child);
    }
    fclose(fp);
    return huffman_tree;
}

String Input(void){
    int n, i;
    String string;

    puts("Enter the number of the string.");
    scanf("%d", &n);
    string.n = n;
    string.string = (char *)malloc(n * sizeof(char));
    string.weight = (int *)malloc(n * sizeof(int));
    if (NULL == string.string || NULL == string.weight)
        exit(-1);
    puts("Input the character and its weight.");
    for(i = 0; i < n ;i++){
        getchar(); //each blankspace or enter
        scanf("%c %d", string.string+i, string.weight+i);
    }

    return string;
}
