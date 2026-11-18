#ifndef QUADRATIC_EQUATION_H_
#define QUADRATIC_EQUATION_H_

#include <iostream>

// Represents a quadratic equation of the form ax^2 + bx + c = 0.
// Coefficient 'a' is always guaranteed to be non-zero.
class QuadraticEquation {
    public:
        // Creates a default equation: x^2 = 0 (a = 1.0, b = 0.0, c = 0.0).
        QuadraticEquation();

        // Creates an equation with all three coefficients. If |coeff_a| is 0.0,
        // it defaults to 1.0.
        QuadraticEquation(double coeff_a, double coeff_b, double coeff_c);

        // Creates an equation with c = 0.0. If |coeff_a| is 0.0, it defaults to 1.0.
        QuadraticEquation(double coeff_a, double coeff_b);

        // Copy constructor.
        QuadraticEquation(const QuadraticEquation& other);

        // Getters and setters for equation coefficients.
        double GetA() const;
        double GetB() const;
        double GetC() const;

        // Sets coefficient 'a'. Returns false and leaves 'a' unchanged if |value|
        // is 0.0.
        bool SetA(double value);
        void SetB(double value);
        void SetC(double value);

        // Returns the discriminant (b^2 - 4ac).
        double GetDiscriminant() const;

        // Calculates real roots and returns a dynamically allocated array.
        // Sets |roots_count| to 0, 1, or 2. Caller owns the returned array.
        double* CalculateRoots(int& roots_count) const;

        // Prefix and postfix increment/decrement operators (shifts all coefficients
        // by +1 or -1 unless coefficient 'a' would become 0.0).
        QuadraticEquation& operator++();
        QuadraticEquation operator++(int);
        QuadraticEquation& operator--();
        QuadraticEquation operator--(int);

        // Implicit conversion to double: returns the discriminant.
        operator double() const;

        // Explicit conversion to bool: returns true if real roots exist.
        explicit operator bool() const;

        // Equality operators comparing all three coefficients.
        bool operator==(const QuadraticEquation& other) const;
        bool operator!=(const QuadraticEquation& other) const;

        friend std::ostream& operator<<(std::ostream& out, const QuadraticEquation& equation);

    private:
        double a;
        double b;
        double c;

        // Shifts all coefficients by |delta| if the resulting 'a' is non-zero.
        bool ShiftCoefficients(double delta);
};

#endif  // QUADRATIC_EQUATION_H_
