/*
 
PIC 10C Homework 2
Author: Sujay Syal
Date: April 25, 2023
 
*/

#include <iostream>
#include <iomanip>
#include <cassert>

#ifndef Mydeque_h
#define Mydeque_h

#endif /* Mydeque_h */


template<typename T>
class Iterator;

template<typename T>
class Mydeque{
private:
    //array called data
    T* data;
    
    //*data = index 0
    //*(data + 1) is index 1
    //*(data + 2) is index 2
    
    //friend class iterator is templated
    friend class Iterator<T>;
    
public:
    //integers for capacity and size
    int cap;
    int sz;
    
    //integers for the front and back index
    int front;
    int back;
    
    Mydeque(); //initialize data members of Mydeque class
    T get_front(); // return data at first index
    T get_back(); //return data at last index
    
    void push_front(const T& value); //add element to front with additional conditions
    void push_back(const T& value); //add element to back with additional conditions
    
    void double_size(int newCap); //using to double capacity and copy
    
    void pop_front(); //remove from front
    void pop_back(); //remove from the back
    
    Iterator<T> begin(); //returns iterator object of front
    Iterator<T> end(); //returns iterator object of back
    
    int size() const; //returns the size of the Deque
    int capacity() const; //returns the capacity of the Deque
    
    T& operator[](int index); //random access operator to retrieve the element at a given index
    
    void print(); //print all elements from front to back;
    void real_print();  //print all elements in data in their actual array position from the first to the last. Use * to replace spots that are not taken
    
};


template <typename T>
Mydeque<T>::Mydeque() {
    cap = 0;
    sz = 0;
    front = 0;
    back = 0;
}


template <typename T>
T Mydeque<T>::get_front(){
    
    
    assert(sz > 0);
    return data[front];
}

template <typename T>
T Mydeque<T>::get_back(){
    
    assert(sz > 0);
    return data[back];
}

template <typename T>
void Mydeque<T>::push_front(const T& value){
    
    if(cap == 0){
        
        T* newDeque = new T[cap+1];
        
        //index of front and back is still 0, update capacity and size
        cap++;
        sz++;
        
        newDeque[front] = value;
        
        data = newDeque;
        
        std::cout << "One spot added. " << "Current capacity: " << cap << std::endl;
        
        return;

    }
    
    if(sz == cap){
        
        double_size(2*cap);

    }
    
    //regular cases push_front
     
     int target = (front - 1 + cap) % cap;
     data[target] = value;
     
     sz++;
     front = target;
    
}

template <typename T>
void Mydeque<T>::push_back(const T& value){
    
    
    if(cap == 0){
        
        T* newDeque = new T[cap+1];
        
        //index of front and back is still 0, update capacity and size
        cap++;
        sz++;
        
        newDeque[front] = value;
        
        data = newDeque;
        
        std::cout << "One spot added." << std::endl;
        
        return;

        
    }
    
    if (sz == cap) {
        
        //find a way to double the array
        double_size(cap*2);

    }
    
    int target = (back + 1) % cap;
    data[target] = value;
    
    //front is unchanged
    
    back = target;
    sz++;
    
}

template <typename T>
void Mydeque<T>::pop_front(){
    //use assert to throw exceptions if the container is already empty
    //you don’t need to account for shrinking the deque capacity
        
    assert(sz != 0);
    front = (front + 1) % cap;
    
    //back remains unchanged
    sz--;
}

template <typename T>
void Mydeque<T>::pop_back(){
    //use assert to throw exceptions if the container is already empty
    //you don’t need to account for shrinking the deque capacity
    
    assert(sz != 0);
    back = (back - 1) % cap;
    
    //back remains unchanged
    sz--;
}

template <typename T>
void Mydeque<T>::double_size(int newCap){
            
    //creating a new array of a new size
    T* newData = new T[newCap];
    
    //copy the elements from the old array to the new array
    for (int i = 0; i < sz; i++) {
        
        newData[i] = data[(front + i) % cap];
        
    }
    
    front = 0;
    back = sz - 1;
    cap = newCap;
    delete[] data;
    data = newData;
    std::cout << "Capacity doubled. " << "Current capacity: " << cap << std::endl;


}

template <typename T>
Iterator<T> Mydeque<T>::begin(){
    Iterator<T> i(this, front);
    return i;
}


template <typename T>
Iterator<T> Mydeque<T>::end(){
    Iterator<T> i(this, (back+1) % cap);
    return i;
}

template <typename T>
int Mydeque<T>::size() const{
    return sz;
}

template <typename T>
int Mydeque<T>::capacity() const{
    return cap;
}



template <typename T>
T& Mydeque<T>::operator[](int index){
    
    //random access operator

    assert(index < cap);
    return data[(front + index) % cap];
}


template <typename T>
void Mydeque<T>::print(){
    
    //print from the front to the back
        
    if(sz == 0){
        std::cout << std::endl;
        return;
    }
        
    for(int i = front; i != back; i = (i+1) % cap ){
        std::cout << data[i] << " ";
    }
    
    std::cout << data[back];
    std::cout << std::endl;

}

//print all elements in data in their actual array position from the first to the last. Use * to replace spots that are not taken

template <typename T>
void Mydeque<T>::real_print(){
        
    for(int i = 0; i < cap; i++){
        if(front < back){
            if(i < front or i > back){
                std::cout << "* ";
            } else {
                std::cout << data[i] << " ";
            }
        } else {
            if(i > back and i < front){
                std::cout << "* ";
            }
            else{
                std::cout << data[i] << " ";
            }
        }
    }

    std::cout<< std::endl;

}


template<typename T>
class Iterator{
private:
    //Iterator contains an integer to represent the index and a pointer to the deque
    int int_index;
    Mydeque<T>* ptr_to_deck;
    friend class Mydeque<T>;
    
public:
    
    Iterator(Mydeque<T>* t, int idx){
        //constructor called when object created
        int_index = idx;
        ptr_to_deck = t;
    }
        
    Iterator<T>& operator++(){
        //prefix ++ doesn't take a copy
        //moves to next position
        
        int_index++;
        //moving the index to the next position
        int_index = int_index % ptr_to_deck->cap;

        return *this;
        
    }
    
    Iterator<T> operator++(int){
        
        //postfix makes a copy of the current iterator
        
        Iterator<T> iter_minus = *this;
        ++int_index;
        return iter_minus;
        
    }
    
    Iterator<T>& operator--(){
        //prefix --
        
        int_index--;
        if(int_index < 0){
            int_index = (ptr_to_deck->cap - 1);
        }
        
        return *this;
        
    }
    
    Iterator<T> operator--(int){
        //postfix --
        
        Iterator<T> iter_minus = *this;
        --int_index;
        return iter_minus;
        
    }
    
    T& operator*() const{
        
        //going inside the deque and taking the data from a particular index
        
        assert(ptr_to_deck != nullptr);
        return ptr_to_deck->data[int_index];
                
    }
    
    //operators to compare different iterators
    
    bool operator==(const Iterator& iter_to_compare){
        
        
        //compare the index to the index of the iterator passed in
        //compare the ptr to deck to the ptr to deck of the iterator passed in
            
        return (int_index  == iter_to_compare.int_index && ptr_to_deck == iter_to_compare.ptr_to_deck);
        
    }
    
    
    bool operator!=(const Iterator& iter_to_compare){
                
        
        //compare the index to the index of the iterator passed in
        //compare the ptr to deck to the ptr to deck of the iterator passed in
        
        return !(int_index  == iter_to_compare.int_index && ptr_to_deck == iter_to_compare.ptr_to_deck);
    }
    
};

