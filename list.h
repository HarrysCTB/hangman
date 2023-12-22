#ifndef LIST_H
#define LIST_H

typedef struct Element {
    char name[50];
    char category[50];
    char difficulty[50];
} Element;

typedef struct Node {
    Element element;
    struct Node *next;
} Node;

typedef struct CategoryNode {
    char category[50];
    Node *list;
    struct CategoryNode *next;
} CategoryNode;

Node *addToList(Node *list, Element element);

#endif // LIST_H