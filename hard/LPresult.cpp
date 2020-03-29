#include "armadillo"
#include "LPresult.h"

using namespace arma;

LPresult::LPresult(bool success, vec x, const vec &c): success(success), x(x) {
    opt_val = as_scalar(c.t()*x);
}
