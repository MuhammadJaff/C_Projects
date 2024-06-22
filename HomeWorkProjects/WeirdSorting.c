#include <stdio.h>

int iteration(int *arr,int size,int round);
int processIt(int *arr,int size,int round);
int recursion(int *arr,int size,int round);

// in this program, we start by taking a number(n), then make an array from 1 to n
// then sort from left to right, right to left one by one until there is only one number left
// then return that number.

// and we did it with 2 ways, by iteration and recursion.

int main(){
    int num,i,result;
    printf("Bismillah\n");
    printf("Enter a number:");
    scanf("%d",&num);
    if(num>1){
      int arr[num];
      for(i = 0;i < num;i++){
        arr[i] = i + 1;
      }
      result = iteration(arr,num,0); // by Iteration
      // result = recursion(arr,num,0); // by Recursion
    }else return 1;
   

    printf("\nNumber is %d  ",result);
    return 0;
}

int recursion(int *arr,int size,int round){
  // break case:
  if(size==1)
    return arr[0];

    if(size>1){
        size = processIt(arr,size,round);
        round++;
        recursion(arr,size,round);
    }
}

int iteration(int *arr,int size,int round){
    while(size>1){
        size = processIt(arr,size,round);
        round++;
    }
    return arr[0]; 
}

// Process It!
int processIt(int *arr,int size,int round){
    int newSize = size/2,i,j; 
      int newArr[size];
        if(round % 2 == 0){
          for(i=0;i<size;i++){
            newArr[(i/2)] = arr[i];
          }
            round++;
        }else{
          for(i=size-1,j=i-1;j>=0;i--){
            if(i % 2 == 1){ 
              newArr[(int)(i/2)] = arr[j];
              j-=2;
           }
          }
            round++;
        }
        for (i = 0; i < newSize; i++) {
          arr[i] = newArr[i];
        }
        printf("\n");
        printf("After round %d, arr = [", round);
        for (i = 0; i < newSize; i++) {
          printf("%d ", arr[i]);
        }
        printf("];");
      return newSize;
}
// Alhamdulillah