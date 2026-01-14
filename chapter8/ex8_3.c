/*Exercise 8-3. Design and write _flushbuf, fflush, and fclose.*/

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
} FILE;

FILE _iob[OPEN_MAX] =
{
    { 0, NULL, NULL, 0, 1, 0, 0, 0, 0 },
    { 0, NULL, NULL, 1, 0, 1, 0, 0, 0 },
    { 0, NULL, NULL, 2, 0, 1, 1, 0, 0 }
};

#define stdin  (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])

FILE *fopen(char *name, char *mode);
int _fillbuf(FILE *fp);
int _flushbuf(int c, FILE *fp);
int fflush(FILE *fp);
int fclose(FILE *fp);
int my_getc(FILE *fp);
int my_putc(int c, FILE *fp);

FILE *fopen(char *name, char *mode)
{
    int fd;
    FILE *fp;

    if (*mode != 'r' && *mode != 'w' && *mode != 'a')
    {
        return NULL;
    }

    for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
    {
        if (!fp->readable && !fp->writable)
        {
            break;
        }
    }

    if (fp >= _iob + OPEN_MAX)
    {
        return NULL;
    }

    if (*mode == 'w')
    {
        fd = creat(name, PERMS);
    }
    else if (*mode == 'a')
    {
        fd = open(name, O_WRONLY, 0);
        if (fd == -1)
        {
            fd = creat(name, PERMS);
        }
        lseek(fd, 0L, 2);
    }
    else
    {
        fd = open(name, O_RDONLY, 0);
    }

    if (fd == -1)
    {
        return NULL;
    }

    fp->fd = fd;
    fp->cnt = 0;
    fp->base = NULL;
    fp->ptr = NULL;
    fp->readable = (*mode == 'r');
    fp->writable = (*mode != 'r');
    fp->unbuf = 0;
    fp->eof = 0;
    fp->err = 0;

    return fp;
}

int _fillbuf(FILE *fp)
{
    int bufsize;

    if (!fp->readable || fp->eof || fp->err)
    {
        return EOF;
    }

    bufsize = fp->unbuf ? 1 : BUFSIZ;

    if (fp->base == NULL)
    {
        fp->base = (char *)malloc(bufsize);
        if (fp->base == NULL)
        {
            fp->err = 1;
            return EOF;
        }
    }

    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);

    if (fp->cnt <= 0)
    {
        if (fp->cnt == 0)
        {
            fp->eof = 1;
        }
        else
        {
            fp->err = 1;
        }
        fp->cnt = 0;
        return EOF;
    }

    fp->cnt--;
    return (unsigned char)*fp->ptr++;
}

int _flushbuf(int c, FILE *fp)
{
    int bufsize;
    int n;

    if (!fp->writable || fp->err)
    {
        return EOF;
    }

    bufsize = fp->unbuf ? 1 : BUFSIZ;

    if (fp->base == NULL)
    {
        fp->base = (char *)malloc(bufsize);
        if (fp->base == NULL)
        {
            fp->err = 1;
            return EOF;
        }
        fp->ptr = fp->base;
        fp->cnt = bufsize;
    }

    n = fp->ptr - fp->base;
    if (n > 0)
    {
        if (write(fp->fd, fp->base, n) != n)
        {
            fp->err = 1;
            return EOF;
        }
    }

    fp->ptr = fp->base;
    fp->cnt = bufsize;

    if (c != EOF)
    {
        fp->cnt--;
        *fp->ptr++ = c;
    }

    return c;
}

int fflush(FILE *fp)
{
    if (fp == NULL)
    {
        return 0;
    }

    if (fp->writable)
    {
        return _flushbuf(EOF, fp);
    }

    return 0;
}

int fclose(FILE *fp)
{
    int r;

    r = 0;

    if (fp->writable)
    {
        r = fflush(fp);
    }

    if (fp->base != NULL)
    {
        free(fp->base);
    }

    fp->cnt = 0;
    fp->ptr = NULL;
    fp->base = NULL;
    fp->readable = 0;
    fp->writable = 0;
    fp->eof = 0;
    fp->err = 0;

    return close(fp->fd) | r;
}

int my_getc(FILE *fp)
{
    if (--fp->cnt >= 0)
    {
        return (unsigned char)*fp->ptr++;
    }
    else
    {
        return _fillbuf(fp);
    }
}

int my_putc(int c, FILE *fp)
{
    if (--fp->cnt >= 0)
    {
        *fp->ptr++ = c;
        return c;
    }
    else
    {
        return _flushbuf(c, fp);
    }
}

int main()
{
    int c;

    while ((c = my_getc(stdin)) != EOF)
    {
        my_putc(c, stdout);
    }

    fclose(stdout);
    return 0;
}
