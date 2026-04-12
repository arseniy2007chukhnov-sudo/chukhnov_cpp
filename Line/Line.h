#pragma once
#include <iostream>

class LineListException {};

template <class T> class LineListCyc;

template <class T> class LineListElem
{
    T data;
    LineListElem* next;
public:
    LineListElem(const T& adata, LineListElem* anext);
    const T& getData() const;
    LineListElem* getNext();
    friend class LineListCyc<T>;
};

template <class T> 
class LineListCyc // Для решения задачи Иосифа циклический список подходит намного лучше обычного
{
    LineListElem<T>* start;
    LineList(const LineListCyc& list);
public:
    LineList();
    ~LineList();
    LineListElem<T>* getStart();
    void deleteFirst(); // Изменено
    void deleteAfter(LineListElem<T>* ptr); // Изменено
    void insertFirst(const T& data); // Изменено
    void insertAfter(LineListElem<T>* ptr, const T& data);
    template <class U>
    friend std::ostream& operator <<(std::ostream& out, const LineListCyc<U>& list); // Изменено
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
LineListCyc<T>::LineListCyc()
{
    start = nullptr;
}

template <class T>
LineListCyc<T>::~LineListCyc()
{
    while (start)
        deleteFirst();
}

template <class T>
LineListCyc<T>::LineListCyc(const LineListCyc& list) : start(nullptr)
{
    *this = list;
}

template <class T>
LineListElem<T>* LineListCyc<T>::getStart()
{
    return start;
}

template <class T>
void LineListCyc<T>::deleteFirst()
{
    if (!start) // Если список пуст
        throw LineListException();

    if (start->next == start) // // Если элемент в списке один
    {
        delete start; // Очищаем всю память по указателю start (первый элемент)
        start = nullptr; // start снова ни на что не указывает
    }
    else // Если больше одного элемента
    {
        LineListElem<T>* end = start; // Создаём указатель end, который будет указывать на последний элемент списка
        while (end->next != start) // Если указатель после end указывает на то же, что и start, то мы дошли до конца списка
            end = end->next;

        LineListElem<T>* temp = start; // Копируем указатель на первый элемент
        start = start->next; // start теперь указывает на второй элемент
        end->next = start; // end теперь смотрит на новый start
        delete temp; // удаляем первый элемент
    }
}

template <class T>
void LineListCyc<T>::deleteAfter(LineListElem<T>* ptr)
{
    if (!ptr) // Если указатель ни на что не указывает
        throw LineListException(); 

    if (ptr->next == start) // Если элемент, на который указывает ptr смотрит на start
    {
        if (start->next == start) // Если start единственный элемент массива
        {
            delete start; // Очищаем память по указателю start
            start = nullptr; // start ни на что не указывает
            return;
        }
        start = ptr->next->next; // start теперь указывает на второй элемент 
    }

    LineListElem<T>* temp = ptr->next; // Копируем указатель на элемент, который мы удаляем
    ptr->next = ptr->next->next; // ptr теперь смотрит на элемент после удаляемого
    delete temp; // Удаляем нужный элемент
}

template <class T>
void LineListCyc<T>::insertFirst(const T& data)
{
    if (!start) // Если start ни на что не указывает (Спискок пуст)
    {
        start = new LineListElem<T>(data, nullptr); // Создаём первый элемент
        start->next = start; // Теперь элемент, на который указывает start, указывает на самого себя
    }
    else // Если первый элемент уже существует
    {
        LineListElem<T>* end = start; // Ищем последний элемент по тому же принципу, что и раньше
        while (end->next != start)
            end = end->next;

        LineListElem<T>* newElem = new LineListElem<T>(data, start); // Создаём новый элемент, который смотрит на первый элемент
        end->next = newElem; // Конечный элемент смотрит на новый первый
        start = newElem; // start теперь указывает на новый первый элемент
    }
}

template <class T>
void LineListCyc<T>::insertAfter(LineListElem<T>* ptr, const T& data)
{
    if (ptr)
    {
        LineListElem<T>* temp = ptr->next;
        ptr->next = new LineListElem<T>(data, temp);
    }
}

template <class T>
std::ostream& operator <<(std::ostream& out, const LineListCyc<T>& list) {
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
        } while (ptr != list.start); // Выводим, пока не дойдём до конца
    }
    return out;
}