#ifndef __LIST_H
#define __LIST_H

#include <pthread.h>

typedef struct _list_item {
  void *value;
  struct _list_item *prev;
  struct _list_item *next;
} list_item;

typedef struct {
  int count;
  list_item *head;
  list_item *tail;
  pthread_mutex_t mutex;
} list;

list *list_create();
void list_free(list *l);

list_item *list_add_element(list *l, void *ptr);
int list_remove_element(list *l, void *ptr);
void list_each_element(list *l, int (*func)(list_item *));

#endif