//Exercise 7-3. Revise minprintf to handle more of the other facilities of printf.

#include <stdio.h>
#include <stdarg.h>

void minprintf(char *fmt, ...)
{
  va_list ap;
  char *p;

  va_start(ap, fmt);

  for(p=fmt;*p;p++) 
  {
    if(*p!='%') 
    {
      putchar(*p);
      continue;
    }

    switch (*++p) 
    {
      case 'd':
        printf("%d", va_arg(ap, int));
        break;

      case 'f':
        printf("%f", va_arg(ap, double));
        break;

      case 's':
        printf("%s", va_arg(ap, char *));
        break;

      case 'c':  
        putchar(va_arg(ap, int));
        break;

      case 'u':  
        printf("%u", va_arg(ap, unsigned int));
        break;

      case 'x':
        printf("%x", va_arg(ap, unsigned int));
        break;

      case 'o':
        printf("%o", va_arg(ap, unsigned int));
        break;

      case '%': 
        putchar('%');
        break;

      default: 
        putchar(*p);
        break;
     }
  }
  va_end(ap);
}

int main()
{
    minprintf("integer: %d\n", 10);
    minprintf("float: %f\n", 3.14);
    minprintf("char: %c\n", 'A');
    minprintf("string: %s\n", "Hello");
    minprintf("unsigned: %u\n", 300);
    minprintf("hex: %x\n", 255);
    minprintf("octal: %o\n", 255);
    minprintf("100%% completed\n");

    return 0;
}


