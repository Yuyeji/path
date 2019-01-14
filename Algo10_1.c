#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
//#define _CRT_SECURE_NO_WARNINGS
void slow_APSP(int **W);
void faster_APSP(int **W);
void DisplayGraph(int **graph, int n);
int **ExtendShortestPath(int **L, int **W);

int m = 1; //배열출력시 사용할 변수 선언
int v; //vertex의 수

int main(void) {
	FILE* f; // 파일
	int startTime = 0, endTime = 0;
	float gap;
	int **W; //비용을 담은 배열
	int ver1, ver2, cost; //vertex1, vertex2, cost 

	f = fopen("graph_sample_directed.txt", "rt"); //파일 열기

	if (f == NULL) {
		printf("파일이 열리지 않습니다.");
		exit(1);
	}

	if (feof(f) == 0) { //파일의 첫번째 값만 읽어온다
		fscanf(f, "%d", &v);
	}

	/*가로,세로 각각 v만큼의 크기를 가진 2차원 배열 생성*/
	W = (int**)malloc(sizeof(int*)*(v));
 	for (int i = 0; i < v; i++) {
		W[i] = (int*)malloc(sizeof(int) * (v));
	}

	/*배열 초기화*/
	for (int i = 0; i < v; i++) {
		for (int j = 0; j < v; j++) {
			W[i][j] = 999;
			if (i == j) {
				W[i][j] = 0;
			}
		}
	}

	/*파일 읽어와서 ver1, ver2, cost값들을 이용해 W배열 생성*/
	for (int i = 1; !feof(f); i++) {
		fscanf(f, "%d %d %d", &ver1, &ver2, &cost);
		W[ver1][ver2] = cost;
	}

	startTime = clock();

	printf("<slow_APSP 실행>\n");
	slow_APSP(W); //slow_APSP 알고리즘 실행
	printf("<faster_APSP 실행>\n");
	faster_APSP(W); //faster_APSP 알고리즘 실행

	endTime = clock();
	gap = (float)(endTime - startTime) / (CLOCKS_PER_SEC);

	printf("측정 시간 : %f\n", gap);

	/*메모리 free*/
	for (int i = 0; i < v; i++) {
		free(W[i]);
	}
	free(W);

	fclose(f); //파일 닫기

	system("pause"); // 테스트 보기 위해.
}

/*배열 출력 함수*/
void DisplayGraph(int **graph, int n) {
	printf("****%d번째 maxrix 확인****\n", n);

	//배열 크기만큼 반복문을 통해 출력
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

	DisplayGraph(L,0); //초기의 배열 출력
	for (int i = 1;i < v-1 ;i++) {
		L = ExtendShortestPath(L, W);
		DisplayGraph(L,i); //iteration마다 배열 출력
	}
	printf("\n\n");
}

void faster_APSP(int **W) {
	int **L = W;
	int i = 1;

	DisplayGraph(L, 0); //초기의 배열 출력
	while (i < v - 1) {
		L = ExtendShortestPath(L, L);
		DisplayGraph(L, m); //iteration마다 배열 출력
		m++;
		i *= 2;
	}
	printf("\n\n");
}

int **ExtendShortestPath(int **L, int **W) {
	int **l;

	/*가로,세로 각각 v만큼의 크기를 가진 2차원 배열 생성*/
	l = (int**)malloc(sizeof(int*)*(v));
	for (int i = 0; i < v; i++) {
		l[i] = (int*)malloc(sizeof(int) * (v));
	}

	/*배열 초기화, 최단경로 업데이트*/
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