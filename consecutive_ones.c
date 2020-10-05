#include <stdio.h>

// find the size of the largest continous subarray of 1s when at most
// k 0 bits are allowed to be flipped

int main()
{
  int i, j=0;
  int arr[] = {1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0};
  int sz = sizeof(arr) / sizeof(int);
  int k = 2;
  for (i=0, j=0;i<sz,j<sz;j++) {
    if (!arr[j])
      k--;
    if (k < 0) {
      if (!arr[i])
	k++;
      i++;
    }

  }
  printf("%d\n", j-i);
}
