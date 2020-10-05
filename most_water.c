#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int min(int a, int b)
{
  return a < b? a:b;
}
int max(int a, int b)
{
  return a > b? a:b;
}

int most_water(int *a, int sz)
{
  int l = 0, r = sz-1;
  int max_area = 0;

  while(l < r) {
    max_area = max(max_area, (min(a[l], a[r]) * ( r - l)));
    if (a[l] < a[r])
      l++;
    else
      r--;
  }
  return max_area;
}

int trap_water(int *h, int sz) {
  int *left_max = (int*) malloc(sz * sizeof(int));
  int *right_max = (int*) malloc(sz * sizeof(int));
  int i, total_water = 0;
  (void*) memset(left_max, 0, sz);
  (void*) memset(right_max, 0, sz);
  left_max[0] = h[0];
  right_max[sz-1] = h[sz-1];
  for (i=1; i<sz; i++)
    left_max[i] = max(h[i], left_max[i-1]);
  for (i=sz-2;i>=0; i--)
    right_max[i] = max(h[i], right_max[i+1]);
  for (i=0;i<sz; i++)
    total_water += min(left_max[i], right_max[i]) - h[i];

  return total_water;
}

int main(int argc, char **argv)
{
  int arr[] = {1,8,6,2,5,4,8,3,7};
  printf("\nmost_water: %d\n", most_water(arr, 9));
  printf("\ntrap_water: %d\n", trap_water(arr, 9));
}
