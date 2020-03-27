#include <stdio.h>  
#include <stdlib.h>  

typedef int value_t;
//typedef i key_t;
  
// A linked list node  
struct Node {  
    int value;
    key_t key;
    struct Node* prev, *next;
    struct Node* prev_sorted, *sort;
};  

//Sorted_list data type
typedef struct {
    struct Node* head;
    struct Node* head_sort;
    struct Node* tails;
    struct Node* tails_sort;
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
void push(Sorted_list * list_detail, value_t  value, key_t  key)  
{  
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));  
    struct Node* current = (struct Node*)malloc(sizeof(struct Node));
 
    new_node->value = value;
    new_node->key = key;
  
    new_node->next = list_detail->head;
    new_node->prev = NULL;

    new_node->sort = NULL;
    new_node->prev_sorted = NULL;

    if (list_detail->head == NULL){
        list_detail->head = new_node;
    }

    else{
	    list_detail->head->prev = new_node;
    }
	
    if(list_detail->head_sort == NULL){
	    list_detail->head_sort = new_node;
    }

    else {
	    if (list_detail->head_sort->key >= new_node->key) {
	        new_node->sort = list_detail->head_sort;
	        new_node->sort->prev_sorted = new_node;
	        list_detail->head_sort = new_node;
	    }
	
	    else {
	        current = list_detail->head_sort;
	
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
    list_detail->head = new_node;
}  

//Function to print the list according to insertion order as well as key sort order
void printList(Sorted_list * list_detail)  
{  
    struct Node* last;  
    struct Node* node;
    struct Node* n2 = (struct Node*)malloc(sizeof(struct Node));

    node = list_detail->head;
    printf("List by insertion order: \n");
    while (node != NULL) {  
        printf(" (%d, %d) ", node->value, node->key);  
        node = node->next; 
    }
    printf("\nList by key_sort order: \n");

    n2 = list_detail->head_sort;
    while (n2 != NULL) {  
        printf(" (%d, %d) ", n2->value, n2->key); 
        n2 = n2->next; 
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
		list_detail->head= NULL;
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
                list_detail->tails= NULL;
                list_detail->tails_sort=NULL;
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

	       
			

/* Main function of the program*/
int main()  
{  
    /* initilizing head and head_sort for the linked list */
    Sorted_list * list_detail=(Sorted_list *)malloc(sizeof(Sorted_list));

    //struct Node
    push(list_detail,  7, 62);  
    push(list_detail,  7, 2);  
    push(list_detail,  5, 1);
    push(list_detail,  7, 26);  
    push(list_detail,  17, 162);  
    push(list_detail,  7, 612);  
    push(list_detail,  7, 42);  
//    push(list_detail,  7, 12);  
//    push(list_detail,  7, 0);  

    //append(&head, &head_sort,  15, 0.59);
    /*append(&head, &head_sort, 14, 0.58);*/
    printList(list_detail);  
  
    //int sz = size(head);
    //printf("\nSize of linked list: %d", sz);
    getchar();  
    return 0;  
}  
