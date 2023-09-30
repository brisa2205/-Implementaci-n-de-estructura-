// =========================================================
// File: list.h
// Author: Brisa Itzel Reyes Castro - A01710395
// Date: 29/09/2023
// =========================================================


#ifndef LIST_H
#define LIST_H

#include <string>
#include <sstream>
#include <stdexcept>

template <class T> class List;

template <class T>
class Node {
private:
    Node(T);
    Node(T, Node<T>*);

    T       value;
    Node<T> *next;

    friend class List<T>;
};

template <class T>
Node<T>::Node(T val) : value(val), next(NULL) {
}

template <class T>
Node<T>::Node(T val, Node<T>* nxt) : value(val), next(nxt) {
}

template <class T>
class List {
private:
    Node<T> *head;
    unsigned int size;

public:
    List();
    ~List();

    unsigned int length() const;
    bool empty() const;
    bool contains(T) const;
    void clear();
    std::string toString() const;

    T front() const;
    T last() const;
    T get(unsigned int) const;

    void push_front(T);
    void push_back(T);
    void insert_at(T, unsigned int);

    T pop_front();
    T pop_back();
    T remove_at(unsigned int);

    long int indexOf(T) const;

    class NoSuchElement : public std::runtime_error {
    public:
        NoSuchElement() : std::runtime_error("No such element in the list") {}
    };

    class IndexOutOfBounds : public std::runtime_error {
    public:
        IndexOutOfBounds() : std::runtime_error("Index out of bounds") {}
    };
};

template <class T>
List<T>::List() : head(NULL), size(0) {
}

template <class T>
List<T>::~List() {
    clear();
}

template <class T>
bool List<T>::empty() const {
    return (head == NULL);
}

template <class T>
unsigned int List<T>::length() const {
    return size;
}

template <class T>
bool List<T>::contains(T val) const {
    Node<T> *p;

    p = head;
    while (p != NULL) {
        if (p->value == val) {
            return true;
        }
        p = p->next;
    }
    return false;
}

template <class T>
void List<T>::clear() {
    Node<T> *p, *q;

    p = head;
    while (p != NULL) {
        q = p->next;
        delete p;
        p = q;
    }

    head = NULL;
    size = 0;
}

template <class T>
std::string List<T>::toString() const {
    std::stringstream aux;
    Node<T> *p;

    p = head;
    aux << "[";
    while (p != NULL) {
        aux << p->value;
        if (p->next != NULL) {
            aux << ", ";
        }
        p = p->next;
    }
    aux << "]";
    return aux.str();
}

template <class T>
T List<T>::front() const {
    if (empty()) {
        throw NoSuchElement();
    }

    return head->value;
}

template <class T>
T List<T>::last() const {
    Node<T> *p;

    if (empty()) {
        throw NoSuchElement();
    }

    p = head;
    while (p->next != NULL) {
        p = p->next;
    }
    return p->value;
}

template <class T>
T List<T>::get(unsigned int index) const {
    if (index < 0 || index >= size) {
        throw IndexOutOfBounds();
    }

    Node<T> *p = head;
    for (unsigned int i = 0; i < index; i++) {
        p = p->next;
    }

    return p->value;
}

template <class T>
void List<T>::push_front(T val) {
    Node<T> *q;

    q = new Node<T>(val);
    q->next = head;
    head = q;
    size++;
}

template <class T>
void List<T>::push_back(T val) {
    Node<T> *p, *q;

    if (empty()) {
        push_front(val);
        return;
    }

    p = head;
    while (p->next != NULL) {
        p = p->next;
    }

    q = new Node<T>(val);
    q->next = p->next;
    p->next = q;
    size++;
}

template <class T>
void List<T>::insert_at(T val, unsigned int index) {
    if (index < 0 || index > size) {
        throw IndexOutOfBounds();
    }

    if (index == 0) {
        push_front(val);
    } else if (index == size) {
        push_back(val);
    } else {
        Node<T> *p, *q;
        p = head;
        for (unsigned int i = 1; i < index; i++) {
            p = p->next;
        }
        q = new Node<T>(val, p->next);
        p->next = q;
        size++;
    }
}

template <class T>
T List<T>::pop_front() {
    T val;
    Node<T> *p;

    if (empty()) {
        throw NoSuchElement();
    }

    p = head;

    head = p->next;
    val = p->value;

    delete p;
    size--;
    return val;
}

template <class T>
T List<T>::pop_back() {
    Node<T> *p, *q;
    T val;

    if (empty()) {
        throw NoSuchElement();
    }

    if (size == 1) {
        return pop_front();
    }

    q = NULL;
    p = head;
    while (p->next != NULL) {
        q = p;
        p = p->next;
    }

    q->next = p->next;
    val = p->value;

    delete p;
    size--;

    return val;
}

template <class T>
T List<T>::remove_at(unsigned int index) {
    T aux;

    if (index < 0 || index >= size) {
        throw IndexOutOfBounds();
    }

    T removedValue;

    if (index == 0) {
        removedValue = pop_front();
    } else {
        Node<T> *p = head;
        Node<T> *q = NULL;
        for (unsigned int i = 0; i < index; i++) {
            q = p;
            p = p->next;
        }
        q->next = p->next;
        removedValue = p->value;
        delete p;
        size--;
    }

    return removedValue;
}

template <class T>
long int List<T>::indexOf(T val) const {
    Node<T> *p = head;
    long int index = 0;

    while (p != NULL) {
        if (p->value == val) {
            return index;
        }
        p = p->next;
        index++;
    }

    return -1;
}

#endif /* LIST_H */


