#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <vector>

using namespace std;

// interface Queue
template <class T>
class Queue {
public:
    Queue() {
    }
    
    virtual ~Queue() {
    }
    
    // interface
    virtual void enqueue(T elem) = 0;
    virtual T dequeue() = 0;
    virtual T peek() = 0;
    virtual int size() = 0;
};

template <class T>
class VectorQueue : public Queue<T> {
protected:
    vector<T> v;

public:
    VectorQueue() : Queue<T>() {
    }
    
    virtual ~VectorQueue() {
    }
    
    // interface
    virtual void enqueue(T elem) {
        v.push_back(elem);
    }
    
    // pre-condition: size() > 0
    virtual T dequeue() {
        T elemToReturn = v[0];
    
        v.erase(v.begin());
    
        return elemToReturn;
    }
    
    // pre-condition: size() > 0
    virtual T peek() {
        return v[0];
    }
    
    virtual int size() {
        return v.size();
    }
};

template <class T>
class VectorPriorityQueue : public Queue<T> {
protected:
    vector<T> v;
    
public:
    VectorPriorityQueue() : Queue<T>() {
    }
    
    virtual ~VectorPriorityQueue() {
    }
    
    // interface
    virtual void enqueue(T elem) {
        for (int i = 0; i < v.size(); i++) {
            if (elem < v[i]) {
                v.insert(v.begin() + i, elem);
                return;
            }
        }

        // 위에서 elem보다 큰 것이 없었다면, 여기까지 나오게 된다.
        // 따라서 맨 끝에 append하면 된다.
        v.push_back(elem);
    }
    
    // pre-condition: size() > 0
    virtual T dequeue() {
        T elemToReturn = v[0];
        
        v.erase(v.begin());
        
        return elemToReturn;
    }
    
    // pre-condition: size() > 0
    virtual T peek() {
        return v[0];
    }
    
    virtual int size() {
        return v.size();
    }
};

#endif
