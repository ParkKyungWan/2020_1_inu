#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef int element;
typedef struct DListNode {
	element data;
	struct DListNode* llink;
	struct DListNode* rlink;
}DListNode; // 노드의 구조

DListNode* current; // 현재 위치
DListNode* not_current; // 지울 위치

// 이중 연결 리스트 초기화
void init(DListNode* phead)
{
	phead->llink = phead;
	phead->rlink = phead;
}
// 이중 연결 리스트의 노드 출력
void print_dlist(DListNode* phead)
{
	DListNode* p;
	for (p = phead->rlink; p != phead; p = p->rlink)
	{
		printf("<-| |%s| |-> ", p->data);
	}
	printf("\n");

}

// 새로운 데이터를 노드 before의 오른쪽에 삽입
void dinsert(DListNode* before, element data)
{
	DListNode* newnode = (DListNode*)malloc(sizeof(DListNode));
	newnode->data = data;
	newnode->llink = before;
	newnode->rlink = before->rlink;
	before->rlink->llink = newnode;
	before->rlink = newnode;
}
// 노드 removed 삭제
void ddelete(DListNode* head, DListNode* removed)
{
	if (removed == head) return;
	removed->llink->rlink = removed->rlink;
	removed->rlink->llink = removed->llink;
	free(removed);
}



int is_last(DListNode* phead) { //마지막 1개만 남아있는지 체크하는 함수입니다.

	return (phead->rlink == phead);
}


int main(void) {

	DListNode* head = (DListNode*)malloc(sizeof(DListNode)); //사용할 이중연결리스트 헤더
	int i = 0;												//반복문 등에서 자유롭게 사용할 int형 변수 i
	DListNode* p;											//반복문에서 이용할 DListNode

	init(head);				//일단 초기화를 해줍니다.

	char strs[16][15] = { "Radio", "Tuesday", "Rain", "Telephone", "Car", "Paper", "Blackboard", "Printer", "Lock", "Glass", "Memory", "Pen", "KO","Flower", "Book", "Computer" };
	//문제에서 제시된 문자열들을 일단 string 배열 (char배열의 배열) 에 넣습니다.

	for (i = 15; i >= 0; i--) {
		dinsert(head, strs[i]);
	}
	//배열 str (문제에서 제시된 문자열들의 배열) 에 있는 값을 그대로 이중연결리스트에 넣습니다.


	for (p = head->rlink; p != head; p = p->rlink) //이중연결리스트에 있는 모든 요소들을 순서대로 돕니다. (p 에 담깁니다)
	{
		if (!strcmp(p->data, "Computer")) { //맨 마지막 노드와 맨 앞 노드를 연결합니다. 
											// 오른쪽 또는 왼쪽으로 연결할때 오버플로우가 일어나면 안되기 때문입니다.
			p->rlink = head->rlink;
			head->llink = p;				//마지막요소의 다음요소는 맨 첫 요소이며, 그 역도 성립합니다.
			head->rlink->llink = p;
			break;
		}

	}

	p = head->rlink;
	while(1) { //while문안에서 조건문을 통해 종료하므로, 일단 무한루프를 하였습니다.
		
		int check_num = strlen(p->data);		//정수 check_num 은 해당 요소의 글자수를 담습니다.
		
		if (check_num % 2 == 0) {				//짝수일 경우,
			while (check_num-- > 0) {			//그 글자수만큼 왼쪽으로 이동합니다
				p = p->llink;
			}
		}
		else {									//그 외의 (홀수인) 경우.
			while (check_num-- > 0) {			//그 글자수만큼 오른쪽으로 이동합니다.
				p = p->rlink;
			}
		}
		printf("%s ", p->data);				//이동이 끝나면 해당 요소의 data를 출력합니다.

		if (is_last(p)) {					//방금 출력한 요소가 마지막 남은 요소였다면,
			ddelete(head, p);				//이것도 지우고
			return 0;						//종료합니다.
		}
		else {										//더 출력할 노드가 남아있다면,
			DListNode* tmp = p->rlink;				//삭제하기전에 임시로 담아둘 DListNode를 만들고, 다음 시작지점은 어디인지 담아둡니다.
			ddelete(head, p);						//해당 노드를 삭제합니다.
			p = tmp;								//다시 p 에 시작지점을 담고, 위로 올라가 글자수세기부터 시작합니다.
		}
	}

	return 0; //종료합니다
}