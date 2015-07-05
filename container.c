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
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

/** Define colours for self balancing RB-Tree */
#define RED 0xff0000
#define BLACK 0x000000

/** Defines direction macros for the stack printer */
// D/s code is D/s
// TODO: For the love of god change these names before submitting it! :')
#define DOM 0xFFF
#define SUB 0x001

#define SEP ','
#define BUF_LENGTH 64

typedef struct StackNode StackNode;
struct StackNode {
	struct StackNode *next;
	int value;
};

typedef struct TreeNode TreeNode;
struct TreeNode {
	/** Left and right children for the tree */
	struct TreeNode *left, *right;

	/** Stack that the node handles*/
	struct StackNode *stackRoot, *stackTop;

	/** Used to pull data from the tree stacks again */
	unsigned short stackSize;

	/* Colours for R-B Tree. Will I actually implement this? */
	short colour;
};

StackNode *createStackNode(short value) {
	struct StackNode *node = malloc(sizeof(struct StackNode));

	node->value = value;
	node->next = NULL;
	return node;
}

TreeNode *createTreeNode(struct StackNode *value) {
	struct TreeNode *node = malloc(sizeof(struct TreeNode));

	node->left = NULL;
	node->right = NULL;
	node->stackRoot = value;
	node->stackTop = value;

	// If a StackNode value was given, set size to 1, otherwise 0
	node->stackSize = (value != NULL) ? 1 : 0;

	return node;
}

/**
 * Takes the root node and a value to insert. Does tree insertion based on the size of
 * the top AND the bottom item in the stack.
 *
 * Returns 0 if insert was successful, returns -1 if something went wrong!
 */
int insertContainer(struct TreeNode *root, int value) {

	// This means that the root node stack doesn't exist (So it's empty!)
	// So we create one and we're done!
	if (root->stackRoot == NULL) {
		root->stackRoot = createStackNode(value);
		root->stackTop = root->stackRoot;
		root->stackSize++;
		return 0;
	}

	// This means that our value is smaller than the top element
	// So we can insert on top!
	if (value <= root->stackTop->value) {
		StackNode *tmp = createStackNode(value);
		root->stackTop->next = tmp;
		root->stackTop = tmp;

		// Bump up the size counter
		root->stackSize++;
		return 0;

		// If our value is larger
	} else {

		// If our value SHOULD be smaller we insert left
		if (value < root->stackRoot->value) {
			if (root->left == NULL)
				root->left = createTreeNode(NULL);
			return insertContainer(root->left, value);

			// Else we insert right
		} else {
			if (root->right == NULL)
				root->right = createTreeNode(NULL);
			return insertContainer(root->right, value);
		}
	}
	return -1;
}

int scrubTreeDebug(struct TreeNode *root) {
	return 0;
}

/** Use one of the macros defined to determine direction */
int printStack(struct StackNode *start, int direction) {
	if (direction == SUB) {
		if (start == NULL)
			return 1;

		printf("%d", start->value);

		if (start->next != NULL) {
			printf(",");
		} else {
			printf(" ");
		}
		return printStack(start->next, direction);
	} else {
		// Print from the top baby
	}

	return -1;
}

void printResultTreeStacks(struct TreeNode *root) {
	if (root == NULL)
		return;

	printResultTreeStacks(root->left);
	printStack(root->stackRoot, SUB);
	printResultTreeStacks(root->right);
}

/** Simple helper function that counts container stacks (nodes) in the tree */
ssize_t countConStacks(TreeNode *root) {
	if (root == NULL)
		return 0;

	int right = countConStacks(root->right);
	int left = countConStacks(root->left);
	return 1 + right + left;
}

/** Free an entire stack from memory */
void freeStack(struct StackNode *root) {
	if (root == NULL)
		return;

	freeStack(root->next);

	free(root);
	root = NULL;
}

/** Frees and entire tree from memory */
void freeTree(struct TreeNode *root) {
	if (root == NULL)
		return;

	freeTree(root->left);
	freeTree(root->right);

	freeStack(root->stackRoot);
	free(root);
	root = NULL;
}

int main(int argn, char **argv) {

	// Create some file handles.
	FILE *fp;
	int lookAhead;
	int c;

	// Init the tree
	struct TreeNode *treeRoot = createTreeNode(NULL);
	size_t counts;
	int value = 0;

	fp = fopen("testdata/input3.data", "r");
	if (fp == NULL) {
		perror("Error in opening file");
		return (-1);
	}
	while ((c = fgetc(fp)) != EOF) {

		switch (c) {
		case '\r':
			lookAhead = fgetc(fp);
			if (lookAhead != '\n') {
				fseek(fp, -1, SEEK_CUR);
			}

		case '\n':
			// Insert the last container
			insertContainer(treeRoot, value);

			// Then do magic *dances*
			counts = countConStacks(treeRoot);
			printf("%zu ", counts);
			printResultTreeStacks(treeRoot);
			printf("\n");

			// Reset some variables.
			counts = 0;
			value = 0;

			// Free memory of tree.
			freeTree(treeRoot);
			treeRoot = NULL;

			// now prep for the new round-
			treeRoot = createTreeNode(NULL);
			break;

		case SEP:
			insertContainer(treeRoot, value);
			value = 0;
			break;

		case '0' ... '9':
			value *= 10;
			value += c - '0';
			break;

		default:
			fputs("An error occured while handling the file!\n", stderr);
			exit(-1);
		}
	}

	fclose(fp);
	return (0);
}
