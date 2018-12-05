/*
	작성일 : 18.12.04
	프로그램명 : AVL 트리
	작성자 : 김혜린
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 데이터를 저장하기 위한 구조체 */
typedef struct AvlNode {
	char eng[20];
	char kor[20];
	struct AvlNode *left_child, *right_child;
}AvlNode;

// 트리의 루트 노드 전역변수로 선언
AvlNode *root;

/* LL 회전 함수
* @param *parent  [균형 인수가 깨진 가까운 조상 노드]
*/
AvlNode* rotate_LL(AvlNode *parent)
{
	AvlNode *child = parent->left_child;
	parent->left_child = child->right_child;
	child->right_child = parent;
	return child;
}

/* RR 회전 함수
* @param *parent  [균형 인수가 깨진 가까운 조상 노드]
*/
AvlNode* rotate_RR(AvlNode *parent)
{
	AvlNode *child = parent->right_child;
	parent->right_child = child->left_child;
	child->left_child = parent;
	return child;
}

/* RL 회전 함수
* @param *parent  [균형 인수가 깨진 가까운 조상 노드]
*/
AvlNode* rotate_RL(AvlNode *parent)
{
	AvlNode *child = parent->right_child;
	parent->right_child = rotate_LL(child);
	return rotate_RR(parent);
}

/* LR 회전 함수
* @param *parent  [균형 인수가 깨진 가까운 조상 노드]
*/
AvlNode* rotate_LR(AvlNode *parent)
{
	AvlNode *child = parent->left_child;
	parent->left_child = rotate_RR(child);
	return rotate_LL(parent);
}

/* 트리의 높이를 반환하는 함수
* @param *node  [높이를 알고자 하는 노드]
*/
int get_height(AvlNode *node)
{
	int height = 0;
	if (node != NULL)
	{
		height = 1 + max(get_height(node->left_child),
			get_height(node->right_child));
		// 왼쪽과 오른쪽의 서브트리 높이를 비교 후 
		// 큰 값에 1증가하여 높이 저장
	}
	return height;
}

/* 노드의 균형 인수를 반환하는 함수
* @param *node  [균형 인수를 알고자 하는 노드]
*/
int get_height_diff(AvlNode *node)
{
	if (node == NULL) return 0;
	return get_height(node->left_child) - get_height(node->right_child);
	// 균형 인수 반환
}

/* 트리를 균형으로 만드는 함수
* @param **node	[해당 노드의 값을 변경하지 않고 참고하기 위한 이중 포인터]
*/
AvlNode * rebalance(AvlNode **node)
{
	int height_diff = get_height_diff(*node);
	// 노드의 높이 저장

	/* 1보다 큰 경우 */
	if (height_diff > 1)
	{
		if (get_height_diff((*node)->left_child) > 0)
			*node = rotate_LL(*node);

		else
			*node = rotate_LR(*node);
	}

	/* -1 보다 작은 경우 */
	else if (height_diff < -1)
	{
		if (get_height_diff((*node)->right_child) < 0)
			*node = rotate_RR(*node);
		else
			*node = rotate_RL(*node);
	}
	return *node;
}

/* 트리에 데이터를 삽입하는 함수
* @param **root	[트리의 루트 노드]
* @param eng	[영어로 저장된 데이터 문자열]
* @param kor	[한글로 저장된 데이터 문자열]
*/
AvlNode* avl_add(AvlNode **root, char eng[], char kor[])
{
	// 트리가 비어있는 경우
	if (*root == NULL)
	{
		/* 루트 노드를 동적할당 */
		*root = (AvlNode *)malloc(sizeof(AvlNode));
		if (*root == NULL)
		{
			fprintf(stderr, "메모리 할당 에러\n");
			exit(1);
		}
		// 루트 노드에 새로운 데이터 삽입
		strcpy((*root)->eng, eng);
		strcpy((*root)->kor, kor);
		(*root)->left_child = (*root)->right_child = NULL;
	}

	/* 루트 노드의 데이터가 새로운 데이터보다 큰 경우 */
	else if (strcmp((*root)->eng, eng) > 0)
	{
		(*root)->left_child = avl_add(&((*root)->left_child), eng, kor);
		// 루트 노드의 왼쪽에 데이터 삽입
		*root = rebalance(root);
		// 트리의 균형을 맞추기 위한 함수 호출
	}

	/* 루트 노드의 데이터가 새로운 데이터보다 작은 경우 */
	else if (strcmp((*root)->eng, eng) < 0)
	{
		(*root)->right_child = avl_add(&((*root)->right_child), eng, kor);
		// 루트 노드의 오른쪽에 새로운 데이터 삽입
		*root = rebalance(root);
		// 트리의 균형을 위한 함수 호출
	}

	/* 새로운 데이터가 이미 삽입된 데이터인 경우 */
	else
	{
		fprintf(stderr, "중복된 키 에러\n");
		exit(1);
	}
	return *root;
	// 현재 루트 반환
}

/* 원하는 노드를 찾는 함수
* @param *node	[트리에 저장된 노드]
* @param eng	[찾고자하는 데이터 문자열]
*/
AvlNode *avl_search(AvlNode *node, char eng[])
{
	/* 트리가 비어있는 경우 */
	if (node == NULL) return NULL;
	/* 찾고자하는 데이터와 현재 노드의 데이터가 같다면 */
	if (strcmp(eng, node->eng) == 0)
		return node;
		// 해당 노드 반환

	/* 현재 노드의 데이터가 더 큰 경우 */
	else if (strcmp(node->eng, eng) > 0)
		return avl_search(node->left_child, eng);
		// 노드의 왼쪽 서브 트리로 이동해 탐색

	/* 현재 노드의 데이터가 더 작은 경우 */
	else
		return avl_search(node->right_child, eng);
		// 노드의 오른쪽 서브 트리로 이동해 탐색
}

/* 트리를 출력하는 함수
* @param *root	[트리의 루트 노드]
* @param size	[공백을 출력하기 위한 값]
*/
void print_avl(AvlNode *node, int size)
{
	/* 루트 노드가 비어있다면 함수 종료 */
	if (node == NULL)	return;
	size += size;
	// size값 증가
	print_avl(node->right_child, size);
	// 오른쪽 서브 트리로 이동하여 데이터 출력 함수 호출

	/* 현재 노드가 루트 노드이면 루트 노드임을 출력 */
	if (strcmp(root->eng, node->eng) == 0)
		printf("Root ->");
	
	for (int i = 0; i < size; i++)
		printf(" ");
		// size크기만큼 공백 출력
	
	printf("%s - %s|\n", node->eng, node->kor);
	// 해당 노드의 데이터 출력
	print_avl(node->left_child, size);
	// 왼쪽 서브 트리로 이동하여 데이터 출력 함수 호출
}

void main()
{
	FILE *fp;
	AvlNode *node;
	char eng[20], kor[20];
	char c;
	int count = 0;

	fp = fopen("data03.txt", "r");
	if (fp == NULL)
	{
		printf("파일이 비어있다.\n");
		return;
	}

	// 데이터를 읽어오기 위해 파일 오픈
	while (!feof(fp))
	{
		// 조건 문자 읽어오기
		fscanf(fp, " %c", &c);
		
		// i라면
		if (c == 'i')
		{
			fscanf(fp, " %s %s", eng, kor);
			// 데이터를 읽어와 변수에 저장
			count++;
			// 데이터의 개수 저장
			avl_add(&root, eng, kor);
			// 트리에 삽입
		}

		// s라면
		else
		{
			fscanf(fp, " %s", eng);
			// 탐색하고자 하는 데이터 읽어오기
			printf("< %s의 의미 탐색 >\n", eng);
			node = avl_search(root, eng);
			// 탐색 함수 호출
			printf("%s - %s\n\n", node->eng, node->kor);
			// 탐색한 결과 값 출력
		}
	}
	printf("< AVL 트리 출력 >\n");
	print_avl(root, count);
	// 노드가 삽입된 트리 출력

	fclose(fp);
	return;
}