#include <iostream>
#include "QuadraticEquation.h"

using std::cin;
using std::cout;
using std::endl;


static void ClearInput() {
    cin.clear();
    while (cin.get() != '\n' && !cin.eof()) {}
}


static double ReadDouble(const char* prompt) {
    double value = 0.0;
    while (true) {
        cout << prompt;
        if (cin >> value && cin.peek() == '\n') {
            ClearInput();
            return value;
        }
        if (cin.eof()) {
            cout << "\nInput complete. Exiting the program." << endl;
            exit(0);
        }
        cout << "Error: you need to enter a number. Please try again." << endl;
        ClearInput();
    }
}


static double ReadCoefficientA() {
    while (true) {
        double value = ReadDouble("Enter a (a != 0): ");
        if (value != 0.0) {
            return value;
        }
        cout << "Error: when a = 0, the equation is not quadratic." << endl;
    }
}


static int ReadMenuChoice(int minValue, int maxValue) {
    while (true) {
        double value = ReadDouble("Your choice: ");
        int choice = (int)value;
        if (value == (double)choice && choice >= minValue && choice <= maxValue) {
            return choice;
        }
        cout << "Error: Please enter an integer from " << minValue << " to " << maxValue << "." << endl;
    }
}


static void PrintMenu() {
    cout << "\nQuadratic equation" << endl;
    cout << "1. Create a default equation (constructor 1)" << endl;
    cout << "2. Create an equation using a, b, and c (constructor 2)" << endl;
    cout << "3. Create an equation in terms of a and b, with c = 0 (constructor 3)" << endl;
    cout << "4. Create a copy of the current equation (copy constructor)" << endl;
    cout << "5. Modify coefficients (properties)" << endl;
    cout << "6. Display the current equation (output operator)" << endl;
    cout << "7. Find the roots of the equation" << endl;
    cout << "8. Increase all coefficients by 1 (the ++ operation)" << endl;
    cout << "9. Decrease all coefficients by 1 (the -- operation)" << endl;
    cout << "10. Get the discriminant (implicit conversion to double)" << endl;
    cout << "11. Are there any roots (explicit conversion to bool)" << endl;
    cout << "12. Compare with another equation (== and != operators)" << endl;
    cout << "0. Exit" << endl;
}


static void ShowRoots(const QuadraticEquation& equation) {
    int rootsCount = 0;
    double* roots = equation.CalculateRoots(rootsCount);

    cout << "Discriminant: " << equation.GetDiscriminant() << endl;
    if (rootsCount == 0) {
        cout << "There are no real roots." << endl;
    } else {
        cout << "Number of roots: " << rootsCount << endl;
        for (int i = 0; i < rootsCount; i++) {
            cout << "x" << (i + 1) << " = " << roots[i] << endl;
        }
    }
    delete[] roots;
}


static void ChangeCoefficients(QuadraticEquation& equation) {
    cout << "What to change? 1 - a, 2 - b, 3 - c" << endl;
    int choice = ReadMenuChoice(1, 3);

    if (choice == 1) {
        equation.SetA(ReadCoefficientA());
    } else if (choice == 2) {
        equation.SetB(ReadDouble("Enter b: "));
    } else {
        equation.SetC(ReadDouble("Enter c: "));
    }
    cout << "Done. Now: " << equation << endl;
}


// Demonstrates ++ (is_increment = true) and -- (is_increment = false).
void ChangeByOne(QuadraticEquation& equation, bool is_increment) {
    cout << "Operation: 1 - prefix (" << (is_increment ? "++x" : "--x")
         << "), 2 - postfix (" << (is_increment ? "x++" : "x--") << ")"
         << endl;
    int choice = ReadMenuChoice(1, 2);

    QuadraticEquation before(equation);

    if (choice == 1) {
        if (is_increment) {
            ++equation;
        } else {
            --equation;
        }
    } else {
        QuadraticEquation returned;
        if (is_increment) {
            returned = equation++;
        } else {
            returned = equation--;
        }
        cout << "Postfix operation returned value BEFORE change: " << returned
             << endl;
    }

    if (equation == before) {
        cout << "Operation rejected: coefficient a would become 0,\n"
             << "making the equation no longer quadratic." << endl;
    }
    cout << "Current equation: " << equation << endl;
}


// Compares the current quadratic equation with another user-defined one.
void CompareWithAnother(const QuadraticEquation& equation) {
    cout << "Enter coefficients for the second equation." << endl;
    double a = ReadCoefficientA();
    double b = ReadDouble("Enter b: ");
    double c = ReadDouble("Enter c: ");
    QuadraticEquation other(a, b, c);

    cout << "First equation: " << equation << endl;
    cout << "Second equation: " << other << endl;

    bool is_equal = (equation == other);
    bool is_not_equal = (equation != other);

    cout << std::boolalpha;
    cout << "equation == other : " << is_equal << endl;
    cout << "equation != other : " << is_not_equal << endl;

    if (is_equal) {
        cout << "Result: equations are equal (all coefficients match)." << endl;
    } else {
        cout << "Result: equations are not equal (coefficients differ)." << endl;
    }
}


int main() {
    QuadraticEquation equation;
    cout << "Task 1,2. exercise 6." << endl;
    cout << "Current equation: " << equation << endl;

    bool isRunning = true;
    while (isRunning) {
        PrintMenu();
        int choice = ReadMenuChoice(0, 12);

        if (choice == 1) {
            equation = QuadraticEquation();
            cout << "Created: " << equation << endl;
        } else if (choice == 2) {
            double a = ReadCoefficientA();
            double b = ReadDouble("Enter b: ");
            double c = ReadDouble("Enter c: ");
            equation = QuadraticEquation(a, b, c);
            cout << "Created: " << equation << endl;
        } else if (choice == 3) {
            double a = ReadCoefficientA();
            double b = ReadDouble("Enter b: ");
            equation = QuadraticEquation(a, b);
            cout << "Created: " << equation << endl;
        } else if (choice == 4) {
            QuadraticEquation copy(equation);
            cout << "Copy created: " << copy << endl;
            equation = copy;
        } else if (choice == 5) {
            ChangeCoefficients(equation);
        } else if (choice == 6) {
            cout << "Current equation: " << equation << endl;
        } else if (choice == 7) {
            cout << "Equation: " << equation << endl;
            ShowRoots(equation);
        } else if (choice == 8) {
            ChangeByOne(equation, true);
        } else if (choice == 9) {
            ChangeByOne(equation, false);
        } else if (choice == 10) {
            double discriminant = equation;   // неявное приведение к double
            cout << "Equation: " << equation << endl;
            cout << "Discriminant (conversion to double): " << discriminant << endl;
        } else if (choice == 11) {
            bool hasRoots = static_cast<bool>(equation);   // явное приведение к bool
            cout << "Equation: " << equation << endl;
            cout << "Conversion to bool: " << (hasRoots ? "true" : "false")
                 << (hasRoots ? " (roots exist)" : " (no roots)") << endl;
        } else if (choice == 12) {
            CompareWithAnother(equation);
        } else {
            isRunning = false;
        }
    }
    return 0;
}