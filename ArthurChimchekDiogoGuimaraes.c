#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<stdbool.h>

typedef struct nodeQueue {
	int value;
	struct nodeQueue *next;
}node;

typedef struct estrutura_paginas_virtuais {
	int valor;
	struct estrutura_paginas_virtuais *prox;
} stPagVirtual;

stPagVirtual *inicio, *pagina, *pag_ant;

int popFront(node ** firstNode);
int getItem(node **);
int getQueueSize(node **firstNode);

bool has(node **firstNode, int value);
void pushBack(node ** lastNode, int newValue);
void printQueue(node **firstNode);

void main() {
	int valor, maxQueueSize, pageFaults, i;
	char req[10];
	node *currentNode, *firstNode;
	FILE *arquivo;

	valor = NULL;
	maxQueueSize = 64;
	pageFaults = 0;

	arquivo = fopen("tests/file4.txt", "r");
	pagina = malloc(sizeof(struct estrutura_paginas_virtuais));
	inicio = pagina;
	pag_ant = pagina;
	inicio->valor = valor;
	fgets(req, 9, arquivo);       			/* Le o arquivo */
	valor = atoi(req);						/* Converte o string lido para inteiro */
	//printf("\nValor lido: %d", valor);
	inicio->valor = valor;
	inicio->prox = NULL;

	while (!feof(arquivo))
	{
		fgets(req, 9, arquivo);				/* Le o arquivo */
		if (!feof(arquivo))					/* Verifica se é fim de arquivo */
		{
			valor = atoi(req);
			//printf("\nValor lido: %d", valor);

			pagina = malloc(sizeof(stPagVirtual)); 		/* Aloca nova página na memória  */
			pagina->valor = valor;

			pag_ant->prox = pagina;						/* Inclui a página na estrutura */
			pag_ant = pagina;
			pagina->prox = NULL;
		}
	}
	pagina = inicio;

	

	currentNode = (node *)malloc(sizeof(node));;
	currentNode->value = pagina->valor;
	currentNode->next = NULL;
	firstNode = (node*)currentNode;

	while (pagina != NULL)			/* passa por toda a lista e mostra o conteúdo  */
	{
		if (has(&firstNode, pagina->valor)) {
			//printf("Tem na memoria\n");
		}
		else {
			if (getQueueSize(&firstNode) == maxQueueSize) {
				//printf("\n\n%d\n\n", getQueueSize(&firstNode));
				popFront(&firstNode);
				pageFaults++;
			}
			pushBack(&currentNode, pagina->valor);
		}
		//printf("\nValor pedido: %d", pagina->valor);
		//printQueue(&firstNode);
		pagina = pagina->prox;
	}

	//printf("%d\n", getQueueSize(&firstNode));
	//printf("%d\n", popFront(&firstNode));
	//printf("%d\n", popFront(&firstNode));
	//printf("%d\n", popFront(&firstNode));
	//printf("%d\n", popFront(&firstNode));
	//printf("%d\n", getQueueSize(&firstNode));
	//printf("%d\n", has(&firstNode, 9));
	//printf("%d\n", has(&firstNode, 4));

	printf("Arquivo %d, %d páginas, %d requisições: FIFO: %d Page Faults", 1, maxQueueSize, 9999, pageFaults);

	scanf("");
}

void printQueue(node **firstNode) {
	node *temp;
	if (firstNode == NULL) {
		printf("\n\n --- Lista vazia !!!");
	}
	else {
		printf("\n\n --- ");
		node * firstNodeB = (*firstNode);
		temp = (node *)malloc(sizeof(node));
		temp = firstNodeB;
		while (temp != NULL) {
			printf("%d ", temp->value);
			temp = temp->next;
		}
		printf("\n");
	}
}

bool has(node **firstNode, int value) {
	node *temp;
	if (firstNode == NULL) {
		//printf("Lista vazia !!!");
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
	if (lastNode == NULL) {
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
