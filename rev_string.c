/* reverses the words in the string */

#include <stdio.h>
#include <string.h>

void reverse(int low, int high, char *str) {
  char c;
  while(low < high) {
    c = str[low];
    str[low] = str[high];
    str[high] = c;
    low ++; high--;
  }
  return;
}

int main(int argc, char** argv) {
  char s[] = "We are all Canucks";
  char* iter, *start, *end;
  printf("Original string: %s\n", s);
  reverse(0, strlen(s)-1, s);
  printf("Reversed string: %s\n", s);

  // now resersing the words in the reverded string
  iter = s;
  while(*iter == ' ' && *iter != '\0')
    iter++;
  while(*iter != '\0') {
    start = iter;
    while(*iter != ' ' && *iter != '\0')
      iter++;
    end = iter-1;
    reverse(start-s, end-s, s);
    while(*iter == ' ')
      iter++;
  }
  printf("String with words reserved: %s\n", s);
  return 0;
}
