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
/* 필요한 헤더파일 추가 if necessary */


typedef struct Node { // typedef 사용한 listNode 구조체 선언
	int key; // 정수형 변수 선언 
	struct Node* llink;  // 링크 노드 선언
	struct Node* rlink;  // 링크 노드 선언
} listNode;



typedef struct Head { // typedef 사용한 headNode 구조체 선언
	struct Node* first; // first 노드 선언
}headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음
         lab3의 initialize와 차이점을 이해 할것 */
int initialize(headNode** h); // 초기화 함수

/* note: freeList는 싱글포인터를 매개변수로 받음
        - initialize와 왜 다른지 이해 할것
         - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode* h);  // 리스트 메모리 해체 함수

int insertNode(headNode* h, int key);  //  노드 삽입 함수
int insertLast(headNode* h, int key);  // 마지막 노드 함수
int insertFirst(headNode* h, int key); // 첫번째 노드 함수
int deleteNode(headNode* h, int key);  // 노드 삭제 함수
int deleteLast(headNode* h); // 마지막 노드 삭제 함수
int deleteFirst(headNode* h); // 첫번째 노드 삭제 함수
int invertList(headNode* h); // 리스트 역순 함수

void printList(headNode* h); // 리스트 출력 함수 


int main()
{
	char command; // 문자형 변수 선언
	int key; // 정수형 변수 선언
	headNode* headnode=NULL; // 헤드노드 null 값 

    printf("[----- [장원도] [2018038099] -----]");

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
		scanf(" %c", &command); // 문자형 변수 입력 받음

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);  // 노드 초기화
			break;
		case 'p': case 'P':
			printList(headnode); // 리스트 출력
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key); // key값 입력
			insertNode(headnode, key); // 입력된 값 노드 삽입
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key); // key값 입력
			deleteNode(headnode, key);  // 입력된 값 노드 삭제
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key); // key값 입력
			insertLast(headnode, key); // 입력된 값을 마지막 노드 삽입
			break;
		case 'e': case 'E':
			deleteLast(headnode); // 마지막 노드 삭제
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key); // key값 입력
			insertFirst(headnode, key); // 입력된 값을 첫번째 위치에 삽입
			break;
		case 't': case 'T':
			deleteFirst(headnode);  // 첫번째 노드 삭제
			break;
		case 'r': case 'R':
			invertList(headnode); // 역순 재배치
			break;
		case 'q': case 'Q':
			freeList(headnode); // 메모리 해제
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(headNode** h) {  // 초기화 함수

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL) // h가 가르키는 곳이 null이 아니면
		freeList(*h); // 동적메모리 해제

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (headNode*)malloc(sizeof(headNode)); // 동적메모리 할당 
	(*h)->first = NULL; // first 노드 null 값 
	return 1; // 1값 반환
}

int freeList(headNode* h){  // 메모리 해제 함수
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first; // p에 first 넣음

	listNode* prev = NULL;  // prev null 값
	while(p != NULL) { // p가 null이 아니면 반복
		prev = p; // p값 넣음
		p = p->rlink; // p에 다음 노드 넣음
		free(prev);  // prev 동적메모리 해제
	}
	free(h); // h 동적메모리 해제
	return 0;  // 0값 반환
}


void printList(headNode* h) { // 리스트 출력 함수
	int i = 0; // 정수형 변수 선언 i에 0 넣음
	listNode* p;  // p노드 선언

	printf("\n---PRINT\n");

	if(h == NULL) {  // h가 null 이면
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;  // p에 first값 넣음

	while(p != NULL) { // p가 null 이 아니면 반복
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink; // p에 p다음 값 넣음
		i++; // i+1
	}

	printf("  items = %d\n", i);
}




/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) { // 마지막 노드 함수

	listNode* node = (listNode*)malloc(sizeof(listNode));  // 동적메모리할당 
	node->key = key; // key값 넣음
	node->rlink = NULL; // null 값 넣음 
	node->llink = NULL; // null 값 넣음 

	if (h->first == NULL) // first가 null이면
	{
		h->first = node; // first에 node값 넣음 
		return 0; // 0 값 반환
	}

	listNode* n = h->first; // n 에 first값 넣음
	while(n->rlink != NULL) { // rlink가 null이 아니면 반복
		n = n->rlink; // n에 rlink 값 넣음
	}
	n->rlink = node; // rlink에 node값 넣음 
	node->llink = n; // llink에 n값 넣음 
	return 0; // 0값 반환 
}



/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) { // 마지막 노드 삭제 함수 

	if (h->first == NULL) // first와 null이 같으면
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;  // n에 헤더가 가르키는 first 넣음
	listNode* trail = NULL; // trail에 null 값

	/* 노드가 하나만 있는 경우, 즉 first node == last node인  경우 처리 */
	if(n->rlink == NULL) { // rlink와 null이 같으면 
		h->first = NULL; // first에 null 값 
		free(n); // 동적메모리 해제
		return 0; // 0 값 반환
	}

	/* 마지막 노드까지 이동 */
	while(n->rlink != NULL) {  // rlink가 null이 아니면 반복
		trail = n; // n 값 넣음 
		n = n->rlink; // n이 가르키는 rlink값 넣음
	}

	/* n이 삭제되므로, 이전 노드의 링크 NULL 처리 */
	trail->rlink = NULL; // trail 이 가르키는 rlink에 null 값
	free(n); // 메모리 해제

	return 0; // 0 값 반환
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) { // 첫번째 노드 함수

	listNode* node = (listNode*)malloc(sizeof(listNode)); // 동적메모리 할당
	node->key = key;  // key값 넣음
	node->rlink = node->llink = NULL; // 노드 rlink, llink 값 null

	if(h->first == NULL) // first 가 null 이면
	{
		h->first = node; // first에 node 넣음 
		return 1; // 1값 반환 
	}

	node->rlink = h->first; // 노드 rlink에 헤더가 가르키는 first값 넣음 
	node->llink = NULL; // llink에 null 값

	listNode *p = h->first; // *p 에 first값 넣음
	p->llink = node; // llink에 node 넣음
	h->first = node; // first에 node 넣음

	return 0; // 0값 반환
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) { // 첫번째 노드 삭제 함수 

	if (h->first == NULL) // first와 null이 같으면 
	{
		printf("nothing to delete.\n");
		return 0; 
	}
	listNode* n = h->first; // n에 헤더가 가르키는 first 넣음
	h->first = n->rlink; // 헤더가 가르키는 first에 노드 rlink값 넣음

	free(n); // 메모리 해제

	return 0; // 0값 반환
}



/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) { // 역순 재배치 함수


	if(h->first == NULL) {  // first와 null이 같으면
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->first;  // 포인터 n에 first값 넣음
	listNode *trail = NULL; // 포인터 trail에 null값
	listNode *middle = NULL;  // 포인터 middle에 null값

	while(n != NULL){ // n이 null 이 아니면 반복
		trail = middle;  // trail 에 middle값 
		middle = n; // middle에 n값
		n = n->rlink; // n에 다음 노드 값
		middle->rlink = trail; // middle 다음 노드에 trail 값 
		middle->llink = n; // middle 이전 노드에 n 값 
	}

	h->first = middle; // first에 middle값

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) { // 노드 삽입 함수

	listNode* node = (listNode*)malloc(sizeof(listNode)); // 동적메모리 할당
	node->key = key; // 노드에 입력된 키값 넣음 
	node->llink = node->rlink = NULL; // 노드 llink, rlink 값 null

	if (h->first == NULL)  // 첫번째 노드가 null 이면 
	{
		h->first = node; // node값 넣음
		return 0;
	}

	listNode* n = h->first; // n에 first값 넣음

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL) { // n이 NULL이면 반복
		if(n->key >= key) { // 노드 키가 입력된 키와 같거나 크면
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->first) { // n 과 first가 같으면
				insertFirst(h, key); // insertFirst 함수호출
			} else { /* 중간이거나 마지막인 경우 */
				node->rlink = n; // 노드 rlink에 n값 넣음
				node->llink = n->llink; // 노드 llink에 n ->llink 값 넣음
				n->llink->rlink = node;  // rlink에 node 값 넣음
			}
			return 0;
		}

		n = n->rlink; // rlink값 넣음
	}

	/* 마지막 노드까지 찾지 못한 경우, 마지막에 삽입 */
	insertLast(h, key); // insertLast 함수 호출 
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) { // 노드 삭제 함수 

	if (h->first == NULL)  // first 가 null 이면
	{
		printf("nothing to delete.\n");
		return 1;
	}

	listNode* n = h->first;  // n에 헤더가 가르키는 first 넣음

	while(n != NULL) {  // n이 null이 아니면 반복 
		if(n->key == key) { // 노드 키가 입력 키와 같으면
			if(n == h->first) { /* 첫 노드째 노드 인경우 */
				deleteFirst(h); // deleteFirst 함수 호출 
			} else if (n->rlink == NULL){ /* 마지막 노드인 경우 */
				deleteLast(h); // deleteLast 함수 호출 
			} else { /* 중간인 경우 */
				n->llink->rlink = n->rlink; // rlink에 n->rlink 값 
				n->rlink->llink = n->llink; // llink에 n->llink 값 
				free(n); // 동적메모리 해제 
			}
			return 1;
		}

		n = n->rlink; // n이 가르키는 rlink값 넣음 
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key);
	return 1;
}


