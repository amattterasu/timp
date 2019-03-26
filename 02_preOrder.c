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

typedef struct nqueue {
    struct nqueue *next;
    Node *cursor;
} nQueue;

typedef struct queue {
	nQueue *frnt;
	nQueue *rear;
	int size;
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

	if (q->frnt != NULL) {
		temp->next = q->frnt;
		q->frnt = temp;
	}
	else {
		q->frnt = temp;
		temp->next = NULL;
	}

	q->rear = temp;
	q->size++;

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

Node* pop (Queue *q) {

	if (q->frnt != NULL) {
		nQueue *ntmp = q->frnt;
		Node *buf = q->frnt->cursor;
		q->frnt = q->frnt->next;

	if (q->frnt == NULL)
		q->rear = NULL;
		free(ntmp);
		
		return buf;
	}
	else
		return NULL;
}

void preOrder(Tree *t) {
	
	if (t == NULL)
		return;

	Node *n = t->root;
	Queue *q;
	q->frnt = q->rear = NULL;

	putToQueue(q, n);

	while (q->frnt) {
		
		Node *tmp = pop(q);

		printf("%d ", tmp->key);

		if (tmp->right) putToQueue (q, tmp->right);
		if (tmp->left) putToQueue(q, tmp->left);
	}
	printf("\n");
	destroyQueue(q);
}

int main(int argc, char const *argv[])
{
	Tree *tree;
	init(tree);

	int a;
	for (int i = 0; i < 7; i++) {
		scanf("%d", &a);
		insert(tree, a);
	}

	preOrder(tree);

	return 0;
}