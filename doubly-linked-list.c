/*
 *  doubly-linked-list.c
 *
 *  Doubly Linked List
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>

/* 필요한 헤더파일 추가 if necessary */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;



typedef struct Head {
	struct Node* first;
}headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음*/
int initialize(headNode** h);

/* note: freeList는 싱글 포인터를 매개변수로 받음
        - initialize와 왜 다른지 이해 할것
        - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode* h);

int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);


int main()
{
	char command;
	int key;
	headNode* headnode = NULL;

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
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(headNode** h) {

    if(*h != NULL)
		freeList(*h); //만약 이미 리스트가 있다면 전부 할당 해제

	
	*h = (headNode*)malloc(sizeof(headNode));
	(*h)->first = NULL;

	return 1;
}

int freeList(headNode* h){

    listNode* p = h->first;

	listNode* prev = NULL;
	while(p != NULL) {
		prev = p;
		p = p->rlink;
		free(prev);
	}
	free(h);

	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return; 
	}

	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i);
}




/**
 * list�� key�� ���� �몃뱶�섎굹瑜� 異붽�
 */
int insertLast(headNode* h, int key) {

    listNode * newNode = (listNode*)malloc(sizeof(listNode));

    listNode * cur = h->first;

    newNode->llink = NULL;
    newNode->rlink = NULL;

    newNode->key = key;

    while(cur->rlink != NULL) cur = cur->rlink;

    cur->rlink = newNode;

    newNode->llink = cur;


	return 0;
}



/**
 * list�� 留덉�留� �몃뱶 ��젣
 */
int deleteLast(headNode* h) {

    listNode * cur = h->first;

    if(cur->rlink == NULL){

        free(cur);
        h->first = NULL;
    }

    else{

        while(cur->rlink != NULL) cur = cur->rlink;
        
        cur = cur->llink;

        free(cur->rlink);

        cur->rlink = NULL;

    }

	return 0;
}



/**
 * list 泥섏쓬�� key�� ���� �몃뱶�섎굹瑜� 異붽�
 */
int insertFirst(headNode* h, int key) {
    

    listNode * cur = h->first;

    listNode * newNode = (listNode*)malloc(sizeof(listNode));

    newNode->llink = NULL;
    newNode->rlink = NULL;
    newNode->key = key;

    if(h->first == NULL){
         h->first = newNode;
    }

    else{

        h->first = newNode;

        newNode->rlink = cur;

        cur->llink = newNode;

    }

	return 0;
    
}

/**
 * list�� 泥ル쾲吏� �몃뱶 ��젣
 */
int deleteFirst(headNode* h) {

    listNode * cur = h->first;

    if(h->first == NULL){
        printf("리스트가 비어있습니다.\n\n");
    }

    else{
        cur = cur->rlink;

        free(h->first);

        if(cur != NULL){

            h->first = cur;

            cur->llink = NULL;

        }

        else h->first = NULL;

 
    }
	return 0;
}



/**
 * 由ъ뒪�몄쓽 留곹겕瑜� ��닚�쇰줈 �� 諛곗튂
 */
int invertList(headNode* h) {

    listNode * cur = h->first;

    listNode * temp;

    int count = 0;

    if(h->first == NULL){
        printf("리스트가 비어있습니다. \n\n");
        return 0;
    }

    while(1){
        temp = cur->rlink;
        cur->rlink = cur->llink;
        cur->llink = temp;

        if(cur->llink == NULL) break;

        cur = temp;
    }

    h->first = cur;

	return 0;
}



/* 由ъ뒪�몃� 寃��됲븯��, �낅젰諛쏆� key蹂대떎 �곌컪�� �섏삤�� �몃뱶 諛붾줈 �욎뿉 �쎌엯 */
int insertNode(headNode* h, int key) {


    listNode * cur = h->first;

    listNode * temp;

    listNode * newNode = (listNode*)malloc(sizeof(listNode));

    newNode ->key = key;
    newNode->llink = NULL;
    newNode->rlink = NULL;

    if(h->first == NULL) {
        insertFirst(h, key);
        return 0;
    }

    while(cur != NULL){
        if(cur->key >= key) {
            temp = cur->llink;
            cur->llink = newNode;

            newNode->rlink = cur;
            newNode ->llink = temp;

            if( temp != NULL) temp -> rlink = newNode;
            else h->first = newNode;

            return 0;
        }

        cur = cur->rlink;
    }

    cur->rlink = newNode;
    newNode->llink = cur;


	return 0;
}


/**
 * list�먯꽌 key�� ���� �몃뱶 ��젣
 */
int deleteNode(headNode* h, int key) {

     listNode * cur = h->first;

    listNode * tempL;
    listNode * tempR;

    while(cur != NULL){

        if(cur->key == key){
            tempL = cur->llink;
            tempR = cur->rlink;
            free(cur);

            if(tempL == NULL && tempR == NULL) h->first = NULL;

            else if(tempL == NULL){
                tempR->llink = tempL;
                h->first = tempR;
            }
            else if(tempR == NULL){
                tempL->rlink = tempR;
            }
            else{
                tempL->rlink = tempR;
                tempR->llink = tempL;
            }
            
            return 0;
        }

        cur = cur->rlink;

    }

    printf("일치하는 값 없음\n\n");

	return 1;
}

