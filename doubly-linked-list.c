/*
 *  doubly-linked-list.c
 *
 *  Doubly Linked List
 *
 *  Data Structures
 *  Department of Computer Science 
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* �ʿ��� ������� �߰� if necessary */


typedef struct Node { // typedef ����� listNode ����ü ����
	int key; // ������ ���� ���� 
	struct Node* llink;  // ��ũ ��� ����
	struct Node* rlink;  // ��ũ ��� ����
} listNode;



typedef struct Head { // typedef ����� headNode ����ü ����
	struct Node* first; // first ��� ����
}headNode;

/* �Լ� ����Ʈ */

/* note: initialize�� ���������͸� �Ű������� ����
         lab3�� initialize�� �������� ���� �Ұ� */
int initialize(headNode** h); // �ʱ�ȭ �Լ�

/* note: freeList�� �̱������͸� �Ű������� ����
        - initialize�� �� �ٸ��� ���� �Ұ�
         - ���������͸� �Ű������� �޾Ƶ� ������ �� ���� �� */
int freeList(headNode* h);  // ����Ʈ �޸� ��ü �Լ�

int insertNode(headNode* h, int key);  //  ��� ���� �Լ�
int insertLast(headNode* h, int key);  // ������ ��� �Լ�
int insertFirst(headNode* h, int key); // ù��° ��� �Լ�
int deleteNode(headNode* h, int key);  // ��� ���� �Լ�
int deleteLast(headNode* h); // ������ ��� ���� �Լ�
int deleteFirst(headNode* h); // ù��° ��� ���� �Լ�
int invertList(headNode* h); // ����Ʈ ���� �Լ�

void printList(headNode* h); // ����Ʈ ��� �Լ� 


int main()
{
	char command; // ������ ���� ����
	int key; // ������ ���� ����
	headNode* headnode=NULL; // ����� null �� 

    printf("[----- [�����] [2018038099] -----]");

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); // ������ ���� �Է� ����

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);  // ��� �ʱ�ȭ
			break;
		case 'p': case 'P':
			printList(headnode); // ����Ʈ ���
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key); // key�� �Է�
			insertNode(headnode, key); // �Էµ� �� ��� ����
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key); // key�� �Է�
			deleteNode(headnode, key);  // �Էµ� �� ��� ����
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key); // key�� �Է�
			insertLast(headnode, key); // �Էµ� ���� ������ ��� ����
			break;
		case 'e': case 'E':
			deleteLast(headnode); // ������ ��� ����
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key); // key�� �Է�
			insertFirst(headnode, key); // �Էµ� ���� ù��° ��ġ�� ����
			break;
		case 't': case 'T':
			deleteFirst(headnode);  // ù��° ��� ����
			break;
		case 'r': case 'R':
			invertList(headnode); // ���� ���ġ
			break;
		case 'q': case 'Q':
			freeList(headnode); // �޸� ����
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(headNode** h) {  // �ʱ�ȭ �Լ�

	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if(*h != NULL) // h�� ����Ű�� ���� null�� �ƴϸ�
		freeList(*h); // �����޸� ����

	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	*h = (headNode*)malloc(sizeof(headNode)); // �����޸� �Ҵ� 
	(*h)->first = NULL; // first ��� null �� 
	return 1; // 1�� ��ȯ
}

int freeList(headNode* h){  // �޸� ���� �Լ�
	/* h�� ����� listNode �޸� ����
	 * headNode�� �����Ǿ�� ��.
	 */
	listNode* p = h->first; // p�� first ����

	listNode* prev = NULL;  // prev null ��
	while(p != NULL) { // p�� null�� �ƴϸ� �ݺ�
		prev = p; // p�� ����
		p = p->rlink; // p�� ���� ��� ����
		free(prev);  // prev �����޸� ����
	}
	free(h); // h �����޸� ����
	return 0;  // 0�� ��ȯ
}


void printList(headNode* h) { // ����Ʈ ��� �Լ�
	int i = 0; // ������ ���� ���� i�� 0 ����
	listNode* p;  // p��� ����

	printf("\n---PRINT\n");

	if(h == NULL) {  // h�� null �̸�
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;  // p�� first�� ����

	while(p != NULL) { // p�� null �� �ƴϸ� �ݺ�
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink; // p�� p���� �� ����
		i++; // i+1
	}

	printf("  items = %d\n", i);
}




/**
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(headNode* h, int key) { // ������ ��� �Լ�

	listNode* node = (listNode*)malloc(sizeof(listNode));  // �����޸��Ҵ� 
	node->key = key; // key�� ����
	node->rlink = NULL; // null �� ���� 
	node->llink = NULL; // null �� ���� 

	if (h->first == NULL) // first�� null�̸�
	{
		h->first = node; // first�� node�� ���� 
		return 0; // 0 �� ��ȯ
	}

	listNode* n = h->first; // n �� first�� ����
	while(n->rlink != NULL) { // rlink�� null�� �ƴϸ� �ݺ�
		n = n->rlink; // n�� rlink �� ����
	}
	n->rlink = node; // rlink�� node�� ���� 
	node->llink = n; // llink�� n�� ���� 
	return 0; // 0�� ��ȯ 
}



/**
 * list�� ������ ��� ����
 */
int deleteLast(headNode* h) { // ������ ��� ���� �Լ� 

	if (h->first == NULL) // first�� null�� ������
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;  // n�� ����� ����Ű�� first ����
	listNode* trail = NULL; // trail�� null ��

	/* ��尡 �ϳ��� �ִ� ���, �� first node == last node��  ��� ó�� */
	if(n->rlink == NULL) { // rlink�� null�� ������ 
		h->first = NULL; // first�� null �� 
		free(n); // �����޸� ����
		return 0; // 0 �� ��ȯ
	}

	/* ������ ������ �̵� */
	while(n->rlink != NULL) {  // rlink�� null�� �ƴϸ� �ݺ�
		trail = n; // n �� ���� 
		n = n->rlink; // n�� ����Ű�� rlink�� ����
	}

	/* n�� �����ǹǷ�, ���� ����� ��ũ NULL ó�� */
	trail->rlink = NULL; // trail �� ����Ű�� rlink�� null ��
	free(n); // �޸� ����

	return 0; // 0 �� ��ȯ
}



/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(headNode* h, int key) { // ù��° ��� �Լ�

	listNode* node = (listNode*)malloc(sizeof(listNode)); // �����޸� �Ҵ�
	node->key = key;  // key�� ����
	node->rlink = node->llink = NULL; // ��� rlink, llink �� null

	if(h->first == NULL) // first �� null �̸�
	{
		h->first = node; // first�� node ���� 
		return 1; // 1�� ��ȯ 
	}

	node->rlink = h->first; // ��� rlink�� ����� ����Ű�� first�� ���� 
	node->llink = NULL; // llink�� null ��

	listNode *p = h->first; // *p �� first�� ����
	p->llink = node; // llink�� node ����
	h->first = node; // first�� node ����

	return 0; // 0�� ��ȯ
}

/**
 * list�� ù��° ��� ����
 */
int deleteFirst(headNode* h) { // ù��° ��� ���� �Լ� 

	if (h->first == NULL) // first�� null�� ������ 
	{
		printf("nothing to delete.\n");
		return 0; 
	}
	listNode* n = h->first; // n�� ����� ����Ű�� first ����
	h->first = n->rlink; // ����� ����Ű�� first�� ��� rlink�� ����

	free(n); // �޸� ����

	return 0; // 0�� ��ȯ
}



/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(headNode* h) { // ���� ���ġ �Լ�


	if(h->first == NULL) {  // first�� null�� ������
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->first;  // ������ n�� first�� ����
	listNode *trail = NULL; // ������ trail�� null��
	listNode *middle = NULL;  // ������ middle�� null��

	while(n != NULL){ // n�� null �� �ƴϸ� �ݺ�
		trail = middle;  // trail �� middle�� 
		middle = n; // middle�� n��
		n = n->rlink; // n�� ���� ��� ��
		middle->rlink = trail; // middle ���� ��忡 trail �� 
		middle->llink = n; // middle ���� ��忡 n �� 
	}

	h->first = middle; // first�� middle��

	return 0;
}



/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(headNode* h, int key) { // ��� ���� �Լ�

	listNode* node = (listNode*)malloc(sizeof(listNode)); // �����޸� �Ҵ�
	node->key = key; // ��忡 �Էµ� Ű�� ���� 
	node->llink = node->rlink = NULL; // ��� llink, rlink �� null

	if (h->first == NULL)  // ù��° ��尡 null �̸� 
	{
		h->first = node; // node�� ����
		return 0;
	}

	listNode* n = h->first; // n�� first�� ����

	/* key�� �������� ������ ��ġ�� ã�´� */
	while(n != NULL) { // n�� NULL�̸� �ݺ�
		if(n->key >= key) { // ��� Ű�� �Էµ� Ű�� ���ų� ũ��
			/* ù ��� ���ʿ� �����ؾ��� ��� ���� �˻� */
			if(n == h->first) { // n �� first�� ������
				insertFirst(h, key); // insertFirst �Լ�ȣ��
			} else { /* �߰��̰ų� �������� ��� */
				node->rlink = n; // ��� rlink�� n�� ����
				node->llink = n->llink; // ��� llink�� n ->llink �� ����
				n->llink->rlink = node;  // rlink�� node �� ����
			}
			return 0;
		}

		n = n->rlink; // rlink�� ����
	}

	/* ������ ������ ã�� ���� ���, �������� ���� */
	insertLast(h, key); // insertLast �Լ� ȣ�� 
	return 0;
}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(headNode* h, int key) { // ��� ���� �Լ� 

	if (h->first == NULL)  // first �� null �̸�
	{
		printf("nothing to delete.\n");
		return 1;
	}

	listNode* n = h->first;  // n�� ����� ����Ű�� first ����

	while(n != NULL) {  // n�� null�� �ƴϸ� �ݺ� 
		if(n->key == key) { // ��� Ű�� �Է� Ű�� ������
			if(n == h->first) { /* ù ���° ��� �ΰ�� */
				deleteFirst(h); // deleteFirst �Լ� ȣ�� 
			} else if (n->rlink == NULL){ /* ������ ����� ��� */
				deleteLast(h); // deleteLast �Լ� ȣ�� 
			} else { /* �߰��� ��� */
				n->llink->rlink = n->rlink; // rlink�� n->rlink �� 
				n->rlink->llink = n->llink; // llink�� n->llink �� 
				free(n); // �����޸� ���� 
			}
			return 1;
		}

		n = n->rlink; // n�� ����Ű�� rlink�� ���� 
	}

	/* ã�� �� �Ѱ�� */
	printf("cannot find the node for key = %d\n", key);
	return 1;
}


