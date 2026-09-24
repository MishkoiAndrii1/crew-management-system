#ifndef NODE_HPP
#define NODE_HPP
#include <string>
using namespace std;

template<typename T>
class Node {
private:
    T data;
    Node<T>* next;

public:
    // Constructor
    Node(const T& data) : data(data), next(nullptr) {}
    
    // Getters
    T getData() const { return data; }
    Node<T>* getNext() const { return next; }
    
    // Setters
    void setData(const T& newData) { data = newData; }
    void setNext(Node<T>* nextNode) { next = nextNode; }
};

#endif