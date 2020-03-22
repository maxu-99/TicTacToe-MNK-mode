/*****************************************************************************
 * Author : Mahmudul Hossain
 * Date : 17/10/2019
 * Purpose : Generic Double-Ended-Doubly-LinkedList to store data
 * Reference : Taken from UCP P07 
 * https://lms.curtin.edu.au/webapps/assignment/uploadAssignment?course_id=_89173_1&content_id=_7107867_1&mode=view
 * **************************************************************************/


#include "LinkedList.h"
#include <stdlib.h>
#include <stdio.h>

/*Create a linked list with 0 nodes */
LinkedList* createLinkedList()
{
    /*Create a Linked list my allocation in the memory */
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));

    /*Set the head and tail to NULL since it has no ListNodes */
    list -> head = NULL;
    list -> tail = NULL;

    /*Since there are currently no elements, set the size to be 0 */
    list -> size = 0; 

    return list;
}


/*Insert at the start of the linked list */
void insertStart(LinkedList* list, void* entry)
{
    /*Create a new list node */
    LinkedListNode* newNode = (LinkedListNode*)malloc(sizeof(LinkedListNode));
    LinkedListNode* prevHead;

    /*Make the list node hold the entry */
    newNode -> data = entry; 

    /*If the list is empty */
    if((list -> head == NULL) && (list -> tail == NULL))
    {
        /*Both head and tail points to new node */
        list -> head = newNode;
        list -> tail = newNode;

        /*Since there is only one ListNode currently exisiting, it should not */
        /*Point to any other node */
        newNode -> next = NULL;
        newNode -> prev = NULL;
    }
    /*If a ListNode already exists */
    else
    {
        /*The new node should point to the head */
        newNode -> next = list -> head;

        /*Since this new node will be the first element, it should not point to */
        /* any previous ListNodes */
        newNode -> prev = NULL;

        /*prevHead is now the head */                       
        prevHead = newNode -> next;

        /*The first node now points to the new node */
        prevHead -> prev = newNode;

        /*Head now points to the new node */
        list -> head = newNode;
    }

    /*Increment the size of the linked list */
    list -> size++; 
}

/*Remove from the start of the linked list */
void* removeStart(LinkedList* list)
{
    /*log will store the value that the removed node will contain */
    void* log = NULL; 

    /*Store the node to be removed */
    LinkedListNode* temp;

    /*Can not remove node is the list is already empty */
    if(list -> size > 0)
    {
        /*If there is only one node in the linked list */
        if((list -> tail ->prev == NULL)&&(list -> head ->next == NULL))
        {

            /*Stores the first node of the linked list */
            temp = list -> head;

            /*The data stored in the first node is retrieved */
            log = temp -> data;
        
            /*Set both head and tail to null since there was only a single node   */
            /* to be removed */
            list -> tail = NULL;
            list -> head = NULL;

            /*Free the memory allocated for the node that is removed*/
            free(temp);
        }
        /*If more than one element exists */
        else
        {
            temp = list -> head;
            log = temp -> data;
    
            /*Head now points to the next available node */
            list -> head = list -> head -> next;

            /*The consecutive node does not link to the previous node pointed */
            /*by the head */
            list -> head -> prev = NULL;   

            /*Dealloacte the memory for the removed node */
            free(temp);
        }

        /*Decrement the size of the list after successful removal */
        list -> size --; 
    }

    return log;
}

/*Insert a new node at the end of the linked list */
void insertLast(LinkedList* list, void*  entry)
{
    /*Allocate memory for the new node */
    LinkedListNode* newNode = (LinkedListNode*)malloc(sizeof(LinkedListNode));

    /*Keep track of the current last node which needs to be connected to the */
    /*new node */
    LinkedListNode* prevNode;

    /*Value is assigned to the new node */
    newNode -> data = entry;

    /*If linked list is empty */
    if((list -> head == NULL) && (list -> tail == NULL))
    {
        /*Both head and tail points to the new node since now only a single */
        /*node exists */
        list -> head = newNode;
        list -> tail = newNode;

        /*The new node must not point to any other node since only a single */
        /*node exists in the linked list */
        newNode -> next = NULL;
        newNode -> prev = NULL;
    }
    /*If an element already exists */
    else
    {
        /*Store the current node the tail is pointing to */
        prevNode = list ->tail;

        /*New node must points its next to null since there should be no nodes */
        /*after the end of linked list */
        newNode -> next = NULL;

        newNode -> prev = prevNode ;

        /*Tail now becomes the new node */
        list -> tail = newNode;
 
        /*The previous tail node now points to the new node */       
        prevNode -> next = newNode;
    }

    /*After successful addition increment the size counter of the linked list */
    list -> size++; 
}

/*Remove node from the end of the linked list */
void* removeLast(LinkedList* list)
{
    /*log will store the value which the removed node had */   
    void* log = NULL;  

    /*temp will store the removed node */
    LinkedListNode* temp;

    /*Remove node from a non-empty linked list */
    if(list -> size > 0)
    {
        /*If the linked list has only one node to be removed */
        if((list -> tail ->prev == NULL)&&(list -> head ->next == NULL))
        {
            temp = list -> tail;
            log = temp ->data;
            /*Make the linked list empty */
            list -> tail = NULL;
            list -> head = NULL;
            /*Deallocate the memory of the removed node */
            free(temp);
        }
        else 
        { 
            /*The node to be removed is the one that the tail is pointing at */
            temp = list -> tail;
            log = temp -> data;

            /*Tail now becomes the previous node */
            list -> tail = list -> tail -> prev;

            /*The tail must not point to any next node since it will itself */
            /*be the last node */
            list -> tail -> next = NULL;

            /*Deallocate the memory of the removed node */
            free(temp);
        }

        /*After successful removal decrement the size of the linked list */
        list -> size --;  
    }

    return log;
}

/*Since this is a generic linked list, an extra function pointer is imported */
/*which will assist to determine the data type of the value stored in each */
/*node and print in specific format*/
void printLinkedList(LinkedList* list, print display)
{
    /*Start from the head */
    LinkedListNode *current = list -> head;
    void* log; 

    /*Iterate from head to the end of linked list */
    while(current != NULL)
    {

        log = current -> data;
        /*Pass the value of the linked list to a specified display function */
        (*display)(log);

        /*Current node now points to the next node */
        current = current -> next;
    }
}

/*Since this is a generic linked list, an extra function pointer is imported */
/* which will help to free the memory by having information of the datatype */
void freeLinkedList(LinkedList* list, deallocate freeMem)
{
    /*The current node and a reference to the next node to be freed */
    LinkedListNode *node, *nextNode;

    /*Start freeing from the head */
    node = list -> head;

    /*Iterate from head to the end of the linked list */
    while(node != NULL)
    {
        /*Since the current node will be free, we need to have a reference to */
        /* the next node beforehand */
        nextNode = node -> next;

        /*Free the value stored in the linked list according to its datatype */
        (*freeMem)(node -> data);
        
        /*Free the current node */
        free(node);

        /*Node now becomes the next node to be freed */
        node = nextNode;
    }

    /*Free the whole linked list */
    free(list);
}




