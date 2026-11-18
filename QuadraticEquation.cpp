#include "QuadraticEquation.h"

namespace {

double SquareRoot(double value) {
    if (value <= 0.0) {
        return 0.0;
    }

    double result;
    if (value > 1.0) {
        result = value;
    } else {
        result = 1.0;
    }

    for (int i = 0; i < 100; ++i) {
        double next = 0.5 * (result + value / result);
        if (next == result) {
            break;
        }
        result = next;
    }
    return result;
    }

}  // namespace

// Constructors

QuadraticEquation::QuadraticEquation() : a(1.0), b(0.0), c(0.0) {}

QuadraticEquation::QuadraticEquation(double coeff_a, double coeff_b, double coeff_c)
    : a(1.0), b(coeff_b), c(coeff_c) {
    SetA(coeff_a);  // If coeff_a == 0.0, 'a' remains 1.0.
}

QuadraticEquation::QuadraticEquation(double coeff_a, double coeff_b) : a(1.0), b(coeff_b), c(0.0) {
    SetA(coeff_a);
}

QuadraticEquation::QuadraticEquation(const QuadraticEquation& other)
    : a(other.a), b(other.b), c(other.c) {}

// Getters and setters

double QuadraticEquation::GetA() const { return a; }
double QuadraticEquation::GetB() const { return b; }
double QuadraticEquation::GetC() const { return c; }

bool QuadraticEquation::SetA(double value) {
    if (value == 0.0) {
        return false;
    }
    a = value;
    return true;
}

void QuadraticEquation::SetB(double value) { b = value; }
void QuadraticEquation::SetC(double value) { c = value; }

// Methods

double QuadraticEquation::GetDiscriminant() const {
    return b * b - 4.0 * a * c;
}

double* QuadraticEquation::CalculateRoots(int& roots_count) const {
    double discriminant = GetDiscriminant();

    if (discriminant < 0.0) {
        roots_count = 0;
        return new double[0];
    }

    if (discriminant == 0.0) {
        roots_count = 1;
        double* roots = new double[1];
        roots[0] = -b / (2.0 * a);
        if (roots[0] == 0.0) {
            roots[0] = 0.0;  // Avoid returning -0.0.
        }
        return roots;
    }

    double sqrt_discriminant = SquareRoot(discriminant);
    roots_count = 2;
    double* roots = new double[2];
    roots[0] = (-b - sqrt_discriminant) / (2.0 * a);
    roots[1] = (-b + sqrt_discriminant) / (2.0 * a);
    return roots;
}

bool QuadraticEquation::ShiftCoefficients(double delta) {
    if (a + delta == 0.0) {
        return false;
    }
    a += delta;
    b += delta;
    c += delta;
    return true;
}

// Unary operators

QuadraticEquation& QuadraticEquation::operator++() {
    ShiftCoefficients(1.0);
    return *this;
}

QuadraticEquation QuadraticEquation::operator++(int) {
    QuadraticEquation previous(*this);  // Save state before modification.
    ShiftCoefficients(1.0);
    return previous;
}

QuadraticEquation& QuadraticEquation::operator--() {
    ShiftCoefficients(-1.0);
    return *this;
}

QuadraticEquation QuadraticEquation::operator--(int) {
    QuadraticEquation previous(*this);
    ShiftCoefficients(-1.0);
    return previous;
}

// Type conversions

QuadraticEquation::operator double() const { return GetDiscriminant(); }

QuadraticEquation::operator bool() const { return GetDiscriminant() >= 0.0; }

// Binary operators

bool QuadraticEquation::operator==(const QuadraticEquation& other) const {
    return a == other.a && b == other.b && c == other.c;
}

bool QuadraticEquation::operator!=(const QuadraticEquation& other) const {
    return !(*this == other);
}

// Stream output operator

std::ostream& operator<<(std::ostream& out, const QuadraticEquation& equation) {
    out << "a = " << equation.a
        << ", b = " << equation.b
        << ", c = " << equation.c
        << "  =>  (" << equation.a << ")x^2 + ("
        << equation.b << ")x + ("
        << equation.c << ") = 0";
    return out;
}
