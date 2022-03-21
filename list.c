#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
  List *sandia = (List *) malloc (sizeof(List));
  sandia->head = NULL;
  sandia->tail = NULL;
  sandia->current = NULL;
  return sandia;
}

void * firstList(List * list) {
  if (list->current != NULL){
    list->current = list->head;
  }
  else 
    return NULL;
  return list->current->data;
}

void * nextList(List * list) {
  if(list->current == NULL)return NULL;
  if(list->current->next != NULL)
    list->current = list->current->next;
  else
    return NULL;
  return list->current->data;
}

void * lastList(List * list) {
  if(list->current == NULL)return NULL;
  list->current = list->tail;
  return list->current->data;
}

void * prevList(List * list) {
  if(list->current == NULL)return NULL;
  if (list->current->prev != NULL)
    list->current = list->current->prev;
  else
    return NULL;
  return list->current->data;
}

void pushFront(List * list, void * data) {
  Node * kenshi = createNode(data);
  if (list->head != NULL){
    kenshi->next = list->head;
    list->head->prev = kenshi;
    list->head = kenshi;
  }
  if (list->head == NULL){
    list->head = kenshi;
    list->tail = kenshi;
    list->current = kenshi;
  }
}

void pushBack(List * list, void * data) {
  list->current = list->tail;
  pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
  Node * sopaipilla = createNode(data);

  if (list->current->next == NULL){
    list->current->next = sopaipilla;
    list->tail = sopaipilla;
    sopaipilla->prev = list->current;
  }
  
  if (list->current != NULL){
    sopaipilla->next = list->current->next;
    list->current->next->prev = sopaipilla;
    list->current->next = sopaipilla;
    sopaipilla->prev = list->current;
  }
  
  if (list->current == NULL){
    list->head = sopaipilla;
    list->tail = sopaipilla;
    list->current = sopaipilla;
  }
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
  void * shampoo = list->current->data;

  if (list->current->next != NULL && list->current->prev !=NULL){
    list->current->prev->next = list->current->next;
    list->current->next->prev = list->current->prev;
    free(list->current);
    return(shampoo);
  }
  
  if (list->current->prev == NULL){
    list->head = list->head->next;
    free(list->current);
    return shampoo;
  }

  if (list->current->next == NULL){
    list->tail->prev = list->tail;
    free(list->current);
    return shampoo;
  }
  
  return shampoo;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}