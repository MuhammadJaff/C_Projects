#include <stdio.h>
#include <string.h>
#include <math.h>

int array[13]={'\0'},filled;

// let's try another method, multiplication
// We can optimize these functions later,

// we should try dynamically changing the array size as load factor changes.

int hashIt(int key){
    double A = 0.37275382526,B;
    B = key*A - (int)(key*A);
    int index = (int)floor(B*13);
    int insertTime = 1;
    while(array[index]!='\0'){
        index++; insertTime++;
        if(index >12) index = index % 13;
        if(insertTime >13) break;
    }
    if(array[index]=='\0') {
        array[index] = key; // we found a mistake here
        filled++;
    }
    return insertTime <= 13 ? insertTime : -1;
}
int deleteIt(int key){
    double A = 0.37275382526,B;
    B = key*A - (int)(key*A);
    int index = (int)floor(B*13);
    int deleteTime = 1;
    while(array[index]!=key){
        index++; deleteTime++;
        if(index >12) index = index % 13;
        if(deleteTime >13) break;
    }
    if(deleteTime < 14) {
        array[index] = '\0';
        filled--;
    }
    return deleteTime <= 13 ? deleteTime : -1;
}

int findIt(int key){
    double A = 0.37275382526,B;
    B = key*A - (int)(key*A);
    int index = (int)floor(B*13);
    int findTime = 1;
    while(array[index] != key){
        index++; findTime++;
        if(index >12) index = index % 13;
        if(findTime>13) break;
    }
    return findTime <= 13 ? findTime : -1; 
}

int main(){
    puts("Bismillah\nHashing (Linear)");
    // now lets make a menu:
    int input=-1;
    while(input){
        puts("\n1.Insert\n2.Find\n3.Delete\n4.See the List\n0.Exit");
        int searchTime=0;
        scanf("%d",&input);
        switch (input){
            case 1:
                puts("Enter a number:");
                scanf("%d: ",&input);
                searchTime = hashIt(input);
                if(searchTime ==-1){
                    puts("its full");
                }else{
                    printf("Inserted in time of %d",searchTime);
                }
                input=-1;
            break;
            case 2:
                puts("Enter a number:");
                scanf("%d: ",&input);
                searchTime = findIt(input);
                if(searchTime ==-1){
                    puts("Not Found");
                }else{
                    printf("Found in time of %d",searchTime);
                }
            break;
            case 3:
                puts("Enter a number:");
                scanf("%d: ",&input);
                searchTime = deleteIt(input);
                if(searchTime ==-1){
                    puts("Not Found");
                }else{
                    printf("Found in time of %d, and deleted",searchTime);
                }
            break;
            case 4:
                for(int i=0;i<13;i++){
                    printf("%d, ",array[i]);
                }
                printf("\n");
                break;
            case 0:
                break; 
            default: break;
        }
    }
    return 0;
}
