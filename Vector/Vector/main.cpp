//
//  main.cpp
//  Vector
//
//  Created by RI on 28.02.16.
//  Copyright © 2016 RI. All rights reserved.
//

#include <iostream>
#include <assert.h>
#define $ CFuncMonitor monitor___(__FILE__, __LINE__, __PRETTY_FUNCTION__);


class CVector {
    const static int size_ = 10;
    int data_[size_];
    int $_;
public:
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
    CVector& operator+(CVector& right) {
        for (int i; i<size_; i++) {
            this->data_[i]+=right[i];
        }
        return *this;
    }
};

CVector::CVector(): data_{1,2,3,4,5,6,7,8,9,10} {
    
}

CVector::~CVector() {
    
}

int main() {
    CVector v;
    int n = v.operator[](4);
    int p = v[2];
    CVector k;
    v=v+k;
    std::cout <<"Numbers:"<< n << " " << p <<std::endl;
    for (int i = 0; i<10; i++) {
        std::cout << v[i] << std::endl;
    }   
    return 0;
}
