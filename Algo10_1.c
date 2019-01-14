#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
//#define _CRT_SECURE_NO_WARNINGS
void slow_APSP(int **W);
void faster_APSP(int **W);
void DisplayGraph(int **graph, int n);
int **ExtendShortestPath(int **L, int **W);

int m = 1; //�迭��½� ����� ���� ����
int v; //vertex�� ��

int main(void) {
	FILE* f; // ����
	int startTime = 0, endTime = 0;
	float gap;
	int **W; //����� ���� �迭
	int ver1, ver2, cost; //vertex1, vertex2, cost 

	f = fopen("graph_sample_directed.txt", "rt"); //���� ����

	if (f == NULL) {
		printf("������ ������ �ʽ��ϴ�.");
		exit(1);
	}

	if (feof(f) == 0) { //������ ù��° ���� �о�´�
		fscanf(f, "%d", &v);
	}

	/*����,���� ���� v��ŭ�� ũ�⸦ ���� 2���� �迭 ����*/
	W = (int**)malloc(sizeof(int*)*(v));
 	for (int i = 0; i < v; i++) {
		W[i] = (int*)malloc(sizeof(int) * (v));
	}

	/*�迭 �ʱ�ȭ*/
	for (int i = 0; i < v; i++) {
		for (int j = 0; j < v; j++) {
			W[i][j] = 999;
			if (i == j) {
				W[i][j] = 0;
			}
		}
	}

	/*���� �о�ͼ� ver1, ver2, cost������ �̿��� W�迭 ����*/
	for (int i = 1; !feof(f); i++) {
		fscanf(f, "%d %d %d", &ver1, &ver2, &cost);
		W[ver1][ver2] = cost;
	}

	startTime = clock();

	printf("<slow_APSP ����>\n");
	slow_APSP(W); //slow_APSP �˰��� ����
	printf("<faster_APSP ����>\n");
	faster_APSP(W); //faster_APSP �˰��� ����

	endTime = clock();
	gap = (float)(endTime - startTime) / (CLOCKS_PER_SEC);

	printf("���� �ð� : %f\n", gap);

	/*�޸� free*/
	for (int i = 0; i < v; i++) {
		free(W[i]);
	}
	free(W);

	fclose(f); //���� �ݱ�

	system("pause"); // �׽�Ʈ ���� ����.
}

/*�迭 ��� �Լ�*/
void DisplayGraph(int **graph, int n) {
	printf("****%d��° maxrix Ȯ��****\n", n);

	//�迭 ũ�⸸ŭ �ݺ����� ���� ���
	for (int i = 0; i < v; i++) {
		for (int j = 0; j < v; j++) {
			printf("%d\t", graph[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void slow_APSP(int **W) {
	int **L = W;

	DisplayGraph(L,0); //�ʱ��� �迭 ���
	for (int i = 1;i < v-1 ;i++) {
		L = ExtendShortestPath(L, W);
		DisplayGraph(L,i); //iteration���� �迭 ���
	}
	printf("\n\n");
}

void faster_APSP(int **W) {
	int **L = W;
	int i = 1;

	DisplayGraph(L, 0); //�ʱ��� �迭 ���
	while (i < v - 1) {
		L = ExtendShortestPath(L, L);
		DisplayGraph(L, m); //iteration���� �迭 ���
		m++;
		i *= 2;
	}
	printf("\n\n");
}

int **ExtendShortestPath(int **L, int **W) {
	int **l;

	/*����,���� ���� v��ŭ�� ũ�⸦ ���� 2���� �迭 ����*/
	l = (int**)malloc(sizeof(int*)*(v));
	for (int i = 0; i < v; i++) {
		l[i] = (int*)malloc(sizeof(int) * (v));
	}

	/*�迭 �ʱ�ȭ, �ִܰ�� ������Ʈ*/
	for (int i = 0; i < v; i++) {
		for (int j = 0; j < v; j++) {
			l[i][j] = 999;
			for (int k = 0; k < v; k++) {
				if (L[i][k] != 999 && W[k][j] != 999) {
					if (l[i][j] > L[i][k] + W[k][j]) {
						l[i][j] = L[i][k] + W[k][j];
					}
				}
			}
		}
	}

	return l;

}