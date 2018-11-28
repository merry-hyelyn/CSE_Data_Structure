/*
작성일 : 18.11.27
프로그램명 : 이차조사법을 이용한 HashTable
작성자 : 김혜린
*/

#include <stdio.h>
#include <string.h>

#define KEY_SIZE 7
#define TABLE_SIZE 7
#define empty(e) (strlen(e.eng)==0)
#define equal(e1,e2) (strcmp(e1.eng,e2.eng)==0)

//데이터를 저장하기 위한 구조체
typedef struct {
	int eng[KEY_SIZE];
	int kor[KEY_SIZE];
}element;

int size;
element hash_table[TABLE_SIZE];
//해시 테이블

//테이블 초기화 하는 함수
void init_table(element ht[])
{
	int i;
	for (i = 0; i < TABLE_SIZE; i++)
	{
		ht[i].eng[0] = NULL;
	}
}

//문자열을 정수로 전환하여 합계를 데이터의 값으로 한다
//경계 폴딩을 이용하여 데이터를 정수화 한다
int transform(char key[])
{
	int number = 0;
	//현재 데이터를 정수화한 값을 저장하는 변수
	int a, b, c;
	for (int i = 0; i < strlen(key); i++)
	{
		//문자열 인덱스가 홀수인 경우에 경계 폴딩 방식 적용
		if ((i % 2) != 0)	
		{
			//해당 값을 역수로 만들어 저장
			if ((int)key[i] >= 100)	//값이 100이상인 경우
			{
				a = (int)key[i] % 10;
				b = ((int)key[i] / 10) % 10;
				c = ((int)key[i] / 10) / 10;
				number += (a * 100) + (b * 10) + (c * 1);
			}

			else	//값이 100미만인 경우
			{
				a = (int)key[i] / 10;
				b = (int)key[i] % 10;
				number += (b * 10) + (a * 1);
			}
		}

		else
			number += (int)key[i];
	}
	return number;
}

//문자열 데이터를 정수형으로 전환하는 함수
int hash_function(char *key)
{
	return transform(key) % TABLE_SIZE;
}

//해시 테이블에 데이터를 삽입하는 함수
void hash_qp_add(element item, element ht[])
{
	int i, hash_value, inc = 0;
	int pre_i;
	hash_value = i = hash_function(item.eng);
	//해시 테이블의 주소를 가리키는 값 계산

	//현재 주소의 해시 테이블이 비어있을 때까지 반복
	while (!empty(ht[i]))
	{
		//같은 값이 이미 저장되어 있는 경우 저장하지 않고 함수 종료
		if (equal(item, ht[i]))
		{
			fprintf(stderr, "탐색 키가 중복되었습니다.");
			return;
		}

		//i변수를 pre_i변수에 저장
		pre_i = i;
		inc = inc + 1;	//이차 조사법의 식을 위한 변수 1증가
		i = (i + inc*inc) % TABLE_SIZE;
		//이차 조사법의 식을 이용한 테이블 주소 갱신

		printf("data = %s 저장도중 HashTable : %d 에서 충돌 감지 - index = %d로 증가하였습니다.\n", item.eng, pre_i, i);

		//테이블의 크기와 데이터를 넣은 개수가 같다면
		if (size == TABLE_SIZE)
		{
			//테이블이 꽉찼음을 출력
			fprintf(stderr, "테이블이 가득찼습니다.\n");
			return;
		}
	}
	ht[i] = item;	//현재 해시 주소에 데이터 저장
	size++;	//데이터 개수 증가
}

//해시 테이블 출력하는 함수
void hash_qp_print(element ht[])
{
	int i;
	for (i = 0; i < 10; i++)
	{
		printf("hashtable[%d] -", i);
		if (!empty(ht[i]))
			printf(" %s > %s", ht[i].eng, ht[i].kor);

		printf("\n");
	}
}

int main()
{
	element temp;
	FILE *fp;
	char eng[10], kor[20];
	int count = 0;

	fp = fopen("data02.txt", "r");

	init_table(hash_table);

	printf("< HashTable Size = [%d] >\n\n", TABLE_SIZE);
	printf("< Date Insert Finish >\n");

	//파일을 읽어와 구조체 변수를 이용하여 데이터를 저장
	while (!feof(fp))
	{
		fscanf(fp, "%s %s", temp.eng, temp.kor);
		hash_qp_add(temp, hash_table);
		//데이터를 해시 테이블에 저장
	}

	printf("\n< Table >\n");
	hash_qp_print(hash_table);	//저장이 완료된 해시 테이블 출력
	printf("< Finish >\n");
	return 0;
}