#include <stdio.h>
#include <math.h>

int QuadraticEquationSolver (float factorA, float factorB, float factorC, float* root) {
    float discriminant;
    discriminant = pow(factorB, 2) - 4 * factorA * factorC;
    if (discriminant < 0) {
        return -1;
    }
    else if (!discriminant) {
        root[0] = (-factorB + sqrt(discriminant)) / (2 * factorA);
        return 1;
    }
    else {
        root[0] = (-factorB + sqrt(discriminant)) / (2 * factorA);
        root[1] = (-factorB - sqrt(discriminant)) / (2 * factorA);
    }
    return 2;
}

int main()
{
    float factorA=0, factorB=0, factorC=0;
    float root[2] = {0};
    scanf("%f %f %f",&factorA, &factorB, &factorC);
    switch (QuadraticEquationSolver(factorA, factorB, factorC, root)) {
        case -1:
            printf("No roots!\n");
            break;
        case 1:
            printf("%.2f", root[0]);
            break;
        case 2:
            printf("%.2f, %.2f\n", root[0], root[1]);
            break;
    }
}
