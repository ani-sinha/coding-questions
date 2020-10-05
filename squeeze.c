//

#include <stdio.h>
#include <string.h>

void shift(char *s, int pos ) {
  int i;

  if (s[pos] == '\0')
    return;
  
  i = pos+1;

  while (s[i] != '\0') {
    s[i-1] = s[i];
    i++;
  }
  s[i-1] = '\0';
  return;
}

void sqeeze(char *s, char c) {
  int i=0;
  while(s[i] != '\0') {
    if (s[i] == c) {
      shift(s, i);
    }
    i++;
  }
  return;
}

void sqeeze2(char *s, char c) {
  int i, j;
  int len = strlen(s);
  for (i=0,j=0; i < len; i++) {
    if (s[i] != c) {
      s[j++] = s[i];
    }
  }
  s[j] = '\0';
}


void sqeeze3(char *s, char c)
{
  int i, j;
  int len = strlen(s);
  i=0;
  for(j=0;j<len;j++) {
    if (s[j] != c)
      {
	s[i] = s[j];
	i++;
      }
  }
  s[i] = '\0';
}

int main(int argc, char **argv) {
  char str[] = "hello world";
  char str2[] = "a quick brown fox jumped over the lazy dog";
  printf("original string: %s\n",str );
  sqeeze2(str, 'o');
  printf("sqeezed string: %s\n", str);
  sqeeze2(str2, 'o');
  printf("sqeezed string: %s\n", str2);
  return 0;
}



