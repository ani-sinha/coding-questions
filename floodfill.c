#include <stdio.h>

void DFS(int image[][], int nrow, int ncol, int r, int c, int col, int newcol)
{
  if (image[r][c] == col)
    image[r][c] = newcol;

  if (r > 0)
    DFS(image, nrow, ncol, r-1, c, col, newcol);
  if (r < nrow - 1)
    DFS(image, nrow, ncol, r+1, c, col, newcol);
  if (c > 0)
    DFS(image, nrow, ncol, r, c-1, col, newcol);
  if (r < ncol - 1)
    DFS(image, nrow, ncol+1, r, c+1, col, newcol);
}

void floodfill(int image[][], int nrow, int ncol, int r, int c, int newcol)
{
  int color = image[r][c];
  DFS(image, nrow, ncol, r, c, color, newcol );
}

