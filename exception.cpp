#include <iostream>

class Exception
{
public:
    Exception()
    {
        std::cout<<"Exception: a general exception was thrown!\n";
    }
};

class IndexOutOfRangeException: public Exception
{
public:
    int index;
    const int undefinedIndex=0xffffffff;
    IndexOutOfRangeException()
    {
        index=undefinedIndex;
        std::cout<<"IndexOutOfRangeException: Element index is out of array (list) bounds!\n";
    }
    IndexOutOfRangeException(int index)
    {
        this->index=index;
        std::cout<<"IndexOutOfRangeException: Element index "<<index<<" is out of array (list) bounds!";
    }
};

class NullArgumentException: public Exception
{
public:
    NullArgumentException()
    {
        std::cout<<"NullArgumentException: Required item is NULL!\n";
    }
};
