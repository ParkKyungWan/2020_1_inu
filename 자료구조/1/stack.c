#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 30 //â�� ������ �ʵ���(�� ���� ������X), ���� ��ǻ�Ͱ� ���� ��츦 ���

typedef struct{  //'��ǻ��'�� ���� ������ �ʿ��� �ҿ�ð���, �ĺ����� �����ϴ�.
	int id;
	int duration;
}computer;

typedef struct{  //'�������'�� ���ÿ� 3���� ��ǻ�͸� ��������
	computer workroom[3]; // ��ǻ�͸� ���� �迭
	int isused[3];         // ������ workroom �� ��������� üũ�� �迭
	int money;
}repairman;


//--- ��Ÿ �Լ� ---//
void error(char *message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}
//--------------------

//---------- ���� �ڵ� ���� --------------

typedef struct {    //'â��'���� ��ǻ�͸� �״� ��⿭�� �ֽ��ϴ�. (���� ���峪 ���� ������ ������ ������ �մϴ�)
	computer Stack[MAX_STACK_SIZE];
	int top;
}warehouse;


// ���� �ʱ�ȭ �Լ�
void init_stack(warehouse *s) {
	s->top = -1;
}

//���� ���� ���� �Լ�
int is_empty(warehouse *s) {
	return(s->top == -1);
}

//��ȭ ���� ���� �Լ�
int is_full(warehouse *s) {
	return(s->top == (MAX_STACK_SIZE));
}

// �����Լ�
void push(warehouse *s, computer item)
{
	if (is_full(s)) {
		fprintf(stderr, "â�� �� á���ϴ�\n");
		return;
	}
	else s->Stack[++(s->top)] = item;
}
// �����Լ�
computer pop(warehouse *s)
{
	if (is_empty(s)) {
		fprintf(stderr, "â�� ������ϴ�\n");
		exit(1);
	}
	else return s->Stack[(s->top)--];
}
//��� �Լ�
void stack_print(warehouse *s) {
	printf("\n-[â�� ��Ȳ]\n");
	if (!is_empty(s)) {
		int i = 0;
		computer c;
		do {

			printf(" %d ���� �ɸ��� ��ǻ��(%d) |  ", s->Stack[i].duration, s->Stack[i].id);
			if (i == s->top)
				break;
			i++;
		} while (i <=s->top);
	}
	else {
		printf("empty");
	}
	printf("\n");
}

// - ------���� �ڵ� ���� ------------


//---------main �Լ�--------------
int main(void) {

	warehouse wh;									//â�� ����
	init_stack(&wh);								//â�� �ʱ�ȭ

	repairman me;									//���� �������Դϴ�.
	me.money = 0;									//���� ���ϱ� ������ �����ż��Դϴ�.
	for (int i = 0; i < 3; i++) {
		me.isused[i] = 0;
	}												//3���� ���� ��� �̻����

	computer c;
	c.id = 0;
	c.duration = 0;

	int num;										//�������� ���� ������ ����
	int total_computer=0;							//��ǻ�� �� ������
	int total_success = 0;							//�������� ��ǻ�� �� ������
	srand(time(NULL));

	for (int i = 0; i < 30; i++) {					//30�ϰ� ���� ����

		printf("\n\n----%d ����, ���� ��ҽ��ϴ�!---------\n\n",i+1);

		num = rand() % 10;

		printf("-[������ �ҽ�]\n");
		if (num < 7) {			//70%Ȯ���� ��(���峭) ��ǻ�͸� �ðԵ˴ϴ�.

			c.id = ++total_computer;
			c.duration = rand() % 7 + 1;

			push(&wh,c);
			printf("���ο� ��ǻ��(%d ��) �� �ð� �Ǿ����ϴ�. * %d ���� �ɸ��ϴ�\n\n",total_computer,c.duration);

		}
		else {                 //�� ���� ���� ���Ҽ��� �ֽ��ϴ�.
			printf("���ο� ���� �����ϴ�.\n\n");
		}

		printf("-[�۾� ����]\n");
		for (int j = 0; j < 3; j++) {				//�� 3���� �۾����� Ȯ���մϴ�.

			if (me.isused[j]) {					//�������� ��ǻ�Ͱ� ���� ���

				me.workroom[j].duration -= 1;				//�Ϸ��� ���� ���� ���Դϴ�.

				if (!me.workroom[j].duration) {				//������ �Ϸ�Ǿ��ٸ� (���� �� ���� �������)
					int pay = rand() % 150000 + 50001;
					me.money += pay;						//pay �Ա�
					me.isused[j] = 0;						//�۾����� ���ϴ�.
					total_success++;						//���� �ϳ� �������߽��ϴ�.


					printf("%d�� �۾��� ����: ���� %d �� ��ǻ���� ������ �Ϸ�Ǿ� \n������ %d���� �޾ҽ��ϴ�.", j + 1, me.workroom[j].id, pay);
					printf("(%d / %d)\n", me.money, total_success);

				}
				else {
					printf("%d�� �۾��� ���� : %d�� ����\n", j + 1, me.workroom[j].duration);
				}
			}
			if (!me.isused[j] && !is_empty(&wh)) {	//�������� ��ǻ�Ͱ� �������,â�� ���� ��ǻ�Ͱ� �ִٸ�

				me.workroom[j] = pop(&wh);				//���� ��ǻ���� ���� '�ֱ���' ���� ������ ä��ϴ�.
				printf("���ú��� %d �� �۾��ǿ��� ��ǻ��(%d)�� ������ �����մϴ�.\n", j + 1, me.workroom[j].id);
				me.isused[j] = 1;

			}

		}

		stack_print(&wh);
		printf("\n\n");
	}
	printf("<<<< ���� ���>>>>\n%d���� ���� �Ͽ� %d���� �������ϴ�.\n\n",total_success,me.money);
	return;

}