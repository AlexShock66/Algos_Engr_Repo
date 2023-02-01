//
// Created by Alex Shockley on 1/23/23.
//

#ifndef DATA_STRUCTURES_LINKED_LIST_H
#define DATA_STRUCTURES_LINKED_LIST_H

#include <exception>
#include <stdexcept>

template<typename T>
class Linked_List {
    struct list_node {
        list_node *prev;
        list_node *next;
        T data;
        list_node(T theData) {
            this->data = theData;
            prev = nullptr;
            next = nullptr;
        }
        list_node() {
            this->data = T();
            prev = nullptr;
            next = nullptr;
        }
    };
public:
    Linked_List();
    Linked_List( Linked_List<T> &cpy);
    Linked_List<T> operator=(Linked_List<T> &cpy);
    ~Linked_List();
    void push_back(T data);
    T pop_back();
    void remove(T data);
    T remove_at(int index);
    void push_front(T data);
    bool has_next();
    T get_next();
    int get_size();
    T& at(int index);
    void reset_iterator();
private:
    list_node *head;
    list_node *tail;
    list_node *curr;
    int size;



};

template<typename T>
Linked_List<T>::Linked_List() {
    head = nullptr;
    tail = nullptr;
    curr = nullptr;
    size = 0;
}

template<typename T>
int Linked_List<T>::get_size() {
    return this->size;
}

template<typename T>
T &Linked_List<T>::at(int index) {
    if(index > size) {
        throw std::invalid_argument("Tried to get element at index" + std::to_string(index) + " with size " + std::to_string(size));
    }
    else {
        auto the_val = this->head;
        for(int i =0; i < index; i ++) {
            the_val = the_val->next;
        }
        return the_val->data;
    }
}

template<typename T>
Linked_List<T>::Linked_List(Linked_List<T> &cpy) {
    size = cpy.size;
    if(cpy.head != nullptr) {
        this->head = new list_node(cpy.head->data);
        curr = this->head;
        auto curr_cpy = cpy.head->next;
        while(curr_cpy != nullptr) {
            curr->next = new list_node(curr_cpy->data);
            curr->next->prev = curr;
            curr = curr->next;
            curr_cpy = curr_cpy->next;
        }
        tail = curr;
        curr = this->head;
    }

}

template<typename T>
Linked_List<T> Linked_List<T>::operator=(Linked_List<T> &cpy) {
   size = cpy.size;
    if(cpy.head != nullptr) {

        this->head = new list_node(cpy.head->data);
        curr = this->head;
        auto curr_cpy = cpy.head->next;
        while(curr_cpy != nullptr) {
            curr->next = new list_node(curr_cpy->data);
            curr->next->prev = curr;
            curr = curr->next;
            curr_cpy = curr_cpy->next;
        }
        tail = curr;
        curr = this->head;
    }
    return *this;
}

template<typename T>
Linked_List<T>::~Linked_List() {
    curr = head;
    if( curr != nullptr) {
        while(curr->next != nullptr) {
            curr = curr->next;
            delete curr->prev;
        }
        delete curr;
    }

}

template<typename T>
void Linked_List<T>::push_back(T data) {
    if(head == nullptr) {
        head = new list_node(data);
        tail = head;
        curr = head;
    } else {
        tail->next = new list_node(data);
        tail->next->prev = tail;
        tail = tail->next;

    }
    size++;
}

template<typename T>
T Linked_List<T>::pop_back() {
    if( head == tail && head != nullptr) {
        T data = head->data;
        delete head;
        head = nullptr;
        tail = nullptr;
        curr = nullptr;
        size--;
        return data;
    }

        if(size == 0) {
            throw std::invalid_argument("Tried to pop from an empty list");
        }

        T data = tail->data;
        tail = tail->prev;
        delete tail->next;
        tail->next = nullptr;
        size--;
        return data;


}

template<typename T>
void Linked_List<T>::remove(T data) {
    auto the_val = head;
    while(the_val != nullptr) {
        if(the_val->data ) {
            if(the_val->prev != nullptr) {
                the_val->prev->next = the_val->next;

            }
            if(the_val->next != nullptr) {
                the_val->next->prev = the_val->prev;
            }
            delete the_val;
            size --;
            return;
        }
        the_val = the_val->next;
    }
    throw std::invalid_argument("Element not found in remove function");
}

template<typename T>
T Linked_List<T>::remove_at(int index) {
    if(size == 0) {
        throw std::invalid_argument("Tried to remove_at from an empty list");
    } else if(index >= size) {
        throw std::invalid_argument("Tried to remove_at index " + std::to_string(index) + " from list size " +
                                            to_string(size) + '\n');

    } else if(size == 1 && index == 0) {
        T theData = head->data;
        delete head;
        head = nullptr;
        tail = nullptr;
        curr = nullptr;
        size--;
        return theData;
    } else if(index == size -1) {
        auto tmp = tail;
        T theData = tail->data;
        delete tail;
        tail =tmp;
        tail->next = nullptr;
        size--;
        return theData;
    } else {
        auto tmp = head;
        for(int i =0; i < index; i ++) {
            tmp = tmp->next;
        }
        tmp->next->prev = tmp->prev;
        tmp->prev->next = tmp->next;
        T theData = tmp->data;
        delete tmp;
        size--;
        return theData;
    }
}

template<typename T>
void Linked_List<T>::push_front(T data) {

    auto tmp = head;
    head = new list_node(data);
    head->next = tmp;
    tmp->prev = head;

}

template<typename T>
bool Linked_List<T>::has_next() {
    return curr != nullptr;
}

template<typename T>
T Linked_List<T>::get_next() {
    if(curr == nullptr) {
        throw std::invalid_argument("Tried to get curr when no curr_next");
    } else {
        T theData = curr->data;
        curr = curr->next;
        return theData;
    }
}

template<typename T>
void Linked_List<T>::reset_iterator() {
    curr = head;

}

#endif //DATA_STRUCTURES_LINKED_LIST_H
