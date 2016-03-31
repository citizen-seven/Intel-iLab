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
private:
    const static int size_ = 10;
    data_T data_[size_];
public:
    CVector(): data_{} {
    };
    
    int Vsize_() {
        return size_;
    }
    
    data_T& operator[] (int index) {
        assert(0 <= index && index < size_);
        return data_[index];
    };
    
    CVector<data_T>& operator+= (CVector<data_T> right) {
        std::cout << "Not implemented" << std::endl;
        return *this;
    };
    
    friend CVector<data_T> operator* (data_T factor, CVector<data_T>& vector) {
        std::cout << "Not implemented" << std::endl;
        return *vector;
    };
    friend CVector<data_T> operator* (CVector<data_T>& vector, data_T factor);
    
};

template<>
CVector<int>& CVector<int>::operator+= (CVector<int> right) {
    for (int i = 0; i < size_; i++) {
        this -> data_[i] += right[i];
    }
    return *this;
}

CVector<int> operator* (int factor, CVector<int>& vector) {
    CVector<int> result;
    for (int i = 0; i < result.Vsize_(); i++) {
        result[i] = factor * vector[i];
    }
    return result;
}

CVector<int> operator* (CVector<int>& vector, int factor) {
    return factor * vector;
}

CVector<int> operator+ (CVector<int>& right, CVector<int>& left) {
    CVector<int> result = right;
    result += left;
    return result;
}

int operator^(CVector<int>& right, CVector<int>& left) {
    int result = 0;
    for (int i = 0; i < right.Vsize_(); i++) {
        result += right[i] * left[i]; // code style
    }
    return result;
}

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
    
    r = v*num_7; //checking overloaded +
    for (int i = 0; i<10; i++) {
        std::cout << "Element " << i+1 << " in sum with + is "  << r[i] << std::endl;
    };
    
    r = num_7*v; //checking overloaded +=
    for (int i = 0; i<10; i++) {
        std::cout << "Element " << i+1 << " in sum with += is " << r[i] << std::endl;
    }
    
    int dot_product = v^k; //checking overloaded ^
    std::cout << "Dot product is: " << dot_product << std::endl;
    
    
    return 0;
}
