#include <stdio.h>
#include <limits.h>

int main()
{
  int arr[] = {7,1,5,3,6,4};
  int i, profit;
  int max_profit = 0;
  int min_price = INT_MAX;
  for (i=0; i< sizeof(arr)/sizeof(int); i++) {
    if (arr[i] < min_price)
      min_price = arr[i];
    else {
      profit = arr[i] - min_price;
      if (max_profit < profit)
	max_profit = profit;
    }
  }
  printf("max_profit: %d\n", max_profit);
}
