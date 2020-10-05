#include <stdio.h>
#include <stdlib.h>


void swap(int *a, int *b)
{
  int t = *a;
  *a = *b;
  *b = t;
}

int partition (int* a, int low, int high)
{
  int pivotloc = low;
  int pivot = a[low];
  int i;
  for (i = low +1; i <= high; i++) {
    if (a[i] < pivot) {
      swap(&a[++pivotloc], &a[i]);
    }
  }
  swap(&a[pivotloc], &a[low]);
  return pivotloc;
}

void quicksort(int* arr, int low, int high)
{
  int pivot;
  if (low < high) {
    pivot = partition(arr, low, high);
    quicksort(arr, low, pivot-1);
    quicksort(arr, pivot+1, high);
  }
}

int main(int argc, char** argv) {

  int i, sz;
  if (argc == 2) {
    sz = atoi(argv[1]);
  } else
    sz = 20;

  int *arr = malloc (20* sizeof(int));
  for (i=0;i<sz; i++) {
    arr[i] = (rand() + 50) % (500 +1);
  }

  printf("unsorted array is: \n");
  for (i=0; i<sz; i++)
    printf("%d ", arr[i]);

  printf("\n");
  quicksort(arr, 0, sz-1);
  printf("Sorted array is: \n");

  for (i=0; i<sz; i++)
    printf("%d ", arr[i]);
  printf("\n");
}
