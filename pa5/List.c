//Katerina Chinnappan
//CruzID: kachinna
//PA 5

#include<stdio.h>
#include<stdlib.h>
#include "List.h"


// private NodeObj type
typedef struct NodeObj
{
   int data;
   struct NodeObj* next;
   struct NodeObj* prev;
}
NodeObj;


// private Node type
typedef NodeObj *Node;

// private ListObj type
typedef struct ListObj
{
   Node front;
   Node back;
   Node cursor;
   int length;
   int index;
}  ListObj;

/*****CONSTRUCTORS - DESTRUCTORS*****/
// newNode()
// Returns reference to new Node object. Initializes next and data fields.
// Private.
Node newNode(int data){
   Node N = malloc(sizeof(NodeObj));
   N->data = data;
   N->prev = NULL;
   N->next = NULL;
   return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
// Private.
void freeNode(Node* pN) {
   if(pN != NULL && *pN != NULL) {
      free(*pN);
      *pN = NULL;
   }
}

// new List()
// Returns reference to new empty List object.
List newList(void){
   List L;
   L = malloc(sizeof(ListObj));
   L->front = L->back = NULL;
   L->cursor = NULL;
   L->length = 0;
   L->index = -1;
   return(L);
}

// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.S
void freeList(List* pL) {
   if(pL != NULL && *pL != NULL) {
      Node temp = (*pL)->front;
      while(temp != NULL) {
         Node current = temp;
         temp = temp->next;
         free(current);
      }

      //deallocates the memory
      free(*pL);
      *pL = NULL;
   }
}

/*****ACCESS FUNCTIONS*****/

// Returns the length of L.
int length(List L)
{
   if(L == NULL)
    {
      printf("Invalid: calling length() on NULL List reference\n");
      exit(1);
   }
   return L->length;
}

//Returns the index of L
int index1(List L)
{
   if(L == NULL)
    {
      printf("Invalid: calling index() on NULL List reference\n");
      exit(1);
   }
   return L->index;
}

// Returns front element. Pre: length()>0
int front(List L) {
   if(L == NULL)
    {
      printf("Invalid: calling front() on NULL List reference\n");
      exit(1);
   }
   if(L->length < 1)
   {
      printf("Invalid: calling front() on empty List reference\n");
      exit(1);
   }
   return L->front->data;
}

// Returns back element. Pre: length()>0
int back(List L)
{
   if(L == NULL)
    {
      printf("Invalid: calling back() on NULL List reference\n");
      exit(1);
   }
   if(L->length < 1)
   {
      printf("Invalid: calling back() on empty List reference\n");
      exit(1);
   }
   return L->back->data;
}

// Returns cursor element. Pre: length()>0, index()>=0
int get(List L)
{
   if(L == NULL)
    {
      printf("Invalid: calling get() on NULL List reference\n");
      exit(1);
   }
   if(L->index < 0)
   {
      printf("Invalid: calling get() with an undefined index on List\n");
      exit(1);
   }
   if(L->length < 1)
   {
      printf("Invalid: calling get() on empty List reference\n");
      exit(1);
   }
   return L->cursor->data;
}

// Returns true if this List and L are the same integer
// sequence. The cursor is ignored in both lists.
int equals(List A, List B)
{
   if(A == NULL || B == NULL)
    {
      printf("Invalid: calling equals() on NULL List reference\n");
      exit(1);
   }
   if(A->length != B->length)
   {
      return 0;
   }

   //set the current node in front to B->front
   Node currentFront = B->front;
   Node temp = A->front;

   while(currentFront->next != NULL && temp->next != NULL)
   {
      if(currentFront->data != temp->data)
         return 0;
      currentFront = currentFront->next;
      temp = temp->next;
   }
   return 1;
}

int isEmpty(List L)
{
    if(L == NULL)
    {
        printf("Invalid: cannot call isEmpty() on empty List");
        exit(1);
    }
    return (L->length == 0);
}
/*****ACCESS FUNCTIONS END*****/


/*****MANIPULATION FUNCTIONS*****/

// Resets this List to its original empty state.
void clear(List L)
{
   if(L == NULL)
    {
      printf("Invalid: calling clear() on NULL List reference\n");
      exit(1);
   }
   Node temp = L->front;
   while(temp != NULL)
   {
      Node current = temp;
      temp = temp->next;

      //calling free(Node)
      //deallocates the memory
      free(current);
   }

   //set front, back of List and cursor to NULL
   L->front = NULL;
   L->back = NULL;
   L->cursor = NULL;

   //set the length back to 0
   L->length = 0;
   //set the index back to -1
   L->index = -1;
}

// If List is non-empty, places the cursor under the specified element,
// otherwise does nothing.
void moveTo(List L, int i)
{
    if(L == NULL)
    {
      printf("Invalid: calling moveFront() on NULL List reference\n");
      exit(1);
   }

    if(0 <= i && i <= length(L) - 1)
    {
      L->cursor = L->front;
      L->index = 0;
      int j;
      for(j = 0; j < i; j++ )
      {
         if(L->cursor == L->back)
         {

         L->cursor = NULL;
         }
         else
         {
         L->cursor=L->cursor->next;
         }
         L->index++;
      }
   }
   else
    {
      L->index = -1;
      L->cursor = NULL;
   }
}

// If List is non-empty, places the cursor under the front element,
// otherwise does nothing.
void moveFront(List L)
{
   if(L == NULL)
    {
      printf("Invalid: calling moveFront() on NULL List reference\n");
      exit(1);
   }
   if(L->length > 0)
   {
      L->cursor = L->front;
      L->index = 0;
   }
}

// If List is non-empty, places the cursor under the back element,
// otherwise does nothing.
void moveBack(List L)
{
   if(L == NULL)
    {
      printf("Invalid: calling moveBack() on NULL List reference\n");
      exit(1);
   }
   if(L->length > 0)
   {
      L->cursor = L->back;
      L->index = L->length - 1;
   }
}

// If cursor is defined and not at front, moves cursor one step toward
// front of this List, if cursor is defined and at front, cursor becomes
// undefined, if cursor is undefined does nothing.
void movePrev(List L)
{
   if(L == NULL)
    {
      printf("Invalid: calling movePrev() on NULL List reference\n");
      exit(1);
   }
   if(L->cursor != NULL && L->index != 0)
   {
      L->cursor = L->cursor->prev;
      --L->index;
   }
   else if(L->cursor != NULL && L->index == 0)
   {
      L->cursor = NULL;
      L->index = -1;
   }
}

// If cursor is defined and not at back, moves cursor one step toward
// back of this List, if cursor is defined and at back, cursor becomes
// undefined, if cursor is undefined does nothing.
void moveNext(List L)
{
   if(L == NULL)
    {
      printf("Invalid: calling moveNext() on NULL List reference\n");
      exit(1);
   }
   if(L->cursor == L->back || L->index == -1)
   {
       L->cursor = NULL;
       L->index = -1;
   }
   else
   {
       L->cursor =  L->cursor->next;
       L->index++;
   }
}

// Insert new element into this List. If List is non-empty,
// insertion takes place before front element.
void prepend(List L, int data)
{
   if(L == NULL)
    {
      printf("Invalid: calling prepend() on NULL List reference\n");
      exit(1);
   }

   Node newEl = newNode(data);

   if(length(L) <= 0)
   {
       L->front =  L->back = newEl;
       L->length++;
   }
   else
   {
       L->front->prev = newEl;
       newEl->next = L->front;
       L->front = newEl;
       L->index++;
       L->length++;
   }
}

// Insert new element into this List. If List is non-empty,
// insertion takes place after front element.
void append(List L, int data)
{
   if(L == NULL)
    {
      printf("L->back = temp; calling append() on NULL List reference\n");
      exit(1);
   }
    Node newEl = newNode(data);
    if(length(L) <= 0)
    {
        L->back = L->front = newEl;
    }
    else
    {
        L->back->next = newEl;
        newEl->prev = L->back;
        L->back = newEl;
    }
    L->length++;
}

// Inserts new element after cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, int data)
{
   if(L == NULL)
    {
      printf("Invalid: calling insertAfter() on NULL List reference\n");
      exit(1);
   }
   if(L->index < 0)
   {
      printf("Invalid: insertAfter() called with an undefined index on List");
      exit(1);
   }
   if(L->length < 1)
   {
      printf("Invalid: insertAfter() called on an empty List");
      exit(1);
   }
   Node temp = newNode(data);

   if(L->cursor->next != NULL)
   {
        L->cursor->next->prev = temp;
   }

   else
      L->back = temp;
   L->cursor->next = temp;
   ++L->length;
}

// Insert new element before cursor.
// Pre: length() > 0, index() >= 0
void insertBefore(List L, int data)
{
   if(L == NULL)
    {
      printf("Invalid: calling insertBefore() on NULL List reference\n");
      exit(1);
   }
   if(L->index < 0)
   {
      printf("Invalid: insertBefore() called with an undefined index on List");
      exit(1);
   }
   else
   {
       if(L->index == 0)
       {
           prepend(L, data);
       }
       else
       {
           Node newEl = newNode(data);
           Node previous = L->cursor->prev;
           newEl->prev = previous;
           newEl->next = L->cursor;
           previous->next = newEl;
           L->cursor->prev = newEl;
           L->length++;
           L->index++;

       }
   }

}

// Deletes the front element.
// Pre: length() > 0
void deleteFront(List L)
{
   if(L == NULL)
    {
      printf("Invalid: deleteFront() called on NULL List reference\n");
      exit(1);
   }
   if(L->length < 1)
   {
      printf("Invalid: deleteFront() called on an empty List\n");
      exit(1);
   }
   if(L->cursor == L->front)
   {
      L->cursor = NULL;
      L->index = -1;
   }

   Node temp = L->front;
   L->front = L->front->next;
   L->front->prev = NULL;
   --L->length;
   freeNode(&temp);
}

// Deletes the back element.
// Pre: length() > 0
void deleteBack(List L)
{
   if(L == NULL)
    {
      printf("Invalid: deleteBack() called on NULL List reference\n");
      exit(1);
   }
   if(L->length < 1)
   {
      printf("Invalid: deleteBack() called on an empty List\n");
      exit(1);
   }
   if(L->cursor == L->back)
   {
      L->cursor = NULL;
      --L->index;
   }

   if(L->back == L->front)
   {
       L->front = NULL;
   }

   Node temp = L->back;
   if(L->back->prev != NULL)
   {
       L->back = L->back->prev;
   }

   L->back->next = NULL;
   --L->length;
   freeNode(&temp);
}

// Deletes cursor element, making cursor undefined.
// Pre: length() > 0, index() >= 0
void delete(List L)
{
   if(L == NULL)
    {
      printf("Invalid: delete() called on NULL List reference\n");
      exit(1);
   }
   if(L->length < 1)
   {
      printf("Invalid: delete() called with an undefined index on List\n");
      exit(1);
   }
   if(L->index < 0)
   {
      printf("Invalid: delete() called on empty List");
      exit(1);
   }
   if(L->cursor == L->back)
   {
      deleteBack(L);
   }
   else if(L->cursor == L->front)
   {
      deleteFront(L);
   }
   else
   {
      Node temp = L->cursor;
      L->cursor->prev->next = L->cursor->next;
      L->cursor->next->prev = L->cursor->prev;
      freeNode(&temp);
      L->cursor = NULL;
      L->index = -1;
      --L->length;
   }
}

/*****MANIPULATION FUNCTIONS*****/

// Overrides Object's toString method. Returns a String
// representation of this List consisting of a space
// separated sequence of integers, with front on left.
void printList(FILE* out, List L)
{
   Node temp = L->front;
   while(temp != NULL)
    {
      fprintf(out,"%d ", temp->data);
      temp = temp->next;
   }
}

// Returns a new List representing the same integer sequence as this
// List. The cursor in the new list is undefined, regardless of the
// state of the cursor in this List. This List is unchanged.
List copyList(List L)
{
   List c = newList();
   Node temp = L->front;
   while(temp != NULL)
    {
      append(c, temp->data);
      temp = temp->next;
   }
   return c;
}
