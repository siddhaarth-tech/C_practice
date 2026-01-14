/*Exercise 8-2. Rewrite fopen and _fillbuf with fields instead of explicit bit operations.
Compare code size and execution speed.*/

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#define OPEN_MAX 20
#define BUFSIZ 1024
#define PERMS 0666
#define EOF (-1)


typedef struct _iobuf
{
  int cnt;
  char *ptr;
  char *base;
  int fd;

  int readable;
  int writable;
  int unbuf;
  int eof;
  int err;
}FILE;

FILE _iob[OPEN_MAX]={
    { 0, NULL, NULL, 0, 1, 0, 0, 0, 0 }, //stdin
    { 0, NULL, NULL, 1, 0, 1, 0, 0, 0 }, //stdout
    { 0, NULL, NULL, 2, 0, 1, 1, 0, 0 }  //stderr
};

#define stdin  (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])

FILE *fopen(char *name,char *mode);
int _fillbuf(FILE *fp);
int my_getc(FILE *fp);

FILE *fopen(char *name,char *mode)
{
   int fd;
   FILE *fp;

    if (*mode != 'r'&& *mode != 'w' && *mode != 'a')
    {
      return NULL;
    }

    for(fp=_iob;fp<_iob+OPEN_MAX;fp++)
    {
        if (!fp->readable && !fp->writable)
        {
          break;
        }
    }

    if (fp>=_iob+OPEN_MAX)
    {
      return NULL;
    }

    if (*mode=='w')
    {
      fd=creat(name,PERMS);
    }
    else if(*mode=='a')
    {
        fd=open(name, O_WRONLY, 0);
        if (fd == -1)
        {
          fd=creat(name, PERMS);
        }
        lseek(fd,0L,2);
    }
    else
    {
      fd=open(name,O_RDONLY,0);
    }

    if(fd==-1)
    {
      return NULL;
    }

    fp->fd=fd;
    fp->cnt=0;
    fp->base=NULL;
    fp->ptr=NULL;

    fp->readable=(*mode=='r');
    fp->writable=(*mode!='r');
    fp->unbuf=0;
    fp->eof=0;
    fp->err=0;

    return fp;
}

int _fillbuf(FILE *fp)
{
    int bufsize;

    if(!fp->readable || fp->eof || fp->err)
    {
      return EOF;
    }

    bufsize=fp->unbuf?1 : BUFSIZ;

    if(fp->base==NULL)
    {
        fp->base=(char *)malloc(bufsize);
        if(fp->base==NULL)
        {
            fp->err=1;
            return EOF;
        }
    }

    fp->ptr=fp->base;
    fp->cnt=read(fp->fd,fp->ptr,bufsize);

    if(fp->cnt<=0)
    {
        if(fp->cnt==0)
        {
          fp->eof=1;
        }
        else
        {
          fp->err=1;
        }
        fp->cnt=0;
        return EOF;
    }

    fp->cnt--;
    return (unsigned char)*fp->ptr++;
}

int my_getc(FILE *fp)
{
    if(--fp->cnt>=0)
    {
      return (unsigned char)*fp->ptr++;
    }
    else
    {
      return _fillbuf(fp);
    }
}

int main(int argc, char *argv[])
{
    FILE *fp;
    int c;

    if(argc!=2)
    {
      write(2,"need more arguments\n",20);
      return 1;
    }

    fp=fopen(argv[1],"r");
    if(fp==NULL)
    {
      write(2,"error opening file\n",19);
      return 1;
    }

    while((c = my_getc(fp))!=EOF)
    {
      write(1, &c, 1);
    }

    return 0;
}
