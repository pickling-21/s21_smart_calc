#include "s21_queue.h"

#include "s21_list.h"
#include "s21_operators.h"

// функция для удаления элемента из начала очереди
void dequeue(struct queue* q) {
  if (q->front == NULL) {
    printf("\nQueue Underflow");
  } else {
    struct list* tmp = q->front;
    q->front = q->front->next;
    if (q->front == NULL) q->rear = NULL;
    free(tmp);
  }
}

struct queue* queue_create() {
  struct queue* queue = (struct queue*)malloc(sizeof(struct queue));
  queue->front = queue->rear = NULL;
  return queue;
}
// функция для добавления элемента в конец очереди
void enqueue(struct queue* q, struct lexeme value) {
  struct list* node = node_create(value);
  if (node) {
    if (q->rear == NULL) {
      q->front = q->rear = node;
    } else {
      q->rear->next = node;
      q->rear = node;
    }
  }
}

int queue_is_empty(struct queue* queue) { return queue->front == NULL; }

void list_add_back(struct list** old, struct lexeme value) {
  if (*old != NULL) {
    list_last(*old)->next = node_create(value);
  } else {
    list_add_front(old, value);
  }
}

struct list* node_create(struct lexeme value) {
  struct list* list = malloc(sizeof(struct list));
  if (list) {
    list->value = value;
    list->next = NULL;
  }
  return list;
}

struct lexeme list_pop_front(struct list* l) {}
// функция для удаления элемента из начала очереди
void dequeue(struct queue* q) {
  if (q->front == NULL) {
    printf("\nQueue Underflow");
  } else {
    struct list* tmp = q->front;
    q->front = q->front->next;
    if (q->front == NULL) q->rear = NULL;
    free(tmp);
  }
}
