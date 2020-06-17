#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000000 /* ���Ѵ� (������ ���� ���) */

typedef struct GraphType {
	int n; // ������ ����
	int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int distance[MAX_VERTICES];/* �����������κ����� �ִܰ�� �Ÿ� */
int found[MAX_VERTICES]; /* �湮�� ���� ǥ�� */


char alpha[9] = { 'A','B','C','D','E','F','G','H','I' };
/*
   int ���� �� �̸� ( A ~ I ) �� ����ȭ �ϱ� ������ ������ �迭�Դϴ�.
   alpha[int] �� �̿��� ���� �̸��� char������ ���� �� �ֽ��ϴ�.
*/

int count[9][9];
/*
   �� ���θ� ����� �������� ���

   count[i][j] �� �� alpha[i]-alpha[j] �� �󵵼��� �ǹ��մϴ�. (�����Լ����� �ʱ�ȭ)
   ex) count[3][4] = �� alpha[3]-alpha[4] �� �󵵼� = �� D-E �� �󵵼�
*/
char name[9][9][sizeof(char) * 4];
/*
   �� ������ �̸� ���

   name[i][j] �� "alpha[i]-alpha[j]" �Դϴ�. (�����Լ����� �ʱ�ȭ)
   ex) count[3][4] = "alpha[3]-alpha[4]"= "D-E"
   �������� �� �� count �迭�� ������ �������� �ǹǷ�, �ٲ� ������ ǥ���ϱ� ���� ����մϴ�.
*/
int between[9][9];
/*

   �߰������� ���

   between[i][j] �� alpha[i]���� alpha[j]�� ���� �ִܰŸ��� �߰����� �ǹ��մϴ�.

   ex)   alpha[3]���� alpha[4] (D -> E) �� ���� �ִܰŸ���
	  D ���� alpha[between[3][4]] ������ �ִܰŸ� + alpha[between[3][4]] ���� E ������ �ִܰŸ�
	  �� �˴ϴ�.

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
	for (i = 0; i < g->n; i++) /* �ʱ�ȭ */
	{
		distance[i] = g->weight[start][i];
		found[i] = FALSE;
	}
	found[start] = TRUE; /* ���� ���� �湮 ǥ�� */
	distance[start] = 0;
	for (i = 0; i < g->n - 1; i++) {
		u = choose(distance, g->n, found);
		found[u] = TRUE;
		for (w = 0; w < g->n; w++) {
			if (!found[w]) {
				if (distance[u] + g->weight[u][w] < distance[w]) {
					distance[w] = distance[u] + g->weight[u][w];

					/*
					�� ��Ȳ����
					distance[w] = distance[u] + g->weight[u][w]
					��, w������ �Ÿ� = u������ �Ÿ� + u���� w������ �Ÿ� �̹Ƿ�
					u�� start �� w ������ �ִܰŸ����� �鸣�� �Ǵ� �߰����� �˴ϴ�.
					*/
					between[start][w] = u;
					//���� u�� �߰������� ����� �ݴϴ�.

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
	// 0~9 ( A~I ) ���� �ٸ� ��� ���� �ִܰŸ����� ���մϴ�.
	// �߰��������� shortest_path ���ο��� between ( int[9][9] ) �� ��ϵ˴ϴ�.


 /*
 ���� count �� name �� �ʱ�ȭ ���ݴϴ�.
 - count�� ���� ���� ( line 25 )
 - name�� ���� ���� ( line 33 )

 count�� ��� ��Ҵ� 0���� �ʱ�ȭ ���ָ�,
 ��� name[i][j] �� "alpha[i]-alpha[j]"�� �ʱ�ȭ���ݴϴ�.
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


	//���� count �� ����� ������ �����Դϴ�.

	for (int i = 0; i < 9; i++) {

		for (int j = 0; j < 9; j++) {
			if (i != j) {             // i �� j �� ���� ��� �����մϴ�.
								 //( ������� �� A-A �� �������� �ʽ��ϴ�)
								 // ���� j���� i �� ���� �ִܰŸ��� ���մϴ�.
				int now = j;
				int next = between[i][j];
				printf("\n\n%c -> %c �� ���� �ִܰ�δ� ������ �����ϴ�. \n %c", alpha[j], alpha[i],alpha[j]);
				/*
				   i ���� j �� ���� �ִ� ��δ� j ���� i�� ���� �ִ� ��ο� �����ϴ�.
				   ���� between[i][j] �� i ���� j �� ���� �ִ� ����߿��� j�� ���� ����� �����Դϴ�.

				   ���� i ���� j �� ���� �ִ� ��δ�
				   i -> j
				   i ->  between[i][j] -> j
				   i ->  between[i][ between[i][j] ] -> between[i][j] -> j
				   ...
				   �� ���� ����ȭ ��ų �� ������, �߰������� ���̻� �������� ���������� �ݺ��Ͽ�
				   ��� ��θ� �˾Ƴ��ϴ�.


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
				   ���� �ڵ�� ������ ������ �����մϴ�.
				   i -> j ��

				   i -> x -> j �� ����ȭ�Ǹ�
				   �� j-x �� �󵵼��� 1 �����ϴ�.

				   i-> x2 -> x - > j �� �ѹ� �� ����ȭ�Ǹ�
				   �� x-x2 �� �󵵼��� 1 �����ϴ�.

				   ���� �Ϻ��� ����ȭ�ɱ��� �ݺ��մϴ�.

				*/
			}

		}
	}

	/*
	   �� A-B �� B-A �� �����Ƿ� , count[i][j] �� count[j][i]�� �ϳ��� ��Ĩ�ϴ�.
	*/
	for (int i = 0, start = 0; i < 9; i++, start++) {
		for (int j = start; j < 9; j++) {
			if (count[i][j] + count[j][i])
				count[i][j] += count[j][i];
		}

	}

	/*
	   ���������� �̿��Ͽ� count �迭 ���� ������ �κи��� �����մϴ�.
	   �� ���� �ٲܶ�, name �� �ٲ��ݴϴ�.
	   ������ ������, count �迭���� ���� ������� ����Ͽ����� ���������̾�� �մϴ�.


	   - �ڼ��� ����-

	   count �迭�� ������ ���� �����Դϴ�.

	   [ A-A �� �󵵼� , A-B�� �󵵼�, A-C�� �󵵼� , ... .. ]
	   [ B-A �� �󵵼� , B-B�� �󵵼� , B-C�� �󵵼� , ... ...]
	   ...
	   [ I-A �� �󵵼�, .... ... ]

	   name �迭�� ������ ���� ���·� �ʱ�ȭ�Ǿ� �ֽ��ϴ�.

	   ["A-A" , "A-B" , "A-C", "A-D " , ... ... ]
	   ["B-A", "B-B", "B-C",             ... ...]
	   ...
	   ["I-A", "I-B", ... ]

	   ���� �� A-B �� �󵵼��� �� A-C�� �󵵼� ���� ū �����
	   �������� ���� (����) �� ���� �� ���� ��ü�մϴ�.


	   count

	   [ A-A �� �󵵼� , A-C�� �󵵼�, A-B�� �󵵼� , ... .. ]
						 |�ٲ� �κ�|
	   [ B-A �� �󵵼� , B-B�� �󵵼� , B-C�� �󵵼� , ... ...]
	   ...
	   [ I-A �� �󵵼�, .... ... ]

	   name
	   ["A-A" , "A-C" ,"A-B" , "A-D " , ... ... ]
			  |�ٲ� �κ�|
	   ["B-A", "B-B", "B-C",             ... ...]
	   ...
	   ["I-A", "I-B", ... ]

	   45������ ���� �Ϻ��� ���������� �˴ϴ�.

	*/

	//������ A-B �� B-A ó�� ��ġ�� �κ��� ���ĵξ����Ƿ� , ������ �����ϰ� �����մϴ�.
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
	���� ������ָ� �˴ϴ�.
	count �迭�� name �迭�� ������� ����ϸ�, ���ĵ� ������ ���Դϴ�.

	*/

	printf("\n\n---- �� ���δ� ����� �����������? (��������)----\n\n");
	for (int i = 0, start = 0; i < 9; i++, start++) {
		for (int j = start; j < 9; j++) {
			if (count[i][j])
				printf("%s : %d ��\n", name[i][j], count[i][j]);
		}
	}
	return 0;


}