#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX 100001   /* biggest text we can handle (including the end character) */

/* ---------- A) static stack + dynamic queue ---------- */

typedef struct {
  char l[MAX];
  int top;
  int size;
} StaticStack;

void ssInit(StaticStack *s, int size) {
  if (size > MAX) {
    printf("Size too big\n");
    exit(1);
  }
  s->top = 0;
  s->size = size;
}

int ssIsEmpty(StaticStack *s) {
  return s->top == 0;
}

int ssIsFull(StaticStack *s) {
  return s->top == s->size;
}

void ssPush(StaticStack *s, char x) {
  if (ssIsFull(s)) {
    printf("Full stack\n");
    exit(1);
  }
  s->l[s->top] = x;
  s->top++;
}

char ssPop(StaticStack *s) {
  if (ssIsEmpty(s)) {
    printf("Empty stack\n");
    exit(1);
  }
  s->top--;
  return s->l[s->top];
}

typedef struct Node {
  char data;
  struct Node *next;
} Node;

typedef struct {
  Node *head;
  Node *tail;
} LinkedQueue;

void lqInit(LinkedQueue *q) {
  q->head = NULL;
  q->tail = NULL;
}

int lqIsEmpty(LinkedQueue *q) {
  return q->head == NULL;
}

void lqEnqueue(LinkedQueue *q, char x) {
  Node *node = (Node *)malloc(sizeof(Node));
  node->data = x;
  node->next = NULL;
  if (lqIsEmpty(q)) {
    q->head = node;
    q->tail = node;
  } else {
    q->tail->next = node;
    q->tail = node;
  }
}

char lqDequeue(LinkedQueue *q) {
  if (lqIsEmpty(q)) {
    printf("Empty queue\n");
    exit(1);
  }
  Node *tmp = q->head;
  char x = tmp->data;
  q->head = q->head->next;
  if (q->head == NULL) {
    q->tail = NULL;
  }
  free(tmp);   /* in C we must free the node ourselves */
  return x;
}

/* keeps only letters and digits, in lower case */
void normalize(char *text, char *result) {
  int j = 0;
  for (int i = 0; text[i] != '\0'; i++) {
    if (isalnum((unsigned char)text[i])) {
      result[j] = (char)tolower((unsigned char)text[i]);
      j++;
    }
  }
  result[j] = '\0';
}

int isPalindrome(char *text) {
  static char cleaned[MAX];
  static StaticStack st;
  LinkedQueue lq;

  normalize(text, cleaned);
  int n = (int)strlen(cleaned);
  ssInit(&st, n);
  lqInit(&lq);

  for (int i = 0; i < n; i++) {
    ssPush(&st, cleaned[i]);
    lqEnqueue(&lq, cleaned[i]);
  }

  while (!ssIsEmpty(&st)) {
    char s = ssPop(&st);
    char q = lqDequeue(&lq);
    if (s != q) {
      while (!lqIsEmpty(&lq)) {   /* free the rest of the queue */
        lqDequeue(&lq);
      }
      return 0;
    }
  }
  return 1;
}

/* ---------- B) dynamic stack + static queue ---------- */

typedef struct {
  Node *top;
} DynamicStack;

void dsInit(DynamicStack *s) {
  s->top = NULL;
}

int dsIsEmpty(DynamicStack *s) {
  return s->top == NULL;
}

void dsPush(DynamicStack *s, char x) {
  Node *node = (Node *)malloc(sizeof(Node));
  node->data = x;
  node->next = s->top;
  s->top = node;
}

char dsPop(DynamicStack *s) {
  if (dsIsEmpty(s)) {
    printf("Empty stack\n");
    exit(1);
  }
  Node *tmp = s->top;
  char x = tmp->data;
  s->top = s->top->next;
  free(tmp);
  return x;
}

typedef struct {
  char l[MAX];
  int head;
  int tail;
  int size;
} StaticQueue;

void sqInit(StaticQueue *q, int size) {
  if (size > MAX) {
    printf("Size too big\n");
    exit(1);
  }
  q->head = 0;
  q->tail = 0;
  q->size = size;
}

int sqIsEmpty(StaticQueue *q) {
  return q->head == q->tail;
}

int sqIsFull(StaticQueue *q) {
  return q->tail == q->size;
}

void sqEnqueue(StaticQueue *q, char x) {
  if (sqIsFull(q)) {
    printf("Full queue\n");
    exit(1);
  }
  q->l[q->tail] = x;
  q->tail++;
}

char sqDequeue(StaticQueue *q) {
  if (sqIsEmpty(q)) {
    printf("Empty queue\n");
    exit(1);
  }
  char x = q->l[q->head];
  q->head++;
  return x;
}

int isPalindromeB(char *text) {
  static char cleaned[MAX];
  static StaticQueue sq;
  DynamicStack ds;

  normalize(text, cleaned);
  int n = (int)strlen(cleaned);
  dsInit(&ds);
  sqInit(&sq, n);

  for (int i = 0; i < n; i++) {
    dsPush(&ds, cleaned[i]);
    sqEnqueue(&sq, cleaned[i]);
  }

  while (!dsIsEmpty(&ds)) {
    char s = dsPop(&ds);
    char q = sqDequeue(&sq);
    if (s != q) {
      while (!dsIsEmpty(&ds)) {   /* free the rest of the stack */
        dsPop(&ds);
      }
      return 0;
    }
  }
  return 1;
}

/* ---------- Extra: char matrix with doubly linked lists ---------- */

typedef struct CharNode {
  char data;
  struct CharNode *next;
  struct CharNode *prev;
} CharNode;

typedef struct {
  CharNode *head;
  CharNode *tail;
  int size;
} CharList;

typedef struct RowNode {
  CharList *row;
  struct RowNode *next;
  struct RowNode *prev;
} RowNode;

typedef struct {
  RowNode *head;
  RowNode *tail;
  int size;
} Matrix;

CharList *clNew() {
  CharList *list = (CharList *)malloc(sizeof(CharList));
  list->head = NULL;
  list->tail = NULL;
  list->size = 0;
  return list;
}

void clAdd(CharList *list, char x) {
  CharNode *node = (CharNode *)malloc(sizeof(CharNode));
  node->data = x;
  node->next = NULL;
  node->prev = NULL;
  if (list->head == NULL) {
    list->head = node;
    list->tail = node;
  } else {
    list->tail->next = node;
    node->prev = list->tail;
    list->tail = node;
  }
  list->size++;
}

char clGet(CharList *list, int i) {
  CharNode *node = list->head;
  for (int k = 0; k < i; k++) {
    node = node->next;
  }
  return node->data;
}

void matrixInit(Matrix *m) {
  m->head = NULL;
  m->tail = NULL;
  m->size = 0;
}

void matrixAdd(Matrix *m, CharList *row) {
  RowNode *node = (RowNode *)malloc(sizeof(RowNode));
  node->row = row;
  node->next = NULL;
  node->prev = NULL;
  if (m->head == NULL) {
    m->head = node;
    m->tail = node;
  } else {
    m->tail->next = node;
    node->prev = m->tail;
    m->tail = node;
  }
  m->size++;
}

void buildMatrix(Matrix *m, char *lines[], int count) {
  matrixInit(m);
  for (int i = 0; i < count; i++) {
    CharList *row = clNew();
    for (int j = 0; lines[i][j] != '\0'; j++) {
      clAdd(row, lines[i][j]);
    }
    matrixAdd(m, row);
  }
}

void freeMatrix(Matrix *m) {
  RowNode *node = m->head;
  while (node != NULL) {
    CharNode *c = node->row->head;
    while (c != NULL) {
      CharNode *tmpC = c;
      c = c->next;
      free(tmpC);
    }
    free(node->row);
    RowNode *tmp = node;
    node = node->next;
    free(tmp);
  }
}

int isRowPalindrome(CharList *row) {
  CharNode *left = row->head;
  CharNode *right = row->tail;
  for (int i = 0; i < row->size / 2; i++) {
    if (left->data != right->data) {
      return 0;
    }
    left = left->next;
    right = right->prev;
  }
  return 1;
}

int areRowsPalindromes(Matrix *m) {
  RowNode *node = m->head;
  while (node != NULL) {
    if (!isRowPalindrome(node->row)) {
      return 0;
    }
    node = node->next;
  }
  return 1;
}

int isColumnPalindrome(Matrix *m, int j) {
  RowNode *top = m->head;
  RowNode *bottom = m->tail;
  for (int i = 0; i < m->size / 2; i++) {
    if (clGet(top->row, j) != clGet(bottom->row, j)) {
      return 0;
    }
    top = top->next;
    bottom = bottom->prev;
  }
  return 1;
}

int areColumnsPalindromes(Matrix *m) {
  int columns = m->head->row->size;
  for (int j = 0; j < columns; j++) {
    if (!isColumnPalindrome(m, j)) {
      return 0;
    }
  }
  return 1;
}

/* ---------- Measuring ---------- */

double measureA(char *text, int *result) {
  clock_t start = clock();
  *result = isPalindrome(text);
  clock_t end = clock();
  return (double)(end - start) * 1000.0 / CLOCKS_PER_SEC;
}

double measureB(char *text, int *result) {
  clock_t start = clock();
  *result = isPalindromeB(text);
  clock_t end = clock();
  return (double)(end - start) * 1000.0 / CLOCKS_PER_SEC;
}

int main() {
  printf("--- A) static stack + dynamic queue ---\n");
  printf("%d\n", isPalindrome("Anna"));                             /* 1 */
  printf("%d\n", isPalindrome("A man, a plan, a canal: Panama"));   /* 1 */
  printf("%d\n", isPalindrome("hello"));                            /* 0 */

  printf("--- B) dynamic stack + static queue ---\n");
  printf("%d\n", isPalindromeB("Anna"));                            /* 1 */
  printf("%d\n", isPalindromeB("A man, a plan, a canal: Panama"));  /* 1 */
  printf("%d\n", isPalindromeB("hello"));                           /* 0 */

  printf("--- Extra: matrix ---\n");
  char *lines1[] = {"aba", "bab", "aba"};
  Matrix m1;
  buildMatrix(&m1, lines1, 3);
  printf("%d\n", areRowsPalindromes(&m1));      /* 1 */
  printf("%d\n", areColumnsPalindromes(&m1));   /* 1 */
  freeMatrix(&m1);

  char *lines2[] = {"abc", "bab", "aba"};
  Matrix m2;
  buildMatrix(&m2, lines2, 3);
  printf("%d\n", areRowsPalindromes(&m2));      /* 0 */
  printf("%d\n", areColumnsPalindromes(&m2));   /* 0 */
  freeMatrix(&m2);

  printf("--- Measuring (n, result A, ms A, result B, ms B, loops) ---\n");
  int sizes[] = {10, 100, 1000, 10000, 100000};
  for (int k = 0; k < 5; k++) {
    int n = sizes[k];
    char *t = (char *)malloc(n + 1);
    for (int i = 0; i < n; i++) {
      t[i] = 'a';
    }
    t[n] = '\0';

    int ra, rb;
    double ma = measureA(t, &ra);
    double mb = measureB(t, &rb);
    int loops = 3 * n;   /* normalize + fill + empty, all n steps */
    printf("%d %d %.3f %d %.3f %d\n", n, ra, ma, rb, mb, loops);
    free(t);
  }
  return 0;
}
