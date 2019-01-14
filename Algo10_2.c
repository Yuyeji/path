#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
//#define _CRT_SECURE_NO_WARNINGS
void DisplayGraph(int **graph); //그래프 출력
void Floyd(int **D, int **path); //플로이드 알고리즘
void PrintPath(int **path, int start, int end); //경로 출력

int v; //vertex의 수
int n = 0; //배열 출력시 반복문을 위한 변수

int main(void) {
	FILE* f; // 파일
	int startTime = 0, endTime = 0;
	float gap;
	int start = 0, end = 0; //시작 정점, 도착 정점
	int **D, **path; //비용을 담은 배열, 경로추적을 위한 배열
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
	D = (int**)malloc(sizeof(int*)*(v));
	path = (int**)malloc(sizeof(int*)*(v));
	for (int i = 0; i < v; i++) {
		D[i] = (int*)malloc(sizeof(int) * (v));
		path[i] = (int*)malloc(sizeof(int) * (v));
	}

	/*배열 초기화*/
	for (int i = 0; i < v; i++) {
		for (int j = 0; j < v; j++) {
			D[i][j] = 999;
			path[i][j] = -1;
			if (i == j) {
				D[i][j] = 0;
			}
		}
	}

	/*파일 읽어와서 ver1, ver2, cost값들을 이용해 weight배열 생성*/
	for (int i = 1; !feof(f); i++) {
		fscanf(f, "%d %d %d", &ver1, &ver2, &cost);
		D[ver1][ver2] = cost;
	}

	/*사용자로 부터 시작,도착 정점을 입력받음*/
	printf("시작 정점과 도착 정점을 입력해주세요.");
	scanf("%d %d", &start, &end);

	startTime = clock();

	DisplayGraph(D); //초기의 D배열 출력
	
	Floyd(D, path); //플로이드 알고리즘 실행

	 /*path의 matrix출력*/
	printf("path의 maxrix\n");
	DisplayGraph(path);

	/*출발점에서부터 도착점까지의 경로 확인*/
	printf("\n****%d에서 %d까지경로확인****\n%d ->", start, end, start);
	PrintPath(path, start, end);
	printf("%d\n\n", end);

	endTime = clock();
	gap = (float)(endTime - startTime) / (CLOCKS_PER_SEC);

	printf("측정 시간 : %f\n", gap);

	/*메모리 free*/
	for (int i = 0; i < v; i++) {
		free(D[i]);
		free(path[i]);
	}
	free(D);
	free(path);

	fclose(f); //파일 닫기

	system("pause"); // 테스트 보기 위해.
}

/*배열 출력 함수*/
void DisplayGraph(int **graph) {
	printf("****%d번째 maxrix 확인****\n", n);
	n++;
	//배열 크기만큼 반복문을 통해 출력
	for (int i = 0; i < v; i++) {
		for (int j = 0; j < v; j++) {
			printf("%d\t", graph[i][j]);
		}
	}
	printf("\n");
}

/*플로이드 알고리즘*/
void Floyd(int **D, int **path) {
	
	for (int k = 0; k < v; k++) {
		for (int i = 0; i < v; i++) {
			for (int j = 0; j < v; j++) {
				//i에서 j로갈때 k를 경유한 값이 더 작으면
				if (D[i][j] > D[i][k] + D[k][j]) {
					D[i][j] = D[i][k] + D[k][j]; //최소값 업데이트
					path[i][j] = k; //path에 k정점을 저장
					DisplayGraph(D); //루프의 각 iteration때마다의 matrix D출력
				}
			}
		}
	}

}

/*경로 출력 함수*/
void PrintPath(int **path, int start, int end) {

	if (path[start][end] != -1) { //다른 노드를 경유하는 경우에만
		PrintPath(path, start, path[start][end]); //start에서 경유하는 노드까지 경로 검사
		printf("%d -> ", path[start][end]); //노드 출력
		PrintPath(path, path[start][end], end); //경유하는 노드에서 도착 지점까지 경로 검사
	}
}