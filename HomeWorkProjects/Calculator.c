#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <time.h>

/* Struct for keeping the data */
struct Multiple{
    int sizeOf1,sizeOf2;
    char *mult1, *mult2;
    char *result;
    int decP1,decP2;
    struct Multiple *next;
};

FILE *fileRead,*fileWrite;

typedef struct Multiple Multiple;

/* 2 pointers for the LL */
Multiple *head = NULL,*tail=NULL;

/* Function for reversing the arrays */
void reverseArray(char *arr ){
    int len = strlen(arr);
    int i;
    for (i = 0; i < len / 2; i++) {
        char temp = arr[i];
        arr[i] = arr[len - 1 - i];
        arr[len - 1 - i] = temp;
    }
}

/* Function for calcuting part */
void calculate(Multiple *head, char arr[],char m1[],char m2[]){
    /* ex: 643434 ->j */
    /*        523 ->i */
    /* m1->j and mul1  |||  m2->i  and mul2; */
    int i,k,j,remind,mul1,mul2,ans,result;
    for(i=0;i<strlen(m2);i++){
        mul2 = m2[i]-'0'; 
        remind=0;
        for(j=0;j<strlen(m1);j++){
            k=j+i; mul1 = m1[j]-'0'; /* into digit */
            ans = arr[k]-'0';
            result = mul1 * mul2 + ans + remind; /* mult. and add k' value if exists */
            remind = 0;/* for new calculation    // and the reminder from the last run */
            if(result>=10){
                ans = result % 10;
                remind = result / 10; /* for overflow */
            }else ans=result;
        
            arr[k]=ans+'0';
        }
        arr[k+1]=remind+'0';
    }
    arr[k + 2] = '\0';

    reverseArray(arr);


    int d,total = head->decP1 + head->decP2;
    d = total > 0 ? 1 : 0;
    head->result = malloc(strlen(arr)+d+1); /* allocate memory for the sum */

    int brP = strlen(arr)-total;
    memcpy(head->result, arr, brP);

    /* if there is '.' then add */
    if (d == 1) {head->result[brP] = '.';}
    /* and continue the copying */
    memcpy(head->result + brP + d, arr + brP, strlen(arr) - brP + 1);
    /*If the result starts with 0*/
    if(head->result[0] == '0'){
        head->result++;
    }
    fprintf(fileWrite, "Multiplicant: %s\n", head->mult1);
    fprintf(fileWrite, "Multiplier: %s\n", head->mult2);
    fprintf(fileWrite, "Result: %s\n\n", head->result);
 }

/* Function one before calculation */
void prepare(Multiple *head){
    int n1 =0,n2 = 0;
    while(head!=NULL){
        /* check for decimal point */
        int i;
        for(i = 0; i< head->sizeOf1;i++){
            if(head->mult1[i] == '.'){
                head->decP1 = (head->sizeOf1)-(i+2);
                break;
            }
        }
        for(i = 0; i< head->sizeOf2;i++){
            if(head->mult2[i] == '.'){
                head->decP2 = (head->sizeOf2)-(i+2);
                break;
            }
        }
        
        if (head->decP1 > 0) n1 = 1;
        if (head->decP2 > 0) n2 = 1;

        /* temp arrays for reversing, with exact size */
        char tempArr1[(head->sizeOf1) - n1]; 
        char tempArr2[(head->sizeOf2) - n2]; 

        int j = 0;
        if (head->decP1 > 0) {
            for (i = 0; head->mult1[i] != '\0'; i++) {
                if (head->mult1[i] == '.') continue;
                tempArr1[j++] = head->mult1[i];
            }
            tempArr1[j] = '\0'; /* end with null */
        } else {
            /* if its decimal number copy without the '.' */
            strncpy(tempArr1, head->mult1, sizeof(tempArr1) - 1);
            tempArr1[sizeof(tempArr1) - 1] = '\0'; /* end with null terminator */
        }

        reverseArray(tempArr1);   /* REVERSE */
        /* the same thing for second array */
        if (head->decP2 > 0) { 
            j = 0; 
            for (i = 0; head->mult2[i] != '\0'; i++) {
                if (head->mult2[i] == '.') continue;  /* To ignore */
                tempArr2[j++] = head->mult2[i];  
            }
                tempArr2[j] = '\0';  /* Null-terminator */
        }
        else {
            strcpy(tempArr2, head->mult2);  /* Just copy */
            tempArr1[sizeof(tempArr1) - 1] = '\0';
        }

        reverseArray(tempArr2); /* REVERSE */

        /* Now time to the Sum array */
        int size;
        if((n1+n2)>1) size = (head->sizeOf1+head->sizeOf2-2);
        else if ((n1+n2) <= 1) size = (head->sizeOf1+head->sizeOf2-1);
        
        char resultant[size];
        memset(resultant, '0', size);
        resultant[size - 1] = '\0';

        /* Final Step */
        calculate(head, resultant,tempArr1,tempArr2);

        head=head->next;
    }
}
/* For freeing the allocated memory */
void freeThe(Multiple *head){
    Multiple *temp;
    while (head!=NULL){
        temp = head;
        head=head->next;
        free(temp->mult1);
        free(temp->mult2);
        free(temp);
    }
    
}

int main(){
    /* file assigning */
    clock_t start, end;  /* Variables to store start and end times */
    double cpu_time_used;

    /* Start measuring time */
    start = clock();

    fileRead = fopen("inputCalc.txt", "r");
    fileWrite = fopen("outputCalc.txt", "w");

    if (fileRead == NULL || fileWrite == NULL) {
        printf("Error opening file.\n");
        return 1; /* Exit with error */
    }
    char temparray1[100],temparray2[100]; /* length can be changed accordingly */
    fprintf(fileWrite,"Bismillah\n");
    while (fscanf(fileRead, "%s%s", temparray1, temparray2) == 2) {
        Multiple *ptr = malloc(sizeof(Multiple));
        if (ptr == NULL) {
            printf("Memory allocation failed.\n");
            return 1;
        }

        ptr->next = NULL;  

        if (head == NULL) {
            head = ptr;
            tail = head;
        } else {
            tail->next = ptr;
            tail = ptr;
        }

        ptr->decP1 = 0;
        ptr->decP2 = 0;

        ptr->mult1 = malloc(strlen(temparray1) + 1); /* allocate a memory pieces */
        ptr->sizeOf1 = strlen(temparray1) + 1;      /* with exact size */
        ptr->mult2 = malloc(strlen(temparray2) + 1);
        ptr->sizeOf2 = strlen(temparray2) + 1;

        if (ptr->mult1 == NULL || ptr->mult2 == NULL) {
            perror("Memory allocation failed for mult1 or mult2");
            return 1; /* in case any problem in allocation */
        }

        strcpy(ptr->mult1, temparray1);
        strcpy(ptr->mult2, temparray2);
    }
        prepare(head); 

        /* Closing */
        fclose(fileRead);
        freeThe(head);

        end = clock();
        /* Calculate elapsed time in seconds */
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        fprintf(fileWrite,"Execution time: %f seconds\n", cpu_time_used);

        fclose(fileWrite);
        printf("Execution time: %f seconds\n", cpu_time_used);
    return 0;
}


And while reading an input, I used tempArray with size of 100,
which can be easily changed if needed. And also, for memory efficiency
and easier calculation allocated memory transferred to the exact size later. 

Considering the some numbers are decimal, best way could be first ignore them and after the calculation done
put them into the correct position.

/* must run under: gcc -ansi -o Calculator Calculator.c */

RUN TIME
I used ready clock function of time.h library
