#include <stdio.h>

int ejemplo(int x, int y)
{
   int a, b;
   b = 7;
   a = 10;
   return x * b + y + a;
}

int main ()
{
   int result;
   result = ejemplo(1,2);
   printf ("el resultado es: %d \n",result);
   return (result);
}
