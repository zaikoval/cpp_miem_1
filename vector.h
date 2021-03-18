#ifndef VECTOR_H
#pragma once
#define VECTOR_H
#include <iostream>


template <typename T>
class Vector{
public:
    Vector() = default; // what it does?
    explicit Vector(size_t n);
    ~Vector();
    const T& operator[](size_t index) const;
    void push_back(const T &value);
    size_t size();
    void clear();

private:
    T *Data = nullptr;
    size_t Size = 0;
    size_t Capacity = 0;

public:
    class Iterator
    {
    public:
        Iterator(const Vector<T> *vector, size_t nIndex);
        const T &operator*() const;
        Iterator &operator++();
        bool operator!=(const Iterator &other) const;

    private:
        const Vector<T> *pVector;
        int idx = -1;
    };

    Iterator begin() const;
    Iterator end() const;
};

template <typename T>
Vector<T>::Iterator::Iterator(const Vector<T> *p, size_t nIndex)
    : pVector(p)
    , idx(nIndex)
{
}

template <typename T>
const T &Vector<T>::Iterator::operator*() const
{
    return pVector->operator[](idx);
}

template <typename T>
typename Vector<T>::Iterator &Vector<T>::Iterator::operator++()
{
    ++idx;
    return *this;
}

template <typename T>
bool Vector<T>::Iterator::operator!=(const Vector<T>::Iterator &other) const
{
    return idx != other.idx;
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::begin() const
{
    return Vector<T>::Iterator{ this, 0 };
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::end() const
{
    return Vector<T>::Iterator{ this, Size };
}

template <typename T>
Vector<T>::Vector(size_t n){
            this->Capacity = n;
            this->Data = new T[n];
}

template <typename T>
Vector<T>::~Vector(){
    delete[] Data;
    Size = 0;
    Capacity = 0;
}

template <typename T>
const T& Vector<T>::operator[](size_t index) const
{
        if (index >= Size)
            throw std::out_of_range("Out of Range in Vector");
        return Data[index];
}

template <typename T>
void Vector<T>::push_back(const T &value)
{

        if (Size == Capacity)
            {
                if (Capacity == 0)
                    Capacity = 1;

                Capacity *= 2;

                auto pNewMemory = new T[Capacity];

                for (auto i = 0; i < Size; ++i)
                    pNewMemory[i] = Data[i];

                delete[] Data;
                Data = pNewMemory;
            }

        Data[Size] = value;
        ++Size;
}

template <typename T>
size_t Vector<T>::size(){
    return Size;
}

template <typename T>
void Vector<T>::clear(){
    delete[] Data;
    Data = nullptr;
    Size = 0;
    Capacity=0;
}


#endif // VECTOR_H
