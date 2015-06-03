/**
 * AUTHOR: KATHARINA 'spacekookie' SABEL <sabel.katharina@gmail.com>
 * LICENSE: MIT PUBLIC LICENSE
 *          (c) 2015
 *
 * NOTES: Implementiert ein Hafendock mit Container stapeln mit einer doppelt verketten Liste
 *        und einem minimalen Red-Black tree für das garantierte suchen (und damit einfügen) von O(log(n)).
 *
 *
 */

// Define colours for the RB tree
#include <malloc.h>

// Internal dependencies
// #include rbtree.h

#define RED 0xff0000
#define BLACK 0x000000

// Define NULL as a checking value
#ifndef NULL
#define NULL   ((void *) 0)
#endif


/** Debugging options */
#define PRINT_OPAQUE_STRUCT(p)  print_mem((p), sizeof(*(p)))

void print_mem(void const *vp, size_t n) {
    unsigned char const *p = vp;
    for (size_t i = 0; i < n; i++)
        printf("%02x\n", p[i]);
    putchar('\n');
};

typedef struct TreeNode TreeNode, *pno;

struct TreeNode {
    struct ListNode *stack;

    // Binary tree implementation
    struct TreeNode *left;
    struct TreeNode *right;
    short colour;

    pno *(*insert)(TreeNode *, TreeNode *);
    // pno *(*search)      (TreeNode *, short);
};

/** Double linked list */
typedef struct ListNode ListNode, *ppo;

struct ListNode {
    struct ListNode *next;
    struct ListNode *prev;
    short value;

    ppo *(*push)(ListNode *, ListNode *);

    ppo *(*pop)(ListNode *);

};

/** Pushes a new element to the linked list
 * And updates the list pointer.
 * */
ppo push(ListNode **top, ListNode *element) {
    /** Connects the two next/ prev values */
    (*top)->next = element;
    element->prev = *top;

    /** Now updates the head */
    *top = element;
}

/**
 * Pops off the top element from the stack and returns the new list pointer
 */
ppo pop(ListNode **top) {
    ListNode *tbr = (*top);
    (*top)->prev->next = NULL;
    (*top) = (*top)->prev;

    // Remove that temp variable again.
    // The new list head is now self.
    return tbr->value;
}

/** Handy helper function to create a new ListNode*/
ListNode *createListNode(short value, ListNode *previous) {
    struct ListNode *node = malloc(sizeof(struct ListNode));

    // Init values with default values
    node->value = value;
    node->prev = NULL;
    node->next = NULL;

    // Define function pointers
    node->push = push;
    node->pop = pop;

    return node;
}

TreeNode *createTreeNode(short value);
/**
 *
 * 1. Check root element (if yes --> insert, if no 2)
 *
 * 2. Check if left child exists
 *      if so --> left >= value
 *          if so --> insert
 *          else --> call recursive with new root
 *
 *      if not:
 *
 *
 *
 */

/** Helper function. DO NOT CALL! */
void treeInsert(TreeNode **parent, short value) {

    // Checks if the first PARENT node is viable to insert
    if(value < (*parent)->stack) {

        (*parent)->stack->push((*parent)->stack, createListNode(value, (*parent)->stack));
        // Otherwise continue with recursive insertion strategy.
    } else {
        // First check if left child is NULL
        if ((*parent)->left != NULL) {

            // Check if that stack is smaller
            if (value < (*parent)->stack->value) {

                // ### SUB OPTIMISATION ###

                // Check if THAT left child is not null
                if ((*parent)->left->left != NULL) {

                    // And then check which one has the better hit result!
                    if ((*parent)->left->stack->value < (*parent)->stack->value
                        && (*parent)->left->stack->value >= value) {

                        // If it is, insert to the lower stack result
                        (*parent)->left->stack->push((*parent)->left->stack, value);
                    } else {

                        // Else insert into the first hit
                        // Ignore and skip to outer insert!
                    }
                } else {
                    // Insert to the left childs stack (either because better hit OR leftest NULL
                    (*parent)->stack->push((*parent)->stack, value);
                }
            } else {
                // This means the value was too large. So in either case we need to go deeper into the tree.
                treeInsert((*parent)->left, value);
            }
        } else {
            // Create a new tree node and insert it.
            (*parent)->left = createTreeNode(value);
        }
    }
}

/**
 * Insertion function into the RBTree. Handles folding events and balance automatically.
 * Changes the root pointer if neccesary.
 *
 * params:      **root          Pointer to the TreeNode root pointer to dynamically change root node
 *              short value     Value to be inserted into the RBTree
 */
TreeNode *insert(TreeNode **top, short value) {
    // Do a normal tree insert
    treeInsert(*top, value);

    // Then restore the RB balance

}

// Helper function that gets called from the RBTree insertion function.
TreeNode *createTreeNode(short value) {
    struct TreeNode *node = malloc(sizeof(struct TreeNode));

    // Init values
    // node->colour = BLACK;
    node->left = NULL;
    node->right = NULL;
    node->stack = createListNode(value, NULL);

    node->insert = insert;

    return node;
}

int main(void) {

}

/*
int main( void ) {
    printf("Started program...\n\n");
    struct ListNode *head = createListNode(25, NULL);
    head->push(&head, createListNode(20, head));
    head->push(&head, createListNode(15, head));
    head->push(&head, createListNode(10, head));
    head->push(&head, createListNode(5, head));
    head->push(&head, createListNode(0, head));

    struct ListNode* target = head;
    while(target) {
        printf("[%i]\n",target->value);
        target = target->prev;
    }

    printf("\nRemoving element: %i\n", head->pop(&head));
    printf("Removing element: %i\n", head->pop(&head));

    printf("\n");

    struct ListNode* target2 = head;
    while(target2) {
        printf("[%i]\n",target2->value);
        target2 = target2->prev;
    }

    free(&target);
    free(&target2);

    return 0;
}*/
