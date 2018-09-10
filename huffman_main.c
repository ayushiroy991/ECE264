#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"

static int t_cmp(TreeNode* p1, TreeNode* p2){
	return (int)((p1)->count - ( p2)->count);
}
/**
static int t2_cmp(TreeNode* p1, TreeNode* p2){
	if ((p1)->count == ((p2)->count)){
		if ((p2)->left != NULL || (p2)->right != NULL){
			return -1;
		}
		else{
			return 1;
		}
	}
	else if((p1)->count > (p2)->count){
		return 1;
	}
	else{
		return -1;
	}
}*/

int main(int argc, char* argv[]) 
{
	if (argc != 5){
		return EXIT_FAILURE;
	}

	char *input = argv[1];
	char *output_1 = argv[2];
	char *output_2 = argv[3];
	char *output_3 = argv[4];

	

	long int asciiCount[256] = {0};

	FILE *fp_input = fopen(input, "r");
	if (fp_input == NULL){
		return EXIT_FAILURE;
	}
	build_count_ascii(fp_input, asciiCount);
	fclose(fp_input);
	//int (*cmp_fn)(TreeNode *, TreeNode*) = t_cmp;
	//TreeNode *tree = NULL;
	Node *head = malloc(sizeof(*head));
	//head = NULL;/ malloc(sizeof(*head));
	head = NULL;
	
	
	Node *new = malloc(sizeof(*new));
	if (new == NULL){
		return EXIT_FAILURE;
	}
	//new=NULL;

	TreeNode *temp = malloc(sizeof(*temp));
	if (temp == NULL){
		return EXIT_FAILURE;
	}
	//temp= NULL;
	
	//int count = 0;	
	for (int i=0; i<256; i++){
		if(asciiCount[i] >  0){
			/**Node *new = malloc(sizeof(*new));
			if (new == NULL){
				return EXIT_FAILURE;
			}
			TreeNode* temp = malloc(sizeof(*temp));
			if (temp == NULL){
				return EXIT_FAILURE;
			}**/

			temp->value=i;
			temp->count = asciiCount[i];
			temp->left = NULL;
			temp->right= NULL;
			new->ptr = temp;
			new->next = NULL;
			p_enqueue(&head, &new, t_cmp);
			
		/**	free_tree(new->ptr);
			free(new);
			free_tree(temp);**/
			
	}
		
	}
//	free_tree(new->ptr);
//	free(new);
//	free_tree(temp);
	
	//build_tree(head, asciiCount);
	
	
	//cmp_fn = t2_cmp;
	TreeNode *thead  = huff_tree(head, t_cmp);
	
	//output 1
	FILE *fp_o_1 = fopen(output_1, "w");
	if (fp_o_1 == NULL){
		return EXIT_SUCCESS;
}
	//int *path =  malloc(sizeof(*path) * count);
	//path = NULL;
	int path[256] = {0};
	huff_traverse(thead, path, 0, fp_o_1);
	//free(path);
	fclose(fp_o_1);

	//output 2
	FILE *fp_o_2 = fopen(output_2, "w");
	if (fp_o_2 == NULL){
		return EXIT_SUCCESS;
	}
	post_order(thead, fp_o_2);
	//fputc('0', fp_o_2);
	fclose(fp_o_2);

	//output 3
	FILE *fp_in_3 = fopen(output_2, "r");
	if (fp_in_3 == NULL){
		return EXIT_SUCCESS;
	}
	char *header = malloc(sizeof(*header)*152);
	FILE *fp_o_3 = fopen(output_3, "w");
	if (fp_o_3 == NULL){
		return EXIT_SUCCESS;
	}
	header_bits(fp_in_3, header, fp_o_3);
	fclose(fp_in_3);
	fclose(fp_o_3);
	
	//free_tree(thead);
	free_tree(thead);
	free(new);
	free(head);
	//free(path);
	free(header);
	//free_tree(new->ptr);
	//free(new);
	//free_tree(temp);


	return EXIT_SUCCESS;
}
