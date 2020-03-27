#include <stdio.h>  
#include <stdlib.h>  
  
// A linked list node  
struct Node {  
    int data;
    double key;
    struct Node* prev, *next;
    struct Node* prev_sorted, *sort;
};  
//Sorted_list data type
typedef struct Sorted_list{
    struct Node* head= NULL;
    struct Node * head_sort=NULL;
    struct Node *tails=NULL;
    struct Node * tails_sort=NULL;
    int size ;//store the node count
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

//append function of the program
void append(struct Node** head_ref, struct Node** head_sort_ref, int value_t, double key_t)
{
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));  
    struct Node* current = (struct Node*)malloc(sizeof(struct Node));
    struct Node* last;
    
    last = *head_ref; 
    new_node->data = value_t;
    new_node->key = key_t;
    new_node->next = NULL;

    if (*head_ref == NULL)
    {
        new_node->prev = NULL;
        *head_ref = new_node;
        return;
    }

    while (last->next != NULL)
        last = last->next;

    last->next = new_node;

    new_node->prev = last;

    if (*head_sort_ref == NULL){
	*head_sort_ref = new_node;
    }

    else {
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

}



//Function to print the list according to insertion order as well as key sort order
void printList(struct Node* node, struct Node* node_sort)  
{  
    struct Node* last;  
    printf("List by insertion order: \n");
    while (node != NULL) {  
        printf(" (%d, %0.2f) ", node->data, node->key);  
        last = node;  
        node = node->next; 
    }

    printf("\nList by ke sort order: \n");
    while (node_sort != NULL) {  
        printf(" (%d, %0.2f) ", node_sort->data, node_sort->key);  
        last = node_sort;  
        node_sort = node_sort->sort; 
    }


}

/*
 *function to find  node by key
 *@param Sorted_list *
 *@param key_t *
 */
//TODO
/*
 *function to remove first node
 *@param Sorted_list *
 *@param value_t
 *@param key_t *
 */
int remove_first(Sorted_list * ADT,value_t * value, key_t * key)
{
	struct Node *ptr;
	value_t deleted_Node_Value;
        key_t 	deleted_Node_Key;
	if(Sorted_list->head == NULL){
		printf("\n UNDERFLOW");
	}
	else if(Sorted_list->head->next==NULL){
		deleted_Node_Value=Sorted_list->head->value;
		deleted_Node_Key=Sorted_list->head->key;
		//onlt one element in list
		Sorted_list->head= NULL
		Sorted_list->head_sort=NULL;
		Sorted_list->tails=NULL;
		Sorted_list->tails_sort=NULL;
		free(Sorted_list->head);
		printf("\nNode deleted\n");
	}
	else{
		ptr =Sorted_list->head;
		deleted_Node_Value=Sorted_list->head->value;
                deleted_Node_Key=Sorted_list->head->key;
		//update head_sort
		Sorted_list->head->sort->prev=Sorted_list->head->prev_sorted;
		Sorted_list->head->prev_sorted->sort=Sorted_list->head->sort;
		//update head
                Sorted_list->head=Sorted_list->head->next;
		Sorted_list->head->prev=NULL;
		free(ptr);
	}
	value=deleted_Node_Value;
	key=deleted_Node_Key;
	return 1;
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
    append(&head, &head_sort,  15, 0.59);
    push(&head, &head_sort,  6, 0.50);
    push(&head, &head_sort,  12, 1.26);
    push(&head, &head_sort,  7, 0.65);
    append(&head, &head_sort, 14, 0.58);
    printList(head, head_sort);  
  
    int sz = size(head);
    printf("\nSize of linked list: %d", sz);

    getchar();  
    return 0;  
}  
