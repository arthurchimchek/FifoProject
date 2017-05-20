#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<stdbool.h>

typedef struct nodeQueue {
	int value;
	struct nodeQueue *next;
}node;

#define FILE_PATH "c://teste.txt"

bool has(node **firstNode, int value);
void pushBack(node ** lastNode, int newValue);
int popFront(node ** firstNode);
int getItem(node **);
int getQueueSize(node **firstNode);

void main() {

	int maxQueueSize = 4;
	int pageFaults = 0;

	int pages[] = { 3, 2, 1, 3, 5, 4, 6, 3, 7, 4 };

	int arrSize = (int)(sizeof(pages) / sizeof(pages[0]));
	int i;
	node *firstNode;
	node *currentNode = (node *)malloc(sizeof(node));;
	currentNode->value = pages[0];
	currentNode->next = NULL;
	firstNode = currentNode;
	for (i = 1; i < arrSize; i++) {
		if (has(&firstNode, pages[i])) {
			printf("Tem na memoria\n");
		}
		else {
			if (getQueueSize(&firstNode) == maxQueueSize) {
				popFront(&firstNode);
				pageFaults++;
			}
			pushBack(&currentNode, pages[i]);
		}
	}

	//printf("%d\n", getQueueSize(&firstNode));
	printf("%d\n", popFront(&firstNode));
	printf("%d\n", popFront(&firstNode));
	printf("%d\n", popFront(&firstNode));
	printf("%d\n", popFront(&firstNode));
	printf("%d\n", getQueueSize(&firstNode));
	//printf("%d\n", has(&firstNode, 9));
	//printf("%d\n", has(&firstNode, 4));

	printf("Arquivo %d, %5d páginas, %7d requisições: FIFO: %5d Page Faults", 1, maxQueueSize, arrSize, pageFaults);

	scanf("");
}

bool has(node **firstNode, int value) {
	node *temp;
	if (firstNode == NULL || (*firstNode)->value == NULL) {
		printf("Lista vazia !!!");
	}
	else {
		node * firstNodeB = (*firstNode);
		temp = (node *)malloc(sizeof(node));
		temp = firstNodeB;
		while (temp != NULL) {
			if (temp->value == value)
				return true;
			temp = temp->next;
		}
	}
	return false;
}

void pushBack(node ** lastNode, int newValue) {
	node *newLastNode;
	if (lastNode == NULL || (*lastNode)->value == NULL) {
		newLastNode = (node *)malloc(sizeof(node));
		newLastNode = (*lastNode);
		newLastNode->value = newValue;
		newLastNode->next = NULL;
	}
	else {
		newLastNode = (node *)malloc(sizeof(node));
		newLastNode->value = newValue;
		newLastNode->next = NULL;
		(*lastNode)->next = newLastNode;
		(*lastNode) = newLastNode;
	}
}

int popFront(node ** firstNode) {
	if (firstNode == NULL || (*firstNode) == NULL)
		return;
	node *newFirstNode = (*firstNode)->next;
	int ret = (*firstNode)->value;
	(*firstNode) = newFirstNode;
	return ret;
}

int getQueueSize(node **firstNode) {
	if (firstNode == NULL || (*firstNode) == NULL)
		return 0;
	node *temp = (node *)malloc(sizeof(node));
	int count = 1;
	temp = (*firstNode)->next;
	while (temp != NULL)
	{
		temp = temp->next;
		count++;
	}
	return count;
}
