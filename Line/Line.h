#pragma once
#include <iostream>

class LineListException {};

template <class T> class LineList;

template <class T> class LineListElem
{
    T data;
    LineListElem* next;
public:
    LineListElem(const T& adata, LineListElem* anext);
    const T& getData() const;
    LineListElem* getNext();
    friend class LineList<T>;
};

template <class T> 
class LineList
{
    LineListElem<T>* start;
    LineList(const LineList& list);
public:
    LineList();
    ~LineList();
    LineListElem<T>* getStart();
    void deleteFirst();
    void deleteAfter(LineListElem<T>* ptr);
    void insertFirst(const T& data);
    void insertAfter(LineListElem<T>* ptr, const T& data);
    // LineList& operator=(const LineList& list);
    template <class U>
    friend std::ostream& operator <<(std::ostream& out, const LineList<U>& list);
};


template <class T>
LineListElem<T>::LineListElem(const T& adata, LineListElem* anext)
{
    data = adata;
    next = anext;
}

template <class T>
const T& LineListElem<T>::getData() const
{
    return data;
}

template <class T>
LineListElem<T>* LineListElem<T>::getNext()
{
    return next;
}

template <class T>
LineList<T>::LineList()
{
    start = nullptr;
}

template <class T>
LineList<T>::~LineList()
{
    while (start)
        deleteFirst();
}

template <class T>
LineList<T>::LineList(const LineList& list) : start(nullptr)
{
    *this = list;
}

template <class T>
LineListElem<T>* LineList<T>::getStart()
{
    return start;
}

template <class T>
void LineList<T>::deleteFirst()
{
    if (!start) //Список пуст
        throw LineListException();

    if (start->next == start) //Один элемент
    {
        delete start;
        start = nullptr;
    }
    else //Несколько элементов
    {
        LineListElem<T>* end = start;
        while (end->next != start)
            end = end->next;

        LineListElem<T>* temp = start;
        start = start->next;
        end->next = start; 
        delete temp;
    }
}

template <class T>
void LineList<T>::deleteAfter(LineListElem<T>* ptr)
{
    if (!ptr)
        throw LineListException(); //Список пуст

    if (ptr->next == start) // ptr равен end
    {
        if (start->next == start) // Если в списке всего 1 элемент
        {
            delete start;
            start = nullptr;
            return;
        }
        start = ptr->next->next;
    }

    LineListElem<T>* temp = ptr->next;
    ptr->next = ptr->next->next;
    delete temp;
}

template <class T>
void LineList<T>::insertFirst(const T& data)
{
    if (!start)
    {
        start = new LineListElem<T>(data, nullptr);
        start->next = start;
    }
    else
    {
        LineListElem<T>* end = start;
        while (end->next != start)
            end = end->next;

        LineListElem<T>* newElem = new LineListElem<T>(data, start);
        end->next = newElem; 
        start = newElem;
    }
}

template <class T>
void LineList<T>::insertAfter(LineListElem<T>* ptr, const T& data)
{
    if (ptr)
    {
        LineListElem<T>* temp = ptr->next;
        ptr->next = new LineListElem<T>(data, temp);
    }
}

template <class T>
std::ostream& operator <<(std::ostream& out, const LineList<T>& list) {
    if (!list.start)
    {
        out << "EMPTY";
    }
    else
    {
        LineListElem<T>* ptr = list.start;
        do {
            out << ptr->getData() << ' ';
            ptr = ptr->getNext();
        } while (ptr != list.start); 
    }
    return out;
}