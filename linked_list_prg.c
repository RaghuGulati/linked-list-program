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
typedef struct {
    struct Node* head;
    struct Node * head_sort;
    struct Node *tails;
    struct Node * tails_sort;
    int size ;//store the node count
}Sorted_list;
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
int remove_first(Sorted_list * list_detail,value_t * value, key_t * key)
{
	struct Node *ptr;
	value_t deleted_Node_Value;
        key_t 	deleted_Node_Key;
	if(list_detail->head == NULL){
		printf("\n UNDERFLOW");
	}
	else if(list_detail->head->next==NULL){
		deleted_Node_Value=list_detail->head->value;
		deleted_Node_Key=list_detail->head->key;
		//onlt one element in list
		list_detail->head= NULL
		list_detail->head_sort=NULL;
		list_detail->tails=NULL;
		list_detail->tails_sort=NULL;
		free(list_detail->head);
		printf("\nNode deleted\n");
	}
	else{
		ptr =list_detail->head;
		deleted_Node_Value=list_detail->head->value;
                deleted_Node_Key=list_detail->head->key;
		//update head_sort
		list_detail->head->sort->prev=list_detail->head->prev_sorted;
		if(list_detail->head->prev_sorted != NULL){//if head and head_sort are same
			list_detail->head->prev_sorted->sort=list_detail->head->sort;
		}
		//update head
                list_detail->head=list_detail->head->next;
		list_detail->head->prev=NULL;
		free(ptr);
	}
	value=deleted_Node_Value;
	key=deleted_Node_Key;
	return 1;
}
/*
 *function to remove last  node
 *@param Sorted_list *
 *@param value_t
 *@param key_t *
 */
int remove_last(Sorted_list * list_detail,value_t * value, key_t * key)
{
        struct Node *ptr;
        value_t deleted_Node_Value;
        key_t   deleted_Node_Key;
        if(list_detail->tails == NULL){
                printf("\n UNDERFLOW");
        }
        else if(list_detail->tails->prev==NULL){
                deleted_Node_Value=list_detail->tails->value;
                deleted_Node_Key=list_detail->tails->key;
                //onlt one element in list
                list_detail->tails= NULL
                list_detail->tail_sort=NULL;
                list_detail->head=NULL;
                list_detail->head_sort=NULL;
                free(list_detail->tails);
                printf("\nNode deleted\n");
        }
        else{
                ptr =list_detail->tails;
                deleted_Node_Value=list_detail->tails->value;
                deleted_Node_Key=list_detail->tails->key;
                //update tails_sort
		if(list_detail->tails->sort != NULL){// if tails and tail_sort are same
                
			list_detail->tails->sort->prev=list_detail->tails->prev_sorted;
		}
		list_detail->tails->prev_sorted->sort=list_detail->tails->sort;
			
		
                //update tails
                list_detail->tails=list_detail->tails->prev;
                list_detail->tails->next=NULL;
                free(ptr);
        }
        value=deleted_Node_Value;
        key=deleted_Node_Key;
        return 1;
}

/*
 *function to remove node having smallest value
 *@param Sorted_list *
 *@param value_t
 *@param key_t *
 */
int remove_smallest_key(Sorted_list * list_detail,value_t * value, key_t * key)
{
	struct Node *ptr;
	value_t deleted_Node_Value;
        key_t 	deleted_Node_Key;
	if(list_detail->head_sort == NULL){
		printf("\n UNDERFLOW");
	}
	else if(list_detail->head_sort->sort==NULL){
		deleted_Node_Value=list_detail->head_sort->value;
		deleted_Node_Key=list_detail->head_sort->key;
		//onlt one element in list
		list_detail->head_sort= NULL
		list_detail->head=NULL;
		list_detail->tails=NULL;
		list_detail->tails_sort=NULL;
		free(list_detail->head_sort);
		printf("\nNode deleted\n");
	}
	else{
		ptr =list_detail->head_sort;
		deleted_Node_Value=list_detail->head_sort->value;
                deleted_Node_Key=list_detail->head_sort->key;
		//update head_sort
		list_detail->head_sort->next->prev=list_detail->head_sort->prev;
		if(list_detail->head_sort->prev != NULL){//if head and head_sort are same
			list_detail->head_sort->prev->next=list_detail->head->next;
		}
		//update head
                list_detail->head_sort=list_detail->head_sort->sort;
		list_detail->head_sort->prev_sorted=NULL;
		free(ptr);
	}
	value=deleted_Node_Value;
	key=deleted_Node_Key;
	return 1;
}

/*
 *function to remove node having largest key
 *@param Sorted_list *
 *@param value_t
 *@param key_t *
 */
int remove_largest_key(Sorted_list * list_detail,value_t * value, key_t * key)
{
        struct Node *ptr;
        value_t deleted_Node_Value;
        key_t   deleted_Node_Key;
        if(list_detail->tail_sort == NULL){
                printf("\n UNDERFLOW");
        }
        else if(list_detail->tail_sort->prev==NULL){
                deleted_Node_Value=list_detail->tail_sort->value;
                deleted_Node_Key=list_detail->tail_sort->key;
                //onlt one element in list
                list_detail->tails= NULL
                list_detail->tail_sort=NULL;
                list_detail->head=NULL;
                list_detail->head_sort=NULL;
                free(list_detail->tail_sort);
                printf("\nNode deleted\n");
        }
        else{
                ptr =list_detail->tail_sort;
                deleted_Node_Value=list_detail->tail_sort->value;
                deleted_Node_Key=list_detail->tail_sort->key;
                //update tails
                if(list_detail->tail_sort->next != NULL){// if tails and tail_sort are same

                        list_detail->tail_sort->next->prev=list_detail->tail_sort->prev;
                }
                list_detail->tail_sort->prev->next=list_detail->tail_sort->next;


                //update tails
                list_detail->tail_sort=list_detail->tail_sort->prev;
                list_detail->tail_sort->next=NULL;
                free(ptr);
        }
        value=deleted_Node_Value;
        key=deleted_Node_Key;
        return 1;
}


	       
			

/* Main function of the program*/
int main()  
{  
    /* initilizing head and head_sort for the linked list */
    struct Node* head = NULL;
    struct Node* head_sort = NULL;
    Sorted_list * list_detail=(Sorted_list *)malloc(sizeof(Sorted_list));

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
