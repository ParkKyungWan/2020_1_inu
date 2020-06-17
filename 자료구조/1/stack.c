#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 30 //창고가 꽉차지 않도록(이 경우는 문제에X), 매일 컴퓨터가 들어올 경우를 대비

typedef struct{  //'컴퓨터'는 각각 수리에 필요한 소요시간과, 식별값을 가집니다.
	int id;
	int duration;
}computer;

typedef struct{  //'수리기사'는 동시에 3개의 컴퓨터를 수리가능
	computer workroom[3]; // 컴퓨터를 담을 배열
	int isused[3];         // 각각의 workroom 이 사용중인지 체크할 배열
	int money;
}repairman;


//--- 기타 함수 ---//
void error(char *message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}
//--------------------

//---------- 스택 코드 시작 --------------

typedef struct {    //'창고'에는 컴퓨터를 쌓는 대기열이 있습니다. (문이 고장나 여는 문에서 물건을 꺼내야 합니다)
	computer Stack[MAX_STACK_SIZE];
	int top;
}warehouse;


// 스택 초기화 함수
void init_stack(warehouse *s) {
	s->top = -1;
}

//공백 상태 검출 함수
int is_empty(warehouse *s) {
	return(s->top == -1);
}

//포화 상태 검출 함수
int is_full(warehouse *s) {
	return(s->top == (MAX_STACK_SIZE));
}

// 삽입함수
void push(warehouse *s, computer item)
{
	if (is_full(s)) {
		fprintf(stderr, "창고가 꽉 찼습니다\n");
		return;
	}
	else s->Stack[++(s->top)] = item;
}
// 삭제함수
computer pop(warehouse *s)
{
	if (is_empty(s)) {
		fprintf(stderr, "창고가 비었습니다\n");
		exit(1);
	}
	else return s->Stack[(s->top)--];
}
//출력 함수
void stack_print(warehouse *s) {
	printf("\n-[창고 상황]\n");
	if (!is_empty(s)) {
		int i = 0;
		computer c;
		do {

			printf(" %d 일이 걸리는 컴퓨터(%d) |  ", s->Stack[i].duration, s->Stack[i].id);
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

// - ------스택 코드 종료 ------------


//---------main 함수--------------
int main(void) {

	warehouse wh;									//창고 생성
	init_stack(&wh);								//창고 초기화

	repairman me;									//저는 수리공입니다.
	me.money = 0;									//일을 구하기 전까진 거지신세입니다.
	for (int i = 0; i < 3; i++) {
		me.isused[i] = 0;
	}												//3개의 공간 모두 미사용중

	computer c;
	c.id = 0;
	c.duration = 0;

	int num;										//랜덤값을 담을 정수형 변수
	int total_computer=0;							//컴퓨터 수 누적값
	int total_success = 0;							//수리성공 컴퓨터 수 누적값
	srand(time(NULL));

	for (int i = 0; i < 30; i++) {					//30일간 수리 진행

		printf("\n\n----%d 일차, 날이 밝았습니다!---------\n\n",i+1);

		num = rand() % 10;

		printf("-[오늘의 소식]\n");
		if (num < 7) {			//70%확률로 새(고장난) 컴퓨터를 맡게됩니다.

			c.id = ++total_computer;
			c.duration = rand() % 7 + 1;

			push(&wh,c);
			printf("새로운 컴퓨터(%d 번) 을 맡게 되었습니다. * %d 일이 걸립니다\n\n",total_computer,c.duration);

		}
		else {                 //새 일을 맡지 못할수도 있습니다.
			printf("새로운 일이 없습니다.\n\n");
		}

		printf("-[작업 진행]\n");
		for (int j = 0; j < 3; j++) {				//총 3개의 작업실을 확인합니다.

			if (me.isused[j]) {					//수리중인 컴퓨터가 있을 경우

				me.workroom[j].duration -= 1;				//하룻동안 일을 했을 것입니다.

				if (!me.workroom[j].duration) {				//수리가 완료되었다면 (남은 일 수가 없을경우)
					int pay = rand() % 150000 + 50001;
					me.money += pay;						//pay 입금
					me.isused[j] = 0;						//작업실을 비웁니다.
					total_success++;						//일을 하나 마무리했습니다.


					printf("%d번 작업실 상태: 오늘 %d 번 컴퓨터의 수리가 완료되어 \n보수로 %d원을 받았습니다.", j + 1, me.workroom[j].id, pay);
					printf("(%d / %d)\n", me.money, total_success);

				}
				else {
					printf("%d번 작업실 상태 : %d일 남음\n", j + 1, me.workroom[j].duration);
				}
			}
			if (!me.isused[j] && !is_empty(&wh)) {	//수리중인 컴퓨터가 없을경우,창고에 쌓인 컴퓨터가 있다면

				me.workroom[j] = pop(&wh);				//쌓인 컴퓨터중 가장 '최근의' 것을 가져와 채웁니다.
				printf("오늘부터 %d 번 작업실에서 컴퓨터(%d)의 수리를 시작합니다.\n", j + 1, me.workroom[j].id);
				me.isused[j] = 1;

			}

		}

		stack_print(&wh);
		printf("\n\n");
	}
	printf("<<<< 최종 결과>>>>\n%d개의 일을 하여 %d원을 벌었습니다.\n\n",total_success,me.money);
	return;

}