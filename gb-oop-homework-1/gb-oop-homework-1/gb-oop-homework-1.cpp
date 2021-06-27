// gb-oop-homework-1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cmath>
#include <cstdint>

using namespace std;

// Task1
class Power {
    double d1, d2;
public:
    void set(double d1, double d2) {
        this->d1 = d1;
        this->d2 = d2;
    }
    double calculate() {
        return pow(d1, d2);
    }
};

// Task2
struct RGBA {
public:
    uint8_t m_red = 0;
    uint8_t m_green = 0;
    uint8_t m_blue = 0;
    uint8_t m_alpha = 255;
    RGBA() = default;
    RGBA(uint8_t m_red, uint8_t m_green, uint8_t m_blue, uint8_t m_alpha)
        : m_red{m_red}, m_green{m_green}, m_blue{m_blue}, m_alpha{m_alpha} 
    {}
    void print() {
        cout
            << "m_red = " << m_red << '\n'
            << "m_green = " << m_green << '\n'
            << "m_blue = " << m_blue << '\n'
            << "m_alpha = " << m_alpha << '\n'
            << endl;
    }
};

// Task3

class Stack {
    int ints[10];
    size_t len = 0;
public:
	void reset() {
		for (int & i : ints) {
			i = 0;
		}
		len = 0;
	}
    bool push(int val) {
        if (len == sizeof(ints) / sizeof(int))
            return false;
        ints[len] = val;
        ++len;
        return true;
    }
    int pop() {
        if (len == 0) {
            cout << "Warning! Stack is empty" << endl;
            return 0;
        }
        return ints[--len];
    }
    void print() {
        cout << "( ";
        for(size_t i = 0; i < len; ++i)
            cout << ints[i] << ' ';
        cout << ")" << endl;
    }
};

int main()
{
	Stack stack;
	stack.reset();
	stack.print();

	stack.push(3);
	stack.push(7);
	stack.push(5);
	stack.print();

	stack.pop();
	stack.print();

	stack.pop();
	stack.pop();
	stack.print();

	return 0;
}
