#include <stdio.h>
#include <stdlib.h>

typedef struct BSTNode{
    int data;
    int bf;
    struct BSTNode * left_child;
    struct BSTNode * right_child;
}BSTNode, *BSTree;

void EatLine(void);
void Travel(BSTree tree);
BSTree SearchBSTree(BSTree tree, int number);
BSTree InsertBSTree(BSTree tree, int number, int *taller);
BSTree DeleteBSTree(BSTree tree, int number, int *shorter);
BSTree LeftBalance(BSTree tree);
BSTree RightBalance(BSTree tree);
BSTree LeftRotation(BSTree tree);
BSTree RightRotation(BSTree tree);
BSTree LeftRightRotation(BSTree tree);
BSTree RightLeftRotation(BSTree tree);

int main(void){
    int number;
    char ch;
    int taller = 0, shorter = 0;
    BSTree tree = NULL;
    do{
        puts("Input:");
        puts("1 : search");
        puts("2 : inseart");
        puts("3 : delete");
        puts("q : quit");
        ch = getchar();
        switch (ch){
            case '1':
                puts("Input the number");
                scanf("%d", &number);
                if(SearchBSTree(tree, number) == NULL)
                    puts("not exist");
                else{
                    puts("exist");
                }
                break;
            case '2':
                puts("Input the number of insertion");
                for(int i = 0; i < 11; i++) {
                    int data[11] = {20, 10, 5, 30, 40, 15, 25, 23, 50, 1, 3};
                    tree = InsertBSTree(tree, data[i], &taller);
                }
                //scanf("%d", &number);
                //tree = InsertBSTree(tree, number, &taller);
                puts("Insert sucessfully");
                Travel(tree);
                break;
            case '3':
                puts("Input the number of deletion");
                scanf("%d", &number);
                tree = DeleteBSTree(tree, number, &shorter);
                puts("Delete sucessfully");
                Travel(tree);
                break;
            case 'q':
                break;
            default:
                puts("Wrong, input again");
                break;
        }
        EatLine();
    }while(ch != 'q');
    return 0;
}

void EatLine(void){
    char ch;
    while(ch = getchar(), ch!='\n' && ch!=EOF)
        continue;
    return;
}

void Travel(BSTree tree){
    if(tree == NULL)
        return;
    else{
        printf("data: %d bf: %d\n", tree->data, tree->bf);
        Travel(tree->left_child);
        Travel(tree->right_child);
    }
    return;
}

BSTree SearchBSTree(BSTree tree, int number){
    while(tree != NULL){
        if(tree->data == number)
            return tree;
        else if(tree->data > number)
            tree = tree->left_child;
        else
            tree = tree->right_child;
    }
    return NULL;
}
BSTree InsertBSTree(BSTree tree, int number, int *taller){
    if(tree == NULL){
        tree = (BSTree)malloc(sizeof(BSTNode));
        if (NULL == tree)
            exit(-1);
        tree->data = number;
        tree->bf = 0;
        tree->left_child = tree->right_child = NULL;
        *taller = 1;
        return tree;
    }
    else if(tree->data > number){ // left, insert
        tree->left_child = InsertBSTree(tree->left_child, number, taller);
        if(*taller == 1){
            switch(tree->bf){
                case 1: // right was high, now, tree is balanced
                    tree->bf = 0;
                    *taller = 0;
                    break;
                case -1: //left was high, now, tree needs rotation
                    tree = LeftBalance(tree);
                    *taller = 0;
                    break;
                case 0: // tree was balanced, now, left is high
                    tree->bf = -1;
                    *taller = 1;
                    break;
            }
        }
    }
    else if(tree->data < number){
        tree->right_child = InsertBSTree(tree->right_child, number, taller);
        if(*taller == 1){
            switch(tree->bf){
                case 1: //right was high, tree needs rotation now
                    tree = RightBalance(tree);
                    *taller = 0;
                    break;
                case -1: //left was high, tree is balanced now
                    tree->bf = 0;
                    *taller = 0;
                    break;
                case 0: //tree was balanced, right is high now
                    tree->bf = 1;
                    *taller = 1;
                    break;
            }
        }
    }
    else
        *taller = 0;

    return tree;
}
BSTree LeftBalance(BSTree tree){
    BSTree lc = tree->left_child;
    BSTree rd = lc->right_child;
    switch (lc->bf){
        case 1:
            switch(rd->bf){
                case 1:
                    tree->bf = 0;
                    lc->bf = -1;
                    break;
                case -1:
                    tree->bf = 1;
                    lc->bf = 0;
                    break;
                case 0:
                    tree->bf = lc->bf= 0;
                    break;
            }
            rd->bf= 0;
            tree->left_child = LeftRotation(tree->left_child);
            tree = RightRotation(tree);
            break;
        case -1:
            tree->bf = lc->bf = 0;
            tree = RightRotation(tree);
            break;
        case 0: //deletion use it
            tree->bf = -1;
            lc->bf = 1;
            tree = RightRotation(tree);
            break;
    }
    return tree;
}
BSTree RightBalance(BSTree tree){
    BSTree rc = tree->right_child;
    BSTree ld = rc->left_child;
    switch(rc->bf){
        case 1:
            tree->bf = rc->bf = 0;
            tree = LeftRotation(tree);
            break;
        case -1:
            switch(ld->bf){
                case 1:
                    tree->bf = -1;
                    rc->bf = 0;
                    break;
                case -1:
                    tree->bf = 0;
                    rc->bf = 1;
                    break;
                case 0:
                    rc->bf = tree->bf = 0;
                    break;
            }
            ld->bf = 0;
            tree->right_child = RightRotation(tree->right_child);
            tree = LeftRotation(tree);
            break;
        case 0: //deletion use it
            tree->bf = 1;
            rc->bf = -1;
            tree = LeftRotation(tree);
            break;
    }
    return tree;
}
BSTree LeftRotation(BSTree tree){
    BSTree rc = tree->right_child;
    tree->right_child = rc->left_child;
    rc->left_child = tree;
    return rc;
}
BSTree RightRotation(BSTree tree){
    BSTree lc = tree->left_child;
    tree->left_child = lc->right_child;
    lc->right_child = tree;
    return lc;
}

BSTree DeleteBSTree(BSTree tree, int number, int *shorter){
    BSTree tmp_tree;
    int tmp_bf;
    if(NULL == tree){
        puts("Not exist");
        *shorter = 0;
        return tree;
    }
    else if(number == tree->data){
        if(tree->left_child == NULL){
            *shorter = 1;
            tmp_tree = tree->right_child;
            free(tree);
            return tmp_tree;
        }
        else if(tree->right_child == NULL){
            *shorter = 1;
            tmp_tree = tree->left_child;
            free(tree);
            return tmp_tree;
        }
        else{ // both left child and right child exist
            switch(tree->bf){
                case 1: //right was high, search and replace minima in right tree
                case 0: //balance
                    tmp_tree = tree->right_child;
                    while(tmp_tree->left_child)
                        tmp_tree = tmp_tree->left_child;
                    tree->data = tmp_tree->data;
                    tree->right_child = DeleteBSTree(tree->right_child, tmp_tree->data, shorter);
                    if(*shorter){
                        switch(tree->bf){
                            case 1:
                                *shorter = 1;
                                tree->bf = 0;
                                break;
                            case -1:
                                tmp_bf = tree->bf;
                                tree = LeftBalance(tree);
                                if(tmp_bf == tree->bf || tmp_bf == -tree->bf)
                                    *shorter = 0;
                                else
                                    *shorter = 1;
                                break;
                            case 0:
                                *shorter = 0;
                                tree->bf = -1;
                                break;
                        }
                    }
                    break;
                case -1: //left was high, search and replace maxima in left tree
                    tmp_tree = tree->left_child;
                    while(tmp_tree->right_child)
                        tmp_tree = tmp_tree->right_child;
                    tree->data = tmp_tree->data;
                    tree->left_child = DeleteBSTree(tree->left_child, tmp_tree->data, shorter);
                    switch(tree->bf){
                        case 1:
                            tmp_bf = tree->bf;
                            tree = RightBalance(tree);
                            if(tmp_bf == tree->bf || tmp_bf == -tree->bf)
                                *shorter = 0;
                            else
                                *shorter = 1;
                            break;
                        case -1:
                            *shorter = 1;
                            tree->bf = 0;
                            break;
                        case 0:
                            *shorter = 0;
                            tree->bf = 1;
                            break;
                    }
                    break;
            }
        }
    }
    else if(number < tree->data){
        tree->left_child = DeleteBSTree(tree->left_child, number, shorter);
        if(*shorter){
            switch(tree->bf){
                case 1:
                    tmp_bf = tree->bf;
                    tree = RightBalance(tree);
                    if(tmp_bf == tree->bf || tmp_bf == -tree->bf)
                        *shorter = 0;
                    else
                        *shorter = 1;
                    break;
                case -1:
                    *shorter = 1;
                    tree->bf = 0;
                    break;
                case 0:
                    *shorter = 0;
                    tree->bf = 1;
                    break;
            }
        }
    }
    else{ //number > tree->data
        tree->right_child = DeleteBSTree(tree->right_child, number, shorter);
        if(*shorter){
            switch(tree->bf){
                case 1:
                    *shorter = 1;
                    tree->bf = 0;
                    break;
                case -1:
                    tmp_bf = tree->bf;
                    tree = LeftBalance(tree);
                    else
                    if(tmp_bf == tree->bf || tmp_bf == -tree->bf)
                        *shorter = 0;
                        *shorter = 1;
                    break;
                case 0:
                    *shorter = 0;
                    tree->bf = -1;
                    break;
            }
        }
    }
    return tree;
}
