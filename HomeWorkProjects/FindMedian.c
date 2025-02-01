#include <stdio.h>
#include <string.h>

void addNumber(int* numArray, int size, int num);
void sortArray(int* numArray, int size);
double findMedian(int* numArray, int size); // defining function prototypes

int main(){
    // puts("Bismillah");
    FILE *input = fopen("inputFindMedian.txt","r"); // read mode is enough

    if(input == NULL){ // if any problem in opening file
        perror("Problem");
        return -1;
    }

    int numArray[20],sizeOfArr=0,temp;
    char str[11];
    puts("Output: ");
    while(!feof(input)){ // if not end then...
        fscanf(input,"%s",str);
        
        if(strncmp(str,"addNumber",sizeof("addNumber")) == 0){ // check
            fscanf(input,"%d",&temp);
            addNumber(numArray,sizeOfArr,temp);
            sizeOfArr++;
        }else if(strncmp(str,"findMedian",sizeof("findMedian")) == 0){ // for more accuracy
            sortArray(numArray,sizeOfArr);
            double median = findMedian(numArray,sizeOfArr);
            if(median == (int)median)
                printf("%d\n",(int)median);
            
            else printf("%.1f\n",median);
            sizeOfArr=0;
        }
    }
    return 0;
}

void addNumber(int* numArray, int size, int num){
    numArray[size] = num; // simply add to array
}

void sortArray(int* numArray, int size){
    // bubble sort method is used here
    int i,j,temp,differ;
    for (i = 0; i < size-1; i++){
        for (j = 0; j < size-1-i; j++){
            if(numArray[j] > numArray[j+1]){
                temp = numArray[j];
                numArray[j] = numArray[j+1];
                numArray[j+1] = temp;
            }
        }
    }
}

double findMedian(int* numArray, int size){
    double result = 0.0;
    int even;
    if(size % 2 == 1){
        result = numArray[size/2];
    }else{
        even = (size/2);
        result = ((double)(numArray[even-1] + numArray[even]))/2;
    }
    return result;
}   
 // Alhamdulillah
