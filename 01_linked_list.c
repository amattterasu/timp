#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	struct node *next;
} node;

struct List {		
	struct node* head;	
} List;

void init(struct List* lst, int data) {
	struct node* cursor;
	cursor = (struct node*)malloc(sizeof(struct node));
	cursor->data = data;
	cursor->next = NULL;
	lst->head = cursor;
}

int isEmpty(struct List* lst) {
	return lst->head == NULL;
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
	}
}

struct node* find(struct List* lst, int data) {
	struct node *cursor = lst->head;
	
	while (cursor->data != data) {
		if (cursor->next != NULL)
			cursor = cursor->next;
		else return 0;
	}
	return cursor;
}

int push_back(struct List* lst, int data) {
	
	if (isEmpty(lst) == 1)
		init (lst, data);
	else {
		struct node* cursor = (struct node*)malloc(sizeof(struct node));
		cursor->data = data;
		cursor->next = NULL;
		
		struct node* temp = lst->head;
		
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = cursor;
	}
	return 0;
}

int push_front(struct List* lst, int data) {
	if (isEmpty(lst) == 1)
		init (lst, data);
	else {
		struct node *cursor = (struct node*)malloc(sizeof(struct node));
		cursor->data = data;
		cursor->next = lst->head;
		lst->head = cursor;
	}
	return 0;
}

void delete(struct List* lst, struct node *node) {
	if (node != NULL) {

		if (node == lst->head) 
			lst->head = node->next;
		else {
			struct node *temp = (struct node*)malloc(sizeof(struct node));
			temp = lst->head;
			
			while (temp->next != node)
				temp = temp->next;
			temp->next = node->next;
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

int insertAfter	(struct List* lst, unsigned n, int data) {
	struct node *cursor = malloc(sizeof(node));
	cursor->data = data;

	struct node* tmp = lst->head;
	struct node* prevTmp = lst->head;
	
	for (int i = 1; i < n + 1; i++) {
		prevTmp = tmp;
		tmp = tmp->next;
		
		if (tmp == NULL) 
			return -1;
	}

	prevTmp->next = cursor;
	cursor->next = tmp;

	return 0;   
}

void print(struct List* lst) {
	struct node* cursor = lst->head;
	
	while (cursor->next != NULL) {
		printf("%d ", cursor->data);
		cursor = cursor->next;
	}
	printf("%d\n", cursor->data);
}

int main()
{
	int n, a;
	struct List* lst=(struct List*)malloc(sizeof(struct List));	

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
	print(lst);

	int t;
	scanf("%d", &t);
	push_front(lst, t);
	print(lst);

	int j, x;
	scanf("%d%d", &j, &x);
	insertAfter(lst, j, x);
	print(lst);

	int z;
	scanf("%d", &z);
	removeFirst(lst, z);
	print(lst);

	clear(lst);

	return 0;
}