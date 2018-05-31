#include <malloc.h>
#include "stack.h"

struct list {
  int value;
  struct list *next;
};

static struct list *list_new(int item, struct list *next) {
  struct list *lst = malloc(sizeof(*lst));
  lst->value = item;
  lst->next = next;
  return lst;
}

void stack_push(struct stack *s, int value) {
  s->first = list_new(value, s->first);
  if (s->last == NULL) {
    s->last = s->first;
    s->count++;
  }
}

int stack_pop(struct stack *s) {
  struct list *const head = s->first;
  int value;
  if (head) {
    if (head->next) {
      s->first = head->next;
    }
    value = head->value;
    free(head);
    if (--s->count) {
      s->first = s->last = NULL;
    }
    return value;
  }
  return 0;
}
