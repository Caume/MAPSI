#include <stdio.h>
void main ()
{
   char *param[2];
   param[0] = "/bin/sh";
   param[1] = NULL; 
   /* execve (const char *filename, char *const argv[], char *const    
      envp[]) */   
   execve(param[0], param, param[1]);
}

