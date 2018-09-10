#include <stdio.h>

typedef struct _TreeNode {
	long int count;
	int value;
	struct _TreeNode *left;
	struct _TreeNode *right;
	struct _TreeNode *next;
} TreeNode ;


typedef struct _Node{
	void *ptr;
	struct _Node *next;
} Node ;

void build_count_ascii(FILE *fp_in, long int *asciiCount);

void build_tree(TreeNode *tree, long int *asciiCount);

TreeNode* huff_tree(Node *head, int (*cmp_fn)(TreeNode*, TreeNode*));

Node *p_enqueue(Node **pq, Node **new_o, int (*cmp_fn)(TreeNode*, TreeNode*));

void huff_traverse(TreeNode *tree, int * path, int i, FILE *fp);

void post_order(TreeNode *tree, FILE *fp);

void header_bits(FILE *fp_in, char *header, FILE *fp_out);

void free_tree(TreeNode*);

//int cmp_fn(int p1, int p2);

Node *dequeue(Node **q);
