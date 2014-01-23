#include <stdio.h>
#include <stdlib.h>

int data[] = { 20, 35, 37, 33, 15, 42 };

typedef struct node {
	int value;
	struct node * pLeft;
	struct node * pRight;
} node;

void init_node(node *pNode, int a){
	pNode->value = a;
	pNode->pLeft = NULL;
	pNode->pRight = NULL;
}

void insert_node(node* pParent, int a){
	if (a > pParent->value){
		if ( NULL == pParent->pRight){
			printf("inserted to the right of %d\n", pParent->value);
			pParent->pRight = (node*) malloc(sizeof(node));
			init_node(pParent->pRight, a);
		}
		else {
			insert_node(pParent->pRight, a);
		}
	} else if ( a < pParent->value){
		if ( NULL == pParent->pLeft){
			printf("inserted to the left of %d\n", pParent->value);
			pParent->pLeft = (node*) malloc(sizeof(node));
			init_node(pParent->pLeft, a);
		}
		else {
			insert_node(pParent->pLeft, a);
		}
	}
}

void loop_data(node *pParent){
	/// we skip the first value since already assign to root
	int i = 1;
	for (;i<sizeof(data)/sizeof(int);i++){
		printf("data=%d\n", data[i]);
		insert_node(pParent, data[i]);
	}
}

int count_depth(node* pParent, int deepest){
	int left_deep = deepest;
	int right_deep = deepest;
	int node_depth = 0;
	if (NULL!=pParent->pLeft){
		++left_deep;
		left_deep = count_depth(pParent->pLeft, left_deep);
	}

	if (NULL!=pParent->pRight){
		++right_deep;
		right_deep = count_depth(pParent->pRight, right_deep);
	}

	if (right_deep > left_deep ){
		node_depth = right_deep;
	}else {
		node_depth = left_deep;
	}

	return node_depth;
}

void print_data(node* pNode){
	/// 1 as the root is the first node
	int deepest = count_depth(pNode, 1);
	printf("deepest = %d\n", deepest);
}

int main(void){
	node* pRoot = (node *)malloc(sizeof(node));
	init_node(pRoot, data[0]);
	loop_data(pRoot);
	print_data(pRoot);
}
