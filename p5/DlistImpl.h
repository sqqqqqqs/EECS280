#ifndef DLIST_IMPL_H
#define DLIST_IMPL_H
#include"Dlist.h"
using namespace std;


template <class T>
bool Dlist<T>::isEmpty() const{
    return !first;
}
template<class T>
void Dlist<T>::insertFront(T *op){
    node *np= new node;
    np->op=op;
    np->prev= nullptr;
    if(isEmpty()){
        np->next= nullptr;
        first=np;
        last=np;
    }
    else{
        first->prev=np;
        np->next=first;
        first=np;
    }
}
template<class T>
void Dlist<T>::insertBack(T *op) {
    node *np=new node;
    np->op=op;
    np->next= nullptr;
    if(isEmpty()){
        np->prev= nullptr;
        first=np;
        last=np;
    }
    else{
        last->next=np;
        np->prev=last;
        last=np;
    }
}

template<class T>
T*Dlist<T>::removeFront() {
    if(isEmpty()){
        throw EmptyList();
    }
    node* victim=first;
    T *t=victim->op;
    if(victim->next!= nullptr){
        first=victim->next;
        first->prev= nullptr;
    }else{
        first= nullptr;
        last= nullptr;
    }
    delete victim;
    return t;
}

template<class T>
T*Dlist<T>::removeBack() {
    if(isEmpty()){
        throw EmptyList();
    }
    node* victim=last;
    T *t=victim->op;
    if(victim->prev!= nullptr){
        last=victim->prev;
        last->next= nullptr;
    }else{
        first= nullptr;
        last= nullptr;
    }
    delete victim;
    return t;
}

template<class T>
Dlist<T>::Dlist():first(nullptr),last(nullptr){}

template<class T>
Dlist<T>::Dlist(const Dlist &l):Dlist() {
        copyAll(l);
}
template<class T>
Dlist<T> &Dlist<T>::operator=(const Dlist<T> &l){
    if (this != &l) {
        copyAll(l);}
    return *this;}

template<class T>
Dlist<T>::~Dlist() {
    removeAll();}

template<class T>
void Dlist<T>::removeAll() {
    while(!isEmpty()){
        T*t=removeFront();
        delete t;}
}

template<class T>
void Dlist<T>::copyAll(const Dlist<T> &l) {
    removeAll();
    node *np=l.first;
    while(np!= nullptr){
        T *t=new T(*(np->op));
        try {
            insertBack(t);
        } catch (...) {
            removeAll();
            delete t;
            throw;}
        np=np->next;}
}
#endif
