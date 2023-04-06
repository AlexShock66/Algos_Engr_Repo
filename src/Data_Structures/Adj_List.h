//
// Created by Alex Shockley on 3/29/23.
//

#ifndef DATA_STRUCTURES_ADJ_LIST_H
#define DATA_STRUCTURES_ADJ_LIST_H
#include "Linked_List.h"
#include <iostream>
template<typename T>
class Adj_List {
private:
    Linked_List<T> *vertical;
    T * roots;
    size_t size;
    size_t curr_root;
public:
    Adj_List();
    Adj_List(size_t init_vertical_size);
    Adj_List(Adj_List<T> &cpy);
    Adj_List<T>& operator=(const Adj_List<T> cpy);

    size_t get_max_length();
    size_t get_curr_length();

    void push_root(T theRoot);
    void push_value(size_t index, T payload);
    Linked_List<T> & operator[](size_t idx);
    void prettyPrint(std::ostream &out);
    ~Adj_List();

};

template<typename T>
Linked_List<T> &Adj_List<T>::operator[](size_t idx) {
    if(idx >= this->curr_root) {
        throw std::runtime_error("Invalid idx in [] operator");
    }
    return vertical[idx];
}

template<typename T>
Adj_List<T>::Adj_List(size_t init_vertical_size) {

    vertical = new Linked_List<T>[init_vertical_size];
    roots = new T[init_vertical_size];
    size = init_vertical_size;
    if(init_vertical_size != 0) {
        this->curr_root = 0;
    } else {
        this->curr_root = -1;
    }
}

template<typename T>
void Adj_List<T>::prettyPrint(std::ostream &out) {
    for(auto i = 0; i < curr_root; i ++) {
        out << this->roots[i] << ":";
        while(this->vertical[i].has_next()) {
            out << this->vertical[i].get_next();
            if(this->vertical[i].has_next()) out << ",";

        }
        if(i + 1 <curr_root)
            out <<std::endl;
        vertical[i].reset_iterator();
    }
}

template<typename T>
size_t Adj_List<T>::get_max_length() {
    return this->size;
}

template<typename T>
size_t Adj_List<T>::get_curr_length() {
    return this->curr_root;
}

template<typename T>
void Adj_List<T>::push_root(T theRoot) {
    if(curr_root >= this->size) {
        size_t new_size = this->size * 2;
        auto new_vertical = new Linked_List<T>[new_size];
        auto new_roots = new T[new_size];
        for(size_t i =0; i < this->size; i ++) {
            new_vertical[i] = this->vertical[i];
            new_roots[i] = this->roots[i];
        }
        delete[] this->vertical;
        delete[] this->roots;
        this->roots = new_roots;
        this->vertical = new_vertical;
        this->size = new_size;

    }
    roots[curr_root] = theRoot;
    curr_root++;

}

template<typename T>
void Adj_List<T>::push_value(size_t index, T payload) {
    if(index >= size) {
        std::cerr << "Invalid push idx of " << index <<" with a size of " << size <<std::endl;
        throw std::runtime_error("Invalid push_value Index in ADJ_LIST");
    }

    vertical[index].push_back(payload);
}

template<typename T>
Adj_List<T>::Adj_List() {
    vertical = new Linked_List<T>[10];
    roots = new T[10];
    size = 10;
    curr_root = 0;
}

template<typename T>
Adj_List<T>::Adj_List(Adj_List<T> &cpy) {

    roots = new T[cpy.size];
    vertical = new Linked_List<T>[cpy.size];
    for(size_t i =0; i < cpy.size; i ++) {
        vertical[i] = cpy.vertical[i];
        roots[i] = cpy.roots[i];
    }
    this->size = cpy.size;
    this->curr_root = cpy.curr_root;
}

template<typename T>
Adj_List<T> &Adj_List<T>::operator=(const Adj_List<T> cpy) {
    delete[] vertical;
    delete[] roots;
    roots = new T[cpy.size];
    vertical = new Linked_List<T>[cpy.size];
    for(size_t i =0; i < cpy.size; i ++) {
        vertical[i] = cpy.vertical[i];
        roots[i] = cpy.roots[i];
    }
    this->size = cpy.size;
    this->curr_root = cpy.curr_root;
    return *this;
}

template<typename T>
Adj_List<T>::~Adj_List() {
    delete[] this->vertical;
    delete[] this->roots;
    this->vertical = nullptr;
    this->roots = nullptr;
}

#endif //DATA_STRUCTURES_ADJ_LIST_H
