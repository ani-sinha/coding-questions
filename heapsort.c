// This file implements heap sort.
#include <stdio.h>
#include <stdlib.h>


void swap(int* a, int* b) {
  int t = *a;
  *a = *b;
  *b = t;
}

void heapify(int arr[], int sz, int i) {
  int l = 2*i +1;
  int r = 2*i + 2;
  int max = i;

  if (l < sz && arr[l] > arr[max])
    max = l;
  
  if (r < sz && arr[r] > arr[max])
    max = r;

  if (i != max) {
    swap(&arr[i], &arr[max]);
    heapify(arr, sz, max);
  }
}

int random_int(int lower, int upper) {
  return (rand() + lower) % (upper + 1);
}

int main(int argc, char **argv) {
  int arr[20];
  int index = 0, sz = 20;
  // randomly populate the array

  int lower = 10;
  int upper = 250;
  
  
  printf("original array is : \n");
  while( index < 20) {
    arr[index] = random_int(lower, upper);
    printf("%d ", arr[index++]);fflush(stdout);
  }
  printf("\n");
  for (index = sz/2 -1; index>=0; index--)
    heapify(arr, sz, index);
  
  for (index = sz-1; index>=0; index--) {
    swap(&arr[0], &arr[index]);
    heapify(arr, index, 0);
  }
  
  printf("sorted array is : \n");
  for (index = 0; index < 20; index++) {
    printf("%d ", arr[index]);
  }
  printf("\n");
}
