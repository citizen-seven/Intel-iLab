//
//  main.c
//  tr
//
//  Created by RI on 11.11.15.
//  Copyright © 2015 RI. All rights reserved.
//

#include <stdio.h>

void matrix_mul(int* m1,int* m2, int* m3, int n) {
    int i,j,k;
    for (i=0; i<n; i++) {
        for (j=0; j<n; j++) {
            *(m3+i*n+j)=0;
            for (k=0; k<n; k++) {
                <#statements#>
            }
            *(m3+i*n+j)+=*(m1+i*n+j)*(*(m2+))
        }
    }
};

int main() {
    }

