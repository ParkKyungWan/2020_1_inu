#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef int element;
typedef struct DListNode {
	element data;
	struct DListNode* llink;
	struct DListNode* rlink;
}DListNode; // ����� ����

DListNode* current; // ���� ��ġ
DListNode* not_current; // ���� ��ġ

// ���� ���� ����Ʈ �ʱ�ȭ
void init(DListNode* phead)
{
	phead->llink = phead;
	phead->rlink = phead;
}
// ���� ���� ����Ʈ�� ��� ���
void print_dlist(DListNode* phead)
{
	DListNode* p;
	for (p = phead->rlink; p != phead; p = p->rlink)
	{
		printf("<-| |%s| |-> ", p->data);
	}
	printf("\n");

}

// ���ο� �����͸� ��� before�� �����ʿ� ����
void dinsert(DListNode* before, element data)
{
	DListNode* newnode = (DListNode*)malloc(sizeof(DListNode));
	newnode->data = data;
	newnode->llink = before;
	newnode->rlink = before->rlink;
	before->rlink->llink = newnode;
	before->rlink = newnode;
}
// ��� removed ����
void ddelete(DListNode* head, DListNode* removed)
{
	if (removed == head) return;
	removed->llink->rlink = removed->rlink;
	removed->rlink->llink = removed->llink;
	free(removed);
}



int is_last(DListNode* phead) { //������ 1���� �����ִ��� üũ�ϴ� �Լ��Դϴ�.

	return (phead->rlink == phead);
}


int main(void) {

	DListNode* head = (DListNode*)malloc(sizeof(DListNode)); //����� ���߿��Ḯ��Ʈ ���
	int i = 0;												//�ݺ��� ��� �����Ӱ� ����� int�� ���� i
	DListNode* p;											//�ݺ������� �̿��� DListNode

	init(head);				//�ϴ� �ʱ�ȭ�� ���ݴϴ�.

	char strs[16][15] = { "Radio", "Tuesday", "Rain", "Telephone", "Car", "Paper", "Blackboard", "Printer", "Lock", "Glass", "Memory", "Pen", "KO","Flower", "Book", "Computer" };
	//�������� ���õ� ���ڿ����� �ϴ� string �迭 (char�迭�� �迭) �� �ֽ��ϴ�.

	for (i = 15; i >= 0; i--) {
		dinsert(head, strs[i]);
	}
	//�迭 str (�������� ���õ� ���ڿ����� �迭) �� �ִ� ���� �״�� ���߿��Ḯ��Ʈ�� �ֽ��ϴ�.


	for (p = head->rlink; p != head; p = p->rlink) //���߿��Ḯ��Ʈ�� �ִ� ��� ��ҵ��� ������� ���ϴ�. (p �� ���ϴ�)
	{
		if (!strcmp(p->data, "Computer")) { //�� ������ ���� �� �� ��带 �����մϴ�. 
											// ������ �Ǵ� �������� �����Ҷ� �����÷ο찡 �Ͼ�� �ȵǱ� �����Դϴ�.
			p->rlink = head->rlink;
			head->llink = p;				//����������� ������Ҵ� �� ù ����̸�, �� ���� �����մϴ�.
			head->rlink->llink = p;
			break;
		}

	}

	p = head->rlink;
	while(1) { //while���ȿ��� ���ǹ��� ���� �����ϹǷ�, �ϴ� ���ѷ����� �Ͽ����ϴ�.
		
		int check_num = strlen(p->data);		//���� check_num �� �ش� ����� ���ڼ��� ����ϴ�.
		
		if (check_num % 2 == 0) {				//¦���� ���,
			while (check_num-- > 0) {			//�� ���ڼ���ŭ �������� �̵��մϴ�
				p = p->llink;
			}
		}
		else {									//�� ���� (Ȧ����) ���.
			while (check_num-- > 0) {			//�� ���ڼ���ŭ ���������� �̵��մϴ�.
				p = p->rlink;
			}
		}
		printf("%s ", p->data);				//�̵��� ������ �ش� ����� data�� ����մϴ�.

		if (is_last(p)) {					//��� ����� ��Ұ� ������ ���� ��ҿ��ٸ�,
			ddelete(head, p);				//�̰͵� �����
			return 0;						//�����մϴ�.
		}
		else {										//�� ����� ��尡 �����ִٸ�,
			DListNode* tmp = p->rlink;				//�����ϱ����� �ӽ÷� ��Ƶ� DListNode�� �����, ���� ���������� ������� ��ƵӴϴ�.
			ddelete(head, p);						//�ش� ��带 �����մϴ�.
			p = tmp;								//�ٽ� p �� ���������� ���, ���� �ö� ���ڼ�������� �����մϴ�.
		}
	}

	return 0; //�����մϴ�
}