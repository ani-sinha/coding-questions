// remove duplicates from an sorted array in O(1)
#include <stdio.h>

int main()
{
  int arr[] = {2,3,3,3, 4, 5, 10, 10, 15, 15, 15, 20, 30, 40, 60};
  int i, j;
  int len = sizeof(arr)/sizeof(int);

  i = 0;
  for (j=i+1; j< len;j++)
    {
      if (arr[j] != arr[i]) {
	i++;
	arr[i] = arr[j];
      }
    }

  len = i;
  for (i=0;i<=len;i++)
    printf("%d ", arr[i]);
  printf("\n");
}
