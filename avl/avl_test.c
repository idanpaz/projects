/******************************
* Developer:      Idan Paz    *
* Reviewer:       Shalev      *
* Version:        1.0         *   
* Description:    AVL Test    *
******************************/

#include <stdio.h>     /* for printing */
#include <stdlib.h>    /* for rand */
#include <time.h>      /* for srand */

#include "avl.h"       /* API */

typedef struct node node_t;

static int CmpFunc(const void *lhs, const void *rhs);
static int PrintTree(void *data, void *param);

int main()
{
    size_t i = 0;
    int arr[1048575] = {0};
    size_t len = sizeof(arr) / sizeof(arr[0]);
    avl_t *tree = AVLCreate(CmpFunc);
    int x = 56;
    int random_num = 0;

    srand(time(NULL));
	
    for (i = 0; i < len; ++i)
    {
        random_num = rand() % len*2;
        arr[i] = random_num;
    }

    for (i = 0; i < len; ++i)
    {
        AVLInsert(tree, &arr[i]);
    }

    AVLForEach(tree, PrintTree, NULL, 0);
    printf("\n");

    for (i = 0; i < len; ++i)
    {
        AVLRemove(tree, &arr[i]);
    }

    if (!AVLIsEmpty(tree))
    {
        printf("IsEmpty failed\n");
    }

    if (AVLSize(tree))
    {
        printf("Size failed\n");
    }

    if (-1 != AVLHeight(tree))
    {
        printf("Height failed\n");
    }
    
    for (i = 0; i < len; ++i)
    {
        arr[i] = i;
    }
    
    for (i = len - 1; i > 0; --i)
    {
        AVLInsert(tree, &arr[i]);
    }

    AVLInsert(tree, &arr[i]);

    AVLForEach(tree, PrintTree, NULL, 0);
    printf("\n");

    if (AVLFind(tree, &x) && 0 != *(int *)AVLFind(tree, &arr[i]))
    {
        printf("Find failed\n");
    }

    if (len != AVLSize(tree))
    {
        printf("Size failed\n");
    }

    if (19 != AVLHeight(tree))
    {
        printf("Tree is not balanced\n");
    }

    for (i = 0; i < len; ++i)
    {
        AVLRemove(tree, &arr[i]);
    }

    AVLDestroy(tree);

    return 0;
}

static int CmpFunc(const void *lhs, const void *rhs)
{
    return (*(int *)lhs - *(int *)rhs);
}

static int PrintTree(void *data, void *param)
{
    (void)param;
    printf("%d ", *(int *)data);
    
    return 0;
}
