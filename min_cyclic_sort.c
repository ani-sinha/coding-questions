#include <stdio.h>

// This finds the minimum element in a cyclically sorted array.
// For example, for the following array,
//  56, 80, 20, 35, 45, 50, 55
// the result returned should be 20.

// takes an arrray of cyclically sorted integers and it's size
// returns the index of the smallest key if found.
// returns -1 in case of error.
int search (int arr[], int sz);

int main(int argc, char **argv) {
  int arr[] = {56, 80, 90, 95, 100, 110, 150, 20, 35, 45, 50, 55};
  int sz;
  int index;
  sz = sizeof(arr) /sizeof (int);
  index = search (arr, sz);
  if (index != -1) {
    printf("index of the smallest element is : %d and it's value is %d\n", index, arr[index]);
  }
  return 0;
}

int search (int arr[], int sz)
{
  int low, mid, high;
  low = 0; high = sz-1;
  while (low < high) {
    mid = low + (high-low)/2;
    if (arr[mid] > arr[high]) {
      low = mid +1;
    }
    else {
      high = mid;
    }
  }
  //printf("low: %d, mid: %d, high: %d\n", low, mid, high);
  return low;
}
