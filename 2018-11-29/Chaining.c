/*
	작성일 : 18.11.28
	프로그래명 : 체이닝을 이용한 HashTable
	작성자 : 김혜린
 */

#include <stdio.h>
#include <stdlib.h>

#define KEY_SIZE 7
#define TABLE_SIZE 10
#define equal(e1,e2) (e1.key == e2.key)

//데이터를 저장하기 위한 구조체
typedef struct {
	int key;
}element;

//체이닝을 생성하기 위한 연결리스트 구조체
typedef struct ListNode {
	element item;
	struct ListNode *link;
}ListNode;

ListNode *hash_table[TABLE_SIZE];

//체이닝을 이용하여 해시 테이블을 생성하는 함수
void hash_chain_add(element item, ListNode *ht[])
{
	int hash_value = item.key % KEY_SIZE;
	//해시 테이블의 주소 값
	ListNode *ptr;
	ListNode *node_before = NULL;
	ListNode *node = ht[hash_value];

	//
	for (;node;node_before = node, node = node->link)
	{
		if (equal(node->item, item))
		{
			fprintf(stderr, "이미 탐색 키가 저장되어 있음\n");
			return;
		}
	}

	//새로운 노드 동적할당 후 데이터 삽입
	ptr = (ListNode *)malloc(sizeof(ListNode));
	ptr->item = item;
	ptr->link = NULL;

	if (node_before)	//변수가 null이면 
		node_before->link = ptr;
		//새로 생성한 노드를 연결
	else
		ht[hash_value] = ptr;
		//
}

//생성된 해시 테이블에서 데이터를 찾는 함수
void hash_chain_find(element item, ListNode *ht[])
{
	ListNode *node;
	int hash_value = item.key % KEY_SIZE;
	//해시 테이블의 주소 값
	int count = 0;

	node = ht[hash_value];

	printf("\n");
	for (node = ht[hash_value];node;node = node->link)
	{
		if (equal(node->item, item))
		{
			count++;	
			break;
			//데이터 값을 찾으면 count값 증가와 반복문 탈출
		}
	}

	//값을 찾았다는 의미로 count값이 1이면
	if (count == 1)
	{
		printf("%d 의 검색 결과 - HashTable[%d] - ", item.key, hash_value);
		for (node = ht[hash_value];node;node = node->link)
		{
			printf("(%d) -> ", node->item.key);
			//해시 테이블의 해당 주소에 연결된 값을 모두 출력
			if (equal(node->item, item))
				return;	//현재 출력한 값이 찾고자 하는 값이면 함수 종료
		}
	}
	//함수가 종료되지 않았으면 데이터를 못 찾았으므로 찾지 못했음을 출력
	printf("입력하신 값 %d 은 HashTable에서 검색되지 않았습니다.",item.key);
}

int main()
{
	FILE *fp;
	element e;
	char c;
	int count = 0;

	fp = fopen("data03.txt", "r");

	if (fp == NULL)
	{
		printf("파일이 비어있다.\n");
		return 0;
	}
	printf("< HashTable Size = [%d] >\n\n", TABLE_SIZE);

	while (!feof(fp))
	{
		fscanf(fp, " %c", &c);
		if (c == 'i')	//해시 테이블에 데이터 삽입
		{
			fscanf(fp, " %d", &e.key);
			//데이터를 구조체에 삽입
			hash_chain_add(e, hash_table);
			//해시 테이블을 생성하는 함수 호출
		}

		else	//해시 테이블에서 데이터 찾기
		{
			if (count == 0)
			{
				printf("< Data Insert Finish >\n\n");
				printf("< Find Data Location >");
			}
			count++;
			fscanf(fp, " %d", &e.key);
			hash_chain_find(e, hash_table);
		}
	}
	printf("\n< Finish >\n");
	return 0;
}