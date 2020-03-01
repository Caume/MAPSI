#include <stdio.h>
void function(int a, int b, int c) {
   char buffer1[4];
   char buffer2[4];
   unsigned long *ret;
   ret = (unsigned long) buffer1 + 8; 
   *ret += 7;                         
   printf("valores de a, b y c: %d %d %d\n",a,b,c);
}
int main() {
  int x;
  x = 0;
  function(1,2,3);
  x = 1;
  printf("Valor de x: %d \n",x);
  return(0);
}

