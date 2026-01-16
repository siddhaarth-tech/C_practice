/*Exercise 8-7. malloc accepts a size request without checking its plausibility; free believes
that the block it is asked to free contains a valid size field. Improve these routines so they
make more pains with error checking.*/


#include <unistd.h>
#include <stdio.h>

typedef long Align;

union header
{
 struct
 {
  union header *ptr;
  unsigned size;
 } s;
 Align x;
};

typedef union header Header;

static Header base;
static Header *freep=NULL;

#define NALLOC 1024
#define MAX_ALLOC 1024*1024

void kfree(void *ap);

static Header *morecore(unsigned nu)
{
 char *cp;
 Header *up;
 if(nu<NALLOC)
 {
  nu=NALLOC;
 }
 cp=sbrk(nu*sizeof(Header));
 if(cp==(char *)-1)
 {
  return NULL;
 }
 up=(Header *)cp;
 up->s.size=nu;
 kfree((void *)(up+1));
 return freep;
}

void *kmalloc(unsigned nbytes)
{
 Header *p,*prevp;
 unsigned nunits;
 if(nbytes==0||nbytes>MAX_ALLOC)
 {
  return NULL;
 }
 nunits=(nbytes+sizeof(Header)-1)/sizeof(Header)+1;
 if((prevp=freep)==NULL)
 {
  base.s.ptr=freep=prevp=&base;
  base.s.size=0;
 }
 for(p=prevp->s.ptr;;prevp=p,p=p->s.ptr)
 {
  if(p->s.size>=nunits)
  {
   if(p->s.size==nunits)
   {
    prevp->s.ptr=p->s.ptr;
   }
   else
   {
    p->s.size-=nunits;
    p+=p->s.size;
    p->s.size=nunits;
   }
   freep=prevp;
   return (void *)(p+1);
  }
  if(p==freep)
  {
   p=morecore(nunits);
   if(p==NULL)
   {
    return NULL;
   }
  }
 }
}

void kfree(void *ap)
{
 Header *bp,*p;
 if(ap==NULL)
 {
  return;
 }
 bp=(Header *)ap-1;
 if(bp->s.size==0||bp->s.size>MAX_ALLOC)
 {
  write(2,"invalid free\n",13);
  return;
 }
 for(p=freep;!(bp>p&&bp<p->s.ptr);p=p->s.ptr)
 {
  if(p>=p->s.ptr&&(bp>p||bp<p->s.ptr))
  {
   break;
  }
 }
 if(bp+bp->s.size==p->s.ptr)
 {
  bp->s.size+=p->s.ptr->s.size;
  bp->s.ptr=p->s.ptr->s.ptr;
 }
 else
 {
  bp->s.ptr=p->s.ptr;
 }
 if(p+p->s.size==bp)
 {
  p->s.size+=bp->s.size;
  p->s.ptr=bp->s.ptr;
 }
 else
 {
  p->s.ptr=bp;
 }
 freep=p;
}

int main()
{
 char *p;
 p=kmalloc(100);
 if(p==NULL)
 {
  write(2,"alloc failed\n",13);
  return 1;
 }
 p[0]='A';
 p[1]='\0';
 write(1,p,1);
 kfree(p);
 return 0;
}

