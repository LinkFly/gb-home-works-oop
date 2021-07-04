// gb-oop-homework-2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <cstdint>
#include <vector>
#include <algorithm>
#include <cctype>
#include <map>

using namespace std;

///////////////// Task 1 //////////////////
struct Person {
	enum class EGender : char {
		M = 'M',
		F = 'F'
	};
private:
    string name;
    uint8_t age;
    EGender gender;
    uint16_t weight;
public:
    Person(const string& name, uint8_t age, EGender gender, uint16_t weight)
        : name{ name }, age{ age }, gender{ gender }, weight{ weight }
    {}

    void setName(const string& name) {
        this->name = name;
    }

    void setAge(uint8_t age) {
        this->age = age;
    }

    void setWeight(uint16_t weight) {
        this->weight = weight;
    }

    auto getName() { return name; }
    auto getAge() { return age; }
    auto getGender() { return gender; }
    auto getWeight() { return weight; }

};

class Student: public Person {
    uint8_t yearsOfStudy;
public:
    static uint32_t studentsCount;
    Student(const string& name, uint8_t age, Person::EGender gender, uint16_t weight, uint8_t yearsOfStudy = 0)
        : Person(name, age, gender, yearsOfStudy)
    {
        this->yearsOfStudy = yearsOfStudy;
        ++studentsCount;
    }
    void setYearsOfStudy(uint8_t years) {
        yearsOfStudy = years;
    }

    void incYearsOfStudy(uint8_t addYears = 1) {
        yearsOfStudy += addYears;
    }
    
    auto getYearsOfStudy() { return yearsOfStudy; }

    void print() {
        cout 
            << "Student: name = " << getName() 
            << ", age = " << getAge() 
            << ", gender = " << ([](Person::EGender gender)
                                {
                                    if (gender == Person::EGender::M) return "male";
                                    else if (gender == Person::EGender::F) return "female";
                                    else return "<unknown>";
                                })(getGender())
            << ", weight = " << getWeight()
            << ", yearsOfStudy = " << getYearsOfStudy()
            << endl;
    }
};

uint32_t Student::studentsCount = 0;
///////////////// end Task 1 //////////////////

///////////////// Task 2 //////////////////
inline constexpr uint8_t operator"" _uc(unsigned long long arg) {
    return static_cast<uint8_t>(arg);
}

struct Fruit {
	struct Color {
        uint8_t r, g, b;
        Color() = default;
        Color(uint8_t r, uint8_t g, uint8_t b): r{r}, g{g}, b{b} {}
        Color(const string& colorName) {
            static map<string, Color> mapColors = {{
                {"red", {255_uc, 0_uc, 0_uc}},
                {"green", {0_uc, 255_uc, 0_uc}},
                {"blue", {0_uc, 0_uc, 255_uc}},
                {"yellow", {255_uc, 255_uc, 0_uc}}
            }};
            *this = mapColors[colorName];
        }

        operator string() {
			static map<vector<uint8_t>, string> mapColors = {{
		        {{255_uc, 0_uc, 0_uc}, "red"},
		        {{0_uc, 255_uc, 0_uc}, "green"},
		        {{0_uc, 0_uc, 255_uc}, "blue"},
                {{255_uc, 255_uc, 0_uc}, "yellow"}
	        }};
            return mapColors[{r, g, b}];
        }
	};
protected:
    string name;
    Color color;
public:
    Fruit(const string& name, const Color& color): name{name}, color{color}
    {}
    string getName() { return name; }
    string getColor() { return color; }
};


struct Apple : public Fruit {
    Apple(const string& color): Fruit{"apple", Color{color}} {}
};

struct Banana : public Fruit {
    Banana(): Fruit{ "banana", Color{"yellow"} } {}
};

struct GrannySmith : public Fruit {
    GrannySmith(): Fruit{ "Granny Smith apple", Color{"green"} } {}
};
///////////////// end Task 2 //////////////////

///////////////// Task 3 //////////////////
/*
******************
Задание: Изучить правила игры в Blackjack. Подумать, как написать данную игру на С++, используя 
объектно-ориентированное программирование. Сколько будет классов в программе? Какие классы 
будут базовыми, а какие производными? Продумать реализацию игры с помощью классов и записать 
результаты.
******************

 - Расписать все состояния игры
 - Расписать типы действий игрока
 - Расписать условия при которых доступны те или иные действия
 - Определить перечисление соответствующее типом карт
 - Классы (базовые/производные):
    - Game
		- GameState
		    - AccessibleGameState
    - Logic
	- Action
		- AccessibleAction
    - CommonPlayer
       - Diller
            - AIDiller
       - Player
    - Card


        За общее управление игрой отвечает класс Game. Он содержит и активно взаимодействует с классом
    AccessibleGameState, настраивая состояние игры и передавая ход либо экземпляру класса AIDiller 
    либо экземпляру класса HumanPlayer. Экзмепляры игроков (экземпляры класса, производного от
    CommonPlayer сожержат экземпляр класса AccessibleAction, который определяет действия в соотв.
    с классом AccessibleGameState (прозиводный класс от GameState, причём GameState включает все
    возможные состояния игры, а AccessibleGameState только возможные состояния игры.
    Класс Logic содержит алгоритмы вычисления доступных состояний и действий.
*/
///////////////// end Task 3 //////////////////

int main()
{
    // Task1
    cout << "Task1:\n----------------------\n";
    vector<Student> students{
        { "Mike", 21, Person::EGender::M, 50 },
        { "Mike", 20, Person::EGender::M, 60 },
        { "Mike", 18, Person::EGender::F, 45 }
    };

	auto strToLower = [](const string& str) {
        string res;
        res.reserve(str.size());
        for (char ch : str) {
            res += tolower(ch);
        }
        return res;
	};

    auto studentsSearcher = [&students, &strToLower](const string& name) -> Student* {
        for(auto& student : students)
            if (strToLower(student.getName()) == strToLower(name)) {
                return &student;
            }
        return nullptr;
    };

    Student* foundStudent;
    string searchStudentName;
    while(true) {
		cout << "Enter student name for find: ";
		cin >> searchStudentName;
        if (searchStudentName.empty()) {
            cout << "Bad student name, try again\n";
            continue;
        }

        foundStudent = studentsSearcher(searchStudentName);
        if (foundStudent != nullptr) {
            foundStudent->print();
            break;
        }
        else {
            cout << "Student not found, try again\n";
            continue;
        }
    };
    cout << endl;

    // Task2
    cout << "Task2:\n----------------------\n";
	Apple a("red");
	Banana b;
	GrannySmith c;

	std::cout << "My " << a.getName() << " is " << a.getColor() << ".\n";
	std::cout << "My " << b.getName() << " is " << b.getColor() << ".\n";
	std::cout << "My " << c.getName() << " is " << c.getColor() << ".\n";

    // Task3
    cout << "Task3:\n----------------------\n";
}
