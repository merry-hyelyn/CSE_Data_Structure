/*
	작성일 : 18.11.27
	프로그램명 : 선형조사법을 이용한 HashTable
	작성자 : 김혜린
*/

#include <stdio.h>
#include <string.h>

#define KEY_SIZE 7
#define TABLE_SIZE 10
#define empty(e) (e.key==NULL)
#define equal(e1,e2) (e1.key==e2.key)

//데이터를 저장하는 구조체
typedef struct {
	int key;
}element;

//데이터를 저장하는 해시 테이블
element hash_table[TABLE_SIZE];

//해시 테이블 초기화
void init_table(element ht[])
{
	int i;
	for (i = 0; i < TABLE_SIZE; i++)
	{
		ht[i].key = NULL;
		//초기의 테이블은 모두 비어있으므로 null
	}
}

//해시 테이블에 데이터 삽입
void hash_lp_add(element item, element ht[])
{
	int i, hash_value, pre_i;
	hash_value = i = item.key % KEY_SIZE;
	//데이터를 mod로 나눠 테이블의 주소를 변수에 저장

	//i주소의 해시 테이블이 비어질 때까지 반복
	while (!empty(ht[i]))
	{
		pre_i = i;	//현재 i값을 다른 변수에 저장
		if (equal(item, ht[i]))
		{
			fprintf(stderr, "탐색 키가 중복되었습니다.");
			return;
		}

		i = (i + 1) % TABLE_SIZE;
		//i값 갱신

		printf("data = %d 저장도중 HashTable : %d 에서 충돌 감지 - index = %d로 증가하였습니다.\n", item.key, pre_i, i);
		//테이블의 주소 값이 변경되었음을 출력
	}
	ht[i] = item;
	//현재 주소 i에 데이터 삽입
}

//해시 테이블에서 원하는 데이터 찾기
void hash_lp_search(element item, element ht[])
{
	int i, hash_value;
	hash_value = i = item.key % KEY_SIZE;
	while (!empty(ht[i]))
	{
		//찾고자 하는 데이터와 현재 주소의 테이블에 저장된 값이 같으면
		if (equal(item, ht[i]))
		{
			printf("%d 는 HashTable : %d 에서 검색되었습니다.\n", item.key, i);
			return;
			//데이터와 테이블의 주소 출력
		}
		i = (i + 1) % TABLE_SIZE;
		//새로운 주소값 갱신
	}
	printf("입력하신 값 %d 은 HashTable 에서 검색되지 않았습니다.\n", item.key);
	//반복문에서 함수가 종료되지 않았으면 해당 값이 테이블에 없음을 출력
}

int main()
{
	element temp;
	FILE *fp;
	char c;
	int count = 0;

	fp = fopen("data01.txt", "r");

	init_table(hash_table);

	printf("< HashTable Size = [%d] >\n\n", TABLE_SIZE);
	printf("< Date Insert Finish >\n");
	while (!feof(fp))
	{
		fscanf(fp, " %c", &c);
		if (c == 'i')	//해시 테이블에 데이터 삽입
		{
			fscanf(fp, " %d", &temp.key);
			//데이터를 읽어와 구조체에 저장
			hash_lp_add(temp, hash_table);
		}
		else	//해시 테이블에서 데이터 탐색
		{
			if (count == 0)
				printf("\n< Find Data Location >\n");

			fscanf(fp, " %d", &temp.key);
			hash_lp_search(temp, hash_table);
			count++;
		}
	}

	printf("< Finish >\n");
	return 0;
}