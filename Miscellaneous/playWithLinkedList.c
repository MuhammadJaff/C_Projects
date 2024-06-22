#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int totalSize = 0;
struct node{
    int num;
    struct node *nextPtr;
};

void addHead(struct node **head,struct node **end, int n){
    struct node *ptr = malloc(sizeof(struct node));
    if(ptr == NULL){
        printf("Problem in allocating memory");
        exit(1);
    }

    ptr->num =n;
    ptr->nextPtr = *head;
    *head = ptr;
    if(totalSize==0) 
        *end=*head;

    totalSize++;
}

void addEnd(struct node **end,struct node **head,int n){
    struct node *ptr = malloc(sizeof(struct node));
    if(ptr == NULL){
        printf("Problem in allocating memory");
        exit(1);
    }
    ptr->num =n;
    ptr->nextPtr = NULL;
    
    if(totalSize==0)
        *head=ptr;
    else  (*end)->nextPtr = ptr;
    
    *end = ptr;
    totalSize++;
}

void addPosition(struct node *head,int n,int pos){
    // here we can just change pass the value not the address
    int count = 1;
    struct node *ptr = malloc(sizeof(struct node));
    ptr->num = n;
    while(count < pos && head != NULL){
        head = head->nextPtr;
        count++;
    }
    ptr->nextPtr = head->nextPtr;
    head->nextPtr = ptr;
    totalSize++;
}

void printData(struct node *head,struct node *end){
    int size = totalSize;
    printf("Address of Head: %d\n",head);
    if(head == NULL || end == NULL){
        printf("List is empty:\n");
    }else{
        int i=1;
        size = totalSize;
        while(size > 0 && head != NULL){
            printf("Data %d: %d\n",i,head->num);
            head = head->nextPtr;
            i++;size--;
        }
    }
}

void deleteHead(struct node **head,struct node **end){
    if(totalSize > 0){
        struct node *temp = *head;
        if(*end == *head){
            *head = NULL; 
            *end = NULL;
        }else{
            *head = (*head)->nextPtr;
        }
        free(temp);
        totalSize--;
    }
}

void deleteTail(struct node **end,struct node **head){
    if(totalSize > 0){
        struct node *temp = *end;
        struct node *innerHead = *head;
        if(innerHead == temp){ //only one elem
            printf("Only one\n");
            *end = NULL;
            *head = NULL;
        }else{
            while(innerHead->nextPtr != temp){
                innerHead = innerHead->nextPtr;
            }
            innerHead->nextPtr = NULL;
            *end = innerHead;
        }
        totalSize--;
        free(temp);
    }
}

void deletePosition(struct node *head,int pos){
    int count =1;
    while(count < pos && head != NULL){ 
        head = head->nextPtr;
        count++;
    }
    struct node *temp= head->nextPtr;
    head->nextPtr = head->nextPtr->nextPtr;
    free(temp);
}

void changeTheValue(struct node *head,struct node *end,int pos,int n){
    int count = 0;
    if(pos == 0){
        head->num = n;
    }else if(pos == (totalSize-1)){
        end->num = n;
    }else if(pos > 0 && pos < (totalSize-1)){
        while(count<pos){
            head = head->nextPtr;
            count++;
        }
        head->num = n;

    }else puts("Invalid position");
}

void reverseList(struct node **head,struct node **end){
    struct node *headPtr = *head, *endPtr = *end, *ptr1,*ptr2;
    if(totalSize == 2){
        puts("\nWORKING\n");
        *head = endPtr;
        *end = headPtr;
        (*end)->nextPtr = NULL;
        (*head)->nextPtr = *end;
        // dont forget about nextptrssss
    }
    else if(totalSize > 2){
        ptr1 = headPtr->nextPtr;
        ptr2 = ptr1->nextPtr;
        (*end)= headPtr;
        (*end)->nextPtr = NULL;
        while(ptr2 !=NULL){
            ptr1->nextPtr = headPtr;
            headPtr = ptr1;
            ptr1 = ptr2;
            ptr2 = ptr2->nextPtr;
        }
        ptr1->nextPtr = headPtr;
        (*head) = ptr1;
    // always first make psedocode
    }
}

void clearInput(){
    char c;
    while ((c = getchar()) != '\n' && c != EOF);
}
void freeList(struct node *head){
    struct node *current;
    while(head !=NULL){
        current = head;
        head= head->nextPtr;
        free(current);
    }
}

int main(){
    struct node *head = NULL;  // head
    struct node *current; //current
    struct node *end = head; // end

    char choice;
    int num,pos,size;
    current = head; // just assign it
    while (choice != '0'){
        puts("\nChoose one of these: \n1. Add to the beginning.");
        puts("2. Add to the end \n3. Add to the certain position."); 
        puts("4. See the numbers \n5. Delete head \n6. Delete tail");
        puts("7. Delete the certain position \n8. Change the value ");
        puts("9. Reverse the list \n0. Exit");

    choice = getchar();
    clearInput();
      switch (choice){
        case '1':
            printf("Enter a number: ");
            scanf("%d",&num);
            clearInput();
            addHead(&head,&end,num);
        break;

        case '2':
            printf("Enter a number: ");
            scanf("%d",&num);
            clearInput();
            addEnd(&end,&head,num);
        break;

        case '3':
            printf("Enter a number: ");
            scanf("%d",&num);
            clearInput();
            printf("\nEnter a position: ");
            scanf("%d",&pos);
            clearInput();
            if(pos == 0){ //begin
                addHead(&head,&end,num);
            }else if(pos == totalSize){ // end
                addEnd(&end,&head,num);
            }else if(pos>0 && pos<totalSize){
                addPosition(head,num,pos);
                printf("good input");
            }else{
                printf("\n\nInvalid position\n");
                break;
            }
        break;

        case '4':
            printData(head,end);
            printf("Press Enter to continue...");
            getchar();
        break;

        case '5':
            deleteHead(&head,&end);
            printf("\nDone\n");
        break;

        case '6':
            deleteTail(&end,&head);
            printf("\nDone\n");
        break;

        case '7':
        if(totalSize>0){
            printf("\nEnter a position: ");
            scanf("%d",&pos);
            clearInput();
            if(pos==0){
                deleteHead(&head,&end);
            }else if(pos == (totalSize-1)){
                deleteTail(&end,&head);
            }else if(pos >0 && pos < (totalSize-1)){
                deletePosition(head,pos);
            }else puts("Invalid position");
        }else puts("List is empty");
        break;

        case '8':
            printf("\nEnter the value: ");
            scanf("%d",&num);
            clearInput();
            printf("\nEnter the position: ");
            scanf("%d",&pos);
            clearInput();
            changeTheValue(head,end,pos,num);
        break;

        case '9':
            // reverse the list
            // no need for an input
            reverseList(&head,&end);
        break;

        case '0':
            break;
        break;
        default:
            break;
      }
    }
    
    freeList(head);
    return 0;
}
// 250 lines of code, 7-7.5 hours of thinking :);