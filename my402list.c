//
//  my402list.c
//  warmup1
//
//  Created by zhangkaiqiang on 1/21/17.
//  Copyright © 2017 zhangkaiqiang. All rights reserved.
//
/******************************************************************************/
/* Important CSCI 402 usage information:                                      */
/*                                                                            */
/* This fils is part of CSCI 402 programming assignments at USC.              */
/*         53616c7465645f5f2e8d450c0c5851acd538befe33744efca0f1c4f9fb5f       */
/*         3c8feabc561a99e53d4d21951738da923cd1c7bbd11b30a1afb11172f80b       */
/*         984b1acfbbf8fae6ea57e0583d2610a618379293cb1de8e1e9d07e6287e8       */
/*         de7e82f3d48866aa2009b599e92c852f7dbf7a6e573f1c7228ca34b9f368       */
/*         faaef0c0fcf294cb                                                   */
/* Please understand that you are NOT permitted to distribute or publically   */
/*         display a copy of this file (or ANY PART of it) for any reason.    */
/* If anyone (including your prospective employer) asks you to post the code, */
/*         you must inform them that you do NOT have permissions to do so.    */
/* You are also NOT permitted to remove or alter this comment block.          */
/* If this comment block is removed or altered in a submitted file, 20 points */
/*         will be deducted.                                                  */
/******************************************************************************/

/*
 * Author:      William Chia-Wei Cheng (bill.cheng@acm.org)
 *
 * @(#)$Id: listtest.c,v 1.1 2016/12/21 19:22:34 william Exp $
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <errno.h>

#include "cs402.h"

#include "my402list.h"

//Returns the number of elements in the list.
int  My402ListLength(My402List* list) {
    int len = list->num_members;
    return len;
}

//Returns TRUE if the list is empty. Returns FALSE otherwise.
int  My402ListEmpty(My402List* list) {
    if (list->num_members == 0) {
        return TRUE;
    }
    else {
        return FALSE;
    }
}

/*  
 If list is empty, just add obj to the list. Otherwise, add obj after Last(). This function returns TRUE if the
 operation is performed successfully and returns FALSE otherwise.
 */
int  My402ListAppend(My402List* list, void* obj) {
    My402ListElem *newElement = (My402ListElem*)malloc(sizeof(My402ListElem));
    if (newElement == NULL) {
        fprintf(stderr, "Unable to allocate new memory");
        return FALSE;
    }
    newElement->obj = obj;
    if (My402ListEmpty(list) == TRUE) {
        list->anchor.next = newElement;
        (list->anchor).prev = newElement;
        newElement->next = &list->anchor;
        newElement->prev = &list->anchor;
    }
    else {
        newElement->next = &list->anchor;
        newElement->prev = list->anchor.prev;
        list->anchor.prev->next = newElement;
        list->anchor.prev = newElement;
    }
    list->num_members++;
    return TRUE;
}

/*
 If list is empty, just add obj to the list. Otherwise, add obj before First(). This function returns TRUE if the 
 operation is performed successfully and returns FALSE otherwise.
*/
int  My402ListPrepend(My402List* list, void* obj) {
    My402ListElem *newElement = (My402ListElem*)malloc(sizeof(My402ListElem));
    if (newElement == NULL) {
        fprintf(stderr, "Unable to allocate new memory");
        return FALSE;
    }
    newElement->obj = obj;
    if (My402ListEmpty(list) == TRUE) {
        list->anchor.next = newElement;
        (list->anchor).prev = newElement;
        newElement->next = &list->anchor;
        newElement->prev = &list->anchor;
    }
    else {
        newElement->next = list->anchor.next;
        newElement->prev = &list->anchor;
        list->anchor.next->prev = newElement;
        list->anchor.next = newElement;
    }
    list->num_members++;
    return TRUE;
}

/*
 Unlink and delete elem from the list. Please do not delete the object pointed to by elem and do not check if elem 
 is on the list.
 */
void My402ListUnlink(My402List* list, My402ListElem* elem) {
    if (My402ListEmpty(list) == TRUE || elem == NULL) {
        return;
    }
    elem->prev->next = elem->next;
    elem->next->prev = elem->prev;
    list->num_members--;
    free(elem);
}

/*
 Unlink and delete all elements from the list and make the list empty. Please do not delete the objects pointed to 
 be the list elements.
 */
void My402ListUnlinkAll(My402List* list) {
    if (My402ListEmpty(list) == TRUE) {
        return;
    }
    My402ListElem *elem=NULL;
    for (elem = My402ListFirst(list); elem != NULL; elem = My402ListNext(list, elem)) {
        elem->prev->next = elem->next;
        elem->next->prev = elem->prev;
        free(elem);
    }
    list->num_members = 0;
}

/*
 Insert obj between elem and elem->next. If elem is NULL, then this is the same as Append(). This function returns 
 TRUE if the operation is performed successfully and returns FALSE otherwise. Please do not check if elem is on the 
 list.
 */
int  My402ListInsertAfter(My402List* list, void* obj, My402ListElem* elem) {
    if (elem == NULL) {
        My402ListAppend(list, obj);
    }
    else {
        My402ListElem *newElement = (My402ListElem*)malloc(sizeof(My402ListElem));
        if (newElement == NULL) {
            fprintf(stderr, "Unable to allocate new memory");
            return FALSE;
        }
        newElement->obj = obj;
        newElement->prev = elem;
        newElement->next = elem->next;
        elem->next->prev = newElement;
        elem->next = newElement;
    }
    list->num_members++;
    return TRUE;
}

/*
 Insert obj between elem and elem->prev. If elem is NULL, then this is the same as Prepend(). This function returns 
 TRUE if the operation is performed successfully and returns FALSE otherwise. Please do not check if elem is on the 
 list.
 */
int  My402ListInsertBefore(My402List* list, void* obj, My402ListElem* elem) {
    if (elem == NULL) {
        My402ListPrepend(list, obj);
    }
    else {
        My402ListElem *newElement = (My402ListElem*)malloc(sizeof(My402ListElem));
        if (newElement == NULL) {
            fprintf(stderr, "Unable to allocate new memory");
            return FALSE;
        }
        newElement->obj = obj;
        newElement->next = elem;
        newElement->prev = elem->prev;
        elem->prev->next = newElement;
        elem->prev = newElement;
    }
    list->num_members++;
    return TRUE;
}

//Returns the first list element or NULL if the list is empty.
My402ListElem *My402ListFirst(My402List* list) {
    if (My402ListEmpty(list) == TRUE) {
        return NULL;
    }
    return list->anchor.next;
}

//Returns the last list element or NULL if the list is empty.
My402ListElem *My402ListLast(My402List* list) {
    if (My402ListEmpty(list) == TRUE) {
        return NULL;
    }
    return list->anchor.prev;
}

//Returns elem->next or NULL if elem is the last item on the list. Please do not check if elem is on the list.
My402ListElem *My402ListNext(My402List* list, My402ListElem* elem) {
    if (list->anchor.prev == elem) {
        return NULL;
    }
    return elem->next;
}

//Returns elem->prev or NULL if elem is the first item on the list. Please do not check if elem is on the list.
My402ListElem *My402ListPrev(My402List* list, My402ListElem* elem) {
    if (list->anchor.next == elem) {
        return NULL;
    }
    return elem->prev;
}

//Returns the list element elem such that elem->obj == obj. Returns NULL if no such element can be found.
My402ListElem *My402ListFind(My402List* list, void* obj) {
    My402ListElem *elem = NULL;
    for (elem = My402ListFirst(list); elem != NULL; elem = My402ListNext(list, elem)) {
        if (elem->obj == obj) {
            return elem;
        }
    }
    return NULL;
}
/*
 Initialize the list into an empty list. Returns TRUE if all is well and returns FALSE if there is an error 
 initializing the list.
 */
int My402ListInit(My402List* list) {
    if (list == NULL) {
        fprintf(stderr, "Unable to allocate new memory");
        return FALSE;
    }
    else {
        list->num_members = 0;
        list->anchor.obj = NULL;
        list->anchor.prev = NULL;
        list->anchor.next = NULL;
    }
    return TRUE;
}
