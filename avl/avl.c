/*****************************
* Developer:      Idan Paz   *
* Reviewer:       Shalev     *
*****************************/

#include <stdlib.h> /* for memory allocation */
#include <assert.h> /* for validating inputs */

#include "avl.h"

typedef struct node node_t;

enum child_node_pos
{
    LEFT = 0,
    RIGHT = 1,
    NUM_OF_CHILDREN = 2
};

struct node
{
	void *data;
	node_t *children[NUM_OF_CHILDREN];
	ssize_t height;
};

struct avl
{
    node_t *root;
    cmpfunc_t cmpfunc;
};

static node_t *Insert(avl_t *tree, node_t *root, void *key);
static node_t *Balance(avl_t *tree, node_t *root);
static node_t *Rotate(avl_t *tree, node_t *root, int dir);
static node_t *Remove(avl_t *avl, node_t *root, void *key);
static node_t *CaseLeafOrOneChild(node_t *root);
static node_t *CaseTwoChildren(avl_t *tree, node_t *root);
static node_t *GetNextInOrder(node_t *node);
static node_t *NewNode(void *data);
static size_t GetHeight(node_t *root);
static ssize_t Max(ssize_t height_tl, ssize_t height_tr);
static void *Find(avl_t *tree, node_t *node, void *key);
static void FreeNodes(node_t *node);
static long int GetBalance(node_t *node);
static int ActPreOrder(node_t *root, int (*action_func)(void *data, void *param), void *param);
static int ActInOrder(node_t *root, int (*action_func)(void *data, void *param), void *param);
static int ActPostOrder(node_t *root, int (*action_func)(void *data, void *param), void *param);
static int Counter(void *data, void *param);

int AVLInsert(avl_t *avl, void *data)
{
    node_t *new_node = NULL;

    assert(avl);

    if (!avl->root)
    {
        avl->root = NewNode(data);
        return (avl->root == NULL);
    }

    new_node = Insert(avl, avl->root, data);

    return (new_node == NULL);
}

static node_t *Insert(avl_t *tree, node_t *root, void *key)
{
    assert(tree);

    if (!root)
    {
        return NewNode(key);
    }

    if (!tree->cmpfunc(key, root->data))
    {
        return root;
    }

    else
    {
        int dir = (tree->cmpfunc(key, root->data) > 0);
        root->children[dir] = Insert(tree, root->children[dir], key);
    }

    root->height = GetHeight(root);

    return Balance(tree, root);
}

static size_t GetHeight(node_t *root)
{
    int dir = 0;

    assert(root);

    if (root->children[LEFT] && root->children[RIGHT])
    {
        return Max(root->children[LEFT]->height, root->children[RIGHT]->height) + 1;
    }

    dir = (root->children[LEFT] == NULL);
    
    if (root->children[dir])
    {
        return root->children[dir]->height + 1;
    }
    
    return 0;
}

static long int GetBalance(node_t *node)
{
    assert(node);

    if (node->children[LEFT] && node->children[RIGHT])
    {
        return (node->children[LEFT]->height - node->children[RIGHT]->height);
    }

    else
    {
        return (!node->children[LEFT]) ? -node->height : node->height;
    }

    return -1;
}

static node_t *Balance(avl_t *tree, node_t *root)
{
    assert(tree);
    assert(root);

    if (GetBalance(root) > 1)
    {
        if (GetBalance(root->children[LEFT]) < 0)
        {
            root->children[LEFT] = Rotate(tree, root->children[LEFT], 0);
        }

        root = Rotate(tree, root, 1);
    }

    if (GetBalance(root) < -1)
    {
        if (GetBalance(root->children[RIGHT]) > 0)
        {
            root->children[RIGHT] = Rotate(tree, root->children[RIGHT], 1);
        }

        root = Rotate(tree, root, 0);
    }
    
    return root;
}

static node_t *Rotate(avl_t *tree, node_t *root, int dir)
{
    node_t *ret = root->children[!dir];
    node_t *temp = ret->children[dir];

    assert(root);

    root->children[!dir] = temp;
    ret->children[dir] = root;
    root->height = GetHeight(root);
    ret->height = GetHeight(ret);

    if (tree->root == root)
    {
        tree->root = ret;
    }

    return ret;
}

void AVLRemove(avl_t *avl, void *data)
 {
    assert(avl);

    if (!AVLFind(avl, data))
    {
        return;
    }
    /* check if last node is removed */
    if (!Remove(avl, avl->root, data))
    {
        avl->root = NULL;
    }
 }

static node_t *Remove(avl_t *tree, node_t *root, void *key)
{   
    if (!root)
    {
        return root;
    }

    if (!tree->cmpfunc(key, root->data))
    {
        if (!root->children[LEFT] || !root->children[RIGHT])
        {
            root = CaseLeafOrOneChild(root);
        }

        else
        {
            root = CaseTwoChildren(tree, root);
        }
    }

    else
    {
        int dir = (tree->cmpfunc(key, root->data) > 0);
        root->children[dir] = Remove(tree, root->children[dir], key);
    }

    if (!root)
    {
        return root;
    }

    root->height = GetHeight(root);

    return Balance(tree, root);
}

static node_t *CaseLeafOrOneChild(node_t *root)
{
    node_t *temp = (root->children[LEFT]) ? root->children[LEFT] : root->children[RIGHT];

    if (!temp)
    {
        temp = root;
        root = NULL;
    }

    else
    {
        int dir = (root->children[LEFT] == NULL);
        root->data = temp->data;

        if (root->children[dir] && !root->children[dir]->children[dir])
        {   
            root->children[dir] = NULL;
        }
    }

    free(temp);

    return root;
}

static node_t *CaseTwoChildren(avl_t *tree, node_t *root)
{
    node_t *temp = GetNextInOrder(root->children[RIGHT]);

    root->data = temp->data;
    root->children[RIGHT] = Remove(tree, root->children[RIGHT], temp->data);

    return root;
}

static node_t *GetNextInOrder(node_t *node)
{
    assert(node);

    while (node->children[LEFT])
    {
        node = node->children[LEFT];
    }

    return node;
}

int AVLForEach(avl_t *avl, int (*action_func)(void *data, void *param), void *param, int traversal_type)
{
    assert(avl);
    assert(action_func);

    switch (traversal_type)
    {
        case -1:
        {
            return ActPreOrder(avl->root, action_func, param);
        }

        case 0:
        {
            return ActInOrder(avl->root, action_func, param);
        }

        case 1:
        {
            return ActPostOrder(avl->root, action_func, param);
        }
    }

    return 1;
}

static int ActPreOrder(node_t *root, int (*action_func)(void *data, void *param), void *param)
{
    int res = 0;

    if (!root)
    {
        return res;
    }

    res = action_func(root->data, param);

    if (!res)
    {
        res = ActPreOrder(root->children[LEFT], action_func, param);

        if (!res)
        {
            res = ActPreOrder(root->children[RIGHT], action_func, param);
        }
    }

    return res;
}

static int ActInOrder(node_t *root, int (*action_func)(void *data, void *param), void *param)
{
    int res = 0;

    if (!root)
    {
        return res;
    }

    res = ActInOrder(root->children[LEFT], action_func, param);

    if (!res)
    {
        res = action_func(root->data, param);

        if (!res)
        {
            res = ActInOrder(root->children[RIGHT], action_func, param);
        }
    }

    return res;
}

static int ActPostOrder(node_t *root, int (*action_func)(void *data, void *param), void *param)
{
    int res = 0;

    if (!root)
    {
        return res;
    }

    res = ActPostOrder(root->children[LEFT], action_func, param);

    if (!res)
    {
        res = ActPostOrder(root->children[RIGHT], action_func, param);

        if (!res)
        {
            res = action_func(root->data, param); 
        }
    }

    return res;
}

void *AVLFind(const avl_t *avl, void *key)
{
    assert(avl);

    return Find((avl_t *)avl, avl->root, key);
}

static void *Find(avl_t *tree, node_t *node, void *key)
{
    if (!node)
    {
        return NULL;
    }

    if (!tree->cmpfunc(key, node->data))
    {
        return key;
    }

    else
    {
        int dir = (tree->cmpfunc(key, node->data) > 0);

        return Find(tree, node->children[dir], key);
    }
}

avl_t *AVLCreate(int (*cmp_func)(const void *lhs, const void *rhs))
{
    avl_t *tree = (avl_t *)malloc(sizeof(avl_t));

    assert(cmp_func);

    if (!tree)
    {
        return NULL;
    }

    tree->root = NULL;
    tree->cmpfunc = cmp_func;

    return tree;
}

void AVLDestroy(avl_t *avl)
{
    assert(avl);

    if (!AVLIsEmpty(avl))
    {
        FreeNodes(avl->root);
    }

    free(avl);
}

static void FreeNodes(node_t *node)
{
    int dir = (node->children[LEFT] == NULL);

    assert(node);

    if (node->children[dir])
    {
        FreeNodes(node->children[dir]);
    }

    free(node);
}

size_t AVLSize(const avl_t *avl)
{
    size_t count = 0;

    assert(avl);

    AVLForEach((avl_t *)avl, Counter, &count, 0);

    return count;
}

ssize_t AVLHeight(const avl_t *avl)
{
    assert(avl);

    return (avl->root) ? avl->root->height : -1;
}

int AVLIsEmpty(const avl_t *avl)
{
    assert(avl);

    return (NULL == avl->root);
}

static node_t *NewNode(void *data)
{
    node_t *new_node = malloc(sizeof(node_t));

    if (!new_node)
    {
        return NULL;
    }

    new_node->children[LEFT] = NULL;
    new_node->children[RIGHT] = NULL;
    new_node->height = 0;
    new_node->data = data;

    return new_node;
}

static ssize_t Max(ssize_t height_tl, ssize_t height_tr)
{
    return (height_tl > height_tr) ? height_tl : height_tr;
}

static int Counter(void *data, void *param)
{
    (void)data;
    
    ++(*(size_t *)param);
    
    return 0;
}