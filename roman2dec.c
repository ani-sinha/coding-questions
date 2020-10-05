#include <stdio.h>
#include <string.h>
#include <assert.h>

int symbols[][2] = {{'M', 1000}, {'D', 500}, {'C', 100},
		   {'L', 50}, {'X', 10}, {'V', 5}, {'I', 1}};

#define SYM_SIZE 7

int find_val(char sym) {
	for (int i=0; i < SYM_SIZE; i++) {
		if(symbols[i][0] == sym)
			return symbols[i][1];
	}
	return -1;
}

int main()
{
  char *roman = "CMXCIV";
  int i, val=0;
  char symbol_curr, symbol_next;
  int val_curr, val_next;
  int len = strlen(roman);
  
  val = find_val(roman[len-1]);
  
  for (i = len-2; i >= 0; i--) {
	  symbol_curr = roman[i];
	  symbol_next = roman[i+1];
	  val_curr = find_val(symbol_curr);
	  val_next = find_val(symbol_next);

	  //printf("current sym: %c, %d ", symbol_curr, val_curr);

	  assert(val_curr != -1);
	  assert(val_next != -1);
	  
	  if (val_curr > val_next)
		  val += val_curr;
	  else
		  val -= val_curr;
  }

  printf("\nval: %d\n", val);
  
}
