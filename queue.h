#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#include <iostream>
#include <sstream>
#include <math.h>
#include <stdlib.h>

using namespace std;

struct list {
    int id;//�����
    //bool del1,del2;
    double out1,//����� ������ �� 1 �������
    t1,//����� ��������� � ��1
    in,//����� ����� �� 2/3 �������
    t2,//����� ��������� � �� 2/3
    out2,//����� ������ �� 2/3 �������
    rnd;//������������� �� 2/3 �������
    list *l,*r;
};

double pop(list* &ptr){
    list *tmp = ptr;
    list* tmp2=ptr->l;
    ptr = ptr->r;
    ptr->l=tmp2;
    tmp2->r=ptr;
    //ptr->del=true;
    double x = tmp->id;
    delete(tmp);
    return(x);
}

void push(list* &ptr, int id, double in,double out1,double out2,double t1,double t2,double rnd)
{
    list *tmp = new(list);
    tmp->id=id;
    tmp->in=in;
    tmp->out1=out1;
    tmp->out2=out2;
    tmp->t1=t1;
    tmp->t2=t2;
    tmp->rnd=rnd;
    if(ptr==NULL)
    {
        tmp->l=tmp;
        tmp->r=tmp;
        ptr=tmp;
    }
    else
    {
        tmp->l=ptr->l;
        ptr->l->r=tmp;
        tmp->r=ptr;
        ptr->l=tmp;
    }
}

void print(list* &ptr)
{
    cout << ptr->id <<" "<< ptr->out1 <<" "<< ptr->t1 <<" "<< ptr->in <<" "<< ptr->t2 <<" "<< ptr->out2 <<" "<< ptr->rnd << endl;
}

#endif // QUEUE_H_INCLUDED
