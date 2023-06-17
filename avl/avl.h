/*********************************************
* Developer:      Idan Paz                   *
* Reviewer:       Shalev                     *
* Version:        1.0                        *   
* Description:    API for avl.c              *
**********************************************/
#ifndef __OL134_AVL_H__
#define __OL134_AVL_H__

#include <sys/types.h>

typedef int (*cmpfunc_t)(const void *data, const void *param);
typedef struct avl avl_t;

typedef enum
{
    PRE_ORDER = 0,
    IN_ORDER = 1,
    POST_ORDER = 2
} travesal_type_t;

/*------------------------------------*/
/* AVLCreate:
    param
        cmp - the function that compares the data
	Return:
		succeed : returns pointer to the new avl
		fail : returns NULL
	Complexity:
		Time - O(1) */
avl_t *AVLCreate(int (*cmp_func)(const void *lhs, const void *rhs));

/*------------------------------------*/
/* AVLDestroy:
	param:
		avl - avl to destroy
	Complexity:
		Time - O(n) */
void AVLDestroy(avl_t *avl);

/*------------------------------------*/
/* AVLSize:
	param:
		avl - the tree to check the size for
	Return:
		the number of elements in the tree
	Complexity:
		Time - O(n) */
size_t AVLSize(const avl_t *avl);
/*------------------------------------*/
/* AVLHeight:
	param:
		avl - the tree 
	Return:
		the number of elements in the tree
	Complexity:
		Time - O(log(n)) */
ssize_t AVLHeight(const avl_t *avl);

/*------------------------------------*/
/* AVLIsEmpty:
	param:
		avl - the tree to check emptiness
	return
	    1 - empty
	    0 - not empty
	Complexity:
		Time - O(1) */
int AVLIsEmpty(const avl_t *avl);

/*------------------------------------*/
/* AVLInsert:
Description:
	param:
		avl - avl to begin the search
	return:
		success - 1
		fail - 0
	Complexity:
		Time - O(log(n)) average, O(1) fail*/
int AVLInsert(avl_t *avl, void *data);

/*------------------------------------*/
/* AVLRemove:
	param:
		data - to remove
	return:
		status : success - 1
				 failed - 0 // Nothing found
	Complexity:
		Time - O(log(n)) average */
 void AVLRemove(avl_t *avl, void *data);
 
/*------------------------------------*/
/* AVLFind:
	param:
	    avl - the tree to search in
	    key - the data's key, which identify the complete data 
	return:
		success - the complete data element
		fail - NULL
	Complexity:
		Time - O(log(n)) average */
void *AVLFind(const avl_t *avl, void *key);

/*------------------------------------*/
/* AVLForEach:
	param:
		action_func
		param
		traversal_type: 1 -> post ,0 -> in-order, -1 ->pre
	return:
	    the status from the action function
	Complexity:
		Time - O(log() */
int AVLForEach(avl_t *avl, int (*action_func)(void *data, void *param), void *param, int traversal_type);		
/*------------------------------------*/


#endif /*  __OL134_AVL_H__ */




