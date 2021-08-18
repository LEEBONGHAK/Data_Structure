#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>		// malloc()
#include <string.h>		// node 안에 문자열 형식으로 들어갈 것임 strcpy()

/*
	Queue Data Structure

	- 데이터를 쌓아서 관리하는 방식
	- 데이터를 넣는(쌓는) 작업을 엔큐(ENQUEUE)
	- 데이터를 꺼내는 작업을 디큐(Dequeue)
	- 마지막에 입력된 데이터가 마지막에 출력되는 방식이며 이 방식을
	  FIFO(Last In, Last Out) 또는 FIFO(First In, First Out)라고 부름

	참고
	- 스기우라 켄 / 그림으로 배우는 알고리즘 Alogorithm Basic
	- 코딩하는거니 / https://www.youtube.com/watch?v=fCRTmqjTKIc
*/


// 구조체와 queue, node 생성함수 - 메모리 할당과 기본값 세팅 함수들 
typedef struct qNode {	// node 구조제 정의

	char* data;			// node 데이터
	struct qNode* next;	// 다음 node 주소
} Node;

typedef struct listQueue {	// queue 구조체 정의

	Node* front;	// 제일 처음을 pointer하는 node
	Node* rear;		// 제일 마지막을 pointer하는 node
	int size;		// queue의 사이즈 기억
} listQueue;

void createQueue(listQueue** Queue) {	// queue 구조체의 메모리, 초기값 세팅 함수

	(*Queue) = (listQueue*)malloc(sizeof(listQueue));	// queue의 메모리 할당
	(*Queue)->front = NULL;	// 초기화
	(*Queue)->rear = NULL;	// 초기화
	(*Queue)->size = 0;		// 초기화
}

Node* createNode(char* newChar) {	// queue을 구성하는 node의 메모리와 초기값 설정 함수

	Node* newNode = (Node*)malloc(sizeof(Node));	// node의 메모리 할당
	newNode->data = (char*)malloc(strlen(newChar) + 1);	// node 내 문자열 메모리 할당 (null character 고려)

	strcpy(newNode->data, newChar);	// 유저가 전달해준 문자열로 node 데이터 입력
	newNode->next = NULL;		// list의 next를 가르키는 link 초기화

	return newNode;
}

void deleteNode(Node* removeNode) {		// node를 비워주는 함수

	free(removeNode->data);		// node 내 데이터 삭제
	free(removeNode);			// node 삭제
}

// 맨 앞에 node를 알려주는 함수
Node* Peek(listQueue* Queue) {
	return Queue->front;
}

// Enqueue(Queue, Node) - queue에 데이터를 집어넣는 함수
void Enqueue(listQueue* Queue, Node* newNode) {		// Enqueue 함수는 target queue과 넣고자 하는 node를 전달 받는다.

	// when queue is empty
	if (Queue->size == 0) {		// = if (Queue->peek == NULL) {

		Queue->front = newNode;	// queue가 비어 있다면 집어 넣는 node front로 설정
		Queue->rear = newNode;
	}
	// when queue is not empty
	else {

		Queue->rear->next = newNode;	// LILO의 특성에 따라 새로운 노드를 현재 마지막 node(rear)의 next link로 설정
		Queue->rear = newNode;			// 새로운 node를 새로운 queue의 마지막 node(rear)로 설정
	}
	Queue->size++;		// queue 사이즈 증가
}


// Dequeue(Queue) - queue에서 가장 처음 Enqueue된 node를 빼내오는 함수
Node* Dequeue(listQueue* Queue) {		// Dequeue함수는 자료를 빼내올 stack을 전달받고 가장 처음 Enqueue된 node를 return

	Node* tempNode;					// return 할 node를 보관할 임시 node pointer

	// when queue is empty
	if (Queue->size == 0) {			// = if (Stack->peer == NULL) {

		printf("Queue is empty");
		tempNode = NULL;			// Dequeue할 node가 없으므로 NULL return
	}
	// when queue is not empty
	else {

		tempNode = Queue->front;		// 현재 맨 처음 node(front)를 임시 노드에 보관
		Queue->front = Queue->front->next;	// 최상단 node가 가르키는 front을 다음 노드로 이동
		Queue->size--;		// queue 사이즈 감소
	}

	return tempNode;		// 임시 보관되어 있는 맨 처음 node return 
}

void deleteQueue(listQueue* Queue) {	// queue를 비워주는 함수

	int count = Queue->size;	// queue size를 받아오는 변수
	int i;
	Node* tempNode;		// node를 보관할 임시 node pointer

	for (i = 0; i < count; i++) {	// loop를 queue size만큼 실행하면서 node를 제거

		tempNode = Dequeue(Queue);		// 임시 node에 제거할 node를 꺼내옴
		deleteNode(tempNode);		// node 제거
	}

	free(Queue);		// queue 제거
}

int main() {

	int i;
	listQueue* Queue;		// queue 구조체 선언

	createQueue(&Queue);	// queue 생성

	Enqueue(Queue, createNode("a"));	// node 생성 후 queue에 node를 넣음
	Enqueue(Queue, createNode("c"));
	Enqueue(Queue, createNode("d"));
	Enqueue(Queue, createNode("b"));

	printf("abcd enqueue\n");

	Node* temp1 = Peek(Queue);		// peek에 있는 node

	printf("\n--Current Queue--[size:%d]\n", Queue->size);
	printf("\nfront is [%s]\n", Queue->front->data);
	printf("rear is : [%s]\n", Queue->rear->data);

	Node* horse = Queue->front;
	for (i = 0; i < (Queue->size); i++) {

		printf("%s\n", horse->data);
		horse = horse->next;
	}

	horse = Dequeue(Queue);
	horse = Dequeue(Queue);

	printf("\n--Current Queue--[size:%d]\n", Queue->size);

	horse = Queue->front;
	for (i = 0; i < (Queue->size); i++) {

		printf("%s\n", horse->data);
		horse = horse->next;
	}

	deleteQueue(Queue);
	printf("\nQueue has been completely free\n");

	return 0;
}