//Exercise 5-9. Rewrite the routines day_of_year and month_day with pointers instead of indexing.

#include<stdio.h>

int day_of_year(int day,int month,int year);
int month_day(int year,int yearday,int *d,int *m);

static char daytab[2][13]={{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};
int main()
{
  int day,month,year;
  printf("finding the day of the year ...\n");
  printf("enter the day : ");
  scanf("%d",&day);
  printf("enter the month : ");
  scanf("%d",&month);
  printf("enter the year : ");
  scanf("%d",&year);
  
  int result = day_of_year(day,month,year);
  if(result==-1)
  {
    printf("invalid input\n");
  }
  else
  {
    printf("Day of the year is %d\n",result);
  }
  
  int m,d;
  int y,yd;
  printf("finding day and month...\n");
  printf("enter the year : ");
  scanf("%d",&y);
  printf("enter the year day: ");
  scanf("%d",&yd);
  
  result=month_day(y,yd,&d,&m);
  if(result==-1)
  {
    printf("invalid input\n");
  }
  else
  {
    printf("the day is %d and the month is %d\n",d,m);
  }
  return 0;
}


int month_day(int year,int yearday,int *day,int *month)
{
  int leap=((year%4==0 && year%100!=0) || year%400==0) ? 1 : 0;
  int maxday = leap ? 366 : 365;
  
  if(yearday<1 || yearday>maxday)
  {
    return -1;
  }
  
  int i=1;
  while(yearday>*(*(daytab+leap)+i) )
  {
    yearday=yearday-*(*(daytab+leap)+i);
    i++;
  }
  *day=yearday;
  *month=i;
  return 0;
}

int day_of_year(int day,int month,int year)
{
  int leap;
  if(month<1 || month>12)
  {
    return -1;
  }
  
  leap=((year%4==0 && year%100!=0) || year%400==0) ? 1 : 0;
  
  if(day<1 || day>(*(*(daytab+leap)+month)) )
  {
    return -1;
  }
  
  for(int i=1;i<month;i++)
  {
    day=day+(*(*(daytab+leap)+i));
  }
  return day;
}