#include <stdio.h>
#include <limits.h>

int arr[]= {-1, -5, 2, 5, 0, -4, 8, -11, -20 };
int ar2[] = {-1, -2, -3, -4, -5};

int max(int a, int b)
{
  return a> b? a:b;
}
int max_subarray1() {
  int i, ssum = 0;
  int max_sum = INT_MIN;
  for(int i =0; i< (sizeof(arr)/sizeof(arr[0])); i++) {
    ssum += arr[i];
    if (ssum < 0)
      ssum = 0;
    else if (max_sum < ssum)
      max_sum = ssum;
  }
  return max_sum;
}

int max_subarray2() {
  int max_sum = INT_MIN;
  int cur_sum = 0;
  for(int i =0; i< (sizeof(arr)/sizeof(arr[0])); i++) {
    cur_sum = max(arr[i], arr[i]+cur_sum);
    max_sum = max(max_sum, cur_sum);
  }
  return max_sum;
}

int main(int argc, char ** argv) {
  int max_sum;
  max_sum = max_subarray2();
  printf("result: %d\n", max_sum);
  max_sum = max_subarray1();
  printf("result: %d\n", max_sum);

  return 0;
}
