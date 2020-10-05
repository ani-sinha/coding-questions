
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NROWS 5
#define NCOLS 5

bool can_be_skipped(int a[][NCOLS], int i, int j) {
  return (i<0 || i>=NROWS || j<0 || j>=NCOLS || a[i][j]!=1 );
}

void DFS(int a[][NCOLS], int i, int j) {
  int dirs[8][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0},
                    {-1,-1}, {1,-1}, {1,1}, {-1,1}};
  int k;

  if (can_be_skipped(a, i, j))
    return;
  
  a[i][j] = -1; // mark it as visited

  for (k=0;k<8;k++) {
      DFS(a, i+dirs[k][0], j+dirs[k][1]);
  } 
}

int find_island(int a[][NCOLS]) {
  int i,j;
  int nislands = 0;
  for (i=0;i<NROWS;i++) {
    for (j=0;j<NCOLS;j++) {
      if (a[i][j] == 1) {
	DFS(a, i,j);
	nislands++;
      }
    }
  }
  return nislands;
}

int main() {
  int nislands = 0, i, j;
  int mat[NROWS][NCOLS] =
    {1, 1, 0, 0, 0,
     0, 1, 0, 0, 1,
     1, 0, 0, 1, 1,
     0, 0, 0, 0, 0,
     1, 0, 1, 0, 1};

  nislands = find_island(mat);

  printf("number of islands is: %d\n", nislands);
  return 0;
}
