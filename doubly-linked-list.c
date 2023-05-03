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

// **현재 노드 = 포인터 포인터가 가리키는 노드를 뜻함**

//** 노드의 노드 포인터에 주소를 넣는 것을 '연결'이라 칭하고 있음**
//** 따라서 노드에 NULL을 연결한다와 같은 매끄럽지 않은 표현도 양해 바람**

// [앞(이전)노드] - [현재 노드] - [뒷노드] 로 설명하고 있음



#include<stdio.h>
#include<stdlib.h>

/* 필요한 헤더파일 추가 if necessary */

typedef struct Node {//노드 자료형
	int key;//값
	struct Node* llink; //이전 노드 포인터
	struct Node* rlink; //이후 노드 포인터
} listNode;



typedef struct Head { //헤드노드 자료형
	struct Node* first; //첫번째 노드 포인터
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

//설명은 헤더가 아닌 정의부에서


int main()
{
	char command; //명령
	int key; //노드의 값 임시저장 변수
	headNode* headnode = NULL; //헤드 포인터

    printf("[-----[유도현][2022041001]-----]\n\n");

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

        //양식

		printf("Command = ");
		scanf(" %c", &command);
        //명령 받기

		switch(command) {//명령 받아서 분류대로 실행
        //각 명령당 할당된 작업은 위 양식에 적혀 있으므로 설명 생략
		case 'z': case 'Z':
			initialize(&headnode);//함수에 헤드노드의 주소 전달
			break;
		case 'p': case 'P':
			printList(headnode);//함수에 헤드노드 전달
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key); //노드 값 받기
			insertNode(headnode, key);//헤드노드와 노드값 전달
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);//삭제할 노드 값 받기
			deleteNode(headnode, key);//헤드노드와 노드값 전달
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);//노드 값 받기
			insertLast(headnode, key);//헤드노드와 노드값 전달
			break;
		case 'e': case 'E':
			deleteLast(headnode);//함수에 헤드노드 전달
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);//노드 값 받기
			insertFirst(headnode, key);//헤드노드와 노드값 전달
			break;
		case 't': case 'T':
			deleteFirst(headnode);//함수에 헤드노드 전달
			break;
		case 'r': case 'R':
			invertList(headnode);//함수에 헤드노드 전달
			break;
		case 'q': case 'Q':
			freeList(headnode);//함수에 헤드노드 전달
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            //지정되지 않은 글자 입력시 출력되는 오류메시지
			break;
		}

	}while(command != 'q' && command != 'Q'); //q나 Q 받으면 반복 종료

	return 1; //함수 종료
}


int initialize(headNode** h) {
    //리스트 (정확히는 헤드노드)를 새로 만드는 함수
    //이중포인터로 받는 이유는 할당된 주소를 반환하는 방식이 아니라 직접 h에 헤드포인터를 할당하기 위해서

    if(*h != NULL)
		freeList(*h); //만약 이미 리스트가 있다면 전부 할당 해제

	
	*h = (headNode*)malloc(sizeof(headNode)); //헤드노드 새로 할당
	(*h)->first = NULL;//헤드노드 뒤 NULL로 지정

	return 1;//함수 종료
}

int freeList(headNode* h){
    //리스트의 모든 요소를 할당해제하는 함수

    listNode* p = h->first;
    //포인터(=cursor) 포인터가 리스트의 첫번째 노드를 가리키게

	listNode* prev = NULL; //p가 가리키는 바로 뒤 노드를 가리킬 포인터

    //  prev    p
    //         ㅁ       ㅁ      ㅁ 
    //(이런 모양새)


	while(p != NULL) {//p가 NULL을 가리킬때까지 반복
		prev = p;//prev를 리스트 한칸 앞으로 땡기기
		p = p->rlink;//p도 리스트 한칸 앞으로 땡기기
		free(prev);//prev를 할당해제
	}
	free(h);//헤드노드 할당해제

	return 0;//함수 종료
}


void printList(headNode* h) {
	int i = 0;//위치 표기용 변수
	listNode* p;//포인터(=cursor) 포인터

	printf("\n---PRINT\n"); //양식

	if(h == NULL) {
		printf("Nothing to print....\n");//리스트 비어있을 시 오류 메세지
		return; //함수 종료
	}

	p = h->first; //p가 리스트 첫 노드 가리키게

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
        //p가 가리키는 노드의 위치와 값 출력
		p = p->rlink; //p가 다음 노드 가리키게
		i++;//위치 증가
	}

	printf("  items = %d\n", i);//총 노드 개수
}




/**
 * list�� key�� ���� �몃뱶�섎굹瑜� 異붽�
 */
int insertLast(headNode* h, int key) { 
    //리스트의 마지막에 노드를 추가하는 함수

    listNode * newNode = (listNode*)malloc(sizeof(listNode)); //노드 동적 할당

    listNode * cur = h->first; //포인터(cursor) 포인터가 첫 노드 가리키게

    newNode->llink = NULL;
    newNode->rlink = NULL;
    newNode->key = key;
    //새로운 노드 양옆 연결과 값 초기화

    while(cur->rlink != NULL) cur = cur->rlink;
    //마지막 노드 까지 포인터 포인터를 넘기기

    cur->rlink = newNode; //마지막 노드 뒤에 새로운 노드 연결

    newNode->llink = cur; //새로운 노드 전에 마지막 노드 연결


	return 0;//함수 종료
}



/**
 * list�� 留덉�留� �몃뱶 ��젣
 */
int deleteLast(headNode* h) {
    //마지막 노드를 삭제하는 함수

    listNode * cur = h->first;
    //포인터 포인터가 첫 노드를 가리키게

    if(cur == NULL){
         printf("리스트가 비어있습니다.\n\n");
         //리스트 비어있으면 오류 메세지 출력
         return 0;//함수 종료
    }

    if(cur->rlink == NULL){
        //노드가 하나밖에 없으면

        free(cur);//현재 노드 할당해제
        h->first = NULL;//헤드포인터가 NULL 가리키게
    }

    else{

        while(cur->rlink != NULL) cur = cur->rlink;
        //현재 노드가 마지막 노드일 때 까지 뒤로 넘기기
        
        cur = cur->llink; //현재 노드를 마지막 전 노드로

        free(cur->rlink); //마지막 노드 할당 해제

        cur->rlink = NULL; //현재 노드 뒤를 NULL로

    }

	return 0;//함수 종료
}



/**
 * list 泥섏쓬�� key�� ���� �몃뱶�섎굹瑜� 異붽�
 */
int insertFirst(headNode* h, int key) {
    //리스트의 처음에 노드를 삽입
    

    listNode * cur = h->first;//포인터(cursor) 포인터가 첫 노드 가리키게

    listNode * newNode = (listNode*)malloc(sizeof(listNode));//노드 동적 할당

    newNode->llink = NULL;
    newNode->rlink = NULL;
    newNode->key = key;
    //새로운 노드 양옆 연결과 값 초기화

    if(h->first == NULL){//만약 리스트가 비어 있으면
         h->first = newNode;//헤드포인터가 새로운 노드 가리키게
    }

    else{

        h->first = newNode;//헤드포인터 뒤에 새로운 노드 연결

        newNode->rlink = cur;//새로운 노드 뒤에 기존 첫 노드 연결

        cur->llink = newNode;//기존 첫 노드 전에 새로운 노드 연결

    }

	return 0; //함수 종료
    
}

/**
 * list�� 泥ル쾲吏� �몃뱶 ��젣
 */
int deleteFirst(headNode* h) {
    //첫 노드 삭제 함수

    listNode * cur = h->first;//포인터(cursor) 포인터가 첫 노드 가리키게

    if(h->first == NULL){
        printf("리스트가 비어있습니다.\n\n");
        //리스트가 비어 있으면 오류 메세지 출력
    }

    else{
        cur = cur->rlink;//포인터 포인터가 첫 노드 다음 노드를 가리키게

        free(h->first);//첫 노드를 할당 해제

        if(cur != NULL){//포인터 포인터가 NULL을 가리키지 않으면

            h->first = cur;//현재 노드를 헤드 포인터와 연결

            cur->llink = NULL;//현재 포인터 전을 NULL로

        }

        else h->first = NULL;
        //현재 노드가 하나 밖에 없는 노드면 헤드포인터에 NULL 연결

 
    }
	return 0;//함수 종료
}



/**
 * 由ъ뒪�몄쓽 留곹겕瑜� ��닚�쇰줈 �� 諛곗튂
 */
int invertList(headNode* h) {

    listNode * cur = h->first;//포인터(cursor) 포인터가 첫 노드 가리키게

    listNode * temp; //임시 노드 포인터

    if(h->first == NULL){
        printf("리스트가 비어있습니다. \n\n");
        //리스트가 비어 있으면 오류 메세지 출력
        return 0;//함수 종료
    }

    while(1){//무한 반복
        temp = cur->rlink;
        cur->rlink = cur->llink;
        cur->llink = temp;
        //위와 같은 과정으로 현재 노드에 연결된 전과 뒤 노드를 반대로 설정

        if(cur->llink == NULL) break;
        //만약 현재 노드가 마지막 노드면 반복 종료

        cur = temp;
        //포인터 포인터가 다음 노드 가리키게
    }

    h->first = cur; //기존 마지막 노드를 헤드 노드와 연결

	return 0;//함수 종료
}



/* 由ъ뒪�몃� 寃��됲븯��, �낅젰諛쏆� key蹂대떎 �곌컪�� �섏삤�� �몃뱶 諛붾줈 �욎뿉 �쎌엯 */
int insertNode(headNode* h, int key) {
    //노드를 적절한 위치에 삽입하는 함수


    listNode * cur = h->first;//포인터(cursor) 포인터가 첫 노드 가리키게

    listNode * temp;//임시 노드 포인터

    listNode * newNode = (listNode*)malloc(sizeof(listNode));//노드 동적 할당

    newNode ->key = key;
    newNode->llink = NULL;
    newNode->rlink = NULL;
    //새로운 노드 양옆 연결과 값 초기화

    if(h->first == NULL) {
        insertFirst(h, key);
        //만약 리스트가 비어있으면 insertFirst 함수에 그대로 전달
        return 0;//함수 종료
    }

    while(cur != NULL){//현재노드가 NULL이 아닐 동안 반복
        if(cur->key >= key) {//만약 입력된 값보다 현재노드의 값이 크면
            temp = cur->llink;
            cur->llink = newNode;
            //현재노드 전에 새로운 노드 연결

            newNode->rlink = cur;
            newNode ->llink = temp;
            //새로운 노드의 양 옆으로 기존 노드들 연결

            if( temp != NULL) temp -> rlink = newNode;
            //만약 이게 첫 노드면 새노드 뒤에 temp가 가리키는 노드 연결
            else h->first = newNode; //아니면 헤드포인터와 새로운 노드 연결

            return 0;//함수 종료
        }

        if(cur->rlink == NULL){//만약 이게 마지막 노드면
            if(cur->key <= key){//만약 현재 노드가 입력받은 값보다 작으면
                cur->rlink = newNode; //현재노드 뒤에 새로운 노드 연결
                newNode->llink = cur; //새로운 노드 전에 현재 노드 연결
                return 0;//함수 종료

            }
        } 

        cur = cur->rlink;//현재 노드가 다음 노드를 가리키게
    }


	return 0;//함수 종료
}


/**
 * list�먯꽌 key�� ���� �몃뱶 ��젣
 */
int deleteNode(headNode* h, int key) {
    //입력 받은 값을 가진 노드를 삭제 하는 함수

     listNode * cur = h->first;//포인터(cursor) 포인터가 첫 노드 가리키게

    listNode * tempL;
    listNode * tempR;
    //앞뒤 노드를 저장할 임시 포인터

    if(h->first == NULL){
        printf("리스트가 비어있습니다. \n\n");
        //리스트가 비어 있으면 오류 메세지 출력
        return 0;//함수 종료
    }

    while(cur != NULL){//포인터 포인터가 NULL을 가리킬 때 까지 반복

        if(cur->key == key){
            tempL = cur->llink;
            tempR = cur->rlink;
            //현재 노드의 앞뒤 노드를 임시 저장
            free(cur);//현재 노드 할당 해제

            if(tempL == NULL && tempR == NULL) h->first = NULL;
            //만약 이게 유일한 노드면 헤드 포인터에 NULL 연결

            else if(tempL == NULL){
                //만약 이게 첫 노드면
                tempR->llink = tempL;
                h->first = tempR;
                //뒷 노드 앞에 NULL 연결하고 헤드 포인터에 뒷 노드 연결
            }
            else if(tempR == NULL){
                //만약 이게 마지막 노드면
                tempL->rlink = tempR;
                //앞 노드 뒤에 NULL 연결
            }
            else{
                tempL->rlink = tempR;
                tempR->llink = tempL;
                //전 노드와 뒷 노드를 서로 연결
            }
            
            return 0;//함수 종료
        }

        cur = cur->rlink;//포인터 포인터가 다음 노드를 가리키게

    }

    printf("일치하는 값 없음\n\n");//일치하는 값 없으면 이렇게 출력

	return 1; //함수 종료
}

