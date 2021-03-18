#include <stdio.h>
#include <stdlib.h>
#define NUM_OF_OPTIONS 6

float avgArray(float *selectedDataSet, int size);
float findMax(float *selectedDataSet, int size);
float findMin(float *selectedDataSet, int size);
float sumArray(float *selectedDataSet, int size);
int allocatePtr(float ***dataSetsArrayPtrPtr, int **dataSetSizesArrayPtrPtr);
int dataSetSelection(float ***dataSetsArrayPtrPtr, int **dataSetSizesArrayPtrPtr, float **selectedDataSet, int numOfSets);
int getDataSets(float ***dataSetsArrayPtrPtr, int **dataSetSizesArrayPtrPtr);
int menuSelection(float *array, int size);
void deallocationPtrs(float ***dataSetsArrayPtrPtr, int **dataSetSizesArrayPtrPtr, int numOfSets);
void getASet(float ***dataSetsArrayPtr, int **dataSetSizesArrayPtr, int currentPos);
void printArray(float *selectedDataSet, int size);

int main() {
    int select = -1;
    float ** dataSetsArrayPtr = NULL;
    int * dataSetSizesArrayPtr = NULL;
    float * selectedDataSet = NULL;
    int numOfSets = 0, selectDataSetSize = 0;
    int exitFlag = 1;

    /* get data with getDataSets */
    numOfSets = getDataSets(&dataSetsArrayPtr, &dataSetSizesArrayPtr);

    /* promote user input, it will end when user selected 6 from menu */
    while (exitFlag == 1) {
        selectDataSetSize = dataSetSelection(&dataSetsArrayPtr, &dataSetSizesArrayPtr, &selectedDataSet, numOfSets);
        exitFlag = menuSelection(selectedDataSet, selectDataSetSize);
    }
    deallocationPtrs(&dataSetsArrayPtr, &dataSetSizesArrayPtr, numOfSets);

    return 0;
}

int allocatePtr(float ***dataSetsArrayPtrPtr, int **dataSetSizesArrayPtrPtr) {
    int numOfSets = 0;

    printf("Enter the number of data sets on which you wish to calculations: ");
    scanf("%i", &numOfSets);

    *dataSetsArrayPtrPtr = calloc(numOfSets, sizeof(float *));
    if (*dataSetsArrayPtrPtr == NULL) {
        printf("Unable to allocate dataSetsArrayPtr.\n");
        exit(0);
    }

    *dataSetSizesArrayPtrPtr = calloc(numOfSets, sizeof(int));
    if (*dataSetSizesArrayPtrPtr == NULL) {
        printf("Unable to allocate dataSetSizesArrayPtr.\n");
        exit(0);
    }

    return numOfSets;
}

void deallocationPtrs(float ***dataSetsArrayPtrPtr, int **dataSetSizesArrayPtrPtr, int numOfSets) {
    int counter = 0;

    free(*dataSetSizesArrayPtrPtr);
    *dataSetSizesArrayPtrPtr = NULL;
    if (*dataSetSizesArrayPtrPtr != NULL) {
        printf("Unable to free dataSetSizesArrayPtrPtr.\n");
    }

    for (counter = 0; counter < numOfSets; counter++) {
        free(*(*dataSetsArrayPtrPtr + counter));
        *(*dataSetsArrayPtrPtr + counter) = NULL;
        if (*(*dataSetsArrayPtrPtr + counter) != NULL) {
            printf("Unable to free one of the element in dataSetsArrayPtrPtr.\n");
        }
    }

    free(*dataSetsArrayPtrPtr);
    *dataSetsArrayPtrPtr = NULL;
    if (*dataSetsArrayPtrPtr != NULL) {
        printf("Unable to free dataSetsArrayPtrPtr.\n");
    }
}

int getDataSets(float ***dataSetsArrayPtrPtr, int **dataSetSizesArrayPtrPtr) {
    int numOfSets = 0;
    int size = 0;
    int counter = 0;

    /* allocate memory spaces */
    numOfSets = allocatePtr(dataSetsArrayPtrPtr, dataSetSizesArrayPtrPtr);

    /* populate stdin to each data set */
    for (counter = 0; counter < numOfSets; counter++) {
        getASet(dataSetsArrayPtrPtr, dataSetSizesArrayPtrPtr, counter);
    }

    return numOfSets;
}

void getASet(float ***dataSetsArrayPtrPtr, int **dataSetSizesArrayPtrPtr, int currentPos) {
    int counter = 0;
    int numOfData = 0;
    float * array = NULL;

    printf("Enter a line (# of data, data1, data2, ...): ");
    scanf("%d", &numOfData);
    array = calloc(numOfData, sizeof(float));
    if (array == NULL) {
        printf("Unable to allocate array.\n");
    }

    *(*dataSetSizesArrayPtrPtr + currentPos) = numOfData;

    for (counter = 0; counter < numOfData; counter++) {
        scanf("%f", array + counter);
    }

    *(*dataSetsArrayPtrPtr + currentPos) = array;
}

int dataSetSelection(float ***dataSetsArrayPtrPtr, int **dataSetSizesArrayPtrPtr, float **selectedDataSet, int numOfSets) {
    int selectDataSetSize, numOfData = 0;
    int counter = 0, counter2 = 0;
    int selection = -1;
    float * array = NULL;

    printf("\n");
    for (counter = 0; counter < numOfSets; counter++) {
        array = *(*dataSetsArrayPtrPtr + counter);
        numOfData = *(*dataSetSizesArrayPtrPtr + counter);

        printf("Set %i: %i ", counter + 1, numOfData);

        for (counter2 = 0; counter2 < numOfData; counter2++) {
            printf("%.2f ", *(array + counter2));
        }
        printf("\n");
    }

    printf("Select your array: ");
    scanf("%i", &selection);

    selection -= 1;
    array = *(*dataSetsArrayPtrPtr + selection);
    selectDataSetSize = *(*dataSetSizesArrayPtrPtr + selection);
    *selectedDataSet = array;

    return selectDataSetSize;
}

int menuSelection(float *array, int size) {
    int counter = 0;
    unsigned int userEntry;
    char * menu[] = {"Find the minimum value.",
                    "Find the maximum value.",
                    "Calculate the sum of all the values.",
                    "Calculate the average of all the values.",
                    "Print the values in the data set.",
                    "Exit the program."
                   };

    for (counter = 0; counter < NUM_OF_OPTIONS; counter++) {
        printf("%i) %s\n", counter + 1, menu[counter]);
    }

    printf("\n");

    printf("Please make your selection: ");
    scanf("%u", &userEntry);
    userEntry--;
    getchar();

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
        break;
    }

    return userEntry < 5 && userEntry >= 0;
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
