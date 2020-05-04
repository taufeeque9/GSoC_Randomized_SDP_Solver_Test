#include<iostream>
#include "armadillo"
#include "LPproblem.h"
// #include "LPresult.h"
#include "float.h"

using namespace arma;

LPproblem::LPproblem(mat &A, vec &b, vec &c, vec x):A(A), b(b), c(c), x(x) {
    p = zeros(A.n_rows);
    s = ones(A.n_cols);
}

LPproblem::LPproblem(mat &A, vec &b, vec &c):A(A), b(b), c(c) {
    x = ones(A.n_cols);
    p = zeros(A.n_rows);
    s = ones(A.n_cols);
}

LPresult LPproblem::minimize(){
    double eps = 10e-8, theta = 1, r=0.99;
    int k = 0, n = x.size(), m = A.n_rows;
    vec e = ones(n);

    while(!(norm(A*x-b,2)<=eps && norm(A.t()*p+s-c,2)<=eps && as_scalar(s.t()*x) <= eps)){
        k++;
        if(k>149) break;
        // cout<<k<<std::endl;
        theta = (1/10)*as_scalar(((x.t()*s)/n));
        mat X = diagmat(x);
        mat S = diagmat(s);
        vec r1 = b - A*x;
        vec r2 = c - A.t()*p - s;
        vec r3 = theta*e - X*S*e;
        // vec del_x = solve(A, r1);
        mat M = zeros<mat>(m+2*n, m+2*n);
        M.submat(0, n, n-1, n+m-1) = A.t();
        M.submat(0, n+m, n-1, m+2*n-1) = eye(n, n);
        M.submat(n, 0, m+n-1, n-1) = A;
        M.submat(m+n, 0, m+2*n-1, n-1) = S;
        M.submat(m+n, n+m, m+2*n-1, m+2*n-1) = X;
        vec R(m+2*n);
        R.subvec(0, size(r2)) = r2;
        R.subvec(r2.n_elem, size(r1)) = r1;
        R.subvec(r1.n_elem+r2.n_elem, size(r3)) = r3;
        vec V = solve(M, R);
        vec del_x = V.subvec(0, n-1);
        vec del_p = V.subvec(n, m+n-1);
        vec del_s = V.subvec(n+m, m+2*n-1);

        // cout<<del_x;
        // cout<<del_p;
        // cout<<del_s;

        double alpha_p = DBL_MAX, alpha_d = DBL_MAX;

        for(int j=0; j<n; j++){
            if(del_x.at(j) < 0 && (x.at(j)/(-1*del_x.at(j))) < alpha_p)
                alpha_p = (x.at(j)/(-1*del_x.at(j)));

            if(del_s.at(j) < 0 && (s.at(j)/(-1*del_s.at(j))) < alpha_d)
                alpha_d = (s.at(j)/(-1*del_s.at(j)));
        }
        if(r*alpha_p>1) alpha_p=1; else alpha_p=r*alpha_p;
        if(r*alpha_d>1) alpha_d=1; else alpha_d=r*alpha_d;
        // cout<<alpha_p<<" "<<alpha_d<<endl;
        x = x + alpha_p*del_x;
        // cout<<x;
        p = p + alpha_d*del_p;
        s = s + alpha_d*del_s;

    }

    if(k==150){
        return LPresult(false, x, c);
    }
    return LPresult(true, x, c);

}
