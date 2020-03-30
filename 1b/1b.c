#include <stdio.h>  
#include <stdlib.h>  
#include<string.h>
//typedef double key_t;
#include "sorted_list.h"
typedef int value_t;
#define INSERTED_ORDER 1
#define SORTED_ORDER 2

/* function description
 * map the values using function pointer.
 * @param Sorted_list * Sorted_list pointer
 * @param value_t (*f)(value_t) function pointer
 * @return Sorted_list pointer of new link list.
 */
Sorted_list * map( Sorted_list * old_list_detail, value_t (*f)(value_t)){
	Sorted_list * new_list= (Sorted_list *)malloc(sizeof(Sorted_list));
	struct Node* old_node;

	//new_list->size=old_list_detail->size;
	old_node = old_list_detail->head;
        //printf("print_all:  Insertion Order \n");
    	while (old_node != NULL) {
        
		//struct Node * new_node=(Node*)malloc(sizeof(struct Node));
		//	printf("     %d  %d\n", node->key, node->value);
		value_t value;
		value=(*f)(old_node->value);
		append(new_list,value,old_node->key);
        	old_node = old_node->next;

		
    	}
	return new_list;
	

}

/* function description
 * reduce the values of link list using function pointer.
 * @param Sorted_list * Sorted_list pointer
 * @param value_t (*f)(value_t)(value_t) function pointer
 * @param value_t init
 * @param int order specify order while reducing 
 * @return value_t single value after reduce
 */

value_t reduce( Sorted_list * list_detail, value_t (*f)(value_t,value_t),value_t init,int order){
        struct Node* node;
	value_t value = init;
	if(order == INSERTED_ORDER){
        	node = list_detail->head;
        	while (node != NULL) {
    
                	value=(*f)(value,node->value);
                	node = node->next;
        	}
        	return value;
	}
	else if(order ==SORTED_ORDER)
	{      node = list_detail->head_sort;
                while (node != NULL) {

                        value=(*f)(value,node->value);
                        node = node->sort;
                }
                return value;
	}   

}

/* function description
 * first applying map, and then reduce using function pointers for both
 * @param Sorted_list * Sorted_list pointer
 * @param value_t (*map_fn)(value_t) function pointer for map
 * @param value_t (*reduce_fn)(value_t)(value_t) function pointer for reduce
 * @param value_t init
 * @param int order specify order while reducing
 * @return value_t return single value.
 */

value_t map_reduce( Sorted_list * list_detail, value_t (*map_fn)(value_t), value_t (*reduce_fn)(value_t,value_t),value_t init,int order){
        struct Node* node;
        value_t value = init;
        if(order == INSERTED_ORDER){
                node = list_detail->head;
                while (node != NULL) {
			value_t tempvalue;
    			tempvalue=(*map_fn)(node->value);
                        value=(*reduce_fn)(value,tempvalue);
                        node = node->next;
                }
                return value;
        }
        else if(order ==SORTED_ORDER)
        {      node = list_detail->head_sort;
                while (node != NULL) {
			value_t tempvalue;
                        tempvalue=(*map_fn)(node->value);
                        value=(*reduce_fn)(value,tempvalue);
                        node = node->sort;
                }
                return value;
        }

}
/* function description
 * first applying map, and then reduce using function pointers for both
 * @param Sorted_list * first Sorted_list pointer 
 * @param Sorted_list * second Sorted_list pointer
 * @param value_t (*map_fn)(value_t) function pointer for map
 * @param int order specify order while reducing
 * @return value_t * return array of value_t.
 */

value_t * map_2_array( Sorted_list * list1,Sorted_list * list2, value_t (*map_fn)(value_t,value_t),int order){
        if(list2->size != list1->size)
		return NULL;

	struct Node* node1,*node2;
	value_t value ;
 value_t * array=(value_t*)malloc(sizeof(value_t)*list1->size);
	int counter=0;
	if(order == INSERTED_ORDER){
        	node1 = list1->head;
		node2= list2->head;
		
        	while (node1 != NULL && node2 != NULL) {
    
                	value=(*map_fn)(node1->value,node2->value);
                	//array[counter]=value;
			
                	*array=value;
			//counter++;
			array++;
			node1 = node1->next;
			node2= node2->next;
        	}
	     	return --array;
	}
	else if(order ==SORTED_ORDER)
	{      node1 = list1->head_sort;
	      node2 = list2->head_sort;
                while (node1 != NULL && node2 != NULL) {

                        
                        value=(*map_fn)(node1->value,node2->value);
			//array[counter]=value;
			
                	*array=value;
			array++;
			//counter++;
                        node1 = node1->sort;
                        node2 = node2->sort;
                }
                return --array;
	}   

}

/* function description
 * first applying map, and then reduce using function pointers for both
 * @param Sorted_list * first Sorted_list pointer
 * @param Sorted_list * second Sorted_list pointer
 * @param value_t (*map_fn)(value_t) function pointer for map
 * @param value_t (*reduce_fn)(value_t)(value_t) function pointer for reduce
 * @param value_t init
 * @param int order specify order while reducing
 * @return value_t return single value.
 */

value_t  map_2_reduce( Sorted_list * list1,Sorted_list * list2, value_t (*map_fn)(value_t,value_t),value_t (*reduce_fn)(value_t,value_t),value_t init,int order){


       	struct Node* node1,*node2;
        value_t value = init;
        int counter=0;
        if(order == INSERTED_ORDER){
                node1 = list1->head;
		node2= list2->head;

                while (node1 != NULL && node2 != NULL) {
			value_t tempvalue;
                        tempvalue=(*map_fn)(node1->value,node2->value);
                        value=(*reduce_fn)(value,tempvalue);
                        node1 = node1->next;

                        node2 = node2->next;
                }
                return value;
        }
        else if(order ==SORTED_ORDER)
        {
                node1 = list1->head;
		node2= list2->head;

                while (node1 != NULL && node2 != NULL) {
			value_t tempvalue;
                        tempvalue=(*map_fn)(node1->value,node2->value);
                        value=(*reduce_fn)(value,tempvalue);
                        node1 = node1->next;

                        node2 = node2->next;
                }
		return value; 
        }

}
//need to remove add2 fn after all completion
value_t add2(value_t x)
{
	return x+2;
}

/* function description
 * function to add 2 numbers (used to pass as function pointer)
 * @param value_t first number
 * @param value_t second number
 * @return value_t return sum of numbers.
 */

value_t add_2_number(value_t x,value_t y)
{
	return x+y;
}

/* function description
 * function to subtract 2 numbers (used to pass as function pointer)
 * @param value_t first number
 * @param value_t second number
 * @return value_t return diffrence of numbers.
 */

value_t subtract_2_number(value_t x,value_t y)
{
	return x-y;
}

/* function description
 * function to square a number used to pass as function pointer
 * @param value_t  number
 * @return value_t return square of number.
 */

value_t square_Of_A_Number(value_t x)
{
	return x*x;
}

/* function description
 * function to square second argument then add square to first argument used to pass as function pointer
 * @param value_t first number
 * @param value_t second number
 * @return value_t return sum of number after square of second argument.
 */

value_t square_and_add_number(value_t x,value_t y)
{
	return x + square_Of_A_Number(x);
}
value_t sum(Sorted_list * list,int order){
   return reduce(list,add_2_number,0,order);

}

/* function description
 * print array
 * @param value_t * arr arr to print
 * @param int size size of array
 * @return void.
 */

void print_array(value_t * arr, int size){

    	for(int z=0;z<size;z++){
            printf("\n     %d",*arr);
            arr--;
    	}

}

/* function description
 *takes two sorted lists of the same size, returns NULL if the sizes are different
 *produces an array whose values are the differences of the values in the sorted lists args
 *third argument that can be set to SORTED_ORDER or INSERTED_ORDER 
 *in order to follow the appropriate links.
 * @param Sorted_list * list1 
 * @param Sorted_list * list2
 * @param int order
 * @return value_t * pointer to array of diffrence.
 */

value_t * diff (Sorted_list * list1,Sorted_list *list2, int order)
{
	if(list1->size != list2->size)
	{ return NULL;}
	
  //    value_t *arr=(value_t *)malloc(sizeof(value_t)*(list2->size));
	return map_2_array(list1,list2,subtract_2_number,order);
//	print_array(arr,list2->size);	
}
/* function description
 * takes a sorted list and produces a new sorted list whose value at a node equals 
 * the original value (not key) squared
 * @param Sorted_list * list
 * @return Sorted_list * return pointer to new Sorted_list
 */


Sorted_list * square(Sorted_list *list)
{
	return map(list,square_Of_A_Number);
}



/* function description
 * takes two sorted lists of the same size
 *returns NULL if the sizes are different produces a value computed as follows:
 * 1. at each node position, take the difference between the values
 * 2. square the resulting difference
 * 3. sum across all nodes into a single result
 * third argument that can be set to SORTED_ORDER or INSERTED_ORDER
 * in order to follow the appropriate links
 * @param Sorted_list * list1
 * @param Sorted_list * list2
 * @param int order
 * @return void * because we need to return NULL if size of link lists is different .
 */
void *sum_of_sq_diff(Sorted_list *list1,Sorted_list* list2,int order)
{
	  if(list1->size != list2->size)
	        { return NULL;}
	  printf("%d",map_2_reduce(list1,list2,subtract_2_number,square_and_add_number,0,order));

}

/* Main function of the program*/
int main( int argc, char *argv[] )  
{  
    /* initilizing head and head_sort for the linked list */
    Sorted_list * list_detail=(Sorted_list *)malloc(sizeof(Sorted_list));
    list_detail->head=NULL;
    list_detail->head_sort=NULL;
    list_detail->tails=NULL;
    list_detail->tails_sort=NULL;
    int i = 0;    
    char chunk[50];
    char commands[50][50];
    size_t malloc_size = 100;
    value_t value;
    key_t key;
    int j = 0;
    int k = 0;
    char *a;

    if(argc == 1){
    	printf("input commands. press ctrl+D to stop entering inputs\n");
	char *input_string;
                size_t input_string_length = 50;
                input_string = (char *) malloc(input_string_length);

                printf("Enter records data and add EOF with Ctrl+D:\n");

                while(getline(&input_string, &input_string_length, stdin) != -1)
                {
                        input_string[strcspn(input_string, "\n")] = 0;
			strcpy(commands[i], input_string);
			i++;
		}
    }

    else if(argc > 2){
    	printf("Too many arguments supplied");
    }
    else{
        FILE *fp;
	fp = fopen(argv[1],"r");

	while(fgets(commands[i],50, fp) != NULL) {
	        commands[i][strlen(commands[i]) -1] = '\0';
		i++;
	}
    }

    while(j<i){
	a = commands[j];
		if(strcmp(a,"rem_first")==0){
			remove_first(list_detail, &value, &key);
			printf("rem_first:  %d %d \n", key, value);
		}
		else if(strcmp(a,"rem_last")==0){
			remove_last(list_detail, &value, &key);
			printf("rem_last:   %d %d \n", key, value);

		}
		else if(strcmp(a,"rem_small")==0){
			remove_smallest_key(list_detail,&value,&key);
			printf("rem_small:  %d %d\n", key, value);
		}
		else if(strcmp(a,"rem_large")==0){
			remove_largest_key(list_detail,&value,&key);
			printf("rem_large:  %d %d\n", key, value);
		}
		else if(strcmp(a,"print_all")==0){
			printList(list_detail);
		}
		else if(strcmp(a,"print_sort")==0){
			printList_sort(list_detail);
		}
	
		else if((a[0] == 'p')){
			int tempk, tempv;
			char *s;
			s = a;
			char *p = strtok(a," ");
			p = strtok(NULL, " ");
			sscanf(p, "%d", &tempk);
			p = strtok(NULL, " ");
			sscanf(p, "%d", &tempv);
			push(list_detail, tempv, tempk);
		}

		else if((a[0] == 'a')){
			int tempk, tempv;
			char *s;
			s = a;
			char *p = strtok(s," ");
			p = strtok(NULL, " ");
			sscanf(p, "%d", &tempk);
			p = strtok(NULL, " ");
			sscanf(p, "%d", &tempv);
			append(list_detail, tempv, tempk);
		}

		else if(strcmp(a, "size")==0){
			int sz = size(list_detail);
			printf("size:       List size = %d\n", list_detail->size);
		}

		else if(strcmp(a, "empty")==0){
			empty_list(list_detail);
			printf("empty:      size = %d\n", list_detail->size);

		}
	j++;
    }
	Sorted_list * list2 =(Sorted_list *)malloc(sizeof(Sorted_list));
printf(" size %d",list_detail->size);
   	list2= map(list_detail,add2);
  //  printList(map(list_detail,add2));
   // printList(map(list_detail,square));
   // value_t getvalue=reduce(list_detail,sum,0,INSERTED_ORDER);
   // value_t *arr=(value_t *)malloc(sizeof(value_t)*(list2->size));
    
    //arr=map_2_array(list_detail,list2,diff,INSERTED_ORDER);
   
  // for(int z=0;z<list2->size;z++){
//	    printf("%d\n",*arr);
//
//arr--;
  //  }
    
//    printf("\n value %d\n",getvalue);
     printf("sum %d",sum(list_detail,INSERTED_ORDER));
	print_array(diff(list_detail,list2,INSERTED_ORDER),list2->size);
	printList(square(list_detail));
	sum_of_sq_diff(list_detail,list2,INSERTED_ORDER);
    getchar();  
    return 0;  
}  
