//
//  main.cpp
//  Stack
//
//  Created by RI on 18.02.16.
//  Copyright © 2016 RI. All rights reserved.
//

#include <iostream>

class CStack {
private:
    int data[100];
    int size;
public:
    CStack();
    ~CStack();
    int push(int val);
    int pop();
    int dump();
};

CStack::CStack(): data(), size(0)
{}

CStack::~CStack() {
    std::cout<<"Stack has been deleted" <<std::endl;
}

int CStack::push(int val) {
    this->data[this->size++] = val;
    return 0;
}

int CStack::pop() {
    if (this->size > 0) {
        return this->data[this->size--];
    } else return 0xBAD;
}

int CStack::dump() {
    std::cout << "Current stack with size " <<this->size << " is: ";
    for (int size_ = 0; size_<size; size_++) {
        std::cout <<this->data[size_]<< " ";
    }
    std::cout << std::endl ;
    return 0;
}

int main() {
    CStack stack;
    stack.push(10);
    stack.push(15);
    stack.dump();
    stack.pop();
    stack.dump();
    return 0;
}
