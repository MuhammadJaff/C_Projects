#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10

int totalNumberOfCars = 0;

FILE *file = NULL;
time_t rawtime;
struct tm *timeinfo;
char buffer[50];

struct carInformation{
    char model[20];
    char brand[20];
    int seriesNo;
    int hp;
    double gasPerKim;
};

typedef struct carInformation Car;
// take a more look
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n'); // if not a newline just continue to remove chars
}
// change with this program and put some while loop in main to go back to the menu
// then in printAll or other method write it to a file .txt ,ok?

void addCar(Car *car){
    clearInputBuffer();
    // it takes car pointer and we should fill it
    puts("We are gonna ask some questions about the car."); 
    puts("What is the Model?");
    fgets(car->model,sizeof(car->model),stdin);
    // car->model[strcspn(car->model, "\n")] = '\0';
    puts("What is the Brand?");
    fgets(car->brand,sizeof(car->brand),stdin);
    // car->model[strcspn(car->brand, "\n")] = '\0';
    puts("What is the Series Number?");
    scanf("%d",&(car->seriesNo));
    puts("How much is the Horse Power?");
    scanf("%d",&(car->hp));
    puts("And gas per kilometer?");
    scanf("%lf",&(car->gasPerKim));
    clearInputBuffer();
}
void changeCarInfo(Car car[]){
    int series,i;
    
    puts("Enter the Series Number of the car you want to change: ");
    scanf("%d",&series);
    // on top we defined SIZE which we should use here: 
    // sizeof(*car)/sizeof(Car) this is equal to one, as we guessed
    for(i=0;i<SIZE;i++){
        if(series == (car+i)->seriesNo){
            addCar((car+i));
        }
    }
}
void searchWithModel(Car car[]){
    char modelChange[20];
    int i;
    puts("Enter the Model of the car you want to change: ");
    fgets(modelChange,sizeof(modelChange),stdin);
    modelChange[strcspn(modelChange, "\n")] = '\0';
    for(i=0;i<SIZE;i++){
        // check they are equal??
        if(strncmp(car[i].model,modelChange,sizeof(modelChange)) == 0){
            addCar((car+i));
        }
    }
}
void printAll(Car car[]){
    // lets print all
    // fputs("\nSee all the cars:",file);
    int i;
    for(i = 0; i < totalNumberOfCars;i++){
        fprintf(file,"\nModel: %s",(car+i)->model);
        fprintf(file,"Brand: %s",(car+i)->brand);
        fprintf(file,"Series Number: %d\n",(car+i)->seriesNo);
        fprintf(file,"Horse Power: %d\n",(car+i)->hp);
        fprintf(file,"Gas Per Kilometer: %.1lf\n\n",(car+i)->gasPerKim);
    }
    printf("\nPrinted to the output file\nExit you will see the results\n\n\n");

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
    fprintf(file, "Printing time: %s\n", buffer);
    // now lets make it write to the output file
    // and lets also add a time, when this relusts are printed???
}

int main(){
    file = fopen("output.txt","r+");

    if(file == NULL){
        printf("Something went wrong, try again");
        exit(1);
    };
    puts("Bismillah");
    int choice;
    Car car[SIZE];
    while(totalNumberOfCars <= 10){
        puts("Choose the option:");
        puts("1-Add a car");
        puts("2-Modify the car");
        puts("3-Search the car with respect to model");
        puts("4-Print Output");
        puts("0-Exit");
        scanf("%d",&choice); // elementary mistake man!!!!!!!
        clearInputBuffer(); 

        switch(choice){
            case 1:
            if(totalNumberOfCars < SIZE){
                addCar(&car[totalNumberOfCars]);
                totalNumberOfCars++;
            }else {
                puts("Car list is full");
            }
            break;
            case 2:
                changeCarInfo(car);
            break;
            case 3:
                searchWithModel(car);
            break;
            case 4:
                printAll(car);
            break;
            case 0:
            printf("\n\nTotalNumberOfCars %d\n",totalNumberOfCars);
                fclose(file);
                exit(0);
                break;
            default:
                puts("Invalid input");
        }
    }
    return 0;
}
// Alhamdulillah