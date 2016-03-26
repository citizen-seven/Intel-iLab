//
//  main.cpp
//  Vector
//
//  Created by RI on 28.02.16.
//  Copyright © 2016 RI. All rights reserved.
//

#include <iostream>
#include <assert.h>


class CVector {
public:
    const static int size_ = 10;
    CVector();
    ~CVector();
    /*int* operator[](int index) {
        assert(0<=index && index<size_);
        return &data_[index];
    }*/
    int& operator[](int index) {
        assert(0<=index && index<size_);
        return data_[index];
    }
    CVector& operator+=(CVector& right) {
        for (int i = 0; i < size_; i++) {
            this->data_[i]+=right[i];
        }
        return *this;
    }
private:
    int data_[size_];
    int $_;
};

CVector::CVector(): data_{} {
    
}

CVector& operator+(CVector& right, CVector& left) {
    CVector& result = right;
    result += left;
    return result;
}

int operator^(CVector& right, CVector& left) {
    int result = 0;
    for (int i = 0; i < right.size_; i++) {
        result += right[i]*left[i];
    }
    return result;
}

CVector::~CVector() {
}

int main() {
    CVector v;
    CVector k;
    CVector r;
    for (int i = 0; i <= 9; i++) {
        v[i] = 1;
        k[i] = 2;
    }
    int n = v.operator[](4);
    int p = v[2];
    r = v+v+k;
    int nu = v^k;
    std::cout << "Dot product is: " << nu << std::endl;
    std::cout << "Numbers: " << n << " and " << p << std::endl;
    for (int i = 0; i<10; i++) {
        std::cout << v[i] << std::endl;
    }
    return 0;
}
