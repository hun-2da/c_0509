#include<stdio.h>
#include <stdlib.h>
// ===== 원형큐 코드 시작 ======
int MAX_QUEUE_SIZE;
typedef char element;
typedef struct { // 큐 타입
	element *data;
	int front, rear;
} QueueType;
// 오류 함수

// 공백 상태 검출 함수
void init_queue(QueueType* q)
{
	MAX_QUEUE_SIZE = 1;
	q->data = malloc(MAX_QUEUE_SIZE * sizeof(char));
	q->front = q->rear = 0;
}
// 공백 상태 검출 함수
int is_empty(QueueType* q)
{
	return (q->front == q->rear);
}
// 포화 상태 검출 함수
int is_full(QueueType* q)
{
	/*if (MAX_QUEUE_SIZE != 0)
		return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
	else return 0;*/
	if (MAX_QUEUE_SIZE == q->rear) {
		return 1;
	}
	else return 0;
}
void enqueue(QueueType* q, char item)
{
	if (is_full(q)) {
		MAX_QUEUE_SIZE++;
		q->data = realloc(q->data, MAX_QUEUE_SIZE * sizeof(char));
		if (q->data == NULL) {
			fprintf(stderr, "NULL.\n");
		}
	}
	q->data[q->rear] = item;
	q->rear++;
}
element delete_rear(QueueType* q)
{
	//int prev = q->rear;
	if (is_empty(q))	return 0;
		//error("큐가 공백상태입니다");
	q->rear--;
	element c = q->data[q->rear];
	return c;
}
element delete_front(QueueType* q)
{
	if (is_empty(q))	return 0;
		//error("큐가 공백상태입니다");
	element c = q->data[q->front];
	q->front++;
	return c;
}
int main(void) {
	int boolean = 1;
	while (boolean) {
		QueueType q;
		init_queue(&q);

		int number = 30;
		char* string = malloc(number * sizeof(char));

		printf("문자열을 입력하시오 : ");
		fgets(string, number, stdin);

		for (int i = 0; ; i++) {
			char c = string[i];
			if (string[i] == '\n') break;

			switch (c) {
			case '\'':	case '\"':	case ' ':	case ',':	case '.':
				continue;
			}
			
			c = tolower(c);
			enqueue(&q,c);
		}
		for (int i = 0; ; i++) {
			if (i == MAX_QUEUE_SIZE / 2 && MAX_QUEUE_SIZE !=1) { printf("회문입니다"); break; }
			char c, c2;
			c = delete_front(&q);
			c2 = delete_rear(&q);
			if (c != c2) {
				printf("회문이 아입니다.");
				break;
			}
		}
		while (1) {
			printf("\n계속 입력하시겠습니까? (YES/NO)");
			char c[4];
			scanf_s("%s", c, 4);
			_strupr_s(c, 4);
			if (strcmp(c, "YES") == 0)
				break;
			else if (strcmp(c, "NO") == 0) { boolean = 0; break; }
		}
		while (getchar() != '\n');
		free(q.data);
		free(string);
	}
}