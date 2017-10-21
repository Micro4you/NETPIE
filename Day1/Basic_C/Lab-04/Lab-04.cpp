#include <stdio.h>

int main(){
    int n=15;
    scanf("%d",&n);
    switch (n) {
    case 1 :
        printf("Select 1");
        break;
    case 2 :
        printf("Select 2");
        break;
    default :
        printf("default");
        break;
    }
}
