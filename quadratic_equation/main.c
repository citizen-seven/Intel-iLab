#include <stdio.h>
#include <math.h>

int QuadraticEquationSolver (float factorA, float factorB, float factorC, float* root) {
    // add simple documentation. what the function does, what parameters accept, what returns
    float discriminant;
    // remove comments. they are not documentation
    //float first_root;
    discriminant = pow(factorB, 2) - 4 * factorA * factorC;
    if (discriminant < 0) {
        return -1;
    }
    else {
        root[0] = (-factorB + sqrt(discriminant)) / (2 * factorA);
        root[1] = (-factorB - sqrt(discriminant)) / (2 * factorA);
    }
    return 0;
}

int main()
{
    float factorA=0, factorB=0, factorC=0;
    float root[2] = {0};
    scanf("%f %f %f",&factorA, &factorB, &factorC);
    if (QuadraticEquationSolver(factorA, factorB, factorC, root) == 0) {
        printf("%.2f, %.2f\n", root[0], root[1]);
    } else {
        printf("No roots!\n");
    }

}
