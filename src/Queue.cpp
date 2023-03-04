#include "Queue.h"
#include <iostream>

using namespace std;

template<typename T>
bool Queue<T>::isEmpty() const {
    return _size == 0;
}

template<typename T>
int Queue<T>::size() const {
    return _size;
}

template<typename T>
void Queue<T>::enqueue(const T &newItem) {
    QueueNode *newNode = new QueueNode;
    if (isEmpty()) {
        newNode->item = newItem;
        newNode->next = newNode;
        _lastNode = newNode;
    } else {
        newNode->item = newItem;
        newNode->next = _lastNode->next;
        _lastNode->next = newNode;
        _lastNode = newNode;

    }
    _size++;
}

template<typename T>
void Queue<T>::dequeue() {
    if (_size==1) {
        QueueNode *firstNode = _lastNode->next;
        _lastNode = NULL;
    } else {
        QueueNode *firstNode = _lastNode->next;
        _lastNode->next = firstNode->next;
        _lastNode=firstNode;

    }
    _size--;
}

template<typename T>
void Queue<T>::getFront(T &queueTop) const {
    if (!isEmpty()) {
        QueueNode *firstNode = _lastNode->next;
        queueTop = firstNode->item;
    }


}

template<typename T>
Queue<T>::Queue() {};

template<typename T>
Queue<T>::~Queue() {};