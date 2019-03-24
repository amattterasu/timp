#include <stdio.h>
#include <stdlib.h>
#define EQUALS(a, b) ((a) == (b))
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

typedef struct nqueue {
    struct nqueue *next;
    struct nqueue *prev;
    Node *cursor;
} nQueue;

typedef struct queue {
	nQueue *frnt;
	nQueue *rear;
} Queue;

int qIsEmpty(Queue *q) {
	if (q->rear < q->frnt) return 1;
    else return 0;
}

void destroyQueue(Queue *q) {

	if (!qIsEmpty(q)) {

		if (q->frnt == NULL) exit(0);

		nQueue *tmp, *tq;
		tmp = q->frnt;

		while(tmp != NULL) {
			tq = tmp;
			tmp = tq->next;
			free(tq);
		}

		q->frnt = q->rear = NULL;
	}
}

int putToQueue(Queue *q, Node *n) {
	nQueue *temp = malloc(sizeof(nQueue));
	temp->cursor = n;
	temp->next = NULL;

	if (q->frnt != NULL)
		q->rear->next = temp;
	else 
		q->frnt = temp;
	q->rear = temp;

	return 0;
}

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

int find(Tree *t, int key, Node **n) {
	Node *cursor = t->root;

	while (cursor != NULL) {

		if (CMP_LT(key, cursor->key))
			cursor = cursor->left;
		else if (CMP_GT(key, cursor->key))
			cursor = cursor->right;
		else { 
			*n = cursor;

			return 0;
		}
	}
	*n = cursor;

	return 1;
}

Node *findNodeKey(Node *tmp, int key) {
	Node *temp = tmp;

	while (temp->key != key) {

		if (CMP_GT(key, temp->key)) 
			temp = temp->right;
		else if (CMP_LT(key, temp->key))
			temp = temp->left;
	}
	return temp;
}

int removeElem(Tree *t, int key) {
	t->size--;
	Node *tmp = t->root;
	tmp = findNodeKey(tmp, key);

	if (tmp == NULL) return 1;
	/*1*/
	if (tmp->left == NULL && tmp->right == NULL) {

		if (tmp->parent->key > key)
			tmp->parent->left = NULL;
		else
			tmp->parent->right = NULL;
		free(tmp);
	}
	/*2*/
	else if (tmp->left == NULL && tmp->right != NULL) {
		tmp->right->parent = tmp->parent;

		if (tmp->parent->key > key)
			tmp->parent->left = tmp->right;
		else
			tmp->parent->right = tmp->right;
		free(tmp);
	}
	/*3*/
	else if (tmp->left != NULL && tmp->right == NULL) {
		tmp->left->parent = tmp->parent;

		if (tmp->parent->key > key)
			tmp->parent->left = tmp->left;
		else 
			tmp->parent->right = tmp->left;
		free(tmp);
	}
	/*4*/
	else if (tmp->left != NULL && tmp->right != NULL) {
		Node *buf = tmp->right;
		
		if (buf->left == NULL) {
			tmp->key = buf->key;
			
			if (buf->right != NULL) {
				tmp->right = tmp->right->right;
				buf->right->parent = tmp;

				free(buf);
			}
			else {
				tmp->right = NULL;
				free(tmp->right);
			}		
		}	
		else {
			
			while(buf->left != NULL)
				buf = buf->left;

			tmp->key = buf->key;
			
			if (buf->right != NULL) {
				tmp->key = buf->key;
				buf->key = buf->right->key;
				tmp->right = NULL;

				free(buf->right);
			}
			else {
				tmp->key = buf->key;
				buf->parent->left = NULL;

				free(buf);
			}
		}
	}
	return 0;
}

int removeMin(Node *n, Tree *t) {
	t->size--;

	if (t->size != 1) {

		while (n->left != NULL)
			n = n->left;

		if (n->right != NULL) {
			n->right->parent = n->parent;

			if (n == t->root)
				t->root = n->right;
			else 
				n->parent->left = n->right;
		}
		else 
			n->parent->left = NULL;
		
		int value = n->key;
		free(n);

		return value;
	} 
	else {
		t->root = NULL;
		t->size = 0;
		free(t->root);

		return 0;
	}
}

void clear(Tree *t) {

	while (t->root != NULL)
		removeMin(t->root, t);
}

int rotateRight(Tree *t) {
	Node *tmp = t->root->left;

	if (tmp == NULL)
		return 1;

	t->root->left = tmp->right;
	tmp->right = t->root;
	tmp->parent = t->root->parent;
	t->root->parent = tmp;
	t->root = tmp;

	return 0;
}

int rotateLeft(Tree *t) {
	Node *tmp = t->root->right;
	
	if (tmp == NULL)
		return 1;
	
	t->root->right = tmp->left;
	tmp->left = t->root;
	tmp->parent = t->root->parent;
	t->root->parent = tmp;
	t->root = tmp;

	return 0;
}

void print (Node *n) {

	if (n == NULL)
		printf("-\n");

	else {
		Queue *queue1 = (Queue*)malloc(sizeof(Queue*));
		Queue *queue2 = (Queue*)malloc(sizeof(Queue*));
		Node *templeft = n->left;
		Node *tempright = n->right;
		Node *tmpQ;
		nQueue *nqueue;
		
		{
			queue1->frnt = queue1->rear = NULL;
			queue2->frnt = queue2->rear = NULL;
		}

		int ur1 = 0, ur2 = 0;

		putToQueue(queue1, n);

		while (!NULL)
		{
			while (queue1->frnt != NULL) {

				if (queue1->frnt != NULL) {
					nQueue *ntmp = queue1->frnt;
					Node *buf = queue1->frnt->cursor;
					queue1->frnt = queue1->frnt->next;

					if (queue1->frnt == NULL)
						queue1->rear = NULL;
					free(ntmp);

					tmpQ = buf;
				}
				else 
					tmpQ = NULL;

				if (EQUALS(queue1->frnt, NULL)) {
					
					if (EQUALS(tmpQ->key, n->key) && ur1 == 1)
						printf("_\n");
					else
						printf("%d\n", tmpQ->key);
				}

				else if(EQUALS(tmpQ->key, n->key) && ur1 == 1)
					printf("_ ");

				else
					printf("%d ", tmpQ->key);

				if (tmpQ->left != NULL)
					putToQueue(queue2, tmpQ->left);
				else 
					putToQueue(queue2, n);

				if (tmpQ->right != NULL)
					putToQueue(queue2, tmpQ->right);
				else 
					putToQueue(queue2, n);
			}

			n->right = n->left = NULL;
			nqueue = queue2->frnt;
			ur1 = 1;

			while (queue2->frnt->cursor->key == n->key) {
				queue2->frnt = queue2->frnt->next;

				if(queue2->frnt->next == NULL) {

					if(queue2->frnt->cursor->key == n->key) {
						ur2 = 1;
						n->left = templeft;
						n->right = tempright;
						destroyQueue(queue2);

						break;
					}
				}		
			}

			queue2->frnt = nqueue;
			queue1->frnt = queue2->frnt;
			queue1->rear = queue2->rear;
			queue2->frnt = queue2->rear = NULL;
			queue2->rear = NULL;

			if(ur2 == 1) 
				break;
		}
	}
}

void printTree(Tree *t)
{
	print(t->root);
}

int main(int argc, char const *argv[])
{
	Tree *tree;
	init(tree);

	int a;
	for (int i = 0; i < 4; i++)
	{
		scanf("%d", &a);
		insert(tree, a);
	}
	printTree(tree);

	for (int i = 0; i < 3; i++)
	{
		scanf("%d", &a);
		insert(tree, a);
	}
	printTree(tree);

	int m;
	for (int i = 0; i < 2; i++)
	{
		scanf("%d", &m);
		
		Node *node;
		int el = find(tree, m, &node);
		if (el == 0)
		{
			if (node->parent != NULL)
				printf("%d ", node->parent->key);
			else 
				printf("_ ");

			if (node->left != NULL)
				printf("%d ", node->left->key);
			else 
				printf("_ ");

			if (node->right != NULL)
				printf("%d\n", node->right->key);
			else 
				printf("_\n");
		}
		else 
			printf("-\n");
	}
	
	scanf("%d", &m); 
	removeElem(tree, m);
	printTree(tree);

	while (rotateLeft(tree) == 0) {
		rotateLeft(tree);
	} 
	printTree(tree);

	while (rotateRight(tree) == 0) {
		rotateRight(tree);
	} 
	printTree(tree);

	printf("%d\n", tree->size);

	clear(tree);
	printTree(tree);

	return 0;
}