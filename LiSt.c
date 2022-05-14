#include "LiSt.h"
/** \file LiSt.c
 * Plik Ÿród³owy LiSt.
 * Zawiera definicje funkcji obs³uguj¹cych listê.
 */

void append(struct dll_node **node,char data[100]){
    if(*node){
    if((*node)->next){
        append(&(*node)->next,data);
    }else{
        (*node)->next=(struct dll_node*)malloc(sizeof(struct dll_node));
        strncpy((*node)->next->data,data,100);
        (*node)->next->next=NULL;
        (*node)->next->prev=*node;

    }
    }else{
        (*node)=(struct dll_node*)malloc(sizeof(struct dll_node));
        strncpy((*node)->data,data,100);
        (*node)->next=NULL;
        (*node)->prev=NULL;

    }
}

void addAtFront(struct dll_node **node,char data[100]){
    if(*node){
        struct dll_node *nNode=(struct dll_node*)malloc(sizeof(struct dll_node));
        strncpy(nNode->data,data,100);
        nNode->next=*node;
        (*node)->prev=nNode;
        (*node)=nNode;

    }else{
        *node=(struct dll_node*)malloc(sizeof(struct dll_node));
        strncpy((*node)->data,data,100);
        (*node)->next=NULL;
        (*node)->prev=NULL;
    }
}

struct dll_node * delete_front(struct dll_node * front) {
    struct dll_node * next = front -> next;
    if (NULL != next)
        next -> prev = NULL;
    free(front);
    return next;
}


void delete_within(struct dll_node * node) {
    node -> next -> prev = node -> prev;
    node -> prev -> next = node -> next;
    free(node);
}

void delete_back(struct dll_node * back) {
    back -> prev -> next = NULL;
    free(back);
}

int delete_node(struct dll_node ** front, struct dll_node*toDelete) {

    if (NULL == front)
        return 0;

    if ((*front) == toDelete){
        (*front)= delete_front((*front));

        return 1;
    }
    struct dll_node * node = toDelete;
    if (NULL != node) {
        if (NULL != node -> next)
            delete_within(node);
        else
            delete_back(node);
    }
    return 1;
}


void print(struct dll_node *node){

    if(node){
        printf("%s",node->data);
        printf(" ");
        print(node->next);
    }
}
void remove_list(struct dll_node ** front) {
    while (NULL != * front) {
        struct dll_node * next = ( * front) -> next;
        free( * front);
        * front = next;
    }
}
