#include <stdio.h>
#include <string.h>
#include <math.h>
#define SIZE 22

int array[SIZE] = {2,3,35,5,1,23,1,17,83,3,67,29,74,38,14,56,47,33,63,125,341,213};

void swap(int size,int last){
    int left,right,temp;
    left = size*2+1;
    right = size*2+2;
    temp = array[size];
    if(left <= last && right <= last){
        if(array[left]>array[right] && array[size]<array[left]){
            array[size] = array[left];
            array[left] = temp;
            swap(left,last);
        }else if(array[left]<array[right] && array[size]<array[right]){
            array[size] = array[right];
            array[right] = temp;
            // go down
            swap(right,last);
        }
    }else if(left <= last && array[size]<array[left]){
        array[size] = array[left];
        array[left] = temp;
    }
}

void heapify(int size){
    int temp = array[size];
    // SWAP 
    swap(size,SIZE-1);

    if(size>0) heapify(--size);//here on
}

void deleteKey(int lastIndex){
    if(lastIndex){
        int temp = array[0];
        array[0] = array[lastIndex];
        //2nd args for using the swap in both functions
        swap(0,lastIndex-1);

        array[lastIndex] = temp;  
    }
    
}

int main(){
    puts("Bismillah");
    for(int i=0;i<SIZE;i++) {
        printf("%d  ",array[i]);
    }
    int half = floor((SIZE-1)/2);
    heapify(half);
    puts("\nHeapify");
    for(int i=0;i<SIZE;i++) printf("%d  ",array[i]);
 
    for(int i=0;i<=SIZE-1;i++) deleteKey(SIZE-i-1);//Delete

    puts("\nDelete=HeapSort"); 
    for(int i=0;i<SIZE;i++) printf("%d  ",array[i]);
    return 0;
}
// Now we can make a delete operation and at the end it would become sorted order
// now this code is static implementation of heap, heapify, easily can be converted into dynamic one, biiznillah.
