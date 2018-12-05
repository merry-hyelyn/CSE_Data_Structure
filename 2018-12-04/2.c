/*
	작성일 : 18.12.04
	프로그램명 : 반복을 이용한 이진 탐색
	작성자 : 김혜린
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 데이터를 저장하기 위한 배열
int *list;

/* 이진 탐색 함수
* @param key	[찾고자 하는 데이터]
* @param low	[배열의 첫 인덱스]
* @param high	[배열의 마지막 인덱스]
*/
int search_binary(int key, int low, int high)
{
	int middle;
	// low, high 인덱스의 중간값

	// 아직 숫자들이 남아 있으면
	while (low <= high)	
	{
		middle = (low + high) / 2;
		if (key == list[middle])
			return middle;
			//탐색 성공 시 해당 인덱스 반환

		// 찾고자 하는 데이터가 중간 값보다 클때
		else if (key > list[middle])
			low = middle + 1;
			// low인덱스를 갱신하여 오른쪽 리스트 탐색
		else
			high = middle - 1;
			// high값을 갱신하여 왼쪽 리스트 탐색
	}
	return -1;	//탐색 실패
}

int main()
{
	FILE *fp;
	int data, search;
	int count = 0;
	int result;
	clock_t start, finish;
	double duration;

	fp = fopen("data01.txt", "r");

	if (fp == NULL)
	{
		printf("파일이 비어있다.\n");
		return 0;
	}

	// 데이터의 개수를 알기 위해 데이터 읽기
	while (!feof(fp))
	{
		fscanf(fp, " %d", &data);
		count++;
	}

	// 배열 동적 할당
	list = (int *)malloc(sizeof(int)*count);
	rewind(fp);		// 파일을 다시 맨 처음으로

	// 동적할당한 배열에 데이터 저장
	for (int i = 0; i < count; i++)
	{
		fscanf(fp, "%d", &list[i]);
	}

	printf("찾고자 하는 정수를 입력하세요 : ");
	scanf("%d", &search);

	printf("\n< 탐색 성공 >\n");

	// 찾고자 하는 데이터를 이진 탐색 함수를 이용하여 탐색
	start = clock();
	result = search_binary(search, 0, count - 1);
	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("%d 번째에 저장되어 있음\n", result);
	// 탐색한 값의 위치를 출력
	printf("이진탐색 실행 속도 : %f\n", duration);

	free(list);
	fclose(fp);
	return 0;
}