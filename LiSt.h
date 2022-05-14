#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/** \file LiSt.h
 * Plik nag³ówkowy LiSt.
 * Zawiera definicje typu bazowego listy dwukierunkowej oraz deklaracje funkcji obs³uguj¹cych listê.
 */


struct dll_node{
    char data[100];
    struct dll_node *next,*prev;
};

void append(struct dll_node **node,char data[100]);
void addAtFront(struct dll_node **node,char data[100]);
int delete_node(struct dll_node**node,struct dll_node *to_delete);
void remove_list(struct dll_node ** front);
void print(struct dll_node *node);

#endif // LIST_H_INCLUDED
