#include <stdio.h>  
#include <stdlib.h>  
#include<string.h>
//typedef double key_t;
#include "sorted_list.h"
typedef int value_t;
#define INSERTED_ORDER 1
#define SORTED_ORDER 2
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

value_t add2(value_t x)
{
	return x+2;
}
value_t add_2_number(value_t x,value_t y)
{
	return x+y;
}
value_t subtract_2_number(value_t x,value_t y)
{
	return x-y;
}
value_t square_Of_A_Number(value_t x)
{
	return x*x;
}
value_t square_and_add_number(value_t x,value_t y)
{
	return x + square_Of_A_Number(x);
}

value_t sum(Sorted_list * list,int order){
   return reduce(list,add_2_number,0,order);

}
void print_array(value_t * arr, int size){

    	for(int z=0;z<size;z++){
            printf("\n     %d",*arr);
            arr--;
    	}

}
value_t * diff (Sorted_list * list1,Sorted_list *list2, int order)
{
	if(list1->size != list2->size)
	{ return NULL;}
	
  //    value_t *arr=(value_t *)malloc(sizeof(value_t)*(list2->size));
	return map_2_array(list1,list2,subtract_2_number,order);
//	print_array(arr,list2->size);	
}
Sorted_list * square(Sorted_list *list)
{
	return map(list,square_Of_A_Number);
}

void *sum_of_sq_diff(Sorted_list *list1,Sorted_list* list2,int order)
{
	  if(list1->size != list2->size)
	        { return NULL;}
	  printf("%d",map_2_reduce(list1,list2,subtract_2_number,square_and_add_number,0,order));

}

void printList_square(Sorted_list * list_detail)  
{  
    struct Node* node;
    
    node = list_detail->head;
    printf("print_all:  Insertion Order \n");
    while (node != NULL) {  
        printf("     %d\n", node->value);  
        node = node->next; 
    }

}

/* Main function of the program*/
int main( int argc, char *argv[] )  
{  
	   /* initilizing head and head_sort for the linked list */
    Sorted_list * list[10];// = (Sorted_list *)malloc(sizeof(Sorted_list));
    int i = 0;    
 
    while(i<10){
    	list[i] = (Sorted_list *)malloc(sizeof(Sorted_list));
	list[i]->head=NULL;
    	list[i]->head_sort=NULL;
    	list[i]->tails=NULL;
    	list[i]->tails_sort=NULL;
	i++;
    }

    char chunk[50];
    char commands[50][50];
    size_t malloc_size = 100;
    value_t value;
    key_t key;
    int j = 0;
    int k = 0;
    char *a;
    i = 0;
    if(argc == 1){
    	printf("input commands. press ctrl+D to stop entering inputs\n");
	char *input_string;
                size_t input_string_length = 50;
                input_string = (char *) malloc(input_string_length);

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
	char *cmd = strtok(a, "|");
	int n;
		if(strcmp(cmd,"rem_first")==0){
			cmd = strtok(NULL, "\0");
			sscanf(cmd, "%d", &n);
			remove_first(list[n], &value, &key);
			printf("rem_first|%d:  %d %d \n",n, key, value);
		}
		else if(strcmp(cmd,"rem_last")==0){
			cmd = strtok(NULL, "\0");
			sscanf(cmd, "%d", &n);
			remove_first(list[n], &value, &key);
			printf("rem_last|%d:  %d %d \n",n, key, value);
		}
		else if(strcmp(cmd,"rem_small")==0){
			cmd = strtok(NULL, "\0");
			sscanf(cmd, "%d", &n);
			remove_smallest_key(list[n], &value, &key);
			printf("rem_small|%d:  %d %d \n",n, key, value);
		}
		else if(strcmp(cmd,"rem_large")==0){
			cmd = strtok(NULL, "\0");
			sscanf(cmd, "%d", &n);	
			remove_largest_key(list[n],&value,&key);
			printf("rem_large|%d:  %d %d\n",n, key, value);
		}
		else if(strcmp(cmd,"print_all")==0){
			cmd = strtok(NULL, "\0");
			sscanf(cmd, "%d", &n);	
			printList(list[n]);
		}
		else if(strcmp(cmd,"print_sort")==0){
			cmd = strtok(NULL, "\0");
			sscanf(cmd, "%d", &n);	
			printList_sort(list[n]);
		}
	
		else if((cmd[0] == 'p')){
			int tempk, tempv;
			char *s;
			cmd = strtok(NULL, " ");
			sscanf(cmd, "%d", &n);	
			
			cmd = strtok(NULL, " ");
			sscanf(cmd, "%d", &tempk);

			cmd = strtok(NULL, " ");
			sscanf(cmd, "%d", &tempv);
			
			printf("p|%d:          %d  %d\n",n, tempk, tempv);
			push(list[n], tempv, tempk);
		}

		else if((cmd[0] == 'a')){
			int tempk, tempv;
			char *s;
			cmd = strtok(NULL, " ");
			sscanf(cmd, "%d", &n);	
			
			cmd = strtok(NULL, " ");
			sscanf(cmd, "%d", &tempk);

			cmd = strtok(NULL, " ");
			sscanf(cmd, "%d", &tempv);
			
			printf("a|%d:          %d  %d\n",n, tempk, tempv);
			append(list[n], tempv, tempk);
		}

		else if(strcmp(cmd, "size")==0){
			cmd = strtok(NULL, "\0");
			sscanf(cmd, "%d", &n);	

			int sz = size(list[n]);
			printf("size|%d:       List size = %d\n",n, list[n]->size);
		}

		else if(strcmp(cmd, "empty")==0){
			cmd = strtok(NULL, "\0");
			sscanf(cmd, "%d", &n);	

			empty_list(list[n]);
			printf("empty|%d:      size = %d\n",n, list[n]->size);

		}
		else if(strcmp(cmd, "sum")==0){
			value_t sum_val;

			cmd = strtok(NULL, " ");
			sscanf(cmd, "%d", &n);	
			
			cmd = strtok(NULL, " ");

			if(strcmp(cmd, "SORTED_ORDER") == 0){
				sum_val = sum(list[n],SORTED_ORDER);
			}
			else if(strcmp(cmd, "INSERTED_ORDER") == 0){
				sum_val = sum(list[n],INSERTED_ORDER);
			}

			printf("sum:        list = %d, result = %d\n",n, sum_val);

		}

		else if(strcmp(cmd, "square")==0){
			cmd = strtok(NULL, " ");
			sscanf(cmd, "%d", &n);	
			printList_square(square(list[n]));
		}

		else if(strcmp(cmd, "diff")==0){
			int m;
			cmd = strtok(NULL, ":");
			sscanf(cmd, "%d", &n);
			cmd = strtok(NULL, " ");
			sscanf(cmd, "%d", &m);
			cmd = strtok(NULL, "\0");
			
			printf("\ndiff:       list1 = %d, list2 = %d", n, m);
			if(strcmp(cmd, "SORTED_ORDER") == 0){
				print_array(diff(list[n],list[m],SORTED_ORDER),list[m]->size);
			}
			else if(strcmp(cmd, "INSERTED_ORDER") == 0){
				print_array(diff(list[n],list[m],INSERTED_ORDER),list[m]->size);
			}
	
		}

		else if(strcmp(cmd, "sum_sq_d")==0){
			int m;
			cmd = strtok(NULL, ":");
			sscanf(cmd, "%d", &n);
			cmd = strtok(NULL, " ");
			sscanf(cmd, "%d", &m);
			cmd = strtok(NULL, "\0");
			
			printf("\ndiff:       list1 = %d, list2 = %d", n, m);
			if(strcmp(cmd, "SORTED_ORDER") == 0){
				printf("sum_sq_d:   list1 = %d, list2 = %d, result = ",n,m);
				sum_of_sq_diff(list[n],list[m],SORTED_ORDER);
			}
			else if(strcmp(cmd, "INSERTED_ORDER") == 0){
				printf("sum_sq_d:   list1 = %d, list2 = %d, result = ",n,m);
				sum_of_sq_diff(list[n],list[m],INSERTED_ORDER);
			}
	
		}

	j++;
    }
	
	/*
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
	sum_of_sq_diff(list_detail,list2,INSERTED_ORDER);*/
    getchar();  
    return 0;  
}  
