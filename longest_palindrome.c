#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

int scan_from_centre(char *s, int len, int left, int right) {
  while(left >= 0 && right < len && s[left] == s[right]) {
    left--;
    right++;
  }
  return right-left-1;
}

char* substr(char *s, int start, int end) {
  char *sub;
  int i = start;
  int pos = 0;

  assert(start <= end);
  sub = malloc((end-start+2) * sizeof(char));

  while(i <= end) {
    sub[pos++] = s[i++];
  }
  sub[i] = '\0';
  return sub;
}

char* longest_palindrome(char *s) {
  int max1, max2, i;
  int max, left, right;
  int len = strlen(s);

  left = 0;
  right = 0;
  
  for (i=0; i < len; i++) {
    max1 = scan_from_centre(s, len, i, i);
    max2 = scan_from_centre(s, len, i, i+1);
    max = max1 > max2? max1 : max2;
    if (max > right - left) {
      left = i - (max-1)/2;
      right = i + (max)/2;
    }
  }
  //  printf("%d %d\n", left, right);
  return substr(s, left, right);
}

int main() {
  char s[] = "forgeeksskeegfor";
  char *lpalin = longest_palindrome(s);
  printf("%s\n", lpalin);
  free(lpalin);
  return 0;
}
