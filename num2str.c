#include <stdio.h>
#include <string.h>

char hexc[] = {'A', 'B', 'C', 'D', 'E', 'F'};

void revstr(char *s)
{
  int l = strlen(s);
  int i = 0, j = l-1;
  char c;
  for (i=0; i< j; i++, j--) {
    c = s[i];
    s[i] = s[j];
    s[j] = c;
  } 
}

// converts a string s in base b1 to a string ss in base b2
void convert_base(char *s, int b1, char *ss, int b2) {
  int num = 0, i=0, d;
  while(s[i] != '\0') {
    num = num * b1 + '0' + s[i++];
  }
  i = 0;
  printf("%s in base %d expressed in decimal is : %d\n", s, b1, num);
  while(num) {
    d = num %b2;
    ss[i++] = (d > 9) ? hexc[d - 10]: (d + '0');
    num = num / b2;
  }
  ss[i] = '\0';
  revstr(ss);
}


int main() {
  char s[10], ss[10];
  char *binn = "1011001\0";
  int num = 12345;
  int d, i= 0;
  char cd;
  while(num) {
    d = num %10;
    cd = d + 48;
    s[i++] = cd;
    num = num / 10;
  }
  s[i] = '\0';
  revstr(s);
  printf("string rep of the number is %s\n", s);
  for (i=0; s[i] != '\0'; i++) {
    num = num * 10 + s[i] - '0';
  }
  printf("original number: %d\n", num);
  convert_base(binn, 2, ss, 16);
  printf("string binn in base 2: %s, in base 16 : %s\n", binn, ss);
  
  return 0;
}
