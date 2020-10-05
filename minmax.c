#include <stdio.h>

// This program finds the minumum and maximum values of
// an array of integers in O(n) time.

int min(int a, int b) {
  return (a < b)? a : b ;
}

int max(int a, int b) {
  return (a > b)? a : b ;
}

int main() {
  int local_min, local_max, global_min, global_max;
  int data[] = {20, 1, 60, -5, 100, 80, 60, -10, 200, 150, 201};
  int sz_data = sizeof(data)/sizeof(int);
  
  global_min = min(data[0], data[1]);
  global_max = max(data[0], data[1]);

  for (int i=2; i+1 < sz_data; i+=2) {
    local_min = min(data[i], data[i+1]);
    local_max = max(data[i], data[i+1]);
    global_min = min(global_min, local_min);
    global_max = max(global_max, local_max);
  }
  if (sz_data % 2) {
    global_min = min(global_min, data[sz_data-1]);
    global_max = max(global_max, data[sz_data-1]);
  }

  printf("max: %d, min: %d\n", global_max, global_min);
}
