#include <stdio.h>
#include <string.h>

int array[] = {6,26,3,28,29,35,37,32,46}, count;

int Partition(int start,int end){
    count++;
    // ok,pivot be the end
    // This is Hoare's method.
    int j=end-1,i=start,temp,pivot =array[end];
    while(i<=j){

        while(array[i] < pivot) ++i;
        while(array[j] > pivot) --j;
        if(array[i] > pivot && array[j] < pivot && i<j){
            // printf("Working2\n");
            temp = array[j];
            array[j] = array[i];
            array[i] = temp;
        }
    }
        temp = array[i];
        array[i] = pivot;
        array[end] = temp;   
    
         

    return i;
}

void quickSort(int start,int end){
    count++;
    if(end <= start) return;
    int pivot = Partition(start,end);
    // printf("Pivot is:%d\n",pivot);
    quickSort(start,pivot-1);
    quickSort(pivot+1,end);
};

int main(){
    puts("Bismillah");
    quickSort(0,8);

    for(int i = 0;i<9;i++) printf("%d ",array[i]);
    printf("\nCount/Time complexity is: %d",count);
    return 0;
}
