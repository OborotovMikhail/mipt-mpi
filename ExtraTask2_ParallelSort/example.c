/* C++ Program for Bitonic Sort. Note that this program
   works only when size of input is a power of 2. */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <omp.h>
  
/*The parameter dir indicates the sorting direction, ASCENDING
   or DESCENDING; if (a[i] > a[j]) agrees with the direction,
   then a[i] and a[j] are interchanged.*/

void swap(int *a, int *b) {
    int t;
    t = *a;
    *a = *b;
    *b = t;
}

void compAndSwap(int *a, int i, int j, int dir)
{
    if (dir==(a[i]>a[j])) {
        swap(&a[i], &a[j]);
    }
}
  
/*It recursively sorts a bitonic sequence in ascending order,
  if dir = 1, and in descending order otherwise (means dir=0).
  The sequence to be sorted starts at index position low,
  the parameter cnt is the number of elements to be sorted.*/
void bitonicMerge(int *a, int low, int cnt, int dir)
{
    if (cnt>1)
    {
        int k = cnt/2;
        for (int i=low; i<low+k; i++)
            compAndSwap(a, i, i+k, dir);
        bitonicMerge(a, low, k, dir);
        bitonicMerge(a, low+k, k, dir);
    }
}
  
/* This function first produces a bitonic sequence by recursively
    sorting its two halves in opposite sorting orders, and then
    calls bitonicMerge to make them in the same order */
void bitonicSort(int *a,int low, int cnt, int dir)
{
    if (cnt>1)
    {
        int k = cnt/2;
  
        // sort in ascending order since dir here is 1
        bitonicSort(a, low, k, 1);
  
        // sort in descending order since dir here is 0
        bitonicSort(a, low+k, k, 0);
  
        // Will merge whole sequence in ascending order
        // since dir=1.
        bitonicMerge(a,low, cnt, dir);
    }
}
  
/* Caller of bitonicSort for sorting the entire array of
   length N in ASCENDING order */
void sort(int *a, int N, int up)
{
    bitonicSort(a, 0, N, up);
}
  
// Driver code
int main()
{
    //int a[]= {3, 7, 4, 8, 6, 2, 1, 5};
    int N = 8;

    int n = 8;
    int* a = (int*)malloc(n * sizeof(int));

    for (size_t i = 0; i < n; i++) {
        a[i] = i + 1;
    }

    if (n > 1) {
        size_t i;
        for (i = 0; i < n - 1; i++) {
            size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
            int t = a[j];
            a[j] = a[i];
            a[i] = t;
        }
    }


    printf("Unsorted array: \n");
    for (int i=0; i<N; i++)
        printf("%d ", a[i]);
    printf("\n");
  
    int up = 1;   // means sort in ascending order
    sort(a, N, up);
  
    printf("Sorted array: \n");
    for (int i=0; i<N; i++)
        printf("%d ", a[i]);
    printf("\n");

    return 0;
}