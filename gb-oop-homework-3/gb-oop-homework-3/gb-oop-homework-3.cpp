// gb-oop-homework-3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <cassert>
#include <functional>
#include <string>
#include <sstream>
#include <cstdint>

#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

//// Task1
class Figure {
    virtual double area() = 0;
};

class Parallelogram : public Figure {
protected:
    double sideA, sideB, abSin;
public:
    Parallelogram(double sideA, double sideB, double abSin): sideA{sideA}, sideB{sideB}, abSin{abSin} {}

    double area() override {
        return sideA * sideB * abSin;
    }
};

class Circle : public Figure {
    double radius;
public:
    Circle(double radius): radius{radius} {}

	double area() override {
        return M_PI * radius * radius;
	}
};

class Rectangle : public Parallelogram {
public:
    Rectangle(double height, double width): Parallelogram{ height, width, 1 } {}

	double area() override {
		return sideA * sideB;
	}
};

class Square : public Parallelogram {
public:
    Square(double side): Parallelogram{side, side, 1} {}

	double area() override {
        return sideA * sideB;
	}
};

class Rhombus : public Parallelogram {
public:
    Rhombus(double side, double sidesSin): Parallelogram{ side, side, sidesSin } {}

	double area() override {
        double& side = sideA;
		return pow(side, 2) * abSin;
	}
};

//// Task2
class Car {
protected:
    string company, model;
    void printProps(const string& className) {
        cout << className << "{company: " << company << ", model : " << model << "}\n";
    }
public:
    Car() {
        printProps("Car");
    }
    Car(const string& company, const string& model) : company{ company }, model{ model } {
        printProps("Car");
    }
};

class PassengerCar : virtual public Car {
public:
    PassengerCar() {
        printProps("PassengerCar");
    }
};

class Bus : virtual public Car {
public:
    Bus() {
		printProps("Bus");
	}
};

class Minivan : public PassengerCar, public Bus {
public:
    Minivan() {
        printProps("Minivan");
	}
};

//// Task3
int getSign(int num) {
    return num < 0 ? -1 : 1;
}

class Fraction {
    int numerator;
    int denominator;

	int coercion(Fraction& fractOrig, const Fraction& fractOther) {
		if (fractOrig.denominator != fractOther.denominator) {
			fractOrig.numerator *= fractOther.denominator;
            int factor = fractOrig.denominator;
			fractOrig.denominator *= fractOther.denominator;
			return factor;
		}
		return 1;
	}

	Fraction applyOp(const Fraction& fract, function<int(int, int)> op) {
		Fraction res = *this;
		int factor = coercion(res, fract);
		return { op(res.numerator, fract.numerator * factor), res.denominator };
	}

	bool applyPredicate(const Fraction& fract, function<bool(int, int)> op) {
		Fraction res = *this;
		int factor = coercion(res, fract);
        return op(numerator, fract.numerator * factor);
	}

public:
    Fraction(int numerator, int denominator): numerator{numerator}, denominator{denominator} {
		assert(denominator != 0);
		numerator *= getSign(numerator) * getSign(denominator);
		denominator = abs(denominator); 
    }

    Fraction operator-() {
        return { -numerator, denominator };
    }


	Fraction operator+(const Fraction& fraction) {
        static auto plus = [](int x, int y) { return x + y; };
        return applyOp(fraction, plus);
	}

	Fraction operator-(const Fraction& fraction) {
		static auto minus = [](int x, int y) { return x - y; };
		return applyOp(fraction, minus);
	}

	Fraction operator*(const Fraction& fraction) {
		return { numerator * fraction.numerator, denominator * fraction.denominator };
	}

	Fraction operator/(const Fraction& fraction) {
        return *this * Fraction{fraction.denominator, fraction.numerator};
	}
    
    bool operator==(const Fraction& fraction) {
        static auto eq = [](int x, int y) { return x == y; };
        return applyPredicate(fraction, eq);
    }

    bool operator!=(const Fraction& fraction) {
        return !(*this == fraction);
    }

	bool operator<(const Fraction& fraction) {
		static auto less = [](int x, int y) { return x < y; };
		return applyPredicate(fraction, less);
	}

	bool operator<=(const Fraction& fraction) {
		return *this < fraction || *this == fraction;
	}

	bool operator>(const Fraction& fraction) {
		return !(*this <= fraction);
	}

	bool operator>=(const Fraction& fraction) {
		return !(*this < fraction);
	}

    operator string() const {
        stringstream sout;
        sout << numerator << "\\" << denominator;
        return sout.str();
    }

    friend decltype(cout)& operator<<(decltype(cout)&, const Fraction& fract);
};

decltype(cout)& operator<<(decltype(cout)&, const Fraction& fract) {
    cout << (string)fract;
    return cout;
}

void testFractionTask3() {
    Fraction fract1(3, 7);
    Fraction fract2(9, 2);

    cout 
        << "3/7: " << fract1 << endl
        << "-3/7: " << -fract1 << endl
        << "3/7 + 9/2: " << fract1 + fract2 << endl
        << "3/7 - 9/2: " << fract1 - fract2 << endl
        << "3/7 * 9/2: " << fract1 * fract2 << endl
        << "3/7 / 9/2: " << fract1 / fract2 << endl

        << "3/7 == 9/2: " << (fract1 == fract2) << endl
        << "3/7 == 3/7: " << (fract1 == fract1) << endl
		<< "3/7 != 9/2: " << (fract1 != fract2) << endl
		<< "3/7 != 3/7: " << (fract1 != fract1) << endl

        << "3/7 < 9/2: " << (fract1 < fract2) << endl
        << "3/7 <= 9/2: " << (fract1 <= fract2) << endl
        << "3/7 > 9/2: " << (fract1 > fract2) << endl
        << "3/7 >= 9/2: " << (fract1 >= fract2) << endl
        ;
}

//// Task4
struct Card {
    enum class Suit : char {
        bubi = 'b',
        piki = 'p',
        tref = 't',
        cher = 'c'
    };
    enum class Value : char {
        two = 2,
        three = 3,
        four = 4,
        five = 5,
        six = 6,
        seven = 7,
        eight = 8,
        nine = 9,
        ten = 10,
        valet = 'v',
        lady = 'l',
        king = 'k',
        ace = 'a',
    };
    Suit suit;
    Value value;
    bool position;

    Card(Suit suit, Value value, bool position = false): suit{suit}, value{value}, position{position} {}

    void Flip() {
        position = !position;
    }

    int GetValue() {
        if (value == Value::ace)
            return 1;
        else if (value == Value::valet
                 || value == Value::lady
                 || value == Value::king)
            return 10;
        else return static_cast<int>(value);
    }
};

void testCardTask4() {
    Card card(Card::Suit::bubi, Card::Value::king);
    cout << "card position: " << card.position << endl;
    card.Flip();
    cout << "card.position (afterFlip): " << card.position << endl;
    cout << "card.GetValue(): " << card.GetValue() << endl;
}

int main()
{
	


    Parallelogram parallelogram(3, 4, 0.5);
    Circle circle(4);
	Rectangle rectangle(3, 4);
	Square square(5);
	Rhombus rhombus(3, 0.5);

    cout << "\n--------- Task1 -------------\n";
    cout 
        << "parallelogram.area(): " << parallelogram.area() << endl
        << "circle.area(): " << circle.area() << endl
        << "rectangle.area(): " << rectangle.area() << endl
        << "square.area(): " << square.area() << endl
        << "rhombus.area(): " << rhombus.area() << endl
        ;

    cout << "\n--------- Task2 -------------\n";
    cout << "Create Minivan:\n";
    Minivan minivan;
    cout << "\nCreate PassengerCar:\n";
    PassengerCar pass;
	cout << "\nCreate Bus:\n";
	Bus bus;

    cout << "\n--------- Task3 -------------\n";
    testFractionTask3();

	cout << "\n--------- Task4 -------------\n";
	testCardTask4();
}
