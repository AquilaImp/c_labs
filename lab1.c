#include <stdio.h>
 int main()
 {
  float a,b;
printf("Enter a: ");
scanf("%f",&a);
printf("Enter b: ");
scanf("%f",&b);
int A=(int ) a;
int B=(int) b;
int s = 0;
while (A!=0)
{
s = s+A%10;
A = A/10;
}
int c = 0;
while (B>0)
{
c = c+B%10;
B = B/10;
}
if (s<c) printf("%f\n",((float)s)/b);
else printf("%f\n",((float)s)/a);
return 0;
}