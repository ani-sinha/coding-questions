#include <stdio.h>

int main(int argc, char **argv) {
	//int 5;
	for (int i = -5; i< 10; i++) 
	printf("i:%d; %d\n", i, i&7);
	return 0;
}



struct alloc_unit {
  char mem[250];
  int req_id;
  struct alloc_unit *next;
};

struct alloc_units {
  int next_free;
  
  struct alloc_unit[100];
  struct alloc_unit *next;
};

struct alloc_units *head;

(sz / 250) +1

