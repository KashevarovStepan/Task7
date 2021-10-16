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
    cout << "Task 7 - Очередь" << endl;
    int i=0;
    double a1,a2,//макс и мин время обработки в ОА1
    b1,b2,//макс и мин время обработки в ОА2
    c1,c2,//макс и мин время обработки в ОА3
    time=0,//общее время моделирования
    time1=0,//текущее время в ОА1 с начала моделирования
    time2=0,//текущее время в ОА2 с начала моделирования
    time3=0,//текущее время в ОА3 с начала моделирования
    wait1=0,wait2=0,wait3=0,//время простоя ОА1/2/3 (= общее время моделирования - время работы)
    work1=0,work2=0,work3=0;//суммарное время обработки заявок в ОА1/2/3
    list*ptrx;
    list*ptry;
    list*ptrz;
    list*X=NULL;//очередь 1
    //Вторая и третья очереди в этой программе используются для более удобного подсчета промежуточных результатов(можно обойтись и без них)
    list*Y=NULL;//очередь 2
    list*Z=NULL;//очередь 3
    cout << "Введите мин и макс время обработки в первой очереди(через пробел):" << endl;
    scanf("%lf %lf",&a1,&a2);
    cout << "Введите мин и макс время обработки во второй очереди(через пробел):" << endl;
    scanf("%lf %lf",&b1,&b2);
    cout << "Введите мин и макс время обработки в третьей очереди(через пробел):" << endl;
    scanf("%lf %lf",&c1,&c2);
    cout << "________________________________________________________" << endl;
    for(i=1;i<1001;i++)//формирование заявок
    {
        double t,t1,t2,rnd;//переменные соответствуют полям каждой заявки из queue.h
        t=(double)rand()/RAND_MAX;
        t1=(a2-a1)*t+a1;
        rnd=(double)rand()/RAND_MAX;
        if(rnd<=0.7)//вторая очередь
        {
            t=(double)rand()/RAND_MAX;
            t2=(b2-b1)*t+b1;
        }
        else//третья очередь
        {
            t=(double)rand()/RAND_MAX;
            t2=(c2-c1)*t+c1;
        }
        push(X,i,-1,-1,-1,t1,t2,rnd);//добавление без времени выхода из 1,2/3 очередей и без времени входа во 2/3 очередь
        ptrx=X->l;//сылка на хвост
        ptrx->out1=time1;
        time1+=ptrx->t1;
        ptrx->in=ptrx->out1+ptrx->t1;
        if(rnd<=0.7)//вторая очередь
        {
            if(ptrx->in>=time2)//простой ОА2
            {
                ptrx->out2=ptrx->in;
                time2=ptrx->out2+ptrx->t2;
            }
            else//ожидание обработки заявки в ОА2
            {
                ptrx->out2=time2;
                time2=ptrx->out2+ptrx->t2;
            }
            push(Y,i,ptrx->in,ptrx->out1,ptrx->out2,t1,t2,rnd);//добавление во 2 очередь
        }
        else//третья очередь
        {
            if(ptrx->in>=time3)//простой
            {
                ptrx->out2=ptrx->in;
                time3=ptrx->out2+ptrx->t2;
            }
            else//ожидание
            {
                ptrx->out2=time3;
                time3=ptrx->out2+ptrx->t2;
            }
            push(Z,i,ptrx->in,ptrx->out1,ptrx->out2,t1,t2,rnd);
        }
    }

    if(time2>=time3)time=time2;
    else time=time3;
    ptrx=X;//ссылка на голову
    ptry=Y;
    ptrz=Z;
    int q1=0,q2=0,q3=0;//Количество обработанных в ОА1/2/3 заявок
    double mt=0;//текущее время
    double y=0,z=0;//время в ОА2/3 на момент обработки очередной заявки
    while(q2+q3<=1000)//подсчет промежуточных результатов
    {
        if(y>ptry->out2+ptry->t2||z>ptrz->out2+ptrz->t2)//проверка на достижения головы очереди 2/3 после прохождения хвоста
        {
            if(y>ptry->out2+ptry->t2)//Во 2 очереди больше нет элементов
            {
                z=ptrz->out2+ptrz->t2;
                ptrz=ptrz->r;
                mt=z;
                q3++;
            }
            else//В 3 очереди больше нет элементов
            {
                y=ptry->out2+ptry->t2;
                ptry=ptry->r;
                mt=y;
                q2++;
            }
        }
        else//Если в обеих очередях еще есть элементы
        {
            if(y<=z)//Если ОА2 обработал заявку быстрее ОА3
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
        if((q2+q3)%100==0)//Промежуточные результаты
        {

            int l1=0,l2=0,l3=0,//Длины очередей
            al1=0,al2=0,al3=0,//Количество заявок вышедших из очереди
            id1=-1,id2=-1,id3=-1;//Номер заявки с самым долгим ожиданием(из присутствующих в очереди в данный момент)

            double n1=-1,n2=-1,n3=-1,//Время выхода из очереди заявки с максимальным ожиданием(из присутствующих в очереди в данный момент)
            a1=0,a2=0,a3=0;//Суммарное время ожидания заявок(уже вышедших из очереди)

            q1=0;
            ptrx=X;
            while(ptrx->in<=mt&&ptrx->id>=q1)//Количество обработанных в ОА1 заявок
            {
                ptrx=ptrx->r;
                q1++;
            }
            ptrx=X;
            for(i=1;i<1001;i++)
            {
                if(ptrx->out1>mt)//Заявка в очереди
                {
                    if(ptrx->out1>n1)//Определение заявки с максимальным ожиданием
                    {
                        n1=ptrx->out1;
                        id1=ptrx->id;
                    }
                    l1++;
                }
                else//Заявка уже вышла из очереди
                {
                    a1+=ptrx->out1;
                    al1++;
                }

                if(ptrx->rnd<=0.7&&ptrx->in<mt&&ptrx->out2>mt)//Заявка в очереди
                {
                    if(ptrx->out2-ptrx->in>n2)//Определение заявки с максимальным ожиданием
                    {
                        n2=ptrx->out2-ptrx->in;
                        id2=ptrx->id;
                    }
                    l2++;
                }
                if(ptrx->rnd<=0.7&&ptrx->out2<=mt)//Заявка уже вышла из очереди
                {
                    a2+=ptrx->out2-ptrx->in;
                    al2++;
                }

                if(ptrx->rnd>0.7&&ptrx->in<mt&&ptrx->out2>mt)//Заявка в очереди
                {
                    if(ptrx->out2-ptrx->in>n3)//Определение заявки с максимальным ожиданием
                    {
                        n3=ptrx->out2-ptrx->in;
                        id3=ptrx->id;
                    }
                    l3++;
                }
                if(ptrx->rnd>0.7&&ptrx->out2<=mt)//Заявка уже вышла из очереди
                {
                    a3+=ptrx->out2-ptrx->in;
                    al3++;
                }

                ptrx=ptrx->r;
            }
            //Если для заявки с макс ожиданием выводит "-1", то очередь пуста
            cout << "Время: " << mt << endl;
            cout << "Количество принятых заявок: ОА 1 - " << q1 << "/ ОА 2 - " << q2 << "/ ОА 3 - " << q3 << endl;
            cout << "Длина очереди 1 - " << l1 << "/ Длина очереди 2 - " << l2 << "/ Длина очереди 3 - " << l3 << endl;
            cout << "Номер заявки с макс ожиданием: Очередь 1 - " << id1 << "/ Очередь 2 - " << id2 << "/ Очередь 3 - " << id3 << endl;
            cout << "Время заявки с макс ожиданием: Очередь 1 - " << n1 << "/ Очередь 2 - " << n2 << "/ Очередь 3 - " << n3 << endl;
            cout << "Среднее время ожидания: Очередь 1 - " << (double)a1/al1 << "/ Очередь 2 - " << (double)a2/al2 << "/ Очередь 3 - " << (double)a3/al3 << endl;
            cout << "................................................................." << endl;
        }
    }
    q1=0;
    q2=0;
    q3=0;
    ptrx=X;
    for(i=1;i<1001;i++)//подсчет общих результатов
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
    cout << "Общее время моделирования:" << time << endl;
    cout << "Время простоя 1 - " << wait1 << "/ Время простоя 2 - " << wait2 << "/ Время простоя 3 - " << wait3 << endl;
    cout << "Количество заявок 1 - " << q1 << "/ Количество заявок 2 - " << q2 << "/ Количество заявок 3 - " << q3 << endl;
    cout << "Введите Enter для выхода" << endl;
    scanf("");
    return 0;
}
