#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SWAP(x,y,t) ((t)=(x), (x)=(y), (y)=(t))
#define MAX 5
#define BUCKETS 10
#define DIGITS 5

typedef struct QueueNode {
	int item;
	struct QueueNode *link;
}QueueNode;

typedef struct {
	QueueNode *front, *rear;
}QueueType;

int sorted[MAX];

void selection_sort(int list[], int n)
{
	int i, j, least, temp;
	for (i = 0;i < n - 1;i++)
	{
		least = i;
		for (j = i + 1;j < n;j++)
			if (list[j] < list[least]) least = j;
		SWAP(list[i], list[least], temp);
	}
}

void insertion_sort(int list[], int n)
{
	int i, j, key;
	for (i = 1;i < n;i++)
	{
		key = list[i];
		for (j = i - 1;j >= 0 && list[j] > key;j--)
			list[j + 1] = list[j];
		list[j + 1] = key;
	}
}

void bubble_sort(int list[], int n)
{
	int i, j, temp;
	for (i = n - 1;i > 0;i--) {
		for (j = 0;j < i;j++)
			if (list[j] > list[j + 1])
				SWAP(list[j], list[j + 1], temp);
	}
}

inc_insertion_sort(int list[], int first, int last, int gap)
{
	int i, j, key;
	for (i = first + gap;i <= last;i = i + gap)
	{
		key = list[i];
		for (j = i - gap;j >= first && key < list[j];j = j - gap)
			list[j + gap] = list[j];
		list[j + gap] = key;
	}
}

void shell_sort(int list[], int n)
{
	int i, gap;
	for (gap = n / 2;gap > 0;gap = gap / 2) {
		if ((gap % 2) == 0) gap++;
		for (i = 0;i < gap;i++)
			inc_insertion_sort(list, i, n - 1, gap);
	}
}

void merge(int list[], int left, int mid, int right)
{
	int i, j, k, l;
	i = left; j = mid + 1; k = left;

	while (i <= mid && j <= right) {
		if (list[i] <= list[j])
			sorted[k++] = list[i++];
		else
			sorted[k++] = list[j++];
	}

	if (i > mid)
		for (l = j;l <= right;l++)
			sorted[k++] = list[l];
	else
		for (l = i;l <= mid;l++)
			sorted[k++] = list[l];

	for (l = left;l <= right;l++)
		list[l] = sorted[l];
}

void merge_sort(int list[], int left, int right)
{
	int mid;
	if (left < right) {
		mid = (left + right) / 2;
		merge_sort(list, left, mid);
		merge_sort(list, mid + 1, right);
		merge(list, left, mid, right);
	}
}

int partition(int list[], int left, int right)
{
	int pivot, temp;
	int low, high;
	low = left;
	high = right + 1;
	pivot = list[left];
	do {
		do
			low++;
		while (low <= right && list[low] < pivot);
		do
			high--;
		while (high >= left && list[high] > pivot);
		if (low < high) SWAP(list[low], list[high], temp);
	} while (low < high);

	SWAP(list[left], list[high], temp);
	return high;
}

void quick_sort(int list[], int left, int right)
{
	if (left < right)
	{
		int q = partition(list, left, right);
		quick_sort(list, left, q - 1);
		quick_sort(list, q + 1, right);
	}
}

void error(char *message)
{
	fprintf(stderr, "%s\n", message);
	return;
}
void init(QueueType * q)
{
	q->front = q->rear = NULL;
}

int is_empty(QueueType *q)
{
	return (q->front == NULL);
}

void enqueue(QueueType *q, int item)
{
	QueueNode *temp = (QueueNode *)malloc(sizeof(QueueNode));
	if (temp == NULL)
		error("메모리를 할당할 수 없습니다.\n");
	else {
		temp->item = item;
		temp->link = NULL;
		if (is_empty(q)) {
			q->front = temp;
			q->rear = temp;
		}

		else {
			q->rear->link = temp;
			q->rear = temp;
		}
	}
}

int dequeue(QueueType *q)
{
	QueueNode *temp = q->front;
	int item;
	if (is_empty(q))
		error("큐가 비어 있다.\n");
	else {
		item = temp->item;
		q->front = q->front->link;
		if (q->front == NULL)
			q->rear = NULL;
		free(temp);
		return item;
	}
}

void radix_sort(int list[], int n)
{
	int i, b, d, factor = 1;
	QueueType queues[BUCKETS];

	for (b = 0; b < BUCKETS; b++)
		init(&queues[b]);   //큐 초기화

	for (d = 0; d < DIGITS; d++) {
		for (i = 0; i < n; i++)
		{
			int radix = (list[i] / factor) % 10;
			enqueue(&queues[radix], list[i]);
		}
		//데이터들을 자릿수에 따라 큐에 입력

		for (b = i = 0; b < BUCKETS; b++)
			while (!is_empty(&queues[b]))
				list[i++] = dequeue(&queues[b]);   //버켓에서 꺼내어 list로 합친다
		factor *= 10;   //다음 자릿수로 이동
	}
}

int main()
{
	FILE *fp;
	clock_t start, finish;
	int i, j;
	int *list;
	double duration;

	fp = fopen("data81.txt", "w");
	list = (int *)malloc(sizeof(int)*MAX);

	if (fp == NULL)
	{
		printf("FILE OPEN ERROR!\n");
		return 0;
	}

	if (list == NULL)
	{
		printf("Memory allocation error!\n");
		return 0;
	}

	srand((unsigned)time(NULL));

	for (i = 0;i < MAX;i++)
	{
		fprintf(fp, "%d ", rand());
	}
	fclose(fp);

	fp = fopen("data81.txt", "r");

	for (j = 0;j < MAX;j++)
	{
		fscanf(fp, "%d ", &list[j]);
	}

	printf("--Selection Sort... --\n");
	start = clock();
	selection_sort(list, MAX);
	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("Selection Sort Elapse Time : %f\n", duration);

	rewind(fp);
	for (j = 0;j < MAX;j++)
	{
		fscanf(fp, "%d ", &list[j]);
	}

	printf("\n\n--Insertion Sort... --\n");
	start = clock();
	insertion_sort(list, MAX);
	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("Insertion Sort Elapse Time : %f\n", duration);

	rewind(fp);
	for (j = 0;j < MAX;j++)
	{
		fscanf(fp, "%d ", &list[j]);
	}

	printf("\n\n--Bubble Sort... --\n");
	start = clock();
	bubble_sort(list, MAX);
	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("Bubble Sort Elapse Time : %f\n", duration);

	rewind(fp);
	for (j = 0;j < MAX;j++)
	{
		fscanf(fp, "%d ", &list[j]);
	}

	printf("\n\n--Shell Sort... --\n");
	start = clock();
	shell_sort(list, MAX);
	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("Shell Sort Elapse Time : %f\n", duration);

	rewind(fp);
	for (j = 0;j < MAX;j++)
	{
		fscanf(fp, "%d ", &list[j]);
	}

	printf("\n\n--Merge Sort... --\n");
	start = clock();
	merge_sort(list, 0, MAX - 1);
	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("Merge Sort Elapse Time : %f\n", duration);

	rewind(fp);
	for (j = 0;j < MAX;j++)
	{
		fscanf(fp, "%d ", &list[j]);
	}

	printf("\n\n--Quick Sort... --\n");
	start = clock();
	quick_sort(list, 0, MAX - 1);
	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("Quick Sort Elapse Time : %f\n", duration);

	rewind(fp);

	printf("\n\n--Radix Sort... --\n");
	start = clock();
	radix_sort(list, MAX);
	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("Radix Sort Elapse Time : %f\n", duration);

	fclose(fp);
}