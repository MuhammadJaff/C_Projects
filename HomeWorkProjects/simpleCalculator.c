#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int calculate(char* s);
// Bismillah
// its much like a simple calculator with numbers and + and - operations
int main(){
    int count = 0;
    char text[100];
    char choice;
    while (1) {// just for making loop
        printf("Example %d\n", ++count);
        printf("Input: ");
        fgets(text, sizeof(text), stdin);
        printf("Output: %d\n", calculate(text));

        printf("\nWant to continue (press enter or n): ");
        choice = getchar();
        if (choice == 'n' || choice == '0')
            break;
    }
    return 0;
}

int calculate(char* arr) {
    int length = strlen(arr);
    int i = 0,RESULT = 0,sign=1,j=0,parenDepth=0,startPos=-1,num;
    // I chose recursive way of solving, when '(' starts, it cuts the string and call
    // the function again, it's good for multiple inner parenthesis and avoid miscalculation
     for (int i = 0; i < length; i++) {
        if (arr[i] == ' ') continue;
        if (arr[i] == '(') {
            if(parenDepth == 0){
                startPos = ++i;
            }
            parenDepth++;
        }else if(arr[i] == ')'){
            parenDepth--;
            if (parenDepth == 0 && startPos != -1) {
                int sublength = i - startPos;
                char *newArr = (char *)calloc(sublength + 1, sizeof(char));
                strncpy(newArr, arr + startPos, sublength);
                newArr[sublength] = '\0';
                RESULT += sign * calculate(newArr);
                free(newArr); // after its returned from stack free the memory
                startPos = -1;
                num = 0;
            }
        }
        else if (parenDepth == 0) {
            if (isdigit(arr[i])) {
                num = num * 10 + (arr[i] - '0'); // for determining how big the number is
            } else if (arr[i] == '+') {
                RESULT += sign * num;
                num = 0;sign = 1;
            } else if (arr[i] == '-') {
                RESULT += sign * num; 
                num = 0;sign = -1;
            }
        }
     }
    RESULT += sign * num; // if there is something left at the end
    return RESULT;
}
