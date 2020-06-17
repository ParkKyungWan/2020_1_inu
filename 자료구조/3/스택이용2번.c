#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000000 /* 무한대 (연결이 없는 경우) */
#define MAX_STACK_SIZE 9 //최단경로의 최대 길이


typedef struct GraphType {
	int n; // 정점의 개수
	int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;
int distance[MAX_VERTICES];/* 시작정점으로부터의 최단경로 거리 */
int found[MAX_VERTICES]; /* 방문한 정점 표시 */

char cityname[9] = { 'A','B','C','D','E','F','G','H','I' }; //숫자를 도시 이름으로 쉽게 변형시키기 위해 만들었습니다.
int cnt[9][9]; //각 도로의 빈도수를 기록할 것입니다.
int dijstra[9][9]; //다익스트라의 결과 (중간 지점)이 기록될 배열입니다.

int choose(int distance[], int n, int found[])
{
	int i, min, minpos;
	min = INT_MAX;
	minpos = -1;
	for (i = 0; i < n; i++)
		if (distance[i] < min && !found[i]) {
			min = distance[i];
			minpos = i;
		}
	return minpos;
}

void shortest_path(GraphType* g, int start)
{
	int i, u, w;
	for (i = 0; i < g->n; i++) /* 초기화 */
	{
		distance[i] = g->weight[start][i];
		found[i] = FALSE;
	}
	found[start] = TRUE; /* 시작 정점 방문 표시 */
	distance[start] = 0;
	for (i = 0; i < g->n - 1; i++) {
		u = choose(distance, g->n, found);
		found[u] = TRUE;
		for (w = 0; w < g->n; w++)
			if (!found[w])
				if (distance[u] + g->weight[u][w] < distance[w]) {
					distance[w] = distance[u] + g->weight[u][w];
					dijstra[start][w] = u + 1; // 다익스트라로 알아낸 u 를 start 와 w 사이의 최단경로로서 기록합니다.
												//* u+1을 담는 이유는 , A (0) 이 false 취급되지 않도록 하기 위함입니다.
				}
	}
}

//--------------------스택을 이용할 것입니다. 스택에 dijstra[시작점][도착점]을 차례로 쌓은다음, pop을 하여 순서대로 경로를 얻어냅니다.

typedef struct {
	int index;
	char city;
}city;

typedef struct {
	city Stack[MAX_STACK_SIZE];
	int top;
}course;

typedef struct {
	int count;
	char name[4];
}street;

// 스택 초기화 함수
void init_stack(course *s) {
	s->top = -1;
}

//공백 상태 검출 함수
int is_empty(course *s) {
	return(s->top == -1);
}

//포화 상태 검출 함수
int is_full(course *s) {
	return(s->top == (MAX_STACK_SIZE));
}

// 삽입함수
void push(course *s, city item)
{
	if (is_full(s)) {
		return;
	}
	else s->Stack[++(s->top)] = item;
}
// 삭제함수
city pop(course *s)
{
	if (is_empty(s)) {
		exit(1);
	}
	else return s->Stack[(s->top)--];
}

//--------------------스택 코드 종료
int main(void)
{
	GraphType g = { 9,
	{{ 0, 9, 3, 8, 6, INF, 3, INF, INF },
	{ 9, 0, 2, 4, INF, INF, INF, INF, INF },
	{ 3,2,0,7,2, INF, INF, INF, INF},
	{ 8,4,7,0,6,7, INF,2, INF },
	{ 6, INF,2,6,0, INF, INF, INF, INF },
	{  INF, INF, INF,7, INF,0,3, INF,4 },
	{ 3, INF, INF, INF, INF,3,0, INF,6 },
	{  INF, INF, INF,2, INF, INF, INF,0,2 },
	{ INF, INF, INF, INF, INF,4,6,2,0 }, }
	};

	for (int i = 0; i < g.n; i++)
		shortest_path(&g, i); //일단 dijstra 배열에 최단경로를 기록합니다.

	

	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)  //cnt을 초기화합니다.
			cnt[i][j] = 0;

	for (int i = 0; i < 9; i++) {


		for (int j = 0; j < 9; j++) {

			course co;
			init_stack(&co);  //co 는 i 에서 출발하여 j 로 도착하는 최단코스를 기록할 배열입니다.

			city c;   //c 는 co 에 담길 도시입니다.

			if (i != j) { // i와 j 가 같은 경우 도로가 존재하지 않습니다.


				int goal = j;   //goal 은 목표도시, start 는 시작 도시입니다.
				int start = i;


				c.index = goal;
				c.city = cityname[goal];
				push(&co, c);


				int next = dijstra[start][goal]; //start와 goal 사이에 dijstra 값이 존재하는 만큼 뽑아내서, 스택에 쌓습니다.
				while (next) {
					next -= 1;
					c.index = next;
					c.city = cityname[next];
					push(&co, c);
					next = dijstra[start][next];
				}


				c.index = start;
				c.city = cityname[start];
				push(&co, c);

				int from = pop(&co).index;  //스택에 쌓아놓은 경로를 순서대로 다시 꺼냅니다.
				while (!is_empty(&co)) {
					int next = pop(&co).index; //꺼내면서 도로의 빈도수를 높입니다.
					cnt[from][next]++;
					from = next;
				}

			}

		}

	}


	
	street sts[36]; //36개의 도로 모두 등장하는 최악의 수 고려
	int final_num = 0;
	for (int i = 0; i < 9; i++) {     // i-j 와 j-i 는 같은 도로이므로, i-j 로 합쳐줍니다.
		for (int j = i; j < 9; j++) {
			cnt[i][j] += cnt[j][i];
			cnt[j][i] = 0;
			if (cnt[i][j]) {
				street s;
				s.count = cnt[i][j];
				s.name[0] = cityname[i];
				s.name[1] = '-';
				s.name[2] = cityname[j];
				s.name[3] = '\0';
				sts[final_num] = s;
				final_num++;
			}
		}
	}

	for (int i = 0; i < final_num; i++) {   // sts(street의 배열) 내부의 street 들을 내림차순으로 정렬해줍니다.
		for (int j = 0; j < final_num - 1; j++) {
			int _j = j + 1;
			if (sts[j].count < sts[_j].count) {
				street s;
				s = sts[_j];
				sts[_j] = sts[j]; sts[j] = s;
			}
		}
	}

	for (int i = 0; i < final_num; i++) { //sts (street의 배열)을 출력합니다.
		printf("\n%s : %d", sts[i].name, sts[i].count);
	}

	return 0;
}