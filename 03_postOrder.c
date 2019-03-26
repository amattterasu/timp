#include <stdio.h>
#include <stdlib.h>
#define CMP_LT(a, b) ((a) < (b))
#define CMP_GT(a, b) ((a) > (b))

typedef struct node {
	struct node *left, *right, *parent;
	int key;
} Node;

typedef struct {
	int size;
	Node *root;
} Tree;

void init(Tree* t) {
	t->root = NULL;
	t->size = 0;
}

Node* getFreeNode(int key, Node *parent) {
	Node *tmp = (Node*)malloc(sizeof(Node));
	tmp->left = tmp->right = NULL;
	tmp->key = key;
	tmp->parent = parent;

	return tmp;
}

int insert(Tree *t, int key) {
    Node *tmp = NULL;

    if (t->root == NULL) {
        t->root = getFreeNode(key, NULL);
       
       	if (t->root == NULL)
       		return 2;
        t->size++;
    }
     
    tmp = t->root;
    
    while (tmp) {
        if (CMP_GT(key, tmp->key)) {
            if (tmp->right) {
                tmp = tmp->right;
                continue;
            } 
            else {
                tmp->right = getFreeNode(key, tmp);
                t->size++;
                return 0;
            }
        } 
        else if (CMP_LT(key, tmp->key)) {
            
            if (tmp->left) {
                tmp = tmp->left;
                continue;
            } 
            else {
                tmp->left = getFreeNode(key, tmp);
                t->size++;
                return 0;
            }
        } 
        else {
            return 1;
        }
    }
}

void postOrder(Node *n) {

	if (n == NULL)
		return;

	postOrder(n->left);
	postOrder(n->right);

	printf("%d ", n->key);
}

int main(int argc, char const *argv[])
{
	Tree *tree = malloc(sizeof(Tree));
	
	init(tree);

	int a;
	for (int i = 0; i < 7; i++) {
		scanf("%d", &a);
		insert(tree, a);
	}

	Node *n = tree->root;
	postOrder(n);
	printf("\n");

	return 0;
}