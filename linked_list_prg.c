#include <stdio.h>  
#include <stdlib.h>  

typedef int value_t;
  
// A linked list node  
struct Node {  
    int value;
    key_t key;
    struct Node* prev;
    struct Node* next;
    struct Node* prev_sorted;
    struct Node* sort;
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
void printList(Sorted_list * list_detail);

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
	list_detail->tails=new_node;
    }

    else{
	    list_detail->head->prev = new_node;
    }
	
    if(list_detail->head_sort == NULL){
	    list_detail->head_sort = new_node;
	    list_detail->tails_sort=new_node;
    }

    else { 
	    if (list_detail->head_sort->key >= new_node->key) {
	        new_node->sort = list_detail->head_sort;
	        new_node->sort->prev_sorted = new_node;
	        list_detail->head_sort = new_node;
	    }

	    else {
	        current = list_detail->head_sort;
		int i=0;
		struct Node* previous=(struct Node*)malloc(sizeof(struct Node));
	        // locate the node after which the new node is to be inserted
	        while (current != NULL && current->key <= new_node->key){
		    previous=current;

	            current =current->sort;
		    if(current == NULL){
			    break;
		    }
		}
	        /* Make the appropriate links */
	        new_node->sort = current;
	        // if the new node is not inserted at the end of the list
	        if (current != NULL){
			
	            	new_node->prev_sorted=current->prev_sorted;
			current->prev_sorted = new_node;
			//new_node->prev_sorted->sort=new_node;
			previous->sort=new_node;
		}else{
			new_node->prev_sorted=previous;
			previous->sort=new_node;
			list_detail->tails_sort=new_node;

		}
		
	        //current->sort = new_node;
	        //new_node->prev_sorted = current;
		//current->sort =new_node;
		
	    }
    }
    list_detail->head = new_node;
} 

void append(Sorted_list * list_detail, value_t  value, key_t  key){
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));  
    struct Node* current = (struct Node*)malloc(sizeof(struct Node));
 
    new_node->value = value;
    new_node->key = key;
  
    new_node->next = NULL;
    new_node->prev = list_detail->tails;;

    new_node->sort = NULL;
    new_node->prev_sorted = NULL;
    
    if (list_detail->tails == NULL){
        list_detail->head = new_node;
	list_detail->tails = new_node;
    }

    else{
	    list_detail->tails->next = new_node;
    }
	
    if(list_detail->tails_sort == NULL){
	    list_detail->head_sort = new_node;
	    list_detail->tails_sort = new_node;
    }

    else { 
	    if (list_detail->head_sort->key >= new_node->key) {
	        new_node->sort = list_detail->head_sort;
	        new_node->sort->prev_sorted = new_node;
	        list_detail->head_sort = new_node;
	    }

	    else {
	        current = list_detail->head_sort;
		int i=0;
		struct Node* previous=(struct Node*)malloc(sizeof(struct Node));
	        // locate the node after which the new node is to be inserted
	        while (current != NULL && current->key <= new_node->key){
		    previous=current;

	            current =current->sort;
		    if(current == NULL){
			    break;
		    }
		}
	        /* Make the appropriate links */
	        new_node->sort = current;
	        // if the new node is not inserted at the end of the list
	        if (current != NULL){
			
	            	new_node->prev_sorted=current->prev_sorted;
			current->prev_sorted = new_node;
			//new_node->prev_sorted->sort=new_node;
			previous->sort=new_node;
		}else{
			new_node->prev_sorted=previous;
			previous->sort=new_node;
			list_detail->tails_sort=new_node;

		}
		
	        //current->sort = new_node;
	        //new_node->prev_sorted = current;
		//current->sort =new_node;
		
	    }
    }
    list_detail->tails = new_node;

}


//Function to print the list according to insertion order as well as key sort order
void printList(Sorted_list * list_detail)  
{  
    struct Node* last;  
    struct Node* node;
    struct Node* n2 = (struct Node*)malloc(sizeof(struct Node));

    node = list_detail->head;
    printf("\nList by insertion order: \n");
    while (node != NULL) {  
        printf(" (%d, %d) ", node->value, node->key);  
        node = node->next; 
    }
    printf("\nList by key_sort order: \n");

    n2 = list_detail->head_sort;
    while (n2 != NULL) {  
        printf(" (%d, %d) ", n2->value, n2->key); 
        n2 = n2->sort; 
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
	*value=deleted_Node_Value;
	*key=deleted_Node_Key;
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
		if(list_detail->tails->sort != NULL){// check tails and tails_sort are same
                
			list_detail->tails->sort->prev=list_detail->tails->prev_sorted;
			list_detail->tails->prev_sorted->sort=list_detail->tails->sort;
		}
		else{
			list_detail->tails->prev_sorted->sort=NULL;
		}

		
                //update tails
                list_detail->tails=list_detail->tails->prev;
                list_detail->tails->next=NULL;
                free(ptr);
        }
        *value=deleted_Node_Value;
        *key=deleted_Node_Key;
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
		list_detail->head_sort= NULL;
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
	*value=deleted_Node_Value;
	*key=deleted_Node_Key;
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
        if(list_detail->tails_sort == NULL){
                printf("\n UNDERFLOW");
        }
        else if(list_detail->tails_sort->prev==NULL){
                deleted_Node_Value=list_detail->tails_sort->value;
                deleted_Node_Key=list_detail->tails_sort->key;
                //onlt one element in list
                list_detail->tails= NULL;
                list_detail->tails_sort=NULL;
                list_detail->head=NULL;
                list_detail->head_sort=NULL;
                free(list_detail->tails_sort);
                printf("\nNode deleted\n");
        }
        else{
                ptr =list_detail->tails_sort;
                deleted_Node_Value=list_detail->tails_sort->value;
                deleted_Node_Key=list_detail->tails_sort->key;
                //update tails
                if(list_detail->tails_sort->next != NULL){// if tails and tails_sort are same

                        list_detail->tails_sort->next->prev=list_detail->tails_sort->prev;
                }
                list_detail->tails_sort->prev->next=list_detail->tails_sort->next;


                //update tails
                list_detail->tails_sort=list_detail->tails_sort->prev;
                list_detail->tails_sort->next=NULL;
                free(ptr);
        }
        *value=deleted_Node_Value;
        *key=deleted_Node_Key;
        return 1;
}

void empty_list(Sorted_list * list_detail){
    struct Node* node;
    struct Node* node_sort;
    node = list_detail->head;
    node_sort = list_detail->head_sort;
    while (node != NULL) {  
       	 node->value = 0;
	 node->key = 0;
	 node = node->next; 
    }
	
    while (node_sort != NULL) {  
       	 node_sort->value = 0;
	 node_sort->key = 0;
	 node_sort = node_sort->sort; 
    }

}

void destroy_list(Sorted_list * list_detail){
	struct Node* current = list_detail->head;
	struct Node* current_sort = list_detail->head_sort;
	struct Node* nxt = (struct Node *)malloc(sizeof(struct Node *));
	struct Node* nxt_sort = (struct Node *)malloc(sizeof(struct Node *));

	while(current!= NULL){
		nxt = current->next;
		free(current);
		current = nxt;
	}

	list_detail->head = NULL;
	list_detail->head_sort = NULL;
}
	       
/* Main function of the program*/
int main()  
{  
    /* initilizing head and head_sort for the linked list */
    Sorted_list * list_detail=(Sorted_list *)malloc(sizeof(Sorted_list));
    list_detail->head=NULL;
    list_detail->head_sort=NULL;
    list_detail->tails=NULL;
    list_detail->tails_sort=NULL;
    //struct Node
    push(list_detail,  1, 62);  
    push(list_detail,  2, 5);  
    append(list_detail, 10, 13);
    push(list_detail,  3, 4);
    push(list_detail,  4, 26);  
    push(list_detail,  5, 2);  
    push(list_detail,  6, 1);  
    push(list_detail,  7, 42);  
    append(list_detail,  7, 12);  
//  push(list_detail,  7, 0);  

  //append(&head, &head_sort,  15, );
    /*append(&head, &head_sort, 14, 0.58);*/
    printf("Final print list detail\n");
    printList(list_detail);  
    int value,key;

    printf("\nremove_first");
    remove_first(list_detail,&value,&key);

    printf("\nremove_first %d  %d",value,key);
   
    printList(list_detail);  
    
    printf("\nremove_last");
    remove_last(list_detail,&value,&key);

    printf("\nremove_last %d  %d",value,key);
   
    printList(list_detail);  
    printf("\nremove_smallest_key");
    remove_smallest_key(list_detail,&value,&key);

    printf("\nremove_smallest_key %d  %d",value,key);
   
    printList(list_detail);  
    printf("\nremove_largest_key");
    remove_largest_key(list_detail,&value,&key);

    printf("\nremove_largest_key %d  %d",value,key);
   
    printList(list_detail);  
 
    //int sz = size(head);
    //printf("\nSize of linked list: %d", sz);


    empty_list(list_detail);
    printList(list_detail);

    destroy_list(list_detail);
    printList(list_detail);


    getchar();  
    return 0;  
}  
