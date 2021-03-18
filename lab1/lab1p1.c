#include <stdlib.h>
#include <stdio.h>
#define DATA_SET_SIZE 10
#define NUM_OF_OPTIONS 6

float avgArray(float *array, int size);
float findMax(float *array, int size);
float findMin(float *array, int size);
float sumArray(float *array, int size);
void getASet(float *array, int size);
void menuSelection(float *array, int size);
void printArray(float *array, int size);

int main() {
    /* define array size */
    float dataSet[DATA_SET_SIZE];
    int dataSetSize = DATA_SET_SIZE;
    int select = -1;

    /* call get a set to get data form stdin */
    getASet(dataSet, DATA_SET_SIZE);
    /* pop menu for user selection */
    menuSelection(dataSet, DATA_SET_SIZE);

    return 0;
}

void getASet(float *array, int size) {
    int counter = 0;

    /* get data from stdin */
    printf("Please enter your data: ");
    for (counter = 0; counter < size; counter ++) {
        scanf("%f", &array[counter]);
    }
}

void menuSelection(float *array, int size) {
    int counter = 0;
    unsigned int userEntry;
    char * menu[] = {"Find the minimum value.",
                    "Find the maximum value.",
                    "Calculate the sum of all the values.",
                    "Calculate the average of all the values.",
                    "Print the values in the data set.",
                    "Exit the program."
                   };

    /* print menu */
    for (counter = 0; counter < NUM_OF_OPTIONS; counter++) {
        printf("%i) %s\n", counter + 1, menu[counter]);
    }
    printf("\n");

    /* ask user to make decision */
    printf("Please make your selection: ");
    scanf("%u", &userEntry);
    /* minus 1 from input since we added one on selections */
    userEntry--;
    /* trash the '\n' */
    getchar();

    while (userEntry != 6) {
        switch (userEntry) {
        case 0:
            printf("The minium value in the data set is: %.2f\n", findMin(array, size));
            break;
        case 1:
            printf("The maximum value in the data set is: %.2f\n", findMax(array, size));
            break;
        case 2:
            printf("The sum of the data set is: %.2f\n", sumArray(array, size));
            break;
        case 3:
            printf("The average of the data set is: %.2f\n", avgArray(array, size));
            break;
        case 4:
            printArray(array, size);
            break;
        default:
            exit(0);
            break;
        }

        printf("Please make your selection: ");
        scanf("%u", &userEntry);
        userEntry--;
        getchar();
    }

}

float findMin(float *array, int size) {
    int counter = 0;
    float min = array[counter];

    for (counter = 0; counter < size; counter ++) {
        if (min > array[counter]) {
            min = array[counter];
        }
    }

    return min;
}

float findMax(float *array, int size) {
    int counter = 0;
    float max = array[counter];

    for (counter = 0; counter < size; counter ++) {
        if (max < array[counter]) {
            max = array[counter];
        }
    }

    return max;
}

float sumArray(float *array, int size) {
    int counter = 0;
    float sum = 0;

    for (counter = 0; counter < size; counter ++) {
        sum += array[counter];
    }

    return sum;
}

float avgArray(float *array, int size) {
    return sumArray(array, size) / size;
}

void printArray(float *array, int size) {
    int counter = 0;

    for (counter = 0; counter < size; counter ++) {
        printf("%.2f ", array[counter]);
    }
    printf("\n");
}
