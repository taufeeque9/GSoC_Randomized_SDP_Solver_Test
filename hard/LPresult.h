#include "armadillo"

using namespace arma;

class LPresult{
public:
    bool success;
    vec x;
    double opt_val;

    LPresult(bool success, vec x, const vec &c);
};
