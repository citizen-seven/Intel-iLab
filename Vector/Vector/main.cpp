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
public: //public has to be the first to make size_ visible
    const static int size_ = 10; // make private and getter
    
    CVector(): data_{} {
    };
    
    data_T& operator[](int index) {
        assert(0<=index && index<size_); // code style
        return data_[index];
    };
    
    CVector<int>& operator+=(CVector<int> right);
private:
    data_T data_[size_]; // add getter & setter
};

template <>
CVector<int>& CVector<int>::operator+=(CVector<int> right) {
    for (int i = 0; i < size_; i++) {
        this->data_[i]+=right[i]; // code style
    }
    return *this;
}

CVector<int> operator+ (CVector<int>& right, CVector<int>& left) {
    CVector<int> result = right;
    result += left;
    return result;
}

int operator^(CVector<int>& right, CVector<int>& left) {
    int result = 0;
    for (int i = 0; i < right.size_; i++) {
        result += right[i]*left[i]; // code style
    }
    return result;
}


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

int main() {
    CVector<int> v;
    CVector<int> k;
    CVector<int> r;
    
    for (int i = 0; i <= 9; i++) { //initialization
        v[i] = 11+i;
        k[i] = 13-i;
    }

    int num_4 = v.operator[](4); //checking overloaded []
    int num_7 = k[7];
    std::cout << "Numbers: " << num_4 << " and " << num_7 << std::endl;
    
    r = v + k; //checking overloaded +
    for (int i = 0; i<10; i++) {
        std::cout << "Element " << i+1 << " in sum with + is "  << r[i] << std::endl;
    };
    
    v += k; //checking overloaded +=
    for (int i = 0; i<10; i++) {
        std::cout << "Element " << i+1 << " in sum with += is " << v[i] << std::endl;
    }
    
    int dot_product = v^k; //checking overloaded ^
    std::cout << "Dot product is: " << dot_product << std::endl;
    
    
    return 0;
}
