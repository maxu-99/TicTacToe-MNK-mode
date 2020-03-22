
/*****************************************************************************
 * Author : Mahmudul Hossain
 * Date : 17/10/2019
 * Purpose : Generic Double-Ended-Doubly-LinkedList to store data
 * Reference : Taken from UCP P07 
 * https://lms.curtin.edu.au/webapps/assignment/uploadAssignment?course_id=_89173_1&content_id=_7107867_1&mode=view
 * **************************************************************************/


typedef struct LinkedListNode
{
    void *data;
    struct LinkedListNode *next;
    struct LinkedListNode *prev;
} LinkedListNode;

typedef struct
{
    LinkedListNode* head;
    LinkedListNode* tail;
    int size;  
} LinkedList;

/*Since the linked list is generic, it has no information on
 * how to print the data stored, hence a function pointer is used direct to 
 * a defined printing function for that specific data */ 
typedef void (*print)(void*);


/*Since the linked list is generic, it has no information on
 * how to free the data stored, hence a function pointer is used direct to 
 * a defined freeing function for that specific data */ 

typedef void (*deallocate)(void*);

void insertStart(LinkedList*, void* );

void* removeStart(LinkedList*);

void insertLast(LinkedList*,void*) ;

void* removeLast(LinkedList*);

void printLinkedList(LinkedList*, print display);

void freeLinkedList(LinkedList*, deallocate freeMem);

LinkedList* createLinkedList();

