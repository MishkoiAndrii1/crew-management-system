#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include "Node.hpp"
#include <functional>
#include <iostream>
#include <string>
using namespace std;

template<typename T>
class LinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    int size;

    // Helper function for case-insensitive string comparison
    string toLower(const string& str) const {
        string result = str;
        for (char& c : result) {
            if (c >= 'A' && c <= 'Z') {
                c = c - 'A' + 'a';
            }
        }
        return result;
    }

    // allows pointer chain no matter if its object or pointer
    template<typename U>
    struct Accessor {
        static auto getTrainingScore(const U& obj) -> decltype(obj.getTrainingScore()) {
            return obj.getTrainingScore();
        }
        static auto getMissionAptitude(const U& obj) -> decltype(obj.getMissionAptitude()) {
            return obj.getMissionAptitude();
        }
        static auto getFirstName(const U& obj) -> decltype(obj.getFirstName()) {
            return obj.getFirstName();
        }
        static auto getLastName(const U& obj) -> decltype(obj.getLastName()) {
            return obj.getLastName();
        }
        static auto getId(const U& obj) -> decltype(obj.getId()) {
            return obj.getId();
        }
        static const U& getForOutput(const U& obj) {
            return obj;
        }
    };

    // Specialization for pointers
    template<typename U>
    struct Accessor<U*> {
        static auto getTrainingScore(const U* obj) -> decltype(obj->getTrainingScore()) {
            return obj->getTrainingScore();
        }
        static auto getMissionAptitude(const U* obj) -> decltype(obj->getMissionAptitude()) {
            return obj->getMissionAptitude();
        }
        static auto getFirstName(const U* obj) -> decltype(obj->getFirstName()) {
            return obj->getFirstName();
        }
        static auto getLastName(const U* obj) -> decltype(obj->getLastName()) {
            return obj->getLastName();
        }
        static auto getId(const U* obj) -> decltype(obj->getId()) {
            return obj->getId();
        }
        static const U& getForOutput(const U* obj) {
            return *obj;
        }
    };

    // Merge sort implementation
    Node<T>* mergeSort(Node<T>* start, function<int(const T&, const T&)> compareFunc) {
        if (start == nullptr || start->getNext() == nullptr) return start;

        // Split the list
        Node<T>* slow = start;
        Node<T>* fast = start->getNext();
        
        while (fast != nullptr && fast->getNext() != nullptr) {
            slow = slow->getNext();
            fast = fast->getNext()->getNext();
        }
        
        Node<T>* middle = slow;
        Node<T>* nextToMiddle = middle->getNext();
        middle->setNext(nullptr);

        // Recursively sort both halves
        Node<T>* left = mergeSort(start, compareFunc);
        Node<T>* right = mergeSort(nextToMiddle, compareFunc);

        // Merge the sorted halves
        return merge(left, right, compareFunc);
    }

    Node<T>* merge(Node<T>* left, Node<T>* right, function<int(const T&, const T&)> compareFunc) {
        if (left == nullptr) return right;
        if (right == nullptr) return left;

        Node<T>* result = nullptr;

        if (compareFunc(left->getData(), right->getData()) <= 0) {
            result = left;
            result->setNext(merge(left->getNext(), right, compareFunc));
        } else {
            result = right;
            result->setNext(merge(left, right->getNext(), compareFunc));
        }

        return result;
    }

public:
    // Constructor & Destructor
    LinkedList() : head(nullptr), tail(nullptr), size(0) {}
    
    ~LinkedList() {
        Node<T>* current = head;
        while (current != nullptr) {
            Node<T>* next = current->getNext();
            delete current;
            current = next;
        }
    }
    
    // Basic Operations
    void insertAtEnd(const T& data) {
        Node<T>* newNode = new Node<T>(data);
        
        if (head == nullptr) {
            
            head = tail = newNode;
        } else {
            tail->setNext(newNode);
            tail = newNode;
        }
        size++;
    }
    //O(n)  find and insert
    void insertSorted(const T& data, function<int(const T&, const T&)> compareFunc) {
        Node<T>* newNode = new Node<T>(data);
        
        if (head == nullptr) {
            head = tail = newNode;
            size++;
            return;
        }
        
        if (compareFunc(data, head->getData()) < 0) {
            newNode->setNext(head);
            head = newNode;
            size++;
            return;
        }
        
        Node<T>* current = head;
        Node<T>* previous = nullptr;
        
        while (current != nullptr && compareFunc(data, current->getData()) >= 0) {
            previous = current;
            current = current->getNext();
        }
        
        previous->setNext(newNode);
        newNode->setNext(current);
        
        if (current == nullptr) {
            tail = newNode;
        }
        
        size++;
    }
    //call mergeSort for algorithm and book keep states
    void sort(function<int(const T&, const T&)> compareFunc) {
        if (size <= 1) return;
        head = mergeSort(head, compareFunc);
        
        // Update tail
        Node<T>* current = head;
        while (current->getNext() != nullptr) {
            current = current->getNext();
        }
        tail = current;
    }
    
    // Search Operations
    // O(n), does not have inherant sorting
    LinkedList<T> searchByTrainingScore(float minScore, float maxScore) const {
        LinkedList<T> result;
        Node<T>* current = head;
        int matchCount = 0;
        
        while (current != nullptr) {
            float score = Accessor<T>::getTrainingScore(current->getData());
            if (score >= minScore && score <= maxScore) {
                result.insertAtEnd(current->getData());
                matchCount++;
            }
            current = current->getNext();
        }
        
        if (matchCount == 0) {
            cout << "No matches found for training score range " 
                 << minScore << " - " << maxScore << endl;
        } else {
            cout << "Found " << matchCount << " match(es) for training score range " 
                 << minScore << " - " << maxScore << ":" << endl;
            result.displayAll();
        }
        
        return result;
    }
    //O(n) no inherant sort
    
    LinkedList<T> searchByMissionAptitude(int minAptitude, int maxAptitude) const {
        LinkedList<T> result;
        Node<T>* current = head;
        int matchCount = 0;
        
        while (current != nullptr) {
            int aptitude = Accessor<T>::getMissionAptitude(current->getData());
            if (aptitude >= minAptitude && aptitude <= maxAptitude) {
                result.insertAtEnd(current->getData());
                matchCount++;
            }
            current = current->getNext();
        }
        
        if (matchCount == 0) {
            cout << "No matches found for mission aptitude range " 
                 << minAptitude << " - " << maxAptitude << endl;
        } else {
            cout << "Found " << matchCount << " match(es) for mission aptitude range " 
                 << minAptitude << " - " << maxAptitude << ":" << endl;
            result.displayAll();
        }
        
        return result;
    }
    //O(n) no inherant sort
    LinkedList<T> searchByName(const string& firstName, const string& lastName) const {
        LinkedList<T> result;
        Node<T>* current = head;
        int matchCount = 0;
        
        string searchFirstLower = toLower(firstName);
        string searchLastLower = toLower(lastName);
        
        while (current != nullptr) {
            string currentFirst = Accessor<T>::getFirstName(current->getData());
            string currentLast = Accessor<T>::getLastName(current->getData());
            
            string currentFirstLower = toLower(currentFirst);
            string currentLastLower = toLower(currentLast);
            
            if (currentFirstLower == searchFirstLower && currentLastLower == searchLastLower) {
                result.insertAtEnd(current->getData());
                matchCount++;
            }
            current = current->getNext();
        }
        
        if (matchCount == 0) {
            cout << "No matches found for name: " << firstName << " " << lastName << endl;
        } else {
            cout << "Found " << matchCount << " match(es) for name: " 
                 << firstName << " " << lastName << ":" << endl;
            result.displayAll();
        }
        
        return result;
    }
    //O(n) no inherant sort
    Node<T>* searchByID(int id) const {
        Node<T>* current = head;
        while (current != nullptr) {
            if (Accessor<T>::getId(current->getData()) == id) {
                cout << "Found match for ID " << id << ":" << endl;
                cout << Accessor<T>::getForOutput(current->getData()) << endl;
                return current;
            }
            current = current->getNext();
        }
        
        cout << "No match found for ID: " << id << endl;
        return nullptr;
    }
    
    // Delete Operations find and delete, no resorting, O(n)
    void deleteByName(const string& firstName, const string& lastName) {
        Node<T>* current = head;
        Node<T>* previous = nullptr;
        
        string searchFirstLower = toLower(firstName);
        string searchLastLower = toLower(lastName);
        
        while (current != nullptr) {
            string currentFirst = Accessor<T>::getFirstName(current->getData());
            string currentLast = Accessor<T>::getLastName(current->getData());
            
            string currentFirstLower = toLower(currentFirst);
            string currentLastLower = toLower(currentLast);
            
            if (currentFirstLower == searchFirstLower && currentLastLower == searchLastLower) {
                if (previous == nullptr) {
                    head = current->getNext();
                    if (head == nullptr) tail = nullptr;
                } else {
                    previous->setNext(current->getNext());
                    if (current->getNext() == nullptr) {
                        tail = previous;
                    }
                }
                
                Node<T>* toDelete = current;
                current = current->getNext();
                delete toDelete;
                size--;
            } else {
                previous = current;
                current = current->getNext();
            }
        }
    }

    // Display
    void displayAll() const {
        Node<T>* current = head;
        while (current != nullptr) {
            cout << Accessor<T>::getForOutput(current->getData()) << endl;
            current = current->getNext();
        }
    }
    
    // Getters
    Node<T>* getHead() const { return head; }
    Node<T>* getTail() const { return tail; }
    int getSize() const { return size; }
    bool isEmpty() const { return head == nullptr; }
};

#endif