#ifndef STACK_HPP
#define STACK_HPP

#include "ArraySequence.hpp"
#include <stdexcept>
#include <functional>
#include <string>
#include <sstream>

using FunctionType = std::function<int(int)>;

class Person {
protected:
    std::string firstName;
    std::string middleName;
    std::string lastName;
    time_t birthDate;

public:
    Person() : firstName(""), middleName(""), lastName(""), birthDate(0) {}

    Person(const std::string& first, const std::string& middle,
        const std::string& last, time_t birth)
        : firstName(first), middleName(middle), lastName(last), birthDate(birth) {
    }
    virtual ~Person() = default;

    std::string GetFirstName() const { return firstName; }
    std::string GetMiddleName() const { return middleName; }
    std::string GetLastName() const { return lastName; }
    std::string GetFullName() const { return firstName + " " + middleName + " " + lastName; }
    time_t GetBirthDate() const { return birthDate; }

    virtual std::string GetID() const = 0;
    virtual std::string ToString() const = 0;
};

class Student : public Person {
    std::string studentID;

public:
    Student() : Person("", "", "", 0), studentID("") {}

    Student(const std::string& first, const std::string& middle, const std::string& last,
        time_t birth, const std::string& id)
        : Person(first, middle, last, birth), studentID(id) {
    }

    std::string GetID() const override { return studentID; }
    std::string ToString() const override {
        return "Student: " + GetFullName() + ", ID: " + studentID;
    }
};

class Professor : public Person {
    std::string professorID;

public:
    Professor() : Person("", "", "", 0), professorID("") {}

    Professor(const std::string& first, const std::string& middle, const std::string& last,
        time_t birth, const std::string& id)
        : Person(first, middle, last, birth), professorID(id) {
    }

    std::string GetID() const override { return professorID; }
    std::string ToString() const override {
        return "Professor: " + GetFullName() + ", ID: " + professorID;
    }
};
struct Complex {
    double real;
    double imag;

    Complex() : real(0.0), imag(0.0) {}
    Complex(double r, double i) : real(r), imag(i) {}

    std::string ToString() const {
        std::ostringstream oss;
        oss << real;
        if (imag >= 0) oss << "+";
        oss << imag << "i";
        return oss.str();
    }
};


template <typename T>
class Stack {
private:
    MutableArraySequence<T>* sequence;

public:
    Stack() : sequence(new MutableArraySequence<T>()) {}
    Stack(const Stack& other) : sequence(new MutableArraySequence<T>(*other.sequence)) {}
    ~Stack() { delete sequence; }

    void Push(T item) {
        sequence->AppendImpl(item);
    }

    T Pop() {
        if (IsEmpty()) {
            throw std::out_of_range("Stack is empty");
        }


        T item = sequence->GetLast();


        MutableArraySequence<T>* temp = new MutableArraySequence<T>();
        if (sequence->GetLength() > 1) {
            ArraySequence<T>* sub = sequence->GetSubsequence(0, sequence->GetLength() - 2);
            for (int i = 0; i < sub->GetLength(); i++) {
                temp->AppendImpl(sub->Get(i));
            }
            delete sub;
        }


        delete sequence;
        sequence = temp;

        return item;
    }

    T Peek() const {
        if (IsEmpty()) {
            throw std::out_of_range("Stack is empty");
        }
        return sequence->GetLast();
    }

    bool IsEmpty() const {
        return sequence->GetLength() == 0;
    }

    size_t Size() const {
        return sequence->GetLength();
    }

    void Clear() {
        delete sequence;
        sequence = new MutableArraySequence<T>();
    }
};

#endif 
