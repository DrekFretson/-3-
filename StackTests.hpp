#ifndef STACK_TESTS_HPP
#define STACK_TESTS_HPP

#include <iostream>
#include <fstream>
#include <ctime>
#include "Stack.h"

void RunTestsFromFile(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream in(inputFile);
    std::ofstream out(outputFile);

    if (!in.is_open() || !out.is_open()) {
        std::cerr << "Error opening files!" << std::endl;
        return;
    }


    Stack<int> intStack;
    int intCount, intValue;
    in >> intCount;
    out << "=== Testing Int Stack (" << intCount << " elements) ===" << std::endl;
    for (int i = 0; i < intCount; ++i) {
        in >> intValue;
        intStack.Push(intValue);
    }
    out << "Top element: " << intStack.Peek() << std::endl;
    out << "Popped elements: ";
    while (!intStack.IsEmpty()) {
        out << intStack.Pop() << " ";
    }
    out << std::endl << std::endl;


    Stack<std::string> stringStack;
    int stringCount;
    std::string stringValue;
    in >> stringCount;
    in.ignore();
    out << "=== Testing String Stack (" << stringCount << " elements) ===" << std::endl;
    for (int i = 0; i < stringCount; ++i) {
        std::getline(in, stringValue);
        stringStack.Push(stringValue);
    }
    out << "Stack contents: ";
    while (!stringStack.IsEmpty()) {
        out << stringStack.Pop() << " ";
    }
    out << std::endl << std::endl;


    Stack<Complex> complexStack;
    int complexCount;
    double real, imag;
    in >> complexCount;
    out << "=== Testing Complex Stack (" << complexCount << " elements) ===" << std::endl;
    for (int i = 0; i < complexCount; ++i) {
        in >> real >> imag;
        complexStack.Push(Complex(real, imag));
    }
    out << "Top complex number: " << complexStack.Peek().ToString() << std::endl;
    complexStack.Pop();
    if (!complexStack.IsEmpty()) {
        out << "Next complex number: " << complexStack.Peek().ToString() << std::endl;
    }
    out << std::endl;


    Stack<Student> studentStack;
    int studentCount;
    std::string firstName, middleName, lastName, id;
    int year, month, day;
    in >> studentCount;
    in.ignore();
    out << "=== Testing Person Stack (" << studentCount << " students) ===" << std::endl;


    for (int i = 0; i < studentCount; ++i) {
        std::getline(in, firstName);
        std::getline(in, middleName);
        std::getline(in, lastName);
        in >> year >> month >> day;
        in.ignore();
        std::getline(in, id);

        struct tm tm = { 0 };
        tm.tm_year = year - 1900;
        tm.tm_mon = month - 1;
        tm.tm_mday = day;
        time_t birthDate = mktime(&tm);

        studentStack.Push(Student(firstName, middleName, lastName, birthDate, id));
    }


    Stack<Student> tempStack;
    while (!studentStack.IsEmpty()) {
        Student current = studentStack.Pop();
        if (current.GetID() != "S12345") {
            tempStack.Push(current);
        }
    }

    while (!tempStack.IsEmpty()) {
        studentStack.Push(tempStack.Pop());
    }


    out << "Students after removal:" << std::endl;
    Stack<Student> printStack = studentStack;
    while (!printStack.IsEmpty()) {
        out << printStack.Pop().ToString() << std::endl;
    }
    out << std::endl;


    out << "=== Error Handling Test ===" << std::endl;
    try {
        Stack<int> emptyStack;
        emptyStack.Pop();
    }
    catch (const std::exception& e) {
        out << "Caught exception: " << e.what() << std::endl;
    }
}


#endif
