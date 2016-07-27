#include <cstdlib>
#include <iostream>
#include "exception.cpp"

using namespace std;

template<typename T>
// ������� ���������� ������
class BListItem
{
public:
    T data;
    BListItem *next;
    BListItem()
    {
        next=NULL;
    }
};

// ��������� ������
template<typename T>
class BList
{
public:
    BListItem<T>* head;    // ������


    BList()
    {
        head=NULL;
    }

    //
    // ������ � ���������
    //

    // �������� ��������
    T get(int pos)
    {
        BListItem<T>* g=getItem(pos);
        if(g==NULL)
            throw IndexOutOfRangeException(pos);
        return g->data;
    }

    // �������� ������� ������ � ������� index ��� NULL, ���� ��� �� ����������
    BListItem<T>* getItem(int index)
    {
        if(index<0) return NULL;
        BListItem<T> *res=head;
        while(index>0)
        {
            res=res->next;
            --index;
            if(!res) return NULL;
        }
        return res;
    }

    // �������� �������, ���������� ���������� ��� ���������
    // (� ���������, ���� child==NULL, ����� ��������� �������)
    BListItem<T>* findParent(BListItem<T>* child)
    {
        if(head==NULL) return NULL;
        if(child==head) return NULL;

        BListItem<T>* parent=this->head;
        while(parent->next!=child)
        {
            parent=parent->next;
            if(!parent) return NULL;
        }
        return parent;
    }

    // ������������� ��������
    int set(int pos, T data)
    {
        BListItem<T>* g=getItem(pos);
        if(g==NULL) throw IndexOutOfRangeException(pos); // �� ���������, ������
        g->data=data;
        return 0; // �����
    }
    // �������� ����� ������
    int getCount()
    {
        BListItem<T>* tmp=head;
        int c=0;
        while(tmp)
        {
            tmp=tmp->next;
            ++c;
        }
        return c;
    }

    // ���������� ������ ������
    BListItem<T>* getHead()
    {
        return head;
    }

    // ���������� ��������� ������� ������
    BListItem<T>* getLast()
    {
        if(head==NULL) return NULL;
        BListItem<T>* tmp=head;
        while(tmp->next)
            tmp=tmp->next;
        return tmp;
    }

    //
    // ���������� �������
    //

    // ��������� ����� ������� � ����� ������
    int add(T data)
    {
        if(head==NULL)
        {
            head=new BListItem<T>();
            head->data=data;
            return 1;
        }
        BListItem<T> *last=head;
        int c=1;
        while(last->next)
        {
            last=last->next;
            ++c;
        }

        last->next=new BListItem<T>();
        last=last->next;
        last->data=data;
        ++c;
        return c;
    }

    // ��������� ������� data � ������� pos
    void insertTo(int pos, T data)
    {
        if(pos==0)
        {
            BListItem<T> *n=new BListItem<T>();
            n->data=data;
            n->next=head;
            head=n;

            return;
        }

        BListItem<T> *li=getItem(pos-1);
        if(li==NULL)
        {
            return;
        }

        BListItem<T> *n=new BListItem<T>();
        n->data=data;
        n->next=li->next;
        li->next=n;
    }

    // ������� ������� � ������� pos
    T removeAt(int pos)
    {
        if(pos<0) throw IndexOutOfRangeException(pos);
        if(head==NULL) throw NullArgumentException();
        BListItem<T> *prev, *toRemove;
        if(pos==0)
        {
            toRemove=head;
            head=head->next;
        }
        else
        {
            prev=getItem(pos-1);
            toRemove=prev->next;
            prev->next=toRemove->next;
        }

        T data=toRemove->data;

        delete toRemove;

        return data;
    }

    // ������� ������ ������� � ��������� �������
    int remove(T data)
    {
        BListItem<T> *prev, *toRemove;
        int pos=1;
        if(data==head->data)
        {
            toRemove=head;
            head=head->next;
            toRemove->next=NULL;
            delete toRemove;
            return 0;
        }
        prev=head;
        while(prev->next->data!=data)
        {
            ++pos;
            prev=prev->next;
            if(!prev) return -1;
        }

        toRemove=prev->next;
        prev->next=toRemove->next;

        delete toRemove;
        return pos;
    }

    // ������� ������, ������� � ��������� ������� startPos, ������� � ��������� �������
    int remove(int startPos, T data)
    {
        if(startPos<0) return -1;
        if(startPos==0) return remove(data);

        BListItem<T> *prev, *toRemove;
        int pos=1;
        prev=getItem(startPos-1);
        while(prev->next->data!=data)
        {
            ++pos;
            prev=prev->next;
            if(!prev) return -1;
        }

        toRemove=prev->next;
        prev->next=toRemove->next;

        delete toRemove;
        return pos+startPos;
    }

    // ������� ��������� �������
    T pop()
    {
        if(head==NULL) throw NullArgumentException();
        if(head->next==NULL) return removeAt(0);

        T data;
        BListItem<T>* tmp=head;

        while(tmp->next->next)
        {
            tmp=tmp->next;
        }

        data=tmp->next->data;
        delete tmp->next;
        tmp->next=NULL;

        return data;
    }

    // ��������� ������
    void clear()
    {
        if(head==NULL) return;
        BListItem<T>* cur=head;
        BListItem<T>* next;
        while(cur)
        {
            next=cur->next;
            delete cur;
            cur=next;
        }
        //�� ������ ������
        head=NULL;
    }

    // ������� ������ �� ����� nlen (���� ��� ������ �������, �� � ����� ������ ����������� ������ ��������)
    int trim(int newSize)
    {
        if(newSize<0) return 0;
        int res=0;
        BListItem<T>* tmp=head;
        for(int i=1; i<newSize; ++i)
        {
            if(tmp->next==NULL)
            {
                tmp->next=new BListItem<T>();
                ++res;
            }
            tmp=tmp->next;
        }
        if(res==0) //������ �� ���������
        {
            BListItem<T>* tmp2=tmp;
            tmp=tmp->next;
            tmp2->next=NULL;
            while(tmp)
            {
                --res;
                tmp2=tmp->next;
                delete tmp;
                tmp=tmp2;
            }
        }
        return res;
    }


    // ��������� ��������� ������� ��� ������� �������� ������, ��������� �� ��� ����� � ��������� �� ����.
    // ������� ������ ���������� �������� �� ���� �����, ���� ���������� �������� �������,
    // � 0 - � ��������� ������
    int forEach(int (*f)(int, T*))
    {
        BListItem<T>* cur=head;
        int r=0, i=0;
        while(cur)
        {
            r=f(i, &(cur->data));
            if(r) break;
            cur=cur->next;
            ++i;
        }
        return r;
    }


    // ������ ����������� ������!
    ~BList()
    {
        clear();
    }
};
