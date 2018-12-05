/*
	작성일 : 18.12.04
	프로그램명 : 개선된 순차 탐색
	작성자 : 김혜린
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int *list;
// 데이터를 저장하기 위한 배열

/* 순차 탐색 함수
* @param key	[찾고자 하는 데이터]
* @param low	[배열의 맨 왼쪽 인덱스]
* @param high	[배열의 가장 오른쪽 인덱스]
*/
int seq_search1(int key, int low, int high)
{
	int i;
	for (i = low; i <= high; i++)
		if (list[i] == key) return i;
		// 탐색에 성공하면 키 값의 인덱스 반환
	return -1;	//탐색에 실패하면 -1반환
}

/* 개선된 순차 탐색 함수
* @param key	[찾고자 하는 데이터]
* @param low	[배열의 맨 왼쪽 인덱스]
* @param high	[배열의 가장 오른쪽 인덱스]
*/
int seq_search2(int key, int low, int high)
{
	int i;
	list[high + 1] = key;
	for (i = low; list[i] != key; i++)
		;	//키 값을 찾으면 종료
	if (i == (high + 1)) return -1;
	//탐색 실패
	else return i;
	//탐색 성공
}

int main()
{
	FILE *fp;
	int data, search;
	int count = 0;
	clock_t start, finish;
	double duration;

	fp = fopen("data01.txt", "r");

	if (fp == NULL)
	{
		printf("파일이 비어있다.\n");
		return 0;
	}

	// 데이터의 개수를 읽어오기 위한 반복문
	while (!feof(fp))
	{
		fscanf(fp, " %d", &data);
		count++;
	}

	// 데이터 개수를 이용하여 배열 동적할당
	list = (int *)malloc(sizeof(int)*count);

	// 파일의 앞으로 이동
	rewind(fp);

	// 동적할당받은 배열에 데이터 삽입
	for (int i = 0; i < count; i++)
	{
		fscanf(fp, "%d", &list[i]);
	}

	printf(">>데이터 개수 : %d\n", count);
	printf("찾고자 하는 정수를 입력하세요 : ");

	// 찾고자 하는 데이터를 입력받음
	scanf("%d", &search);

	printf("\n< 탐색 성공 >\n");
	start = clock();	// 함수 시작 시간
	seq_search1(search, 0, count - 1);
	// 순차 탐색 함수 호출
	finish = clock();	// 함수 종료 시간
	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("순차탐색 실행 속도 : %f\n", duration);

	start = clock();	// 함수 시작 시간
	seq_search2(search, 0, count - 1);
	// 개선된 순차 탐색 함수 호출
	finish = clock();	//함수 종료 시간
	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("개선된 순차탐색 실행 속도 : %f\n", duration);

	free(list);
	fclose(fp);
	return 0;
}