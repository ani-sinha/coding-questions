// This solves the 8 queens problem

#include <stdio.h>

int currow = -1;
int row[8];
int down_diag[15];
int up_diag[15];
int colfull[8];

// prints the set of (row, column) where queens are placed.
// for a single result
void printResult() {
  int r, c;
  for (r = 0; r<8; r++) {
    printf("(%d, %d) ", r, row[r] +1 );
  }
  printf("\n");
}


void solve_8queens() {
  int c;
  currow++;

  if (currow == 8) {
    printResult();
    currow--;
    return;
  }
  
  for (c = 0; c< 8; c++) { // trying to find a column where to place a queen
    if (!colfull[c] && !up_diag[row +c] && !down_diag[row-c+7]) {
      // found a place for a queen
      row[currow] = c;
      colfull[c] = 1;
      up_diag[row +c] = 1;
      down_diag[row-c+7] = 1;
      solve_8queens();
      // backtrack
      colfull[c] = 0;
      up_diag[row +c] = 0;
      down_diag[row-c+7] = 0;
    }
  }
  currow--;
  return;
}


int main(int argc, char** argv)
{
  solve_8queens();
  return 0;
}
