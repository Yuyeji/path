#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
//#define _CRT_SECURE_NO_WARNINGS
void DisplayGraph(int **graph); //�׷��� ���
void Floyd(int **D, int **path); //�÷��̵� �˰���
void PrintPath(int **path, int start, int end); //��� ���

int v; //vertex�� ��
int n = 0; //�迭 ��½� �ݺ����� ���� ����

int main(void) {
	FILE* f; // ����
	int startTime = 0, endTime = 0;
	float gap;
	int start = 0, end = 0; //���� ����, ���� ����
	int **D, **path; //����� ���� �迭, ��������� ���� �迭
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
	D = (int**)malloc(sizeof(int*)*(v));
	path = (int**)malloc(sizeof(int*)*(v));
	for (int i = 0; i < v; i++) {
		D[i] = (int*)malloc(sizeof(int) * (v));
		path[i] = (int*)malloc(sizeof(int) * (v));
	}

	/*�迭 �ʱ�ȭ*/
	for (int i = 0; i < v; i++) {
		for (int j = 0; j < v; j++) {
			D[i][j] = 999;
			path[i][j] = -1;
			if (i == j) {
				D[i][j] = 0;
			}
		}
	}

	/*���� �о�ͼ� ver1, ver2, cost������ �̿��� weight�迭 ����*/
	for (int i = 1; !feof(f); i++) {
		fscanf(f, "%d %d %d", &ver1, &ver2, &cost);
		D[ver1][ver2] = cost;
	}

	/*����ڷ� ���� ����,���� ������ �Է¹���*/
	printf("���� ������ ���� ������ �Է����ּ���.");
	scanf("%d %d", &start, &end);

	startTime = clock();

	DisplayGraph(D); //�ʱ��� D�迭 ���
	
	Floyd(D, path); //�÷��̵� �˰��� ����

	 /*path�� matrix���*/
	printf("path�� maxrix\n");
	DisplayGraph(path);

	/*������������� ������������ ��� Ȯ��*/
	printf("\n****%d���� %d�������Ȯ��****\n%d ->", start, end, start);
	PrintPath(path, start, end);
	printf("%d\n\n", end);

	endTime = clock();
	gap = (float)(endTime - startTime) / (CLOCKS_PER_SEC);

	printf("���� �ð� : %f\n", gap);

	/*�޸� free*/
	for (int i = 0; i < v; i++) {
		free(D[i]);
		free(path[i]);
	}
	free(D);
	free(path);

	fclose(f); //���� �ݱ�

	system("pause"); // �׽�Ʈ ���� ����.
}

/*�迭 ��� �Լ�*/
void DisplayGraph(int **graph) {
	printf("****%d��° maxrix Ȯ��****\n", n);
	n++;
	//�迭 ũ�⸸ŭ �ݺ����� ���� ���
	for (int i = 0; i < v; i++) {
		for (int j = 0; j < v; j++) {
			printf("%d\t", graph[i][j]);
		}
	}
	printf("\n");
}

/*�÷��̵� �˰���*/
void Floyd(int **D, int **path) {
	
	for (int k = 0; k < v; k++) {
		for (int i = 0; i < v; i++) {
			for (int j = 0; j < v; j++) {
				//i���� j�ΰ��� k�� ������ ���� �� ������
				if (D[i][j] > D[i][k] + D[k][j]) {
					D[i][j] = D[i][k] + D[k][j]; //�ּҰ� ������Ʈ
					path[i][j] = k; //path�� k������ ����
					DisplayGraph(D); //������ �� iteration�������� matrix D���
				}
			}
		}
	}

}

/*��� ��� �Լ�*/
void PrintPath(int **path, int start, int end) {

	if (path[start][end] != -1) { //�ٸ� ��带 �����ϴ� ��쿡��
		PrintPath(path, start, path[start][end]); //start���� �����ϴ� ������ ��� �˻�
		printf("%d -> ", path[start][end]); //��� ���
		PrintPath(path, path[start][end], end); //�����ϴ� ��忡�� ���� �������� ��� �˻�
	}
}