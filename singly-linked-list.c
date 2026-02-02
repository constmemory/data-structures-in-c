/**
 * Program: Singly Linked List Implementation
 * Language: C
 * Description: Complete implementation of a singly linked list supporting
 * insertion, deletion, traversal, sorting, and reversal operations.
 */

#include<stdio.h>
#include<stdlib.h>

// Definition of the node structure
typedef struct node{
    int data;
    struct node *next;
} node;

// Creates a new node with the given value
node *createNode(int value){
    node *newNode = malloc(sizeof(node));
    if(newNode == NULL){
        printf("Memory allocation error.\n");
        return NULL;
    }
    newNode -> data = value;
    newNode -> next = NULL;
    return newNode;
}

// Checks if the list is empty
int isEmpty(const node *head){
    return (head == NULL);
}

// Calculates the length of the linked list
int length(const node *head){
    int count = 0;
    const node *temp = head;
    while(temp != NULL){
        count++;
        temp = temp -> next;
    }
    return count;
}

// Prints the linked list
void printList(const node *head){
    if(head == NULL){
        printf("List is empty.\n");
        return;
    }
    const node *temp = head;
    while(temp != NULL){
        printf("%d -> ", temp -> data);
        temp = temp -> next;
    }
    printf("NULL\n");
}

// Inserts a node at the beginning of the list
node *insertAtBeginning(node *head, int value){
    node *newNode = createNode(value);
    if(newNode == NULL)
        return head;

    newNode -> next = head;
    return newNode;  // new head
}

// Inserts a node at the end of the list
node *insertAtEnd(node *head, int value){
    node *newNode = createNode(value);
    if(newNode == NULL)
        return head;

    if(head == NULL)
        return newNode;

    node *temp = head;
    while(temp -> next != NULL)
        temp = temp -> next;

    temp -> next = newNode;
    return head;
}

// Inserts a node at a specific position (1-based index)
node *insertAtPosition(node *head, int value, int position){
    if(position <= 1)
        return insertAtBeginning(head, value);

    node *newNode = createNode(value);
    if(newNode == NULL)
        return head;

    node *temp = head;
    for(int i = 1; i < position - 1 && temp != NULL; i++)
        temp = temp -> next;

    if(temp == NULL){
        printf("Invalid position.\n");
        free(newNode);
        return head;
    }

    newNode -> next = temp -> next;
    temp -> next = newNode;
    return head;
}

// Deletes the first node of the list
node *deleteFirstNode(node *head){
    if(head == NULL){
        printf("List is empty.\n");
        return NULL;
    }

    node *temp = head;
    head = head -> next;
    free(temp);
    return head;
}

// Deletes the last node of the list
node *deleteLastNode(node *head){
    if(head == NULL){
        printf("List is empty.\n");
        return NULL;
    }

    if(head -> next == NULL){
        free(head);
        return NULL;
    }

    node *temp = head;
    while(temp -> next -> next != NULL)
        temp = temp -> next;

    free(temp -> next);
    temp -> next = NULL;
    return head;
}

// Deletes a node at a specific position (1-based index)
node *deleteAtPosition(node *head, int position){
    if(head == NULL){
        printf("List is empty.\n");
        return NULL;
    }

    if(position <= 1)
        return deleteFirstNode(head);

    node *temp = head;
    for(int i = 1; i < position - 1 && temp -> next != NULL; i++)
        temp = temp -> next;

    if(temp -> next == NULL){
        printf("Invalid position.\n");
        return head;
    }

    node *toDelete = temp -> next;
    temp -> next = toDelete -> next;
    free(toDelete);
    return head;
}

// Searches for a key in the list (1-based index)
int searchNode(const node *head, int key){
    int position = 1;
    const node *temp = head;

    while(temp != NULL){
        if(temp -> data == key)
            return position;  // position of the key
        temp = temp -> next;
        position++;
    }
    return -1;  // element not found
}

// Counts the number of occurrences of a key in the list
int countOccurrences(const node *head, int key){
    int count = 0;
    const node *temp = head;

    while(temp != NULL){
        if(temp -> data == key)
            count++;
        temp = temp -> next;
    }
    return count;
}

// Finds the middle element of the list (Tortoise and Hare algorithm)
int findMiddle(const node *head){
    if(head == NULL) 
        return -1;  // list is empty

    const node *slow = head;
    const node *fast = head;

    while(fast != NULL && fast -> next != NULL){
        slow = slow -> next;
        fast = fast -> next -> next;
    }
    return slow -> data;
}

// Finds the minimum value in the list
int findMin(const node *head){
    if(head == NULL)
        return -1;  // list is empty

    int min = head -> data;
    const node *temp = head -> next;

    while(temp != NULL){
        if(temp -> data < min)
            min = temp -> data;
        temp = temp -> next;
    }
    return min;
}

// Finds the maximum value in the list
int findMax(const node *head){
    if(head == NULL)
        return -1;  // list is empty

    int max = head -> data;
    const node *temp = head -> next;

    while(temp != NULL){
        if(temp -> data > max)
            max = temp -> data;
        temp = temp -> next;
    }
    return max;
}

// Reverses the linked list
node *reverseList(node *head){
    node *prev = NULL;
    node *current = head;
    node *next = NULL;

    while(current != NULL){
        next = current -> next;
        current -> next = prev;
        prev = current;
        current = next;
    }
    return prev;  // new head
}

// Sorts the linked list (Recursive bubble sort logic)
node *sortList(node *head){
    if(head == NULL || head -> next == NULL)
        return head;

    node *ptr = head;
    int swapped = 0;

    while(ptr -> next != NULL){
        if(ptr -> data > ptr -> next -> data){
            // swap data
            int temp = ptr -> data;
            ptr -> data = ptr -> next -> data;
            ptr -> next -> data = temp;
            swapped = 1;
        }
        ptr = ptr -> next;
    }

    if(swapped)
        return sortList(head);
        
    return head;
}

// Frees the entire linked list
void freeList(node *head){
    node *temp;
    while(head != NULL){
        temp = head;
        head = head -> next;
        free(temp);
    }
}

// Helper function to handle input buffer clearing
void clearInputBuffer(){
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

int main(){
    node *head = NULL;
    int choice, value, position;

    while(1){
        printf("\n--- SINGLY LINKED LIST MENU ---\n");
        printf("1.  Insert at Beginning\n");
        printf("2.  Insert at End\n");
        printf("3.  Insert at Position\n");
        printf("4.  Delete First Node\n");
        printf("5.  Delete Last Node\n");
        printf("6.  Delete at Position\n");
        printf("7.  Print List\n");
        printf("8.  Search Node\n");
        printf("9.  Count Occurrences\n");
        printf("10. Find Middle / Min / Max\n");
        printf("11. Reverse List\n");
        printf("12. Sort List\n");
        printf("13. Length of list\n");
        printf("0.  Exit\n");
        printf("Enter your choice : ");

        if(scanf("%d", &choice) != 1){
            printf("Invalid input! Please enter a number.\n");
            clearInputBuffer();
            continue;
        }

        switch(choice){
            case 1:
                printf("Enter value to insert : ");
                if(scanf("%d", &value) != 1){
                    printf("Invalid input! Please enter a number.\n");
                    clearInputBuffer();
                    continue;
                }
                head = insertAtBeginning(head, value);
                break;

            case 2:
                printf("Enter value to insert : ");
                if(scanf("%d", &value) != 1){
                    printf("Invalid input! Please enter a number.\n");
                    clearInputBuffer();
                    continue;
                }
                head = insertAtEnd(head, value);
                break;

            case 3:
                printf("Enter value to insert : ");
                if(scanf("%d", &value) != 1){
                    printf("Invalid input! Please enter a number.\n");
                    clearInputBuffer();
                    continue;
                }
                printf("Enter position : ");
                if(scanf("%d", &position) != 1){
                    printf("Invalid input! Please enter a number.\n");
                    clearInputBuffer();
                    continue;
                }
                head = insertAtPosition(head, value, position);
                break;

            case 4:
                head = deleteFirstNode(head);
                break;

            case 5:
                head = deleteLastNode(head);
                break;

            case 6:
                printf("Enter position to delete : ");
                if(scanf("%d", &position) != 1){
                    printf("Invalid input! Please enter a number.\n");
                    clearInputBuffer();
                    continue;
                }
                head = deleteAtPosition(head, position);
                break;

            case 7:
                printList(head);
                break;

            case 8:
                printf("Enter value to search : ");
                if(scanf("%d", &value) != 1){
                    printf("Invalid input! Please enter a number.\n");
                    clearInputBuffer();
                    continue;
                }
                position = searchNode(head, value);
                if(position != -1)
                    printf("Value found at position : %d\n", position);
                else 
                    printf("Value not found.\n");
                break;

            case 9:
                printf("Enter value to count : ");
                if(scanf("%d", &value) != 1){
                    printf("Invalid input! Please enter a number.\n");
                    clearInputBuffer();
                    continue;
                }
                printf("Occurrences : %d\n", countOccurrences(head, value));
                break;

            case 10:
                if(isEmpty(head)){
                    printf("List is empty.\n");
                } else{
                    printf("Middle Element : %d\n", findMiddle(head));
                    printf("Minimum Element : %d\n", findMin(head));
                    printf("Maximum Element : %d\n", findMax(head));
                }
                break;

            case 11:
                head = reverseList(head);
                printf("List reversed.\n");
                break;

            case 12:
                head = sortList(head);
                printf("List sorted.\n");
                break;

            case 13:
                printf("Length : %d\n", length(head));
                break;

            case 0:
                printf("Exiting... Memory cleared.\n");
                freeList(head);
                return 0;
            
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}

