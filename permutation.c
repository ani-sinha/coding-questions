// this code generates all permutations of a given string
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

char *final;

void swap(char *s1, char* s2) {
  char t;
  t = *s1;
  *s1 = *s2;
  *s2 = t;
}

void permute (int i, char *s, int nrep)
{
  int k, steps;
  bool backtrack = true;

  if (i > nrep) {
    k = i-1;
    steps = nrep;
    while(steps) {
      if (s[k] != s[k-1]) {
	backtrack = false;
	break;
      }
      k--;
      steps--;
    }
    if (backtrack) {
      return;
    }
  }
  
  if (i == (strlen(s)-1)) {
    //printf("%s\n", s);
    if (strcmp(final, s) < 0)
      strcpy(final, s);
    return;
  }
  
  for (k = i; k < strlen(s); ++k) {
    swap(&s[i], &s[k]);
    permute(i+1, s, nrep);
    swap(&s[i], &s[k]);
  }
  
  return;
}

int main(int argc, char** argv) {
  char str[] = "mmrabbmarrm";
  int sz = sizeof(str) * sizeof(char);
  final = malloc(sz);
  memset(final, sz, 0);
  
  permute(0, str, 3);
  printf("%s\n", final);
}
