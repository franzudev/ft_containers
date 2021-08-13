#pragma once

#include "TestHelper.hpp"

template <class T>
struct StackTester {
	ft::stack<T> &stack;

	StackTester(std::string msg, ft::stack <T> &stack): stack(stack) {
		std::cout << msg << std::endl;
	};

	void printStack() {
		std::cout << stack.top() << std::endl;
	}

	void	printSizes() {
		std::cout << std::endl;
		std::cout << "Size: 	" << stack.size() << std::endl;
		std::cout << "Empty: " << stack.empty() << std::endl;
		std::cout << std::endl;
	}

	void	testPush(T value) {
		printSizes();
		stack.push(value);
		printSizes();
		printStack();

		for (size_t i = 0; i < 5; i++)
			stack.push(value);
		printSizes();
		printStack();
	}

	void	testPop() {
		printSizes();
		stack.pop();
		printSizes();
		printStack();

		for (size_t i = 0; i < 5; i++)
			stack.pop();
		printSizes();
		printStack();
	}

	void	testTop() {
		printSizes();
		stack.top();
		printSizes();
		printStack();
	}

private:
	StackTester();
};

template <typename T>
void	testStackFunctions(std::string  msg, ft::stack<T> &toTest)
{
	StackTester<T>	tester(msg, toTest);
	T randArray[TEST_ARR_SIZE];
	for (unsigned int i = 0; i < TEST_ARR_SIZE; ++i)
		randArray[i] = generateVal<T>(i);

	tester.testPush(generateVal<T>(545));
	tester.testPush(generateVal<T>(54));
	tester.testPop();
	tester.testTop();
}

template <class T>
void	testStackConstructors(std::string msg)
 {
 	ft::stack<T> toTest;
 	StackTester<T>	tester(msg, toTest);
 	T randArray[TEST_ARR_SIZE];
 	for (unsigned int i = 0; i < TEST_ARR_SIZE; ++i)
 		randArray[i] = generateVal<T>(i);
	for (size_t i = 0; i < TEST_ARR_SIZE; i++)
		toTest.push(generateVal<T>(i));
	testStackFunctions(msg, toTest);
 	ft::stack<T>	vec0;
 	ft::stack<T>	stdVec1;
 	ft::stack<T>	stdVec2;
 	testStackFunctions<T>(msg, vec0);
 	ft::stack<T>	vec1(stdVec1);
 	testStackFunctions<T>(msg, vec1);
 	ft::stack<T>	vec2 = stdVec2;
 	testStackFunctions<T>(msg, vec2);
 	vec2 = vec0;
 	testStackFunctions<T>(msg, vec2);
 	vec2 = stdVec2;
 	testStackFunctions<T>(msg, vec2);
 }
