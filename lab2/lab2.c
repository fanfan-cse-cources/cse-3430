#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Data {
    char title[50];
    char author[50];
    int stockNumber;
    float wholesalePrice;
    float retailPrice;
    int wholesaleQuantity;
    int retailQuantity;
};

typedef struct Node {
    struct Data book;
    struct Node *next;
} Node;

void getDataAndBuildList(Node **headPtr);
Node *createNodeAndGetData(void);
void insert(Node **headPtr, Node *newNodePtr);
void delete(Node **headPtr, int prodNumberToDelete);
void getUserOption(Node **head);
double calculateTotalRevenue(const Node *head);
double calculateInvestmentInInventory(const Node *head);
double calculateTotalWholesaleCost(const Node *head);
double calculateTotalProfit(const Node *head);
int calculateTotalBooksSold(const Node *head);
double calculateAverageProfit(const Node *head);
void printList(const Node *head);
void freeAllNodes(Node **headPtr);

int main() {
    Node *head = NULL;
    getDataAndBuildList(&head);
    getUserOption(&head);
    return 0;
}

void getDataAndBuildList(Node **headPtr) {
    Node *newNodePtr;
    printf("Please enter data about the books.\n\n");
    while ((newNodePtr = createNodeAndGetData())) {
        insert(headPtr, newNodePtr);
    }
}

Node *createNodeAndGetData(void) {
    Node *newNodePtr;
    newNodePtr = malloc (sizeof(Node));
    if (newNodePtr == NULL) {
        printf("Error: memory could not be allocated for enough nodes. ");
        printf("Terminating program!\n");
        exit (0);
    } else {
        scanf("%[^\n]", newNodePtr -> book.title);
        if (strcmp(newNodePtr -> book.title, "END_DATA") == 0) {
            /* free Node if end of book data detected */
            free(newNodePtr);
            return NULL;
        } else {
            /* consume newline before author string */
            getchar();
            scanf("%[^\n]s", newNodePtr -> book.author);
            scanf("%i", &newNodePtr -> book.stockNumber);
            scanf("%f", &newNodePtr -> book.wholesalePrice);
            scanf("%f", &newNodePtr -> book.retailPrice);
            scanf("%i", &newNodePtr -> book.wholesaleQuantity);
            scanf("%i", &newNodePtr -> book.retailQuantity);
            /* consume newline before next title string */
            getchar();
        }
        return newNodePtr;
    }
}


void insert(Node **headPtr, Node *newNodePtr) {
    /* WRITE THE CODE FOR THIS FUNCTION */
    Node *traversePtr = *headPtr;
    Node *priorNodePtr;

    if(traversePtr == NULL) {
        /* if there is nothing in headPtr */
        *headPtr = newNodePtr;
        newNodePtr -> next = NULL;
    } else if(newNodePtr -> book.stockNumber < traversePtr -> book.stockNumber) {
        newNodePtr -> next = traversePtr;
        *headPtr = newNodePtr;
    } else {
        priorNodePtr = traversePtr;
        traversePtr = traversePtr -> next;
        while((traversePtr != NULL) && (newNodePtr -> book.stockNumber > traversePtr -> book.stockNumber)) {
            priorNodePtr = traversePtr;
            traversePtr = traversePtr -> next;
        }
        /* insert newNodePtr */
        newNodePtr -> next = traversePtr;
        priorNodePtr -> next = newNodePtr;
    }
}

void getUserOption(Node **headPtr) {
    int option;
    Node *newNodePtr;
    int bookNumToDelete;
    do {
        printf("\nPlease enter an integer between 1 and 9 to select an operation on the data:\n");
        scanf("%i", &option);
        getchar();
        switch (option) {
        case 1:
            printList (*headPtr);
            break;
        case 2:
            printf("\nTotal revenue: %.2f\n", calculateTotalRevenue(*headPtr));
            break;
        case 3:
            printf("\nTotal wholesale cost: %.2f\n", calculateTotalWholesaleCost(*headPtr));
            break;
        case 4:
            printf("\nTotal investment in inventory: %.2f\n", calculateInvestmentInInventory(*headPtr));
            break;
        case 5:
            printf("\nTotal profit: %.2f\n", calculateTotalProfit(*headPtr));
            break;
        case 6:
            printf("\nTotal number of books sold: %i\n", calculateTotalBooksSold(*headPtr));
            break;
        case 7:
            printf("\nAverage profit: %.2f\n", calculateAverageProfit(*headPtr));
            break;
        case 8:
            printf("\nPlease enter the data for the book you wish to add:\n\n");
            newNodePtr = createNodeAndGetData();
            insert(headPtr, newNodePtr);
            printf("\nBook stock number %i added to the inventory.\n\n", newNodePtr -> book.stockNumber);
            break;
        case 9:
            printf("\nPlease enter the book stock number of the book you wish to delete, ");
            printf("followed by enter.\n");
            scanf("%i", &bookNumToDelete);
            delete (headPtr, bookNumToDelete);
            break;
        case 10:
            freeAllNodes(headPtr);
            break;
        default:
            printf("Valid option choices are 1 to 10. Please choose again!\n");
            break;
        }
    } while (option != 10);
}

double calculateTotalRevenue(const Node *head) {
    /* WRITE THE CODE FOR THIS FUNCTION */
    double revenue = 0.0;
    const Node *traversePtr = head;

    /* iterating the linked list and calculate the total revenue */
    while (traversePtr != NULL) {
        revenue += (traversePtr -> book.retailPrice) * (traversePtr -> book.retailQuantity);

        traversePtr = traversePtr -> next;
    }

    return revenue;
}

double calculateInvestmentInInventory(const Node *head) {
    /* WRITE THE CODE FOR THIS FUNCTION */
    double investmentInInventory = 0.0;
    const Node *traversePtr = head;

    /* iterating the linked list and calculate the investment in inventory */
    while (traversePtr != NULL) {
        investmentInInventory += ((traversePtr -> book.wholesaleQuantity) - (traversePtr -> book.retailQuantity)) * (traversePtr -> book.wholesalePrice);

        traversePtr = traversePtr -> next;
    }

    return investmentInInventory;
}

double calculateTotalWholesaleCost(const Node *head) {
    /* WRITE THE CODE FOR THIS FUNCTION */
    double wholesaleCost = 0.0;
    const Node *traversePtr = head;

    /* iterating the linked list and calculate the total wholesale cost */
    while (traversePtr != NULL) {
        wholesaleCost += (traversePtr -> book.wholesalePrice) * (traversePtr -> book.wholesaleQuantity);

        traversePtr = traversePtr -> next;
    }

    return wholesaleCost;
}

double calculateTotalProfit(const Node *head) {
    /* WRITE THE CODE FOR THIS FUNCTION */
    return (calculateTotalRevenue(head) - calculateTotalWholesaleCost(head) + calculateInvestmentInInventory(head));
}

int calculateTotalBooksSold(const Node *head) {
    /* WRITE THE CODE FOR THIS FUNCTION */
    double booksSold = 0.0;
    const Node *traversePtr = head;

    while (traversePtr != NULL) {
        /* iterating the linked list and calculate the total books sold */
        booksSold += (traversePtr -> book.retailQuantity);

        traversePtr = traversePtr -> next;
    }

    return booksSold;
}

double calculateAverageProfit(const Node *head) {
    /* WRITE THE CODE FOR THIS FUNCTION */
    return (calculateTotalProfit(head) / calculateTotalBooksSold(head));
}

void delete(Node **headPtr, int stockNumToDelete) {
    /* WRITE THE CODE FOR THIS FUNCTION */
    Node *traversePtr = *headPtr;
    Node *priorNode;

    /* when stock number of the book is located at the head */
    if (traversePtr != NULL && traversePtr -> book.stockNumber == stockNumToDelete) {
        /* set the second node as the head */
        *headPtr = traversePtr -> next;
        /* deallocate the head, and set to NULL */
        free(traversePtr);
        traversePtr = NULL;

        printf("\nBook stock number %i deleted from the inventory.\n\n", stockNumToDelete);
        return;
    }

    /* set Node n to the stock number to be deleted */
    while (traversePtr != NULL && traversePtr -> book.stockNumber != stockNumToDelete) {
        priorNode = traversePtr;
        traversePtr = traversePtr -> next;
    }

    /* when the node exist, then it will be freed */
    if (traversePtr != NULL) {
        printf("\nBook stock number %i deleted from the inventory.\n\n", stockNumToDelete);

        /* link the priorNode with next node of Node n */
        priorNode -> next = traversePtr -> next;
        free(traversePtr);
        traversePtr = NULL;
    } else {
        printf("\nERROR: Book stock number %i not found in the list!\n", stockNumToDelete);
        return;
    }
}

void printList(const Node *head) {
    const Node *traversePtr = head;
    printf("\nBook list:\n");
    while (traversePtr != NULL) {       /* determine not at end of list */
        printf("%s\n", traversePtr -> book.title);
        traversePtr = traversePtr -> next;
    }
    printf("\n");
}

void freeAllNodes(Node **headPtr) {
    Node *traversePtr = *headPtr;
    Node *restOfListPtr = *headPtr;
    while (restOfListPtr != NULL) {         /* determine list is not empty */
        restOfListPtr = restOfListPtr -> next;
        free(traversePtr);
        traversePtr = restOfListPtr;
    }
    *headPtr = NULL; /* set headPtr back to NULL after space freed */
}
