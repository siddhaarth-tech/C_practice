/*Exercise 8-8. Write a routine bfree(p,n) that will free any arbitrary block p of n characters
into the free list maintained by malloc and free. By using bfree, a user can add a static or
external array to the free list at any time.*/


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

void kfree(void *ap);

static Header *morecore(unsigned nu)
{
 char *cp;
 Header *up;
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
   if((p=morecore(nunits))==NULL)
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

void bfree(void *p,unsigned n)
{
 Header *hp;
 unsigned nunits;
 if(n<sizeof(Header))
 {
  return;
 }
 nunits=n/sizeof(Header);
 hp=(Header *)p;
 hp->s.size=nunits;
 kfree((void *)(hp+1));
}

int main()
{
 static char buffer[4096];
 kmalloc(1);
 bfree(buffer,4096);
 char *p=kmalloc(100);
 if(p)
 {
  write(1,"memory allocated using bfree\n",29);
 }
 return 0;
}
