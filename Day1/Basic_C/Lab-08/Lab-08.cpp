#include <stdio.h>

void helloWorld(){
   printf("Hello World\n");
   printf("Test \n");
}

void displayNum(int inputNum){
   printf("Input number is : %d \n",inputNum);
}

int sum(int num1, int num2){
   int output;
   output = num1 + num2;
   return output;
}

int main(){
   displayNum(sum(9,7));

}
