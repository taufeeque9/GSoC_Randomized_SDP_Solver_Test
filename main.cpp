#include "armadillo"
#include "LPproblem.h"
// #include "LPresult.h"

using namespace arma;

int main() {
    mat A = mat(7, 12);
    double n = -1, p = 1;
    A = {
            {n, n, p, 0, p, 0, 0, 0, 0, p, 0, 0},
            {p, 0, 0, p, 0, p, 0, 0, 0, 0, 0, 0},
            {0, 0, n, n, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, p, p, 0, 0, p, 0},
            {0, 0, 0, 0, n, n, n, 0, p, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, n, n, 0, 0, p},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, n, n, n}
        };

    vec b = vec(7);
    b = {0, 19, -16, 33, 0, 0, -36};

    vec c = vec(12);
    c = {2, 4, 9, 11, 4, 3, 8, 7, 0, 15, 16, 18};


    LPproblem problem = LPproblem(A, b, c);
    LPresult result = problem.minimize();
    if(result.success){
        cout<<"Operation terminated successfully!\n";
        cout<<"Vector x which minimizes the objective function is:\n";
        cout<<result.x;
        cout<<"Optimum value for the objective function is: "<<result.opt_val<<"\n";
    }
    else{
        cout<<"Operation did not terminate.\n";
    }
    return 0;
}
