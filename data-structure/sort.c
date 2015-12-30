/*
	给定N个（长整型范围内的）整数，要求输出从小到大排序后的结果。

	本题旨在测试各种不同的排序算法在各种数据情况下的表现。各组测试数据特点如下：
	数据0：只有1个元素；
	数据1：11个不相同的整数，测试基本正确性；
	数据2：103个随机整数；
	数据3：104个随机整数；
	数据4：105个随机整数；
	数据5：105个顺序整数；
	数据6：105个逆序整数；
	数据7：105个基本有序的整数；
	数据8：105个随机正整数，每个数字不超过1000。
	
	输入格式：
	输入第一行给出正整数N（<= 105），随后一行给出N个（长整型范围内的）整数，其间以空格分隔。

	输出格式：
	在一行中输出从小到大排序后的结果，数字间以1个空格分隔，行末不得有多余空格。

	输入样例：
	11
	4 981 10 -17 0 -20 29 50 8 43 -5
	输出样例：
	-20 -17 -5 0 4 8 10 29 43 50 981
*/ 
#include <stdio.h>
#include <stdlib.h>
#define ElementType int

void Swap ( ElementType *x, ElementType *y ); // Swap

void Bubble_Sort ( ElementType A[], int N );
void Insertion_Sort ( ElementType A[], int N );
void Shell_Sort ( ElementType A[], int N );
void Selection_Sort ( ElementType A[], int N );
// Heap_Sort
void Heap_Sort ( ElementType A[], int N );
void PercDown (ElementType A[], int i , int N); // BuildHeap 
// Merge_Sort
// 递归算法 
void Merge ( ElementType A[], ElementType TmpA[], int L, int R, int RightEnd ); // 核心：有序子列的归并 带倒回 
void MSort ( ElementType A[], ElementType TmpA[], int L, int RightEnd ); // 分治 
void Merge_Sort ( ElementType A[], int N ); // 统一函数接口
// 非递归算法
void Merge1 ( ElementType A[], ElementType TmpA[], int L, int R, int RightEnd ); // 核心：有序子列的归并  不带倒回 
void Merge_Pass ( ElementType A[], ElementType TmpA[], int N, int length );
void Merge_Sort1 ( ElementType A[], int N ); 
 
int main ( void )
{
	int N, i;
	scanf ("%d", &N);
	
	int A[N];
	
	for (i = 0; i < N; i++)
		scanf ("%d", A+i);
		
	Merge_Sort1 (A, N);
	
	for (i = 0; i < N; i++)
	{
		if (i)
			printf (" %d", A[i]);
		else
			printf ("%d", A[i]);
	}
	
	return 0;
} 

void Swap ( ElementType *x, ElementType *y )
{
	ElementType Tmp;
	
	Tmp = *x;
	*x = *y;
	*y = Tmp;
	
	return;
}

// Bubble_Sort
void Bubble_Sort ( ElementType A[], int N )
{  
	int P, i, flag;
	
	for (P = N-1; P >= 0; P--)
	{// 每次循环为Max找到位置 
		flag = 0;
		for (i = 0; i < P; i++)
		{
			if (A[i] > A[i+1])
			{
				Swap (&A[i], &A[i+1]);
				flag = 1;
			}
		}
		if (flag == 0) // 若是没有Swap，则说明排序已完成，跳出循环 
			break;
	}
	
	return;
}

// Insertion_Sort
void Insertion_Sort ( ElementType A[], int N )
{
	int P, i;
	ElementType Tmp;
	
	for (P = 1; P < N; P++)
	{
		Tmp = A[P];
		for (i = P; i > 0 && Tmp < A[i-1]; i--)
		{
			A[i] = A[i-1];
		}
		A[i] = Tmp;
	}
	
	return;
}

// Shell_Sort 
void Shell_Sort ( ElementType A[], int N )
{
	int D, P, i;
	ElementType Tmp;
	
	for (D = N/2; D > 0; D /= 2) // 希尔增量序列 
	{
		for (P = D; P < N; P++) // 插入排序 
		{ // P++的原因：为间距为D的各个子数列排序 
			Tmp = A[P];
			for (i = P; i >= D && Tmp < A[i-D]; i -=D)
			{
				A[i] = A[i-D];
			} 
			A[i] = Tmp;
		}
	}
	
	return;
}

// Selection_Sort
void Selection_Sort ( ElementType A[], int N )
{ // 每次循环找到最小元 
	int i, j, temp;
	
	for (i = 0; i < N-1; i++)
	{
		for (temp = j = i; j < N; j++)
		{
			if (A[temp] > A[j])
				temp = j;
		}
		Swap (&A[i], &A[temp]);
	}
	return; 
}

// Heap_Sort
void Heap_Sort ( ElementType A[], int N )
{
	int i;
	
	for (i = N/2; i >= 0; i--)
		PercDown (A, i , N); 	// 每次调用该函数，总会创建个最大堆，最大堆的元素个数从1or2or3开始，直至N 
	for (i = N-1; i > 0; i--)
	{
		Swap (&A[0], &A[i]);
		PercDown (A, 0 , i);   // 此步骤是第一个for循环的特例，当i = 0时 
	}
	
	return;
}
// BuildHeap 
void PercDown (ElementType A[], int i , int N)
{
	int Parent, Child;
	ElementType Tmp;
	
	Tmp = A[i];
	for (Parent = i; Parent*2+1 < N; Parent = Child)
	{
		Child = Parent * 2 + 1;
		if (Child != N-1 && A[Child] < A[Child+1])
			Child++;
		if (Tmp < A[Child])
			A[Parent] = A[Child];
		else
			break;
	} 
	A[Parent] = Tmp;
	
/*	另一种Code
	int Tmp; 
	for (Parent = i, Tmp = Parent; Parent*2+1 < N; Parent = Child)
	{
		Child = 2 * Parent + 1; // 根结点从0开始 
		if (Child != N-1 && A[Child] < A[Child+1])
			Child++;
		if (A[Child] > A[Tmp])
		{
			Swap (A+Child, A+Tmp);   
			Tmp = Child;
		}
	} 

	每次调用该函数，总会创建个最大堆，最大堆的元素个数从1or2or3开始，直至N 
	那么每次调用，每个子节点都是一个最大堆，因此该最大堆的建立过程类似于最大堆的删除 
*/ 

	return;
} 

// Merge_Sort
// 递归算法 
// 核心：有序子列的归并 带倒回 
void Merge ( ElementType A[], ElementType TmpA[], int L, int R, int RightEnd )
{ // L = 左边起始位置， R = 右边起始位置， RightEnd = 右边终点位置    A[]：原始的待排序列 TmpA[]临时数组 
  // 假设左右两列挨着 
	int NumElements = RightEnd - L + 1;
	int LeftEnd = R - 1;
	int Tmp = L;
	int i;
	// 类似与多项式的加法 
	while (L <= LeftEnd && R <= RightEnd)
	{
		if (A[L] <= A[R])
			TmpA[Tmp++] = A[L++];
		else
			TmpA[Tmp++] = A[R++];
	} 
	while (L <= LeftEnd)
		TmpA[Tmp++] = A[L++];
	while (R <= RightEnd)
		TmpA[Tmp++] = A[R++];
	for (i = 0; i < NumElements; i++, RightEnd--)
		A[RightEnd] = TmpA[RightEnd]; //把数从TmpA倒回A 
	 
	return;	
}
// 分治 
void MSort ( ElementType A[], ElementType TmpA[], int L, int RightEnd )
{
	int Center;
	
	if (L < RightEnd)
	{
		Center = (L + RightEnd) / 2;
		MSort (A, TmpA, L, Center);
		MSort (A, TmpA, Center+1, RightEnd);
		Merge (A, TmpA, L, Center+1, RightEnd);
	}
	
	return; 
}
// 统一函数接口
void Merge_Sort ( ElementType A[], int N )
{
	ElementType *TmpA = (ElementType *)malloc (N * sizeof (ElementType));
	if (NULL == TmpA)
		exit (-1);
	else
	{
		MSort (A, TmpA, 0, N-1);
		free (TmpA);
	}
	
	return;
}

// 非递归算法
// 核心：有序子列的归并  不带倒回 
void Merge1 ( ElementType A[], ElementType TmpA[], int L, int R, int RightEnd )
{
	int NumElements = RightEnd - L + 1;
	int LeftEnd = R - 1;
	int Tmp = L;
	int i;
	
	while (L <= LeftEnd && R <= RightEnd)
	{
		if (A[L] >= A[R])
			TmpA[Tmp++] = A[R++];
		else
			TmpA[Tmp++] = A[L++];
	}
	while (L <= LeftEnd)
		TmpA[Tmp++] = A[L++];
	while (R <= RightEnd)
		TmpA[Tmp++] = A[R++];
	
	return;
}

void Merge_Pass ( ElementType A[], ElementType TmpA[], int N, int length )
{
	int i, j;
	
	for (i = 0; i <= N-2*length; i += 2*length) // Here N-2*length !! Reason：余下部分若 > length,则可归并；若不满足则把A中余下部分倒到TmpA中 
		Merge1 (A, TmpA, i, i+length, i+2*length-1); // 将元素归并到TmpA里面
	if (i+length < N) // 归并最后2个子列
		Merge1 (A, TmpA, i, i+length, N-1); 
	else // 最后只剩1个子列 
		for (j = i; j < N; j++)
			TmpA[j] = A[j];

	return;
}

void Merge_Sort1 ( ElementType A[], int N )
{
	ElementType *TmpA = (ElementType *)malloc (N * sizeof (ElementType));
	int length = 1;
	
	if (NULL == TmpA)
		exit (-1);
	else
	{
		while (length < N)
		{
			Merge_Pass (A, TmpA, N, length); // 执行上次Merge_pass后就已经排序完毕，下次Merge_pass会把TmpA中的数据倒到A中 
			length *= 2;
			Merge_Pass (TmpA, A, N, length);
			length *= 2;
			// 循环内2次Merge_pass保证跳出循环后结果在A中 
		}
		free (TmpA);
	}
	return;
}
