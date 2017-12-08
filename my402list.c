/*
 * Author:      Niveditha Ganeson Vijaya (ganesonv@usc.edu)
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>

#include "cs402.h"

#include "my402list.h"

// Returns the number of elements in the list. 

int  My402ListLength(My402List *list)
 {
 	return list->num_members;
 }

 // Returns TRUE if the list is empty. Returns FALSE otherwise. 

int  My402ListEmpty(My402List *list)
 {
 	if((list->anchor.next==list->anchor.prev) && list->anchor.next==&list->anchor && list->anchor.prev==&list->anchor && list->num_members==0)
 		return 1;
 	else
 		return 0;
 }

 // If list is empty, just add obj to the list. Otherwise, add obj after Last(). 
 // This function returns TRUE if the operation is performed successfully and returns FALSE otherwise. 

int  My402ListAppend(My402List *list, void *obj)
 {
 	list->num_members++;
 	My402ListElem *elem= (My402ListElem*)malloc(sizeof(My402ListElem));
 	My402ListElem *temp;
 	elem->next=NULL;
 	elem->prev=NULL;
 	
 	if(elem==NULL)
 	{
 		return 0;
 	}

 	if (My402ListEmpty(list)==1)
	{
		list->anchor.next = elem;
		list->anchor.prev = elem;
		elem->next =&list->anchor;
		elem->prev =&list->anchor;
		elem->obj = obj;

	}

	else
	{
		temp = My402ListLast(list);
		temp->next = elem;
		elem->prev = temp;
		elem->next = &list->anchor;
		list->anchor.prev = elem;
		elem->obj = obj;

	}
	
 	return 1;

 	
 }

 //     If list is empty, just add obj to the list. Otherwise, add obj before First(). 
 //      This function returns TRUE if the operation is performed successfully and returns FALSE otherwise.



int  My402ListPrepend(My402List *list, void *obj)
 {
	list->num_members++;
 	My402ListElem *elem= (My402ListElem*)malloc(sizeof(My402ListElem));
 	elem->next=NULL;
 	elem->prev=NULL;
 	elem->obj=obj;
 	if(My402ListEmpty(list)==1)
 	{
 		list->anchor.next=elem;
 		elem->prev=&list->anchor;
 		elem->next=&list->anchor;
 		list->anchor.prev=elem;
 		return 1;
 	}
 	else if(My402ListEmpty(list)!=1)
 	{
 		elem->next=list->anchor.next;
 		list->anchor.next->prev=elem;
 		elem->prev=&list->anchor;
 		list->anchor.next=elem;
 		return 1;
 	}
 	else
 		return 0;
 }

 // Unlink and delete elem from the list. Please do not delete the object pointed to by elem and do not check if elem is on the list.



void My402ListUnlink(My402List *list, My402ListElem *elem)
 {
 	list->num_members--;
 	elem->prev->next=elem->next;
 	elem->next->prev=elem->prev;
 	free(elem);
 }

 // Unlink and delete all elements from the list and make the list empty. Please do not delete the objects pointed to by the list elements. 

void My402ListUnlinkAll(My402List *list)
 {
 	int i=0;
 	i=list->num_members;
 	My402ListElem *elem;
 	elem=list->anchor.next;
 	while(i!=0)
 	{
 		My402ListUnlink(list,elem);
 		elem=list->anchor.next;
 		i--;
 	}
 	list->num_members=0;
 	list->anchor.next=list->anchor.prev=&list->anchor;
 }



 // Insert obj between elem and elem->next. If elem is NULL, then this is the same as Append(). 
 //This function returns TRUE if the operation is performed successfully and returns FALSE otherwise. Please do not check if elem is on the list. 


int  My402ListInsertAfter(My402List *list, void *obj, My402ListElem *elem)
 {
 	list->num_members++;
 	My402ListElem *after= (My402ListElem*)malloc(sizeof(My402ListElem));
 	after->next=NULL;
 	after->prev=NULL;
 	after->next=elem->next;
 	elem->next->prev=after;
 	after->prev=elem;
 	elem->next=after;
 	after->obj=obj;
 	if(after->next!=NULL || after->prev!=NULL)
 		return 1;
 	else 
 		return 0;
 	return 0;
 }

 // Insert obj between elem and elem->prev. 
 // If elem is NULL, then this is the same as Prepend(). 
 // This function returns TRUE if the operation is performed successfully and returns FALSE otherwise. Please do not check if elem is on the list.

int  My402ListInsertBefore(My402List *list, void *obj, My402ListElem *elem)
 {
 	list->num_members++;
 	My402ListElem *before= (My402ListElem*)malloc(sizeof(My402ListElem));
 	before->next=NULL;
 	before->prev=NULL;
 	before->prev=elem->prev;
 	elem->prev->next=before;
 	before->next=elem;
 	elem->prev=before;
 	before->obj=obj;
 	if(before->next!=NULL || before->prev!=NULL)
 		return 1;
 	else 
 		return 0;
 }

// Returns the first list element or NULL if the list is empty.

My402ListElem *My402ListFirst(My402List *list)
 {
 	if(My402ListEmpty(list)!=1)
 		return list->anchor.next;
 	else
 		return NULL;
 }

 // Returns the last list element or NULL if the list is empty. 

My402ListElem *My402ListLast(My402List *list)
 {
 	if(My402ListEmpty(list)!=1)
 		return list->anchor.prev;
 	else
 		return NULL;
 }

 // Returns elem->next or NULL if elem is the last item on the list. Please do not check if elem is on the list. 

My402ListElem *My402ListNext(My402List *list, My402ListElem *elem)
 {
 	if(elem->next!=&list->anchor)
 		return elem->next;
 	else
 		return NULL;
 }

 // Returns elem->next or NULL if elem is the last item on the list. Please do not check if elem is on the list. 

My402ListElem *My402ListPrev(My402List *list, My402ListElem *elem)
 {
 	if(elem->prev!=&list->anchor)
 		return elem->prev;
 	else
 		return NULL;
 }

 // Returns the list element elem such that elem->obj == obj. Returns NULL if no such element can be found. 

My402ListElem *My402ListFind(My402List *list, void *obj)
 {
 	int i=0;
 	My402ListElem *elem;
 	elem=list->anchor.next;
 	for(i=list->num_members; elem!=&list->anchor; i--)
 	{
 		if(elem->obj==obj)
 		{
 			break;
 		}
 		elem=elem->next;
 	}
 	if(elem!=&list->anchor)
 		return elem;
 	else
 		return NULL;
 }

 // Initialize the list into an empty list. Returns TRUE if all is well and returns FALSE if there is an error initializing the list. 

int My402ListInit(My402List *list)
 {
 	
 	
	list->num_members= 0;
	list->anchor.next = NULL;
	list->anchor.prev = NULL;
	list->anchor.obj = NULL;
 	list->anchor.next=&list->anchor;
 	list->anchor.prev=&list->anchor;
 	if(list->anchor.prev==NULL || list->anchor.next==NULL || list==NULL)
 		return 0;
 	else
 		return 1;

 }
