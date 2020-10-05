#include <stdio.h>
#include <string.h>

int my_strstr(char *needle, char *haystack, int n, int h) {
  int ni, hi;
  int start, len;
  ni = 0, hi = 0;
  while(hi < h) {
    while((haystack[hi] != needle[ni]) && hi < h)
      hi++;
    if (hi >= h)
      break;
    start = hi;
    len = 0;
    while((haystack[hi] == needle[ni]) && ni < n && hi < h){
      hi++;
      ni++;
      len++;
    }
    if (ni == n)
      return start;
    else if (len != 0){
      hi = hi - len + 1;
      ni = 0;
    }
  }
  return -1;
}
int main(int argc, char **argv)
{
  char * needle = "dog";
  char * haystack = "a quick brown fox jumps over the lazy dog";
  printf("strings needle: %s, haystack: %s\n", needle, haystack);
  printf("\no/p from strstr: %d\n", my_strstr(needle, haystack, strlen(needle), strlen(haystack)));
}
