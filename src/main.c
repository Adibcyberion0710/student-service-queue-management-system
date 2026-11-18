
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure of each student request
struct Node
{
    int tokenNumber;
    int studentID;
    char name[50];
    char serviceType[50];

    struct Node *prev;
    struct Node *next;
};

// Global pointers
struct Node *head = NULL;
struct Node *tail = NULL;

int nextToken = 101;


// Add a new student request
void addStudent()
{
    struct Node *newNode;

    newNode = (struct Node *)malloc(sizeof(struct Node));

    if (newNode == NULL)
    {
        printf("Memory allocation failed!\n");
        return;
    }

    printf("Enter Student ID: ");
    scanf("%d", &newNode->studentID);
    getchar();

    printf("Enter Student Name: ");
    fgets(newNode->name, 50, stdin);
    newNode->name[strcspn(newNode->name, "\n")] = '\0';

    printf("Enter Service Type: ");
    fgets(newNode->serviceType, 50, stdin);
    newNode->serviceType[strcspn(newNode->serviceType, "\n")] = '\0';

    newNode->tokenNumber = nextToken++;

    newNode->prev = NULL;
    newNode->next = NULL;

    if (head == NULL)
    {
        head = newNode;
        tail = newNode;
    }
    else
    {
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }

    printf("\nRequest added successfully!\n");
    printf("Token Number: %d\n", newNode->tokenNumber);
}


// Serve the first student
void serveStudent()
{
    struct Node *temp;

    if (head == NULL)
    {
        printf("Queue is empty!\n");
        return;
    }

    temp = head;

    printf("\nServing Student:\n");
    printf("Token Number: %d\n", temp->tokenNumber);
    printf("Name: %s\n", temp->name);

    head = head->next;

    if (head == NULL)
    {
        tail = NULL;
    }
    else
    {
        head->prev = NULL;
    }

    free(temp);

    printf("Request served successfully!\n");
}


// Cancel a request using token number
void cancelRequest()
{
    struct Node *temp;
    int token;

    if (head == NULL)
    {
        printf("Queue is empty!\n");
        return;
    }

    printf("Enter Token Number: ");
    scanf("%d", &token);

    temp = head;

    while (temp != NULL && temp->tokenNumber != token)
    {
        temp = temp->next;
    }

    if (temp == NULL)
    {
        printf("Request not found!\n");
        return;
    }

    if (temp == head)
    {
        head = temp->next;
    }
    else
    {
        temp->prev->next = temp->next;
    }

    if (temp == tail)
    {
        tail = temp->prev;
    }
    else
    {
        temp->next->prev = temp->prev;
    }

    free(temp);

    printf("Request cancelled successfully!\n");
}


// Search a request using token number
void searchStudent()
{
    struct Node *temp;
    int token;

    printf("Enter Token Number: ");
    scanf("%d", &token);

    temp = head;

    while (temp != NULL)
    {
        if (temp->tokenNumber == token)
        {
            printf("\nRequest Found!\n");
            printf("Token Number: %d\n", temp->tokenNumber);
            printf("Student ID: %d\n", temp->studentID);
            printf("Name: %s\n", temp->name);
            printf("Service: %s\n", temp->serviceType);
            return;
        }

        temp = temp->next;
    }

    printf("Request not found!\n");
}


// Display all pending requests
void displayQueue()
{
    struct Node *temp = head;

    if (head == NULL)
    {
        printf("Queue is empty!\n");
        return;
    }

    printf("\n===== STUDENT SERVICE QUEUE =====\n");

    while (temp != NULL)
    {
        printf("\n-------------------------\n");
        printf("Token Number: %d\n", temp->tokenNumber);
        printf("Student ID: %d\n", temp->studentID);
        printf("Name: %s\n", temp->name);
        printf("Service: %s\n", temp->serviceType);

        temp = temp->next;
    }
}


// Main function
int main()
{
    int choice;

    do
    {
        printf("\n====================================\n");
        printf(" STUDENT SERVICE QUEUE MANAGEMENT\n");
        printf("====================================\n");

        printf("1. Add Student Request\n");
        printf("2. Serve Student\n");
        printf("3. Cancel Request\n");
        printf("4. Search Request\n");
        printf("5. Display Queue\n");
        printf("6. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                addStudent();
                break;

            case 2:
                serveStudent();
                break;

            case 3:
                cancelRequest();
                break;

            case 4:
                searchStudent();
                break;

            case 5:
                displayQueue();
                break;

            case 6:
                printf("Thank you for using the system!\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while (choice != 6);

    // Free remaining memory
    while (head != NULL)
    {
        struct Node *temp = head;
        head = head->next;
        free(temp);
    }

    tail = NULL;

    return 0;
}
