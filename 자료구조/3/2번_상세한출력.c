#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000000 /* 무한대 (연결이 없는 경우) */

typedef struct GraphType {
	int n; // 정점의 개수
	int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int distance[MAX_VERTICES];/* 시작정점으로부터의 최단경로 거리 */
int found[MAX_VERTICES]; /* 방문한 정점 표시 */


char alpha[9] = { 'A','B','C','D','E','F','G','H','I' };
/*
   int 값을 길 이름 ( A ~ I ) 로 문자화 하기 쉽도록 만들어둔 배열입니다.
   alpha[int] 를 이용해 길의 이름을 char형으로 얻을 수 있습니다.
*/

int count[9][9];
/*
   각 도로를 몇번씩 지나는지 기록

   count[i][j] 는 길 alpha[i]-alpha[j] 의 빈도수를 의미합니다. (메인함수에서 초기화)
   ex) count[3][4] = 길 alpha[3]-alpha[4] 의 빈도수 = 길 D-E 의 빈도수
*/
char name[9][9][sizeof(char) * 4];
/*
   각 도로의 이름 기록

   name[i][j] 는 "alpha[i]-alpha[j]" 입니다. (메인함수에서 초기화)
   ex) count[3][4] = "alpha[3]-alpha[4]"= "D-E"
   버블정렬 할 때 count 배열의 순서가 망가지게 되므로, 바뀐 순서를 표현하기 위해 사용합니다.
*/
int between[9][9];
/*

   중간지점을 기록

   between[i][j] 는 alpha[i]에서 alpha[j]로 가는 최단거리의 중간점을 의미합니다.

   ex)   alpha[3]에서 alpha[4] (D -> E) 로 가는 최단거리는
	  D 에서 alpha[between[3][4]] 까지의 최단거리 + alpha[between[3][4]] 에서 E 까지의 최단거리
	  가 됩니다.

*/



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
		for (w = 0; w < g->n; w++) {
			if (!found[w]) {
				if (distance[u] + g->weight[u][w] < distance[w]) {
					distance[w] = distance[u] + g->weight[u][w];

					/*
					이 상황에서
					distance[w] = distance[u] + g->weight[u][w]
					즉, w까지의 거리 = u까지의 거리 + u에서 w까지의 거리 이므로
					u가 start 와 w 사이의 최단거리에서 들르게 되는 중간점이 됩니다.
					*/
					between[start][w] = u;
					//따라서 u를 중간점으로 기록해 줍니다.

				}
			}

		}

	}
}

int main(void)
{

	GraphType g = { 9,
	{{ 0, 9, 3, 8, 6, INF, 3, INF, INF }, //A~
	{ 9, 0, 2, 4, INF, INF, INF, INF, INF }, //B~
	{ 3,2,0,7,2, INF, INF, INF, INF},//C~
	{ 8,4,7,0,6,7, INF,2, INF },//D~
	{ 6, INF,2,6,0, INF, INF, INF, INF },//E~
	{  INF, INF, INF,7, INF,0,3, INF,4 },//F~
	{ 3, INF, INF, INF, INF,3,0, INF,6 }, //G~
	{  INF, INF, INF,2, INF, INF, INF,0,2 }, //H~
	{ INF, INF, INF, INF, INF,4,6,2,0 }, }//I~
	};
	for (int i = 0; i < 9; i++)
		shortest_path(&g, i);
	// 0~9 ( A~I ) 에서 다른 길로 가는 최단거리들을 구합니다.
	// 중간지점들이 shortest_path 내부에서 between ( int[9][9] ) 에 기록됩니다.


 /*
 이제 count 와 name 을 초기화 해줍니다.
 - count에 대한 설명 ( line 25 )
 - name에 대한 설명 ( line 33 )

 count의 모든 요소는 0으로 초기화 해주며,
 모든 name[i][j] 를 "alpha[i]-alpha[j]"로 초기화해줍니다.
 */
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			count[i][j] = 0;

			name[i][j][0] = alpha[i];
			name[i][j][1] = '-';
			name[i][j][2] = alpha[j];
			name[i][j][3] = '\0';
		}
	}


	//이제 count 를 제대로 설정할 차례입니다.

	for (int i = 0; i < 9; i++) {

		for (int j = 0; j < 9; j++) {
			if (i != j) {             // i 와 j 가 같은 경우 무시합니다.
								 //( 예를들어 길 A-A 는 존재하지 않습니다)
								 // 도시 j에서 i 로 가는 최단거리를 구합니다.
				int now = j;
				int next = between[i][j];
				printf("\n\n%c -> %c 에 대한 최단경로는 다음과 같습니다. \n %c", alpha[j], alpha[i],alpha[j]);
				/*
				   i 에서 j 로 가는 최단 경로는 j 에서 i로 오는 최단 경로와 같습니다.
				   또한 between[i][j] 는 i 에서 j 로 가는 최단 경로중에서 j와 가장 가까운 도시입니다.

				   따라서 i 에서 j 로 가는 최단 경로는
				   i -> j
				   i ->  between[i][j] -> j
				   i ->  between[i][ between[i][j] ] -> between[i][j] -> j
				   ...
				   와 같이 세분화 시킬 수 있으며, 중간지점이 더이상 존재하지 않을때까지 반복하여
				   모든 경로를 알아냅니다.


				*/
				while (next) {
					if (between[i][next])
						count[now][next]++;
					now = next;
					printf("-> %c ", alpha[now]);
					next = between[i][next];
				}
				count[now][i]++;
				printf("-> %c ", alpha[i]);
				/*
				   위의 코드는 다음의 연산을 실행합니다.
				   i -> j 가

				   i -> x -> j 로 세분화되면
				   길 j-x 의 빈도수를 1 높힙니다.

				   i-> x2 -> x - > j 로 한번 더 세분화되면
				   길 x-x2 의 빈도수를 1 높힙니다.

				   길이 완벽히 세분화될까지 반복합니다.

				*/
			}

		}
	}

	/*
	   길 A-B 는 B-A 와 같으므로 , count[i][j] 와 count[j][i]를 하나로 합칩니다.
	*/
	for (int i = 0, start = 0; i < 9; i++, start++) {
		for (int j = start; j < 9; j++) {
			if (count[i][j] + count[j][i])
				count[i][j] += count[j][i];
		}

	}

	/*
	   버블정렬을 이용하여 count 배열 내의 합쳐진 부분만을 정렬합니다.
	   두 값을 바꿀땐, name 도 바꿔줍니다.
	   정렬이 끝나면, count 배열내의 값을 순서대로 출력하였을때 내림차순이어야 합니다.


	   - 자세한 설명-

	   count 배열은 다음과 같은 형태입니다.

	   [ A-A 의 빈도수 , A-B의 빈도수, A-C의 빈도수 , ... .. ]
	   [ B-A 의 빈도수 , B-B의 빈도수 , B-C의 빈도수 , ... ...]
	   ...
	   [ I-A 의 빈도수, .... ... ]

	   name 배열은 다음과 같은 형태로 초기화되어 있습니다.

	   ["A-A" , "A-B" , "A-C", "A-D " , ... ... ]
	   ["B-A", "B-B", "B-C",             ... ...]
	   ...
	   ["I-A", "I-B", ... ]

	   만약 길 A-B 의 빈도수가 길 A-C의 빈도수 보다 큰 경우라면
	   내림차순 정렬 (버블) 을 위해 두 값을 교체합니다.


	   count

	   [ A-A 의 빈도수 , A-C의 빈도수, A-B의 빈도수 , ... .. ]
						 |바뀐 부분|
	   [ B-A 의 빈도수 , B-B의 빈도수 , B-C의 빈도수 , ... ...]
	   ...
	   [ I-A 의 빈도수, .... ... ]

	   name
	   ["A-A" , "A-C" ,"A-B" , "A-D " , ... ... ]
			  |바뀐 부분|
	   ["B-A", "B-B", "B-C",             ... ...]
	   ...
	   ["I-A", "I-B", ... ]

	   45바퀴를 돌면 완벽히 내림차순이 됩니다.

	*/

	//이전에 A-B 와 B-A 처럼 겹치는 부분을 합쳐두었으므로 , 절반은 무시하고 정렬합니다.
	for (int loop = 0; loop < 45; loop++) {
		int i_before = 0;
		int j_before = 0;
		for (int i = 0, start = 0; i < 9; i++, start++) {
			for (int j = start; j < 9; j++) {
				if (count[i_before][j_before] < count[i][j]) {
					int tmp = count[i][j];
					char tmp_name[sizeof(char) * 4];
					strcpy(tmp_name, name[i][j]);
					strcpy(name[i][j], name[i_before][j_before]);
					strcpy(name[i_before][j_before], tmp_name);
					count[i][j] = count[i_before][j_before];
					count[i_before][j_before] = tmp;

				}

				i_before = i;
				j_before = j;
			}

		}
	}


	/*
	이제 출력해주면 됩니다.
	count 배열과 name 배열을 순서대로 출력하면, 정렬된 값들이 보입니다.

	*/

	printf("\n\n---- 각 도로는 몇번씩 등장했을까요? (내림차순)----\n\n");
	for (int i = 0, start = 0; i < 9; i++, start++) {
		for (int j = start; j < 9; j++) {
			if (count[i][j])
				printf("%s : %d 번\n", name[i][j], count[i][j]);
		}
	}
	return 0;


}