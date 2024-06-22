//Bismillah
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *file;
int totalSize = 0; // node list size

typedef struct String{
    char str[25];
    int count;
    struct String *nextAlpha;
    struct String *nextCount;
} String;

void inc(String** headAlpha, String** headCount, char* key) {
    // If there is nothing
    String *current = NULL,*hdCount = NULL;
    String *ptr = malloc(sizeof(String));
    if(ptr == NULL){
        puts("Cannot allocate memory");
        return;
    }
    ptr->count = 1;
    ptr->nextAlpha = NULL;
    ptr->nextCount = NULL;
    strcpy(ptr->str,key);

// 3 MAIN CASE: FIRST,EXIST,NEW ADDED
    if(*headAlpha == NULL){ // AT FIRST
        *headAlpha = ptr;
        *headCount = ptr;
        totalSize++;
        return;
    }
    else{
        current = *headAlpha;
        hdCount = *headAlpha;
        // ALPHA
        while( strcmp(current->str,key) != 0  && current->nextAlpha != NULL){
            current = current->nextAlpha; // stay at the node not the link of it
        }
        // COUNT
        while(hdCount->nextCount != NULL){
            hdCount = hdCount->nextCount; // making the last node of count
        }
        if(strcmp(current->str,key) == 0){ // lets approach with true case first
            current->count += 1; // here when count increments we should check the headCount
            free(ptr);
            return;
        }else if (current->nextAlpha == NULL){
            current->nextAlpha = ptr;
            hdCount->nextCount = ptr;
            totalSize++;
        }
    } 
    // SORTING ALPHA
    String *temp = *headAlpha, *prev = NULL;
    
    if(strcmp(ptr->str,(*headAlpha)->str) < 0){ // if its 'smaller' than head;
        *headAlpha = ptr;
        ptr->nextAlpha = temp;
        current = ptr->nextAlpha;
        // for making the last node to NULL
        while(current->nextAlpha != ptr){
            current=current->nextAlpha;
        }
        current->nextAlpha = NULL;
    }
    else if(totalSize > 2){ // if onlt two nodes, first IF is enough

        while(strcmp(ptr->str,temp->str) > 0){
            prev = temp;
            temp = temp->nextAlpha;
        }
        // after the head, we go through each node and check for being 'smaller'
        // then is found we should make (the node one before ptr to NULL)
        // cause ptr will 'change its order' in the list
        current = ptr;
        if(strcmp(ptr->str,temp->str) < 0){
            ptr->nextAlpha = temp;
            prev->nextAlpha = ptr;

            while(temp->nextAlpha != current){
                temp=temp->nextAlpha;
            }
        }
        if(temp->nextAlpha == current){
            temp->nextAlpha = NULL;
        }
    }
}

void dec(String** headAlpha, String** headCount, char* key) {
// It is guaranteed that key exists in the data structure
// before the decrement, we assume there is this elem
    String *head = *headAlpha,
           *hdCount = *headCount,
           *prevHead = NULL, *prevHdCount = NULL;

    while(strcmp(head->str,key) != 0 && head != NULL){
        prevHead = head;  // one previous
        head = head->nextAlpha;
    }
    while(strcmp(hdCount->str,key) != 0 && hdCount != NULL){
        prevHdCount = hdCount; // one previous
        hdCount = hdCount->nextCount;
    }
    // now its supposed to be at that node

    if(strcmp(head->str,key) == 0 && head->count > 1){
        head->count -= 1;
    } else if(strcmp(head->str,key) == 0 && head->count == 1){ //checking with head is enough
        // HeadAlpha
        if(*headAlpha == head){
            *headAlpha = head->nextAlpha;
        }
        else  prevHead->nextAlpha = head->nextAlpha;

        // HeadCount
        if(*headCount == hdCount){
            *headCount = hdCount->nextCount;
        }
        else prevHdCount->nextCount = hdCount->nextCount;
    }
    
}

// Sorting count
void sortCount(String** headCount) {
   // check for not null and at least 2 by 
    String *head = *headCount;
    if(head == NULL || head->nextCount == NULL ){
       return;
    }
    int i,j;
    
    for(i=0;i<totalSize-1;i++){
        String *prev=NULL,*current=head,*next = current->nextCount;

        for(j=0;j<totalSize-1-i;j++){
            if(next == NULL){
                break;
            }
            if(current->count < next->count){    
                if(prev  == NULL){ // for checking head
                    (*headCount) = next;
                }else{
                    prev->nextCount = next;
                }
                current->nextCount = next->nextCount;
                next->nextCount = current;

                // now update
                prev = next;
                next =current->nextCount;
            }else{
                // just update
                prev = current;
                current = next;
                next = next->nextCount;
            }
        }
    }
}

char* getMaxKey(String* head) {
    if(head == NULL){
        return "";
    }
    else return head->str;
}
char* getMinKey(String* head) {
    if(head == NULL){
        return "";
    }
    else {
        while(head->nextCount != NULL){
            head = head->nextCount;
        }
        return head->str;
    }
}

char *printList(String *head,int num){
    String *current = head;
    if(current == NULL){
        puts("Empty list");
        return "";
    }
    if(num == 1){
        puts("\nThe list in alphabetical order:");
        while(current != NULL){
            printf("---> %s (%d)",current->str,current->count);
            current = current->nextAlpha;
        }
        printf("---> NULL");
    }else if(num == 2){
        puts("\nThe list in descending order:");
        while(current != NULL){
            printf("---> %s (%d)",current->str,current->count);
            current = current->nextCount;
        }  
        printf("---> NULL");
    }
    
}

// FREE THE LIST
void freeList(String *headAlpha){
    String *temp;
    while(headAlpha != NULL){
        temp = headAlpha;
        headAlpha = headAlpha->nextAlpha;
        free(temp);
    }
}

int main(){
    // puts("Bismillah");
    String *headAlpha = NULL; 
    String *headCount = NULL; 
    file = fopen("input2.txt","r");
    if(file == NULL){
        puts("Something went wrong ");
        exit(1);
    }
    char tempString[25];
    // time to reading the lines
    while(!feof(file)){
        fscanf(file,"%s",tempString);
        // increment
        if((strncmp("inc",tempString,3))==0){
            fscanf(file,"%s",tempString);
            inc(&headAlpha,&headCount,tempString);
            sortCount(&headCount);
        }
        // decrement
        else if((strncmp("dec",tempString,3))==0){
            // puts("DECREMENT");
            fscanf(file,"%s",tempString);
            dec(&headAlpha,&headCount,tempString);
            sortCount(&headCount);
        }
        // getMaxKey
        else if((strncmp("getMaxKey",tempString,9))==0){
            printf("%s\n",getMaxKey(headCount));
        }
        // getMaxKey
        else if((strncmp("getMinKey",tempString,9))==0){
            printf("%s\n",getMinKey(headCount));
        }
        // printList
        else if((strncmp("printList",tempString,9))==0){
            int temp;
            fscanf(file,"%d",&temp);
            if(temp == 1) printList(headAlpha,1);
            else if(temp == 2) printList(headCount,2);
            puts("");
        }
    }
    freeList(headAlpha); // free the list
    return 0;
}