#pragma once

#ifndef __SMART_PTR_HPP__
#define __SMART_PTR_HPP__

#include <iostream>

template<typename T>
class   Smart_ptr {
public:
    Smart_ptr(T* ptr = NULL);
    Smart_ptr(const Smart_ptr& sptr);
    Smart_ptr&  operator=(const Smart_ptr& sptr);
    ~Smart_ptr();

    T&  operator*();
    T*  operator->();

    Smart_ptr   make_smart(T obj);

private:
    T*  _ptr;

    void    swap(Smart_ptr<T> sptr);
};

template<typename T>
Smart_ptr<T>::Smart_ptr(T* ptr) : _ptr(ptr) {}

template<typename T>
Smart_ptr<T>::Smart_ptr(const Smart_ptr<T>& sptr) : _ptr(new T) {
    *_ptr = *sptr._ptr;
}

template<typename T>
Smart_ptr<T>::~Smart_ptr() { delete _ptr; }

template<typename T>
Smart_ptr<T>&   Smart_ptr<T>::operator=(const Smart_ptr<T>& sptr) {
    swap(sptr);
    return *this;
}

template<typename T>
void    Smart_ptr<T>::swap(Smart_ptr<T> sptr) {
    T*  temp = sptr._ptr;

    sptr._ptr = _ptr;
    _ptr = temp;
}

template<typename T>
T&  Smart_ptr<T>::operator*() {
    return *_ptr;
}

template<typename T>
T*  Smart_ptr<T>::operator->() {
    return _ptr;
}

template<typename T>
Smart_ptr<T>    Smart_ptr<T>::make_smart(T obj) {
    return Smart_ptr<T>(new T(obj));
}

#endif
