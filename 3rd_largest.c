#include <stdio.h>
#include <limits.h>

int main()
{
  int arr[] = {18, 4, 3, 15, 45, 50, 30, 1, 16, 11, 9};
  int sz = sizeof(arr)/sizeof(int);
  int first = INT_MIN;
  int second = INT_MIN;
  int third = INT_MIN;
  int i;

  for (i=0; i<sz; i++) {
    if (arr[i] > first) {
      third = second;
      second = first;
      first = arr[i];
    } else if (arr[i] > second) {
      third = second;
      second = arr[i];
    } else if (arr[i] > third) {
      third = arr[i];
    }
  }

  printf("first: %d second: %d third: %d\n", first, second, third);
  return 0;
}
