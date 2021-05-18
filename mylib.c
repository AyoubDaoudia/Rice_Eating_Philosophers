#include "mylib.h"

// Stack Functions

stack* new_stack(int data){
    stack* P=(stack*)malloc(sizeof(stack));
    P->data=data;
    P->next=NULL;
    return P;
}

bool is_empty(stack* head){
    if(head==NULL){
        return true;
    }
    return false;
}

void push(stack** head, int data){
    stack* P=new_stack(data);
    P->next=*head;
    *head=P;
    return;
}

void pop(stack** head){
    if(is_empty(*head)){
        return ;
    }
    stack* L=*head;
    *head=(*head)->next;
    free(L);
    return ;
}

// Singly Linked List Functions

s_linked* create_node(int data){
    s_linked* L=(s_linked*)malloc(sizeof(s_linked));
    L->data=data;
    L->next=NULL;
    return L;
}

void add_node(s_linked** head, int data){
    s_linked* L=create_node(data);
    if(head==NULL){
        head=&L;
        return;
    }
    s_linked* temp= *head;
    while(temp->next!=NULL){
        temp=temp->next;
    }
    temp->next=L;
    return;
}

s_linked* array_to_list(int* array,int len){
    if(array == NULL){
        return NULL;
    }
    s_linked* L=create_node(array[0]);
    for(int i=1 ; i < len ; i++){
        add_node(&L,array[i]);
    }
    return L;
}

void print_list(s_linked* head){
    s_linked* temp=head;
    printf("[ ");
    while(temp!=NULL){
        printf("%d ",temp->data);
    }
    printf("]/n");
    return;
}

void remove_node(s_linked** head,int address){
    s_linked* temp_1=*head;
    s_linked* temp=*head;
    if(head == NULL){
        return;
    }
    if(address == 0){
        *head = (*head)->next;
        free(temp);
        return;
    }
    int i = 0;
    while(temp->next != NULL && i < address){
        temp_1=temp;
        temp=temp->next;
        i++;
    }
    if(i == address){
        temp_1->next=temp->next;
        free(temp);
    }
    return;
}

// Queue Functions 

queue* new_queue(int data)
{
    queue * F = (queue*)malloc(sizeof(queue));
    F->data = data;
    F->next = NULL;
    return F;
};

bool q_is_empty(queue ** F)
{
    if(F==NULL)
        return true;
    false;
};

void q_pop(queue** head)
{
    if(q_is_empty(head))
        return ;
    queue* L=*head;
    *head=(*head)->next;
    free(L);
    return ;
};

void q_push(queue** head,int data)
{
    queue * C =new_queue(data);
    if(head==NULL)
        *head=C;
    queue* temp = *head;
    while(temp->next!=NULL)
    {
        temp=temp->next;
    }
    temp->next=C;
    return;
};

// Double Linked List Functions

d_linked* create_list(int data)
{
    d_linked * L =(d_linked*)malloc(sizeof(d_linked));
    L->data=data;
    L->start=L;
    L->end=NULL;
    return L;
};

void show_first(d_linked * L)
{
   if(L==NULL){
        printf("[ ]\n");
        return;
    }
    printf("[ %d ]",L->start->data);
    return;
};

void show_last(d_linked * L)
{
    if(L==NULL){
        printf("[ ]\n");
        return;
    }
    printf("[ %d ]",L->end->data);
    return;
};