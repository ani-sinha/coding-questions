#include <string.h>
#include <stdio.h>
void swap(char *a, char *b)
{
  char t;
  t = *a;
  *a = *b;
  *b = t;
}

void reverse_str(char *s) {
  int len = strlen(s), i, j;
  for (i = 0, j = len-1; i< j; i++, j--) {
    swap(s+i, s+j);
  }
  return;
}

int main(int argc, char **argv) {
  char str[] = "hello";
  reverse_str(str);
  printf("%s\n", str);
  return 0;
}
