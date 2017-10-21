#include <stdio.h>

int main(){
   int n=0;
   while(n < 10){
      printf("%d \n",n);
      n++;
      if (n == 3) break;
   }
}
