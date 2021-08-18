#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>		// malloc()
#include <string.h>		// node 안에 문자열 형식으로 들어갈 것임 strcpy()

/*
	Stack Data Structure

	- 데이터를 쌓아서 관리하는 방식
	- 데이터를 넣는(쌓는) 작업을 푸시(PUSH)
	- 데이터를 꺼내는 작업을 팝(POP)
	- 마지막에 입력된 데이터가 먼저 출력되는 방식이며 이 방식을
	  LIFO(Last In, First Out) 또는 FILO(First In, Last Out)라고 부름

	참고
	- 스기우라 켄 / 그림으로 배우는 알고리즘 Alogorithm Basic
	- 코딩하는거니 / https://www.youtube.com/watch?v=wcMe3vpZe28
*/


// 구조체와 stack, node 생성함수 - 메모리 할당과 기본값 세팅 함수들 
typedef struct sNode {	// node 구조제 정의

	char* data;			// node 데이터
	struct sNode* next;	// 이전 node 주소
} Node;

typedef struct listStack {	// stack 구조체 정의

	Node* peek;		// 제일 마지막에 push된 node 추척
	int size;		// stack의 사이즈 기억
} listStack;

void createStack(listStack** Stack) {	// stack 구조체의 메모리, 초기값 세팅 함수

	(*Stack) = (listStack*)malloc(sizeof(listStack));	// stack의 메모리 할당
	(*Stack)->peek = NULL;	// 초기화
	(*Stack)->size = 0;		// 초기화
}

Node* createNode(char* newChar) {	// stack을 구성하는 node의 메모리와 초기값 설정 함수

	Node* newNode = (Node*)malloc(sizeof(Node));	// node의 메모리 할당
	newNode->data = (char*)malloc(strlen(newChar) + 1);	// node 내 문자열 메모리 할당 (null character 고려)
	
	strcpy(newNode->data, newChar);	// 유저가 전달해준 문자열로 node 초기값 설정
	newNode->next = NULL;		// list의 next를 가르키는 link 초기화
}

void deleteNode(Node* removeNode) {		// node를 비워주는 함수

	free(removeNode->data);		// node 내 데이터 삭제
	free(removeNode);			// node 삭제
}

// Push(Stack, Node) - stack에 데이터를 집어넣는 함수
void Push(listStack* Stack, Node* newNode) {		// Push 함수는 target stack과 넣고자 하는 node를 전달 받는다.
	
	// when stack is empty
	if (Stack->size == 0) {		// = if (Stack->peek == NULL) {

		Stack->peek = newNode;	// stack이 비어 있다면 집어 넣는 node peek으로 설정
	}
	// when stack is not empty
	else {

		newNode->next = Stack->peek;	// LIFO의 특성에 따라 새로운 노드를 현재 최상단 node(peek)의 next link로 설정
		Stack->peek = newNode;			// 새로운 node를 새로운 stack의 최상단 node(peek)로 설정
	}
	Stack->size++;		// stack 사이즈 증가
}


// Pop(Stack) - stack에서 마지막 Push된 node를 빼내오는 함수
Node* Pop(listStack* Stack) {		// Pop함수는 자료를 빼내올 stack을 전달받고 마지막에 Push된 node를 return

	Node* tempNode;					// return 할 node를 보관할 임시 node pointer

	// when stack is empty
	if (Stack->size == 0) {			// = if (Stack->peer == NULL) {
		printf("Stack is empty");
		tempNode = NULL;			// Pop할 node가 없으므로 NULL return
	}
	// when stack is not empty
	else {
		tempNode = Stack->peek;		// 현재 최상단 node(peer)를 임시 노드에 보관
		Stack->peek = Stack->peek->next;	// 최상단 node가 가르키는 peek을 다음 노드로 이동
		Stack->size--;		// stack 사이즈 감소
	}

	return tempNode;		// 임시 보관되어 있는 최상단 node return 
}

void deleteStack(listStack* Stack) {	// stack를 비워주는 함수

	int count = Stack->size;	// stack size를 받아오는 변수
	int i;
	Node* tempNode;		// node를 보관할 임시 node pointer

	for (i = 0; i < count; i++) {	// loop를 stack size만큼 실행하면서 node를 제거

		tempNode = Pop(Stack);		// 임시 node에 제거할 node를 꺼내옴
		deleteNode(tempNode);		// node 제거
	}

	free(Stack);		// stack 제거
}

int main() {

	int i;
	listStack* Stack;		// stack 구조체 선언

	createStack(&Stack);	// stack 생성

	Push(Stack, createNode("a"));	// node 생성 후 stack에 node를 넣음
	Push(Stack, createNode("b"));
	Push(Stack, createNode("c"));
	Push(Stack, createNode("d"));

	printf("abcd push\n");

	printf("\n--Current Stack--[size:%d]\n", Stack->size);

	Node* horse = Stack->peek;
	for (i = 0; i < (Stack->size); i++) {
		printf("%s\n", horse->data);
		horse = horse->next;
	}

	horse = Pop(Stack);
	horse = Pop(Stack);

	printf("\n--Current Stack--[size:%d]\n", Stack->size);

	horse = Stack->peek;
	for (i = 0; i < (Stack->size); i++) {
		printf("%s\n", horse->data);
		horse = horse->next;
	}

	deleteStack(Stack);
	printf("\nStack has been completely free\n");

	return 0;
}