#include <stdio.h>
#include <string.h>
#define SIZE 7

// int bubble(int [],int n);
int insertion(int [],int n);

int main(){
    int arr[SIZE] = {3,6,1,2,5,8,4};
    printf("Before sort: \n");
    for(int i = 0; i < 7; i++){
        printf("%d ",arr[i]);
    }
    printf("\nAfter sort: \n");

    //second part BUBBLE SORT
    insertion(arr,SIZE);
    // bubble(arr,SIZE);
    for(int i = 0; i < 7; i++){
        printf("%d ",arr[i]);
    }
    return 0;
}
int insertion(int b[],int size){
    int value,i,j;
    for(i=1;i<size;i++){
        value = b[i];
        j=i-1;
        while((j>=0)&& b[j]>value){
            b[j+1] =b[j];
            j--;
        }
        // later take a look again
        b[j+1] = value;
    }
}