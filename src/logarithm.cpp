#include <stdexcept>
#include "math_functions.h"

int _log2_ceiling(double);
double _ln_1to2(double);
double _pow(double, int);

double ln(double x) {
    const double ln2 = 0.693147180559945;

    if (x <= 0) {
        throw std::invalid_argument("x should be higher than 0");
    }
    if (x == 1) {
        return 0;
    }

    int n = _log2_ceiling(x);
    if (n > 0) {
        x = x / (1 << n);
    } else {
        x = x * (1 << -n);
    }

    return _ln_1to2(x) + n*ln2;
}

// Using Teilor series to compute ln near x=1
double _ln_1to2(double x) {
    const double epsilon = 1e-15;
    const double maxSteps = 100;

    x -= 1;
    double approx = x;
    double next = x;
    int step = 1;
    while (next > epsilon || next < -epsilon) {
        step += 1;
        next = _pow(x, step)/(double)step;
        if (step % 2 == 0) {
            next = -next;
        }
        approx += next;
        if (step > maxSteps) {
            break;
        }
    }
    return approx;
}

inline double _pow(double x, int n) {
    return n == 0 ? 1 : x*_pow(x, n-1);
}

int _log2_ceiling(double x) {
    int c = 0;
    if (x > 1) {
        do {
            x = x / 2;
            c += 1;
        } while (x > 2);
    } else if (x < 1) {
        do {
            x = x * 2;
            c -= 1;
        } while (x < 2);
    }

    // (x == 1) => (return 0)
    return c;
}
