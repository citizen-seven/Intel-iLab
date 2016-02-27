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

CStack::CStack(): data(), size(0)  // better to put them on separate lines
{}

CStack::~CStack() {
    std::cout<<"Stack has been deleted" <<std::endl; // this is a debug printf... and you forgot spaces around operators
  // make size = -1 here at least. something to know that stack has been deleted.
}

int CStack::push(int val) {
    // where is check?
    this->data[this->size++] = val;
    return 0;
}

int CStack::pop() {
    if (this->size > 0) {
        return this->data[this->size--]; // wrong. should be decremented before poping. data[--size] 
    } else return 0xBAD;  // wrong. you may have 0xbad as a value.
    // also, remember google code-style I asked you to read?
    // if you use brackets in if statement, use it in else as well.
}

int CStack::dump() {
    std::cout << "Current stack with size " <<this->size << " is: "; // spaces
    for (int size_ = 0; size_<size; size_++) {  // either use this-> everywhere, or don't use it at all
        std::cout <<this->data[size_]<< " ";  // spaces
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
