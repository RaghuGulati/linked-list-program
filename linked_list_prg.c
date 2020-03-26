#include <stdio.h>  
#include <stdlib.h>  
  
// A linked list node  
struct Node {  
    int data;
    double key;
    struct Node* prev, *next;
    struct Node* prev_sorted, *sort;
/*    struct Node* prev;
    struct Node* prev_sorted;  */
};  

/*push function to add the node to the head of the list*/
void push(struct Node** head_ref, int new_data, double new_key)  
{  
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));  
    struct Node* current = (struct Node*)malloc(sizeof(struct Node));
 
    new_node->data = new_data;
    new_node->key = new_key;
  
    new_node->next = (*head_ref);
    new_node->prev = NULL;

    new_node->sort = NULL;
    new_node->prev_sorted = NULL;

//    (*head_ref) = new_node;  
    // if list is empty
    if (*head_ref == NULL){
        *head_ref = new_node;
    }

    // if the node is to be inserted at the beginning of the doubly linked list
    else {
	    (*head_ref)->prev = new_node;

	    if ((*head_ref)->key >= new_node->key) {
	        new_node->sort = *head_ref;
	        new_node->sort->prev_sorted = new_node;
	        *head_ref = new_node;
	    }
	
	    else {
	        current = *head_ref;
	
	        // locate the node after which the new node
	        // is to be inserted
	        while (current->sort != NULL && current->sort->key < new_node->key){
	            current = current->sort;
		}

	        /* Make the appropriate links */
	        new_node->sort = current->sort;
	
	        // if the new node is not inserted at the end of the list
	        if (current->sort != NULL){
	            new_node->sort->prev_sorted = new_node;
		}

	        current->sort = new_node;
	        new_node->prev_sorted = current;
	    }
   }
    (*head_ref) = new_node;
}  


// This function prints contents of linked list starting from the given node  
void printList(struct Node* node)  
{  
    struct Node* last;  
//    node = main;

    while (node != NULL) {  
        printf(" (%d, %0.2f) ", node->data, node->key);  
        last = node;  
        node = node->next; 
    }
}  
  
/* Driver program to test above functions*/
int main()  
{  
    /* Start with the empty list */
    struct Node* head = NULL;
    struct Node* head_sort = NULL;
    //struct Node
//    push(&head, 7, 0.62);  
    push(&head, 1, 1.95);  
    push(&head, 4, 1.85);
    push(&head, 6, 1.65);
    push(&head, 8, 1.4);
    push(&head, 5, 0.92);
    push(&head, 15, 0.59);
    push(&head, 6, 0.50);
    push(&head, 12, 1.26);

//    push(&head, 7, 0.65);
    printf("Created DLL is: ");  
    printList(head);  
  
  /*  int size = length(head);
    printf("\nSize of linked list: %d \n", size);*/

    getchar();  
    return 0;  
}  
