#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iosfwd>

struct Polynomial {
private:
    double* coefs = nullptr;
    int degree = -1;

    void swap(Polynomial& other) noexcept;

public:
    Polynomial(const double* p, int d);
    Polynomial(const Polynomial& other);
    Polynomial& operator=(const Polynomial& other);
    Polynomial(Polynomial&& other) noexcept;
    Polynomial& operator=(Polynomial&& other) noexcept;
    ~Polynomial();

    void print(std::ostream& os) const;
    double evaluate(double x) const;
    void add(const Polynomial& other);
    void mul(const Polynomial& other);
    bool is_equal(const Polynomial& other, double eps = 1e-9) const;
};

#endif // POLYNOMIAL_H