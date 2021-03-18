#ifndef LIST_H
#pragma once
#define LIST_H
template <typename T> class List {
public:
    List();
    ~List();
    int size();
    T front() const;
    T back() const;
    void clear();
    void push_front(T data);
    void push_back(T data);
    void pop_front();
    void pop_back();
    const T& operator[](int index) const;


private:
    class Node {
    public:
        Node *pPrev;
        Node *pNext;
        T data;
        explicit Node(T data, Node *pNext = nullptr, Node *pPrev = nullptr);

    };

    int Size = 0;
    Node *head;
    Node *tail;

public:
    class iterator {
    public:

        iterator& operator++();
        T& operator*();
        T* operator->();
        bool operator==(const iterator& other) const;
        bool operator!=(const iterator& other) const;
    private:
        iterator(Node data, bool isEnd);
        Node* data;
        bool isEnd;
    };
    iterator begin();
    iterator end();

};

template <typename T>
List<T>::List(){
    this->Size = 0;
    this->head = nullptr;
    this->tail = nullptr;
}

template <typename T>
List<T>::~List(){
    clear();
}

template <typename T>
int List<T>::size(){
        return this->Size;
}

template <typename T>
T List<T>::front() const {
    if (head != nullptr)
        return head->data;
     else
        return nullptr;
}

template <typename T>
T List<T>::back() const {
    if (head != nullptr)
        if (tail != nullptr)
            return tail->data;
        else
            return nullptr;
}

template<typename T>
void List<T>::clear()
{
    while(this->Size > 0)
        pop_back();
}

template<typename T>
void List<T>::push_front(T data)
{
    if (head == nullptr){
        head = new Node(data);
        tail = head;
    } else {
        Node *p = new Node(data);
        p->pPrev = nullptr;
        p->pNext = head;
        head->pPrev = p;
        head = head->pPrev;
    }
    Size++;
}

template<typename T>
void List<T>::push_back(T data)
{
    if (tail == nullptr){
        head = new Node(data);
        tail = head;
    } else {
        Node *p = new Node(data);
        p->pPrev = tail;
        p->pNext = nullptr;
        tail->pNext = p;
        tail = tail->pNext;
    }
    Size++;
}

template<typename T>
void List<T>::pop_front()
{
    Node *p = head;
    head = head->pNext;
    if (head != nullptr){
        head->pPrev = nullptr;
    }
    delete p;
    Size--;
}

template<typename T>
void List<T>::pop_back()
{
    Node *p = tail;
    tail = tail->pPrev;
    if (tail != nullptr)
        tail->pNext = nullptr;
    delete p;
    Size--;
}

template<typename T>
typename List<T>::iterator &List<T>::iterator::operator++(){
    if (data != nullptr){
        if (data->pNext == nullptr){
            isEnd = true;
        } else {
            data = data->pNext;
        }
    }
    return *this;
}

template<typename T>
T &List<T>::iterator::operator*(){
    return *data->data;
}

template<typename T>
T *List<T>::iterator::operator->(){
    return data->data;
}

template<typename T>
bool List<T>::iterator::operator==(const iterator& other) const{
    return data == other.data and isEnd == other.isEnd;
}

template<typename T>
bool List<T>::iterator::operator!=(const iterator& other) const{
    return data != other.data or isEnd != other.isEnd;
}

template<typename T>
List<T>::iterator::iterator(Node data, bool isEnd){
    this->data = data;
    this->isEnd = isEnd;
}

template<typename T>
typename  List<T>::iterator List<T>::begin(){
    return List<T>::iterator(head, false);
}

template<typename T>
typename  List<T>::iterator List<T>::end(){
    return List<T>::iterator(tail, true);
}
template<typename T>
const T& List<T>::operator[](int index) const{
    if ((index < Size) && (index >= 0)){
        if ((float)(index / Size) < 0.5){
            Node* p = this->head;
            for (int i = 0; i<index; i++){
                p = p->pNext;
            }
            return p->data;
        } else {
            Node* p = this->tail;
            for (int i = Size-1; i>index; i--){
                p = p->pPrev;
            }
            return p->data;
        }

    }
};

template<typename T>
List<T>::Node::Node(T data, Node *pNext, Node *pPrev)
{
    this->data = data;
    this->pNext = pNext;
    this->pPrev = pPrev;
}


#endif // LIST_H
