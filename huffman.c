#include "huffman.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

long int _count_ascii(int index, FILE *fp){

	fseek(fp, 0, SEEK_SET);
	char ch = fgetc(fp);
	long int count = 0; 

	while (ch != EOF){
		if (ch == index){
			count++;
		}
		ch = fgetc(fp);
	}

	return count; 

}

void build_count_ascii(FILE *fp_in, long int *asciiCount){
	for (int i=0; i<256; i++){
		//asciiCount[i]->value= i;
		asciiCount[i]= _count_ascii(i, fp_in); 
	}
}

/**
void build_tree(TreeNode *tree, Node head,  long int *asciiCount){
	//TreeNode *new;
	for (int i =0; i<256; i++){
		if (asciiCount[i]>0){
			//new->value = i;
			//new->count = asciiCount[i];
			p_enqueue(&tree, asciiCount[i], i, NULL, NULL);
		}
	}
}
**/

/**int cmp_fn(int p1, int p2){
	int rtr_val = p1-p2;
	return rtr_val;
}**/

 int k =1;
 	while (k <= size/3){
	  k = 3*k+1;
	}
	
Node *p_enqueue(Node **pq, Node **new_o, int (*cmp_fn)(TreeNode*, TreeNode*)){


	if (new_o==NULL){
		return NULL;
	}

	if (*pq == NULL){
		*pq = *new_o;
		return *pq;
	}

/*	Node *new = malloc(sizeof(*new));
	new->ptr = (void *)new_o;
	
	Node dummy;
	dummy.next = *pq;*/

	Node *prev;
	Node *curr;

	prev = NULL;
	curr = *pq;
	

	if (cmp_fn(curr->ptr, (*new_o)->ptr)>= 0 ){
		(*new_o)->next = *pq;
		*pq = *new_o;
		return *new_o;
	}

	while ((curr != NULL) && cmp_fn(curr->ptr, (*new_o)->ptr) < 0){
	/**	if (cmp_fn(curr->ptr, new_o)> 0){//before = curr;
			break;
		}**/
		prev = curr;	
		curr = curr ->next;
	}
	
	prev->next = *new_o;
	(*new_o)->next = curr;
	//curr->next = new;
	
	//*pq = dummy.next;

	return *new_o;


}

TreeNode* huff_tree(Node *head, int (*cmp_fn)(TreeNode*, TreeNode*)){
	Node* temp_n;

	while ((head)->next != NULL){
		Node * left = dequeue(&head);
		Node * right = dequeue(&head);
		TreeNode* temp = malloc(sizeof(*temp));
		temp->left = (TreeNode*)(left->ptr);
		temp->right = (TreeNode*)(right->ptr);
		long int n_count = ((TreeNode*)(left->ptr))->count + ((TreeNode*)(left->ptr))->count;
		temp->value = 0;
		temp->count = n_count;
		left->ptr = NULL;
		left->next = NULL;
		right->ptr = NULL;
		right->next = NULL;

		temp_n = malloc(sizeof(*temp));
		temp_n->ptr = temp;
		temp_n->next = NULL;
		p_enqueue(&head, &temp_n, cmp_fn);
		}
	 
	return (head)->ptr;

}

Node *dequeue(Node **q){
	if (q == NULL){
		return NULL;
	}
	//TreeNode *rem_Node = *q;
	if ((*q)->next ==NULL){
			Node* rem_Node = *q;
			*q = NULL;
			return rem_Node;
	}
	//*q = (*q)->next;
	//rem_Node->next = NULL;
	Node* first = *q;
	Node* second = (*q)->next;
	*q = second;
	first->next = NULL;

	return first;
}

void free_tree(TreeNode* tree){

	if (tree != NULL){

	if (tree->left != NULL){
		free_tree(tree->left);
	}
	if (tree->right != NULL){
		free_tree(tree->right);
	}
		free(tree);
	}
	//free_tree(tree->left);
	//ree_tree(tree->right);
	//free(tree);
}

void huff_traverse(TreeNode *tree, int * path, int i, FILE *fp){
	int x = 0;	
	if (tree->left==NULL && tree->right == NULL){
		path[i] = 7;
		fprintf(fp, "%c:", tree->value);
		while (path[x] != 7){
			fprintf(fp, "%d", path[x]);
			x++;
		}
			fprintf(fp, "\n");

		//fprintf(fp, "%c:%d\n", tree->value, path[i]);
	}
	else{	
	if(tree->left !=NULL){
		path[i] = 0;
		
		huff_traverse(tree->left, path, i+1, fp);
	}
	if(tree->right != NULL){
		path[i] = 1;
		huff_traverse(tree->right, path, i+1, fp);
	}
	}


}

void post_order(TreeNode *tree, FILE *fp){
	
	if (tree->left == NULL && tree->right ==NULL){
		fprintf(fp, "1%c", tree->value);
		return;
	}

	post_order(tree->left, fp);
	post_order(tree->right, fp);
	fputc('0', fp);

}

void header_bits(FILE *fp_in, char *header, FILE *fp){
	
	int i = 0;
	int ch = fgetc(fp_in);
	while(ch != EOF){
		//nt ch = fgetc(fp_in);
		/*if (feof(fp_in)){
			break;
		}**/
		header[i] = ch;
		header[i+1] = '\0';
		i++;
		ch = fgetc(fp_in);
	}

	int num = 0; 
	int n_bits = 0; 

	unsigned char data = 0;
	unsigned char temp = 0;

	while(header[num] != '\0'){
		if(header[num] == '0'){
			data = data<<1;
			n_bits++;
			if (n_bits == 8){
				fputc(data, fp);
				n_bits=0;
			}
		}

		else{
			data = data<<1 | 1;
			n_bits++;
			num++;
			if (n_bits == 8){
				fputc(data, fp);
				n_bits = 0;
			}
			data = data << (8-n_bits);
			temp = header[num];
			data = data | (header[num] >> n_bits);
			fputc(data, fp);
			data = temp<< (8-n_bits);
			data = data >> (8-n_bits);
		}
		num++;
		
	}


}


