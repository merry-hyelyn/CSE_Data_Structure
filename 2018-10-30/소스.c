/*
	작성일 : 18.10.31
	프로그램명 : 삽입 정렬을 이용한 연결리스트 데이터 정렬
	작성자 : 김혜린
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int num;
	int kor;
	int eng;
	int math;
	int sum;
	double avg;
}student;

typedef struct ListNode {
	student element;
	struct ListNode *link;
}ListNode;

void error(char *message) {
	fprintf(stderr, "%s", message);
	return;
}

void insert_node(ListNode **phead, ListNode *p, ListNode *new_node)
{
	if (phead == NULL) {
		new_node->link = NULL;
		*phead = new_node;
	}

	else if (p == NULL) {
		new_node->link = *phead;
		*phead = new_node;
	}

	else {
		new_node->link = p->link;
		p->link = new_node;
	}
}

ListNode *create_node(student data, ListNode *link) {
	ListNode *new_node;
	new_node = (ListNode *)malloc(sizeof(ListNode));
	if (new_node == NULL) error("메모리 할당 에러");
	new_node->element = data;
	new_node->link = link;
	return (new_node);
}

ListNode *reverse(ListNode *head) {
	ListNode *p, *q, *r;

	p = head;
	q = NULL;

	while (p != NULL)
	{
		r = q;
		q = p;
		p = p->link;
		q->link = r;
	}
	return q;
}

void display(ListNode *head)
{
	ListNode *p = head;
	printf("|=========================================|\n");
	printf("|  학번  | 국어 | 영어 | 수학 |총 점|평 균|\n");
	while (p != NULL)
	{
		printf("|%d|   %d |   %d |   %d | %d |%.2lf|\n", p->element.num, p->element.kor, p->element.kor, p->element.math, p->element.sum, p->element.avg);
		p = p->link;
	}
	printf("|=========================================|\n");
}

void insertion_list(ListNode **new_phead, ListNode *new_data)
{	
	ListNode *p = *new_phead;

	if (*new_phead == NULL)
	{
		new_data->link = NULL;
		*new_phead = new_data;
	}

	else if ((*new_phead)->element.sum < new_data->element.sum)
	{
		new_data->link = *new_phead;
		*new_phead = new_data;
	}

	else
	{
		while (p != NULL && p->link != NULL)
		{
			if (p->link->element.sum < new_data->element.sum)
			{
				new_data->link = new_phead;
				new_phead = new_data;
				break;
			}
			p = p->link;
		}
		p->link = new_data;
	}
}

void search_list(ListNode **phead)
{
	ListNode *p = *phead;
	ListNode *sorted = NULL;

	while (p != NULL)
	{
		insertion_list(&sorted,create_node(p->element,NULL));
		p = p->link;
	}

	*phead = sorted;
	display(*phead);
}

int main()

{
	FILE *fp;
	student data;
	ListNode *list = NULL;

	fp = fopen("data80.txt", "r");

	if (fp == NULL) {
		printf("파일이 비어있다.");
		return 0;
	}

	while (!feof(fp)) {
		fscanf(fp, "%d %d %d %d", &data.num, &data.kor, &data.eng, &data.math);
		data.sum = data.kor + data.eng + data.math;
		data.avg = (double)data.sum / 3.0;
		insert_node(&list, NULL, create_node(data, NULL));
	}

	list = reverse(list);
	printf("< 정렬 전 >\n");
	display(list);

	printf("\n< 정렬 후 >\n");
	search_list(&list);

	fclose(fp);
	free(list);
	return 0;
}