
#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 30 //â�� ������ �ʵ���(�� ���� ������X), ���� ��ǻ�Ͱ� ���� ��츦 ���

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

//-----------����ť �ڵ� ���� --------------

typedef struct {    //'â��'���� ��ǻ�͸� �״� ��⿭�� �ֽ��ϴ�.
	computer Queue[MAX_QUEUE_SIZE];
	int front, rear;
}warehouse; 

//���� ���� ���� �Լ�
int init_queue(warehouse *q) {
	q->front = q->rear = 0;
}
int is_empty(warehouse *q) {
	return (q->front == q->rear);
}

//��ȭ ���� ���� �Լ�
int is_full(warehouse *q) {
	return((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

//���� �Լ�
void enqueue(warehouse *q, computer c) {
	if (is_full(q))
		error("â�� �� á���ϴ�");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->Queue[q->rear] = c;
}

//���� �Լ�
computer dequeue(warehouse *q) {
	if (is_empty(q))
		error("â�� ����ֽ��ϴ�");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->Queue[q->front];
}

//��� �Լ�
void queue_print(warehouse *q) {
	printf("\n-[â�� ��Ȳ]\n");
	if (!is_empty(q)) {
		int i = q->front;
		computer c;
		do {

			i = (i + 1) % (MAX_QUEUE_SIZE);
			printf(" %d ���� �ɸ��� ��ǻ��(%d) |  ", q->Queue[i].duration, q->Queue[i].id);
			if (i == q->rear)
				break;
		} while (i != q->front);
	}
	else {
		printf("empty");
	}
	printf("\n");
}
// - ------����ť �ڵ� ���� ------------


//---------main �Լ�--------------
int main(void) {
	
	warehouse wh;									//â�� ����
	init_queue(&wh);								//â�� front,rear �ʱ�ȭ

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

			enqueue(&wh,c);
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

				me.workroom[j] = dequeue(&wh);				//���� ��ǻ���� ���� ������ ���� ������ ä��ϴ�.
				printf("���ú��� %d �� �۾��ǿ��� ��ǻ��(%d)�� ������ �����մϴ�.\n", j + 1, me.workroom[j].id);
				me.isused[j] = 1;

			}

		}

		queue_print(&wh);
		printf("\n\n");
	}
	printf("<<<< ���� ���>>>>\n%d���� ���� �Ͽ� %d���� �������ϴ�.\n\n",total_success,me.money);
	return;

}
