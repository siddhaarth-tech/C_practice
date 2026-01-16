/*Exercise 8-6. The standard library function calloc(n,size) returns a pointer to n objects of
size size, with the storage initialized to zero. Write calloc, by calling malloc or by
modifying it.*/

  #include <stdio.h>
  #include <stdlib.h>

  void *my_calloc(unsigned n,unsigned size)
  {
      unsigned total_bytes;
      unsigned i;
      char *p;

      total_bytes=n*size;

      p=(char *)malloc(total_bytes);
      if(p==NULL)
      {
          return NULL;
      }

      for(i=0;i<total_bytes;i++)
      {
          p[i]=0;
      }

      return (void *)p;
  }

  int main()
  {
      int *arr;
      int i;

      arr=(int *)my_calloc(5,sizeof(int));
      if(arr==NULL)
      {
          printf("Memory allocation failed\n");
          return 1;
      }

      for(i=0;i<5;i++)
      {
          printf("%d ",arr[i]);
      }
      printf("\n");

      free(arr);
      return 0;
  }
