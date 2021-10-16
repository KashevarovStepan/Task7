#include <iostream>
#include <stdio.h>
#include "queue.h"
#include <cstdlib>
#include <limits.h>
#include <float.h>
#include <cstddef>
#include <time.h>

using namespace std;

double maxq(double a, double b)
{
    if(a>=b)return a;
    else return b;
}

double minq(double a, double b)
{
    if(a<=b)return a;
    else return b;
}

int main()
{
    srand((unsigned int)time(NULL)/2);
    setlocale(LC_ALL,"Russian");
    cout << "Task 7 - �������" << endl;
    int i=0;
    double a1,a2,//���� � ��� ����� ��������� � ��1
    b1,b2,//���� � ��� ����� ��������� � ��2
    c1,c2,//���� � ��� ����� ��������� � ��3
    time=0,//����� ����� �������������
    time1=0,//������� ����� � ��1 � ������ �������������
    time2=0,//������� ����� � ��2 � ������ �������������
    time3=0,//������� ����� � ��3 � ������ �������������
    wait1=0,wait2=0,wait3=0,//����� ������� ��1/2/3 (= ����� ����� ������������� - ����� ������)
    work1=0,work2=0,work3=0;//��������� ����� ��������� ������ � ��1/2/3
    list*ptrx;
    list*ptry;
    list*ptrz;
    list*X=NULL;//������� 1
    //������ � ������ ������� � ���� ��������� ������������ ��� ����� �������� �������� ������������� �����������(����� �������� � ��� ���)
    list*Y=NULL;//������� 2
    list*Z=NULL;//������� 3
    cout << "������� ��� � ���� ����� ��������� � ������ �������(����� ������):" << endl;
    scanf("%lf %lf",&a1,&a2);
    cout << "������� ��� � ���� ����� ��������� �� ������ �������(����� ������):" << endl;
    scanf("%lf %lf",&b1,&b2);
    cout << "������� ��� � ���� ����� ��������� � ������� �������(����� ������):" << endl;
    scanf("%lf %lf",&c1,&c2);
    cout << "________________________________________________________" << endl;
    for(i=1;i<1001;i++)//������������ ������
    {
        double t,t1,t2,rnd;//���������� ������������� ����� ������ ������ �� queue.h
        t=(double)rand()/RAND_MAX;
        t1=(a2-a1)*t+a1;
        rnd=(double)rand()/RAND_MAX;
        if(rnd<=0.7)//������ �������
        {
            t=(double)rand()/RAND_MAX;
            t2=(b2-b1)*t+b1;
        }
        else//������ �������
        {
            t=(double)rand()/RAND_MAX;
            t2=(c2-c1)*t+c1;
        }
        push(X,i,-1,-1,-1,t1,t2,rnd);//���������� ��� ������� ������ �� 1,2/3 �������� � ��� ������� ����� �� 2/3 �������
        ptrx=X->l;//����� �� �����
        ptrx->out1=time1;
        time1+=ptrx->t1;
        ptrx->in=ptrx->out1+ptrx->t1;
        if(rnd<=0.7)//������ �������
        {
            if(ptrx->in>=time2)//������� ��2
            {
                ptrx->out2=ptrx->in;
                time2=ptrx->out2+ptrx->t2;
            }
            else//�������� ��������� ������ � ��2
            {
                ptrx->out2=time2;
                time2=ptrx->out2+ptrx->t2;
            }
            push(Y,i,ptrx->in,ptrx->out1,ptrx->out2,t1,t2,rnd);//���������� �� 2 �������
        }
        else//������ �������
        {
            if(ptrx->in>=time3)//�������
            {
                ptrx->out2=ptrx->in;
                time3=ptrx->out2+ptrx->t2;
            }
            else//��������
            {
                ptrx->out2=time3;
                time3=ptrx->out2+ptrx->t2;
            }
            push(Z,i,ptrx->in,ptrx->out1,ptrx->out2,t1,t2,rnd);
        }
    }

    if(time2>=time3)time=time2;
    else time=time3;
    ptrx=X;//������ �� ������
    ptry=Y;
    ptrz=Z;
    int q1=0,q2=0,q3=0;//���������� ������������ � ��1/2/3 ������
    double mt=0;//������� �����
    double y=0,z=0;//����� � ��2/3 �� ������ ��������� ��������� ������
    while(q2+q3<=1000)//������� ������������� �����������
    {
        if(y>ptry->out2+ptry->t2||z>ptrz->out2+ptrz->t2)//�������� �� ���������� ������ ������� 2/3 ����� ����������� ������
        {
            if(y>ptry->out2+ptry->t2)//�� 2 ������� ������ ��� ���������
            {
                z=ptrz->out2+ptrz->t2;
                ptrz=ptrz->r;
                mt=z;
                q3++;
            }
            else//� 3 ������� ������ ��� ���������
            {
                y=ptry->out2+ptry->t2;
                ptry=ptry->r;
                mt=y;
                q2++;
            }
        }
        else//���� � ����� �������� ��� ���� ��������
        {
            if(y<=z)//���� ��2 ��������� ������ ������� ��3
            {
                y=ptry->out2+ptry->t2;
                ptry=ptry->r;
                mt=y;
                q2++;
            }
            else
            {
                z=ptrz->out2+ptrz->t2;
                ptrz=ptrz->r;
                mt=z;
                q3++;
            }
        }
        if((q2+q3)%100==0)//������������� ����������
        {

            int l1=0,l2=0,l3=0,//����� ��������
            al1=0,al2=0,al3=0,//���������� ������ �������� �� �������
            id1=-1,id2=-1,id3=-1;//����� ������ � ����� ������ ���������(�� �������������� � ������� � ������ ������)

            double n1=-1,n2=-1,n3=-1,//����� ������ �� ������� ������ � ������������ ���������(�� �������������� � ������� � ������ ������)
            a1=0,a2=0,a3=0;//��������� ����� �������� ������(��� �������� �� �������)

            q1=0;
            ptrx=X;
            while(ptrx->in<=mt&&ptrx->id>=q1)//���������� ������������ � ��1 ������
            {
                ptrx=ptrx->r;
                q1++;
            }
            ptrx=X;
            for(i=1;i<1001;i++)
            {
                if(ptrx->out1>mt)//������ � �������
                {
                    if(ptrx->out1>n1)//����������� ������ � ������������ ���������
                    {
                        n1=ptrx->out1;
                        id1=ptrx->id;
                    }
                    l1++;
                }
                else//������ ��� ����� �� �������
                {
                    a1+=ptrx->out1;
                    al1++;
                }

                if(ptrx->rnd<=0.7&&ptrx->in<mt&&ptrx->out2>mt)//������ � �������
                {
                    if(ptrx->out2-ptrx->in>n2)//����������� ������ � ������������ ���������
                    {
                        n2=ptrx->out2-ptrx->in;
                        id2=ptrx->id;
                    }
                    l2++;
                }
                if(ptrx->rnd<=0.7&&ptrx->out2<=mt)//������ ��� ����� �� �������
                {
                    a2+=ptrx->out2-ptrx->in;
                    al2++;
                }

                if(ptrx->rnd>0.7&&ptrx->in<mt&&ptrx->out2>mt)//������ � �������
                {
                    if(ptrx->out2-ptrx->in>n3)//����������� ������ � ������������ ���������
                    {
                        n3=ptrx->out2-ptrx->in;
                        id3=ptrx->id;
                    }
                    l3++;
                }
                if(ptrx->rnd>0.7&&ptrx->out2<=mt)//������ ��� ����� �� �������
                {
                    a3+=ptrx->out2-ptrx->in;
                    al3++;
                }

                ptrx=ptrx->r;
            }
            //���� ��� ������ � ���� ��������� ������� "-1", �� ������� �����
            cout << "�����: " << mt << endl;
            cout << "���������� �������� ������: �� 1 - " << q1 << "/ �� 2 - " << q2 << "/ �� 3 - " << q3 << endl;
            cout << "����� ������� 1 - " << l1 << "/ ����� ������� 2 - " << l2 << "/ ����� ������� 3 - " << l3 << endl;
            cout << "����� ������ � ���� ���������: ������� 1 - " << id1 << "/ ������� 2 - " << id2 << "/ ������� 3 - " << id3 << endl;
            cout << "����� ������ � ���� ���������: ������� 1 - " << n1 << "/ ������� 2 - " << n2 << "/ ������� 3 - " << n3 << endl;
            cout << "������� ����� ��������: ������� 1 - " << (double)a1/al1 << "/ ������� 2 - " << (double)a2/al2 << "/ ������� 3 - " << (double)a3/al3 << endl;
            cout << "................................................................." << endl;
        }
    }
    q1=0;
    q2=0;
    q3=0;
    ptrx=X;
    for(i=1;i<1001;i++)//������� ����� �����������
    {
        q1++;
        work1+=ptrx->t1;
        if(ptrx->rnd<=0.7)
        {
            work2+=ptrx->t2;
            q2++;
        }
        else
        {
            work3+=ptrx->t2;
            q3++;
        }
        ptrx=ptrx->r;
    }
    wait1=time-work1;
    wait2=time-work2;
    wait3=time-work3;
    cout << "________________________________________________________" << endl;
    cout << "����� ����� �������������:" << time << endl;
    cout << "����� ������� 1 - " << wait1 << "/ ����� ������� 2 - " << wait2 << "/ ����� ������� 3 - " << wait3 << endl;
    cout << "���������� ������ 1 - " << q1 << "/ ���������� ������ 2 - " << q2 << "/ ���������� ������ 3 - " << q3 << endl;
    cout << "������� Enter ��� ������" << endl;
    scanf("");
    return 0;
}
