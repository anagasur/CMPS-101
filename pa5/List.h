//Katerina Chinnappan
//CruzID: kachinna
//PA 5
//Based on Tantalo examples, FILEIO

#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED


typedef struct ListObj* List;

/*****CONSTRUCTORS - DESTRUCTORS*****/
// Returns reference to new empty Queue object.
List newList(void);

// Frees all heap memory associated with Queue *pQ, and sets *pQ to NULL.
void freeList(List* pL);
/*****CONSTRUCTORS - DESTRUCTORS END*****/

/*****ACCESS FUNCTIONS*****/
int length(List L);

int index1(List L);

int front(List L);

int back(List L);

int get(List L);

int equals(List A, List B);

int isEmpty(List L);

/*****ACCESS FUNCTIONS END*****/


/*****MANIPULATION FUNCTIONS*****/
void clear(List L);

void moveTo(List L, int i);

void moveFront(List L);

void moveBack(List L);

void movePrev(List L);

void moveNext(List L);

void prepend(List L, int data);

void append(List L, int data);

void insertBefore(List L, int data);

void insertAfter(List L, int data);

void deleteFront(List L);

void deleteBack(List L);

void delete(List L);
/*****MANIPULATIONS FUNCTIONS END*****/


void printList(FILE* out, List L);

List copyList(List L);




#endif // LIST_H_INCLUDED

