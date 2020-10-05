// binary to gray code and gray to binary conversion.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char xor(char a, char b) {
  return (a == b) ? '0':'1';
}

char flip(char a) {
  return a == '0' ? '1':'0';
}

/* 4 bit Binary b3 b2 b1 b0 to gray g3 g2 g1 g0 :
g3 = b3
g2 = b3 XOR b2
g1 = b2 XOR b1
g0 = b1 XOR b0
*/
void binary2gray(char* binary, char* gray) {
  int i;
  gray[0] = binary[0];

  for (i =1; i < strlen(binary); ++i) {
    gray[i] = xor(binary[i], binary[i-1]);
  }

  printf("gray code for binary %s is %s\n", binary, gray);
}

/* 4 bit gray g3 g2 g1 g0 to binary b3 b2 b1 b0 :
b3 = g3
b2 = g2 ==0 ? b3:flip(b3)
b1 = g1 ==0 ? b2:flip(b2)
b2 = g0 ==0 ? b1:flip(b1)
*/
void gray2binary(char * binary, char* gray) {
  int i;
  binary[0] = gray[0];
  for (i = 1; i < strlen(gray); i++) {
    binary[i] = (gray[i] == '0') ? binary[i-1]:flip(binary[i-1]);
  }
  printf("binary code for gray %s is %s\n", gray, binary);
}


int main(int argc, char **argv) {
  char binary[] = "101110011010111";
  char *gray = malloc(sizeof(binary));

  binary2gray(binary, gray);
  gray2binary(binary, gray);
}
