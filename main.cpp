#include <iostream>
#include "blist.cpp"

// Определяем многочлен и одночлен как связанный список целых чисел
typedef BList<int> Polynom;
// и его элемент
typedef BListItem<int> Mononom;

using namespace std;

// Получает коэффициэнты многочлена с клавиатуры и возвращает сформированный список
Polynom* inputPolynom()
{
    cout<<"Enter maximal power: ";
    int maxp=0;
    cin>>maxp;
    if(maxp<0) return NULL;

    // Инициализация
    Polynom* result=new Polynom();
    result->head=new Mononom();
    Mononom* current=result->getHead();

    int c=0; // Буфер для чтения
    int curp=1; //Текущая степень

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

// Вывод многочлена в виде "3 +7x -12x^2 -3x^5"
void outputPolynom(Polynom* p)
{
    if(p==NULL) return;
    Mononom* c=p->head; // Текущий одночлен
    int pow=2;
    bool smthOut=false; // На случай, если все коэффициэнты - 0

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

// Вспомогательная функция, проверяет, имеют ли все дети данного элемента списка
// значения 0
bool checkNextNulls(Mononom* m)
{
    while(m)
    {
        if(m->data!=0) return false;
        m=m->next;
    }
    return true;
}
// Сравнивает многочлены
bool comparePolynoms(Polynom* p1, Polynom* p2)
{
    if(p1==NULL && p2==NULL) return true;
    Mononom* cur1=p1->head; // Текущий одночлен для p1
    Mononom* cur2=p2->head;// Текущий одночлен для p2
    if(cur1==NULL && cur2==NULL) return true;

    while(true)
    {
        // Коэффициэнты не совпали
        if(cur1->data!=cur2->data) return false;

        cur1=cur1->next; cur2=cur2->next;

        // Один из многочленов закончился, в то время как второй - нет
        if(cur1==NULL && cur2!=NULL)
        {
            return checkNextNulls(cur2); // если второй многочлен завершается нулями
        }
        if(cur2==NULL && cur1!=NULL)
        {
            return checkNextNulls(cur2); // если первый многочлен завершается нулями
        }
        // Оба многочлена закончились
        if(cur1==NULL && cur2==NULL) return true;
    }

    // Недостижимо
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
