#include "Stack.h"


using namespace std;


template<typename T>
bool Stack<T>::isEmpty() const {
    return _size == 0;

}

template<typename T>
int Stack<T>::size() const {
    return _size;
}

template<typename T>
void Stack<T>::push(const T &newItem) {
    ListNode *newNode = new ListNode;
    newNode->item = newItem;
    newNode->next = _head;
    _head = newNode;
    _size++;
}

template<typename T>
void Stack<T>::getTop(T &stackTop) const {
    if (!isEmpty()) {
        stackTop = _head->item;
    }
}

template<typename T>
void Stack<T>::pop() {
    if (!isEmpty()) {
        _head = _head->next;
        _size--;
    }
}

template<typename T>
Stack<T>::Stack() {};

template<typename T>
Stack<T>::~Stack() {};