#include <iostream>
#include "blist.cpp"

// ���������� ��������� � �������� ��� ��������� ������ ����� �����
typedef BList<int> Polynom;
// � ��� �������
typedef BListItem<int> Mononom;

using namespace std;

// �������� ������������ ���������� � ���������� � ���������� �������������� ������
Polynom* inputPolynom()
{
    cout<<"Enter maximal power: ";
    int maxp=0;
    cin>>maxp;
    if(maxp<0) return NULL;

    // �������������
    Polynom* result=new Polynom();
    result->head=new Mononom();
    Mononom* current=result->getHead();

    int c=0; // ����� ��� ������
    int curp=1; //������� �������

    cout<<"Enter free coeff.: ";
    cin>>c;
    current->data=c;

    if(maxp==0)
    {
        return result;
    }

    current->next=new Mononom();
    current=current->next;


    while(curp<maxp)
    {
        cout<<"Enter coeff. at x^"<<curp<<": ";
        cin>>c;
        current->data=c;
        current->next=new Mononom();
        current=current->next;
        ++curp;
    }
    cout<<"Enter coeff. at x^"<<maxp<<": ";
    cin>>c;
    current->data=c;
    cout<<endl<<endl;

    return result;
}

// ����� ���������� � ���� "3 +7x -12x^2 -3x^5"
void outputPolynom(Polynom* p)
{
    if(p==NULL) return;
    Mononom* c=p->head; // ������� ��������
    int pow=2;
    bool smthOut=false; // �� ������, ���� ��� ������������ - 0

    if(!c)
    {
        cout<<"[empty polynom]";
        return;
    }
    if(c->data!=0 || c->next==NULL)
    {
        cout<<c->data<<" ";
        smthOut=true;
    }
    c=c->next;
    if(!c)
    {
        cout<<endl;
        return;
    }

    if(c->data!=0)
    {
        if(c->data>0) cout<<"+";
        cout<<c->data<<"x ";
        smthOut=true;
    }
    c=c->next;

    while(c)
    {
        if(c->data!=0)
        {
            if(c->data>0) cout<<"+";
            cout<<c->data<<"x^"<<pow<<" ";
            smthOut=true;
        }
        c=c->next;
        ++pow;
    }
    if(!smthOut) cout<<0;
    cout<<endl;
}

// ��������������� �������, ���������, ����� �� ��� ���� ������� �������� ������
// �������� 0
bool checkNextNulls(Mononom* m)
{
    while(m)
    {
        if(m->data!=0) return false;
        m=m->next;
    }
    return true;
}
// ���������� ����������
bool comparePolynoms(Polynom* p1, Polynom* p2)
{
    if(p1==NULL && p2==NULL) return true;
    Mononom* cur1=p1->head; // ������� �������� ��� p1
    Mononom* cur2=p2->head;// ������� �������� ��� p2
    if(cur1==NULL && cur2==NULL) return true;

    while(true)
    {
        // ������������ �� �������
        if(cur1->data!=cur2->data) return false;

        cur1=cur1->next; cur2=cur2->next;

        // ���� �� ����������� ����������, � �� ����� ��� ������ - ���
        if(cur1==NULL && cur2!=NULL)
        {
            return checkNextNulls(cur2); // ���� ������ ��������� ����������� ������
        }
        if(cur2==NULL && cur1!=NULL)
        {
            return checkNextNulls(cur2); // ���� ������ ��������� ����������� ������
        }
        // ��� ���������� �����������
        if(cur1==NULL && cur2==NULL) return true;
    }

    // �����������
    return false;
}

int main()
{
    Polynom* p1=NULL;
    do
    {
        cout<<"Enter polynom #1:"<<endl;
        p1=inputPolynom();
    }
    while(!p1);

    cout<<endl<<endl;

    Polynom* p2=NULL;
    do
    {
        cout<<"Enter polynom #2:"<<endl;
        p2=inputPolynom();
    }
    while(!p2);

    cout<<endl<<endl<<endl<<"Polynom #1:"<<endl;
    outputPolynom(p1);
    cout<<"Polynom #2:"<<endl;
    outputPolynom(p2);
    cout<<"Are they equal? "<<comparePolynoms(p1, p2);

    delete p1;
    delete p2;

    return 0;
}
