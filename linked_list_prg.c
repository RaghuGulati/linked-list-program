#include <stdio.h>  
#include <stdlib.h>  
  
// A linked list node  
struct Node {  
    int data;
    double key;
    struct Node* prev, *next;
    struct Node* prev_sorted, *sort;
};  

//size function to calculate the size of linked list
int size(struct Node* head) {
   int length = 0;
   struct Node *current;
	
   for(current = head; current != NULL; current = current->next){
      length++;
   }
	
   return length;
}

/*push function to add the node to the head of the list*/
void push(struct Node** head_ref, struct Node** head_sort_ref, int value_t, double key_t)  
{  
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));  
    struct Node* current = (struct Node*)malloc(sizeof(struct Node));
 
    new_node->data = value_t;
    new_node->key = key_t;
  
    new_node->next = (*head_ref);
    new_node->prev = NULL;

    new_node->sort = NULL;
    new_node->prev_sorted = NULL;

    if (*head_sort_ref == NULL){
        *head_ref = new_node;
	*head_sort_ref = new_node;
    }

    else {
	    (*head_ref)->prev = new_node;

	    if ((*head_sort_ref)->key >= new_node->key) {
	        new_node->sort = *head_sort_ref;
	        new_node->sort->prev_sorted = new_node;
	        *head_sort_ref = new_node;
	    }
	
	    else {
	        current = *head_sort_ref;
	
	        // locate the node after which the new node is to be inserted
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

//Function to print the list according to insertion order as well as key sort order
void printList(struct Node* node, struct Node* node_sort)  
{  
    struct Node* last;  
    printf("List by insertion order: ");
    while (node != NULL) {  
        printf(" (%d, %0.2f) ", node->data, node->key);  
        last = node;  
        node = node->next; 
    }

    printf("\nList by ke sort order: ");
    while (node_sort != NULL) {  
        printf(" (%d, %0.2f) ", node_sort->data, node_sort->key);  
        last = node_sort;  
        node_sort = node_sort->sort; 
    }


}  
  
/* Main function of the program*/
int main()  
{  
    /* initilizing head and head_sort for the linked list */
    struct Node* head = NULL;
    struct Node* head_sort = NULL;

    //struct Node
    push(&head, &head_sort,  7, 0.62);  
    push(&head, &head_sort,  1, 1.95);  
    push(&head, &head_sort,  4, 1.85);
    push(&head, &head_sort,  6, 1.65);
    push(&head, &head_sort,  8, 1.4);
    push(&head, &head_sort,  5, 0.92);
    push(&head, &head_sort,  15, 0.59);
    push(&head, &head_sort,  6, 0.50);
    push(&head, &head_sort,  12, 1.26);
    push(&head, &head_sort,  7, 0.65);
    printList(head, head_sort);  
  
    int sz = size(head);
    printf("\nSize of linked list: %d \n", sz);

    getchar();  
    return 0;  
}  
