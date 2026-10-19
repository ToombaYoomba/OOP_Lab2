#include "polynomial.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <utility>

void Polynomial::swap(Polynomial& other) noexcept {
    std::swap(coefs,  other.coefs);
    std::swap(degree, other.degree);
}

Polynomial::Polynomial(const double* p, int d) 
: coefs(d >= 0 ? new double[d + 1]{} : nullptr),
degree(d) {
    if (d >= 0){
        std::copy(p, p + d + 1, coefs);
    }
}

Polynomial::Polynomial(const Polynomial& other)  
: coefs(other.degree >= 0 ? new double[other.degree + 1]{} : nullptr),
degree(other.degree) {
    std::copy(other.coefs, other.coefs + other.degree + 1, coefs);
}

Polynomial& Polynomial::operator=(const Polynomial& other) {
    if (this != &other) {
        Polynomial tmp(other);
        swap(tmp);
    }
    return *this;
}

Polynomial::Polynomial(Polynomial&& other) noexcept
: coefs(std::exchange(other.coefs, nullptr)),
degree(std::exchange(other.degree, -1)) {}

Polynomial& Polynomial::operator=(Polynomial&& other) noexcept {
    if (this != &other) {
        delete[] coefs;
        coefs = std::exchange(other.coefs, nullptr);
        degree = std::exchange(other.degree, -1);
    }
    return *this;
}

Polynomial::~Polynomial() {
    delete[] coefs;
}

void Polynomial::print(std::ostream& os) const {
    bool first = true;
    for (int i = 0; i <= degree; i++) {
        if (coefs[i] != 0) {
            if (!first) os << " + ";
            os << coefs[i];
            if (i == 1) os << "x";
            else if (i > 1) os << "x^" << i;
            first = false;
        }
    }
    if (first) os << "0";
    os << std::endl;
}

double Polynomial::evaluate(double x) const {
    double res = 0.0;
    for (int i = 0; i < degree+1; i++){
        res += coefs[i] * std::pow(x, i);
    }
    return res;
}

void Polynomial::add(const Polynomial& other){
    double* res = (degree >= other.degree) ? new double[degree+1] : new double[other.degree+1];
    for (int i = 0; i < other.degree+1 || i < degree+1; i++){
        double a = (i <= degree) ? coefs[i] : 0.0;
        double b = (i <= other.degree) ? other.coefs[i] : 0.0;
        res[i] = a + b;
    }

    degree = (degree >= other.degree) ? degree : other.degree;
    delete[] coefs;
    coefs = res;
}

void Polynomial::mul(const Polynomial& other){
    double* res = new double[other.degree + degree + 1]();
    for (int i = 0; i < degree+1; i++){
        for (int j = 0; j < other.degree+1; j++){
            res[i+j] += coefs[i] * other.coefs[j];
        }
    }
    delete[] coefs;
    coefs = res;
    degree = degree + other.degree;
}

bool Polynomial::is_equal(const Polynomial& other, double eps) const {
    for (int i = 0; i < degree+1 || i < other.degree+1; i++){
        double a = (i <= degree) ? coefs[i] : 0.0;
        double b = (i <= other.degree) ? other.coefs[i] : 0.0;
        if (std::fabs(a - b) > eps) return false;
    }
    return true;
}