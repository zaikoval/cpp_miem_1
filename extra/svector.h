#ifndef SVECTOR_H
#define SVECTOR_H

#include <stdexcept>
#include <cstddef>
#include <algorithm>

namespace Simple
{

template <typename T>
class SVector
{
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T *;
    using reference = T &;

public:
    /* The iterator */
    class Iterator
    {
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T *;
        using reference = T &;
        using iterator_category = std::random_access_iterator_tag;

    public:
        Iterator() = default;
        Iterator(T *pData) : m_ptr(pData) {}

        reference       operator*()                     { return *m_ptr; }
        const reference &operator*()            const   { return *m_ptr; }
        pointer         operator->()                    { return m_ptr; }
        const pointer   operator->()            const   { return m_ptr; }
        reference       operator[](int offset)          { return m_ptr[offset]; }
        const reference operator[](int offset)  const   { return m_ptr[offset]; }

        Iterator &operator++()      { ++m_ptr; return *this; }
        Iterator &operator--()      { --m_ptr; return *this; }
        Iterator operator++(int)    { Iterator it(*this); ++m_ptr; return *this; }
        Iterator operator--(int)    { Iterator it(*this); --m_ptr; return *this; }

        Iterator &operator+=(int offset) { m_ptr += offset; return *this; }
        Iterator &operator-=(int offset) { m_ptr -= offset; return *this; }

        Iterator operator+(int offset) const { Iterator it(*this); return it += offset; }
        Iterator operator-(int offset) const { Iterator it(*this); return it -= offset; }

        difference_type operator-(const Iterator &other) const { return m_ptr - other.m_ptr; }

        // Note: comparing iterator from different containers
        //       is undefined behavior so we don't need to check
        //       if they are the same container.
        bool operator<  (const Iterator &other) const   { return m_ptr < other.m_ptr; }
        bool operator<= (const Iterator &other) const   { return m_ptr <= other.m_ptr; }
        bool operator>  (const Iterator &other) const   { return m_ptr > other.m_ptr; }
        bool operator>= (const Iterator &other) const   { return m_ptr >= other.m_ptr; }
        bool operator== (const Iterator &other) const   { return m_ptr == other.m_ptr; }
        bool operator!= (const Iterator &other) const   { return m_ptr != other.m_ptr; }

    private:
        T *m_ptr{ nullptr };
    };

public:
    // constructors
    SVector() = default;
    explicit SVector(std::size_t nCapacity);

    void insert(value_type value);

    std::size_t size() const;

    reference operator[](std::size_t nIndex);
    const reference operator[](std::size_t nIndex) const;

    Iterator begin();
    Iterator end();

private:
    void resizeIfRequired();
    void detectCapacity();
    void allocateMemory();

private:
    std::shared_ptr<value_type[]> m_pData{ nullptr };
    std::size_t m_nSize = 0;
    std::size_t m_nCapacity = 0;
};

/*
 * Vector methods
 **/
template <typename T>
SVector<T>::SVector(std::size_t nCapacity)
{
    if (nCapacity > 0)
    {
        m_nCapacity = nCapacity;
        m_pData = std::make_unique<value_type[]>(nCapacity);
    }
}

template <typename T>
void SVector<T>::insert(value_type value)
{
    resizeIfRequired();

    // insert the new element
    m_pData[m_nSize] = std::move(value);
    ++m_nSize;
}

template <typename T>
std::size_t SVector<T>::size() const
{
    return m_nSize;
}

template <typename T>
typename SVector<T>::reference SVector<T>::operator[](std::size_t nIndex)
{
    if (nIndex >= m_nSize)
        throw std::exception("Index out of range");

    return m_pData[nIndex];
}

template <typename T>
typename const SVector<T>::reference SVector<T>::operator[](std::size_t nIndex) const
{
    return operator[](nIndex);
}

template <typename T>
typename SVector<T>::Iterator SVector<T>::begin()
{
    return SVector<T>::Iterator{ m_pData.get() };
}

template <typename T>
typename SVector<T>::Iterator SVector<T>::end()
{
    return SVector<T>::Iterator{ m_pData.get() + m_nSize };
}

template <typename T>
void SVector<T>::resizeIfRequired()
{
    if (m_nSize == m_nCapacity)
    {
        detectCapacity();
        allocateMemory();
    }
}

template <typename T>
void SVector<T>::detectCapacity()
{
    if (m_nCapacity == 0)
    {
        m_nCapacity = 1;
        m_pData = std::make_unique<T[]>(m_nCapacity);
    }
    else
        m_nCapacity *= 2;
}

template <typename T>
void SVector<T>::allocateMemory()
{
    // allocate new memory
    auto pNewMemory = new T[m_nCapacity];

    // move data to there
    std::move(m_pData.get(), m_pData.get() + m_nSize, pNewMemory);

    m_pData.reset(pNewMemory);
}

} // namespace Simple

#endif // !SVECTOR_H