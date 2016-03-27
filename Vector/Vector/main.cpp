//
//  main.cpp
//  Vector
//
//  Created by RI on 28.02.16.
//  Copyright © 2016 RI. All rights reserved.
//

#include <iostream>
#include <assert.h>
#include <string>

template <typename data_T>
class CVector {
    const static int size_ = 10;
    data_T data_[size_];
public:
    CVector(): data_{} {
    };
    //~CVector();
    data_T& operator[](int index) {
        assert(0<=index && index<size_);
        return data_[index];
    }
    CVector& operator+=(CVector right) {
        if (typeid(data_T) == typeid(int)) {
            for (int i = 0; i < size_; i++) {
                this->data_[i]+=right[i];
            }
        } else if (typeid(data_T) == typeid(char)) {
            for (int i = 0; i<size_; i+=2) {
                this->data_[i+1] = right[i];
            }
        }
        return *this;
    }
};

/*class CVector {
public:
    const static int size_ = 10;
    CVector();
    ~CVector();
    int* operator[](int index) {
        assert(0<=index && index<size_);
        return &data_[index];
    }
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
};*/
template<class T>
T& operator+ (CVector<int>& right, CVector<int>& left) {
    CVector<int>& result = right;
    result += left;
    return result;
}

/*int operator^(CVector& right, CVector& left) {
    int result = 0;
    for (int i = 0; i < right.size_; i++) {
        result += right[i]*left[i];
    }
    return result;
}*/



int main() {
    CVector<char> v;
    CVector<char> k;
    //CVector k;
    //CVector r;
    for (int i = 0; i <= 9; i++) {
        v[i] = 'a';
        k[i] = 'b';
    }
    char n = v.operator[](4);
    v+=k;
    //int nu = v^k;
    //std::cout << "Dot product is: " << nu << std::endl;
    std::cout << "Numbers: " << n << " and " << "hey" << std::endl;
    for (int i = 0; i<10; i++) {
        std::cout << v[i] << std::endl;
    }
    return 0;
}
