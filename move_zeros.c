#include <stdio.h>

void move_zeros(int *arr, int sz) {
  int i, j, k;
  
  for (i=0;i<sz;i++) {
    if (arr[i] == 0) {
      k = i;
      for(j=i+1;j<sz;j++)
	arr[k++] = arr[j];
      arr[sz-1] = 0;
      sz--;
    }
  }
}

void move_zeros2(int *a, int sz ) {
  int last_nonzero_seen = 0;
  int i;
  for (i=0;i<sz;i++) {
    if(a[i] !=0) {
      a[last_nonzero_seen++] = a[i];
    }
  }
  for(i=last_nonzero_seen; i< sz;i++)
    a[i] = 0;
}

int main()
{
  int arr[] = {0,1,0,3,12};
  int i, j, k;
  int sz = sizeof(arr)/sizeof(int);
  sz = sizeof(arr)/sizeof(int);
  move_zeros2(arr, sz);

  for(i=0;i<sz;i++)
    printf("%d ", arr[i]);
  printf("\n");
}
