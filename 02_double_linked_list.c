#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	struct node *next;
	struct node *prev;
} node;

struct List {		
	struct node* head;
	struct node* tail;	
} List;

int isEmpty(struct List* lst) {
	return lst->head == NULL && lst->tail == NULL;
}

void init(struct List* lst, int data) {
	struct node* cursor;
	cursor = (struct node*)malloc(sizeof(struct node));
	cursor->data = data;
	cursor->next = NULL;
	cursor->prev = NULL;
	lst->head = cursor;
	lst->tail = cursor;
}

int clear(struct List* lst) {
	
	if (isEmpty(lst) != 0) {
		struct node *tmp = lst->head;
		struct node *temp = NULL;
		
		while (tmp != NULL)
		{
			temp = tmp->next;
			free(tmp);
			tmp = temp;
		}
		lst->head = NULL;
		lst->tail = NULL;
	}
}

struct node* find(struct List* lst, int data) {
	struct node *cursor = lst->head;
	
	while (cursor->data != data) {
		if (cursor->next != NULL)
			cursor = cursor->next;
		else return NULL;
	}
	return cursor;
}

struct node* find_inv(struct List* lst, int data) {
	struct node *cursor = lst->tail;
	
	while (cursor->data != data) {
		if (cursor->prev != NULL)
			cursor = cursor->prev;
		else return NULL;
	}
	return cursor;
}

int push_back(struct List* lst, int data) {
	
	if (isEmpty(lst) == 1)
		init (lst, data);
	else {
		struct node* cursor = (struct node*)malloc(sizeof(struct node));
		cursor->data = data;
		cursor->prev = lst->tail;
		cursor->next = NULL;
		
		lst->tail = cursor;
		cursor->prev->next = cursor;
	}
	return 0;
}

int push_front(struct List* lst, int data) {
	if (isEmpty(lst) == 1)
		init (lst, data);
	else {
		struct node *cursor = (struct node*)malloc(sizeof(struct node));
		cursor->data = data;
		cursor->prev = NULL;
		cursor->next = lst->head;
		cursor->next->prev = cursor;
		lst->head = cursor;
	}
	return 0;
}


int insertAfter	(struct List* lst, unsigned n, int data) {
	struct node *cursor = lst->head;

	for (int i = 1; i < n; ++i) {
		cursor = cursor->next;

		if (cursor == NULL) return -1;
	}
	struct node *node = malloc(sizeof(node));
	node->data = data;
	node->next = cursor->next;
	node->prev = cursor;

	cursor->next->prev = node;
	cursor->next = node;
	
	return 0;
}

int insertBefore(struct List* lst, unsigned n, int data) {
	struct node *cursor = lst->head;

	for (int i = 1; i < n; ++i) {
		cursor = cursor->next;

		if (cursor == NULL) return -1;
	}
	struct node *node = malloc(sizeof(node));
	node->data = data;
	node->prev = cursor->prev;
	node->next = cursor;

	cursor->prev = node;
	node->prev->next = node;

	return 0;
}

void delete(struct List* lst, struct node *node) {
	if (node != NULL) {

		if (node == lst->head && node == lst->tail) {
			clear(lst);
			return;
		} 
		if (node == lst->head) {
			lst->head = node->next;
			node->next->prev = NULL;
		} else if (node == lst->tail) {
			lst->tail = node->prev;
			node->prev->next = NULL;
		} else if (node != lst->head && node != lst->tail) {
			node->next->prev = node->prev;
			node->prev->next = node->next;
		}
		free(node);
	}
}

int removeFirst(struct List* lst, int data) {
	struct node* node = find(lst, data);

	if (node != NULL){
		delete(lst, node);
		return 0;
	}
	return -1;
}

int removeLast(struct List* lst, int data) {
	struct node* node = find_inv(lst, data);

	if (node != NULL){
		delete(lst, node);
		return 0;
	}
	return -1;
}

void print(struct List* lst) {
	struct node* cursor = lst->head;
	
	while (cursor->next != NULL) {
		printf("%d ", cursor->data);
		cursor = cursor->next;
	}
	printf("%d\n", cursor->data);
}

void printInv(struct List* lst) {
	struct node* cursor = lst->tail;
	
	while (cursor->prev != NULL) {
		printf("%d ", cursor->data);
		cursor = cursor->prev;
	}
	printf("%d\n", cursor->data);
}

int main()
{
	int n, a;
	struct List* lst = (struct List*)malloc(sizeof(struct List));	

	scanf("%d", &n);

	for (int i = 0; i < n; ++i) {
		scanf("%d", &a);
		push_back(lst, a);
	}
	print(lst);
	
	int k;
	struct List* res = (struct List*)malloc(sizeof(struct List));

	for (int i = 0; i < 3; ++i) {
		scanf("%d",&k);

		if (find(lst, k)!= NULL)
			push_front(res, 1);
		else push_front(res, 0);
	}
	print(res);

	int m;
	scanf("%d", &m);
	push_back(lst, m);
	printInv(lst);

	int t;
	scanf("%d", &t);
	push_front(lst, t);
	print(lst);

	int j, x;
	scanf("%d%d", &j, &x);
	insertAfter(lst, j, x);
	printInv(lst);

	int u, y;
	scanf("%d%d", &u, &y);
	insertBefore(lst, u, y);
	print(lst);

	int z;
	scanf("%d", &z);
	removeFirst(lst, z);
	printInv(lst);

	int r;
	scanf("%d", &r);
	removeLast(lst, r);
	print(lst);

	clear(lst);

	return 0;
}