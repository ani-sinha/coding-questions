#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int generate_pivot(int low, int high) {
  int r;
  srand(time(0));
  r = (rand() % (high +1)); // 0 and high
  if (r < low) { // add low as offset then make sure we do not exceed high
   r = r + low;
   if (r > high)
     r = high;
  }
  return r;
}

void swap(int* a, int *b)
{
  int t = *b;
  *b = *a;
  *a = t;
}

int partition(int *a, int low,
	      int high, int pivot_index)
{
  int i;
  int pivot = *( a+pivot_index );
  int pivotloc = low;
  swap( a+pivot_index, a+high );
  for (i = low; i<high; i++) {
    if (a[i] < pivot) {
      if (i != pivotloc)
	swap(a+i, a+pivotloc);
      pivotloc++;
    }
  }
  swap(a+pivotloc, a+high);
  return pivotloc;
}

int kth_largest(int *a, int low, int high, int k)
{

  int pivot_idx, new_pivot_index;

  while(low <= high) {
    pivot_idx = generate_pivot(low, high);

    new_pivot_index = partition(a, low, high, pivot_idx);

    if (new_pivot_index == k-1)
      break;
    else if (new_pivot_index < k-1)
      low = new_pivot_index +1;
    else
      high = new_pivot_index -1;
  }
  return *(a + new_pivot_index);
}

int main(int argc, char **argv)
{

  int a[] = {3, 7, 20, 15,
	     40, 60, 30, 12, 5}; // 3, 5, 7, 12, 15, 20, 30, 40, 60 
  int k ;
  for (k=1; k<10; k++)
    printf("%dth largest in the array is %d\n", k, kth_largest(a, 0, 8, k));
  return 0;
}
