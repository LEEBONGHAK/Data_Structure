#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>		// malloc()

/*
	List

	- 데이터들은 모두 떨어져 있지만, 끈(주소)으로 묶여 있다.

	Doubly Linked List Data Structure (양방향 리스트)

	- List안에서 앞쪽에서부터 뒷쪽을 가리키는 끈과 뒤에서 앞을 가리키는 끈 2개를 사용하여 순서가 있는 데이터들을 연결하는 방식
	- 데이터, 이전 요소를 가리키는 포인터, 다음 요소를 가리키는 포인터 로 구성되어 있음
	- HEAD 포인터가 가리키는 요소에서 시작하고 NEXT 포인터에 종료 정보를 저장한 요소로 끝나는 끈과 TAIL포인터가 가리키는 요소에서 시작하고 PREV 포인터에 종료 정보를 저장한 요소로 끝나는 끈으로 관리

	참고
	- 스기우라 켄 / 그림으로 배우는 알고리즘 Alogorithm Basic
	- 코딩하는거니 / url : https://www.youtube.com/watch?v=z28hgyxgORY
*/

typedef struct doubleListNode {	// node 구조제 정의

	int data;			// node 데이터
	struct doubleListNode* next;	// 이전 node 주소
	struct doubleListNode* prev;	// 다음 node 주소
} Node;


Node* createNode(int data) {	// list을 구성하는 node의 메모리와 초기값 설정 함수

	Node* newNode = (Node*)malloc(sizeof(Node));	// node의 메모리 할당

	// variable initialization
	newNode->data = data;
	newNode->next = NULL;		// list의 next를 가르키는 link 초기화
	newNode->prev = NULL;		// list의 prev를 가르키는 link 초기화

	return newNode;
}

void deleteNode(Node* removeNode) {		// node를 비워주는 함수

	free(removeNode);			// node 삭제
}

Node* getNodeAt(Node* head, int index) { // head node에서 index에 해당하는 node를 찾는 함수

	Node* horse = head;
	int count = 0;

	while (horse != NULL) {

		if (count++ == index) {		// count가 원하는 index와 같다면 horse node 반환

			return horse;
		}

		horse = horse->next;	// 못찾으면 horse는 다음 node로 이동 후 count + 1
	}

	return NULL;	// 모든 곳에서 못 찾으면 NULL 반환
}

int countNode(Node* head) {		// List 내 node의 위치(index)를 구하는 함수

	int count = 0;
	Node* horse = head;

	while (horse->next != NULL) {

		horse = horse->next;
		count++;
	}

	return count;
}

void addNode(Node** head, Node* newNode) {		// List에 node를 마지막에 추가하는 함수 (append)

	// no list exists
	if ((*head) == NULL) {

		*head = newNode;
	}
	// list exists
	else {

		Node* horse = (*head);

		while (horse->next != NULL) {		// List의 마지막을 찾음

			horse = horse->next;
		}

		// List 연결
		horse->next = newNode;
		newNode->prev = horse;
	}
}

void insertNode(Node* current, Node* newNode) {		// List 중간에 node 삽입

	// head
	if (current->prev == NULL) {

		newNode->next = current->next;
		newNode->prev = current;
		current->next = newNode;
	}
	else {
		// if tail
		if (current->next == NULL) {
			addNode(&current, newNode);
		}
		// in the middle
		else {

			current->next->prev = newNode;
			newNode->prev = current;
			newNode->next = current->next;
			current->next = newNode;
		}
	}
}

void removeNode(Node** head, Node* remove) {		// List의 node 제거

	// remove node is head
	if (*head == remove) {

		*head = remove->next;
	}

	// when remove node has next link to go
	if (remove->next != NULL) {

		remove->next->prev = remove->prev;
	}

	// when removie node has prev link to go
	if (remove->prev != NULL) {

		remove->prev->next = remove->next;
	}

	deleteNode(remove);
}

int main() {

	int i = 0;
	int count = 0;

	// future head
	Node* List = NULL;

	// temporary node
	Node* newNode = NULL;

	// current node
	Node* curr = NULL;


	for (i = 0; i < 5; i++) {

		newNode = createNode(i);
		addNode(&List, newNode);
	}

	count = countNode(List);
	for (i = 0; i < count; i++) {

		curr = getNodeAt(List, i);
		printf("List[%d] = %d\n", i, curr->data);
	}
	printf("---------- 5 Nodes Created ----------\n\n");


	newNode = createNode(99);
	curr = getNodeAt(List, 0);
	insertNode(curr, newNode);

	newNode = createNode(77);
	curr = getNodeAt(List, 4);
	insertNode(curr, newNode);

	count = countNode(List);
	for (i = 0; i < count; i++) {

		curr = getNodeAt(List, i);
		printf("List[%d] = %d\n", i, curr->data);
	}
	printf("---------- After 2 Nodes inserted ----------\n\n");


	newNode = getNodeAt(List, 1);
	removeNode(&List, newNode);

	newNode = getNodeAt(List, 0);
	removeNode(&List, newNode);

	count = countNode(List);
	for (i = 0; i < count; i++) {

		curr = getNodeAt(List, i);
		printf("List[%d] = %d\n", i, curr->data);
	}
	printf("---------- After 2 Nodes removed ----------\n\n");

	return 0;
}