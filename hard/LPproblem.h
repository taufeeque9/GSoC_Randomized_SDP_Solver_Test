#include<iostream>
#include "armadillo"
#include "LPresult.h"

using namespace arma;

class LPproblem{
    mat &A;
    vec &b;
    vec &c;
    vec x;
    vec s; vec p;


public:
    LPproblem(mat &A, vec &b, vec &c, vec x);
    LPproblem(mat &A, vec &b, vec &c);
    LPresult minimize();
};
