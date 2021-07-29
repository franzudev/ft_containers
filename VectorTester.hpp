#pragma once

#define TEST_ARR_SIZE 10

#ifdef USE_STL
# define STL "std: "
# include <iterator>
# include <vector>
# include <array>
# include <set>
namespace ft = std;
#else
# define STL "ft: "
# include "Bureaucrat.hpp"
# include "iterator.hpp"
# include "vector.hpp"
# include "is_integral.hpp"
#endif

#include <iostream>
#include "Timer.hpp"

template <class T>
struct VectorTester {
	ft::vector<T> &vector;

	VectorTester(std::string msg, ft::vector <T> &vector): vector(vector) {
		std::cout << msg << std::endl;
	};

	void printVector() {
		for (typename ft::vector<T>::iterator start = vector.begin(); start != vector.end(); start++)
			std::cout << *start;
		std::cout << std::endl;
	}

	void	printSizes() {
		std::cout << std::endl;
		std::cout << "Size: 	" << vector.size() << std::endl;
//		std::cout << "Capacity: " << vector.capacity() << std::endl;
		std::cout << "Max_size: " << vector.max_size() << std::endl;
		std::cout << "Empty: " << vector.empty() << std::endl;
		std::cout << std::endl;
	}

	void testIterators()
	{
		Timer	test("IterTest");
		typename ft::vector<T>::iterator			it;
		typename ft::vector<T>::reverse_iterator	rit;


		it = vector.begin();
		rit = vector.rbegin();
		typename ft::vector<T>::iterator			itCp(it);
		if (it == itCp)
			std::cout << "equal" << std::endl;
		typename ft::vector<T>::reverse_iterator	ritCp(rit);
		if (rit == ritCp)
			std::cout << "equal" << std::endl;
		// --- Iterations
		while (it != vector.end())
		{
			std::cout << *it << std::endl;
			it++;
		}
		while (rit != vector.rend())
		{
			std::cout << *rit << std::endl;
			rit++;
		}
		it = vector.end();
		rit = vector.rend();
		while (it != vector.begin())
		{
			if (it != vector.end())
				std::cout << *it << std::endl;
			it--;
		}
		while (rit != vector.rbegin())
		{
			if (rit != vector.rend())
				std::cout << *rit << std::endl;
			rit--;
		}
		// --- operations
		it = vector.end();
		rit = vector.rend();
		it--;
		rit--;
		it += 1;
		rit += 1;
		it -= 1;
		rit -= 1;
		it + 1;
		it - 1;
		rit + 1;
		rit - 1;
		typename ft::vector<T>::iterator			*itPointer;
		it = vector.begin();
		itPointer = &it;
		if (vector.size())
			std::cout << **itPointer << std::endl;
		// --- ConstIterators
		if (vector.size())
		{
			it = vector.begin();
			rit = vector.rbegin();

			typename ft::vector<T>::const_iterator cit;
			typename ft::vector<T>::const_reverse_iterator rcit;

			
			cit = vector.begin();
			rcit = vector.rbegin();
			*it = *cit;
			*rit = *rcit;
			std::cout << *it << *rit << std::endl;
			std::cout << *cit << *rcit << std::endl;
			while (cit != vector.end())
			{
				cit++;
			}
			while (rcit != vector.rend())
			{
				rcit++;
			}
		}
		test.getDiff();
	}
	template<class InputIterator>
	void	testTemplatedAssign(InputIterator first, InputIterator last) {
		printSizes();
		Timer test(std::string(STL) + "Testing templated assign(InputIterator, InputIterator) ");
		vector.assign(first, last);
		test.getDiff();
		for (InputIterator start = first; start != last; start++)
			std::cout << *start << std::endl;
		printSizes();
		printVector();
	}

	void	testSizedAssign(size_t n, const T& val) {
		printSizes();
		Timer test(std::string(STL) +"Testing assign(size_t, const T&) ");
		vector.assign(n, val);
		test.getDiff();
		printSizes();
		printVector();
	}

	void	testPushBack(T &value) {
		printSizes();
		Timer test(std::string(STL) +"Testing push_back(T value) single ");
		vector.push_back(value);
		test.getDiff();
		printSizes();
		printVector();

		Timer test2(std::string(STL) +"Testing push_back(T value) with 1000 iterations ");
		for (size_t i = 0; i < 5; i++)
			vector.push_back(value);
		test2.getDiff();
		printSizes();
		printVector();
	}

	void	testPopBack() {
		printSizes();
		Timer test(std::string(STL) + "Testing pop_back(T value) single ");
		vector.pop_back();
		test.getDiff();
		printSizes();
		printVector();

		Timer test2(std::string(STL) + "Testing pop_back(T value) with 1000 iterations ");
		for (size_t i = 0; i < 10; i++)
			vector.pop_back();
		test2.getDiff();
		printSizes();
		printVector();
	}

	void	testSingleInsert(const T& value) {
		printSizes();
		Timer test(std::string(STL) + "Testing insert(iterator, T&) single ");
		vector.insert(vector.begin(), value);
		test.getDiff();
		printSizes();

		Timer test2(std::string(STL) + "Testing insert(iterator, T&) with 1000 iterations ");
		typename ft::vector<T>::iterator it = vector.begin();
		for (size_t i = 0; i < 10; i++)
			it = vector.insert(it, value);
		test2.getDiff();
		printSizes();
		printVector();
	}

	void	testSizedInsert(size_t n, const T& val) {
		printSizes();
		Timer test(std::string(STL) + "Testing insert(iterator, size_t, const T&");
		vector.insert(vector.end(), n, val);
		test.getDiff();
		printSizes();
		printVector();
	}

	template<class InputIterator>
	void	testIteratorsInsert(InputIterator first, InputIterator last) {
		printSizes();
		Timer test(std::string(STL) + "Testing insert(iterator, inputIterator, inputIterator)");
		vector.insert(vector.begin(), first, last);
		test.getDiff();
		printSizes();
		printVector();
	}

	void	testErase() {
		printSizes();
		Timer test(std::string(STL) + "Testing erase(iterator)");
		vector.erase(vector.begin());
//		vector.erase(vector.begin() + 10);
		test.getDiff();
		printSizes();
//		printVector();
	}

	void	testEraseIterators() {
		printSizes();
		Timer test(std::string(STL) + "Testing erase(iterator, iterator)");
		vector.erase(vector.begin(), vector.begin() + 10);
		test.getDiff();
		printSizes();
		printVector();
	}

	void	testSwap(ft::vector<T> second) {
		printSizes();
		Timer test(std::string(STL) + "Testing swap(ft::vector)");
		vector.swap(second);
		test.getDiff();
		printSizes();
		printVector();
	}

	void	testResize(size_t n) {
		printSizes();
		Timer test(std::string(STL) + "Testing resize(size_t)");
		vector.resize(n);
		test.getDiff();
		printSizes();
		printVector();
	}

	void	clearVector() {
		printSizes();
		Timer test("Testing clear() ");
		test.getDiff();
		printSizes();
	}

private:
	VectorTester();
};

template<class Tp>
struct is_string : public std::false_type {};
template<>
struct is_string<std::string> : public std::true_type {};

template<typename T>
T	generateVal(unsigned int index, typename ft::enable_if<ft::is_integral<T>::value, T>::type* = 0) {
	return T(index);
}

template<typename T>
T	generateVal(unsigned int index, typename ft::enable_if<!ft::is_integral<T>::value && !is_string<T>::value, T>::type* = 0) {
	return T(index);
}

template<typename T>
std::string	generateVal(unsigned int index, typename ft::enable_if<is_string<T>::value, T>::type* = 0) {
	std::string arr[] = {"aaa", "bbb", "ccc", "ddd", "eee", "fff", "ggg", "hhh", "iii"};
	return T(arr[index % 9]);
}

template <typename T>
void	testFunctions(std::string  msg, ft::vector<T> &toTest)
{
	VectorTester<T>	tester(std::string(STL) + msg, toTest);
	tester.testIterators();
	T randArray[TEST_ARR_SIZE];
	for (unsigned int i = 0; i < TEST_ARR_SIZE; ++i)
		randArray[i] = generateVal<T>(i);
	ft::vector<T> vectorItTest(std::begin(randArray), std::end(randArray));

	tester.testTemplatedAssign(std::begin(randArray), std::end(randArray));
	tester.clearVector();
	tester.testSizedAssign(100, generateVal<T>(1));
	tester.testPushBack(*(vectorItTest.begin() + 4));
	tester.clearVector();
	tester.testPushBack(*(vectorItTest.begin() + 6));
	tester.testPopBack();
	tester.testSingleInsert(generateVal<T>(4));
	tester.testSizedInsert(10, generateVal<T>(5));
	tester.testIteratorsInsert(vectorItTest.begin(), vectorItTest.end());
	std::cout << "Is == " << (toTest == vectorItTest) << std::endl;
	std::cout << "Is <  " << (toTest < vectorItTest) << std::endl;
	std::cout << "Is <= " << (toTest <= vectorItTest) << std::endl;
	std::cout << "Is >  " << (toTest > vectorItTest) << std::endl;
	std::cout << "Is >= " << (toTest >= vectorItTest) << std::endl;
	tester.testErase();
	tester.testEraseIterators();
}

void	stringTestFunctions(std::string  msg, ft::vector<std::string> &toTest)
{
	VectorTester<std::string>	tester(std::string(STL) + msg, toTest);
	std::string randArray[TEST_ARR_SIZE];
	for (unsigned int i = 0; i < TEST_ARR_SIZE; ++i)
		randArray[i] = std::to_string(i);
	ft::vector<std::string> vectorItTest(std::begin(randArray), std::end(randArray));

	tester.testTemplatedAssign(std::begin(randArray), std::end(randArray));
	tester.clearVector();
	tester.testSizedAssign(100, std::to_string(1));
	tester.testPushBack(*(vectorItTest.begin() + 4));
	tester.clearVector();
	tester.testPushBack(*(vectorItTest.begin() + 6));
	tester.testPopBack();
	tester.testSingleInsert(std::to_string(4));
	tester.testSizedInsert(10, std::to_string(5));
	tester.testIteratorsInsert(vectorItTest.begin(), vectorItTest.end());
	std::cout << "Is == " << (toTest == vectorItTest) << std::endl;
	std::cout << "Is <  " << (toTest < vectorItTest) << std::endl;
	std::cout << "Is <= " << (toTest <= vectorItTest) << std::endl;
	std::cout << "Is >  " << (toTest > vectorItTest) << std::endl;
	std::cout << "Is >= " << (toTest >= vectorItTest) << std::endl;
	tester.testErase();
	tester.testEraseIterators();
}

template <class T>
void	testConstructors(std::string msg)
 {
 	ft::vector<T> toTest;
 	VectorTester<T>	tester(std::string(STL) + msg, toTest);
 	T randArray[TEST_ARR_SIZE];
 	for (unsigned int i = 0; i < TEST_ARR_SIZE; ++i)
 		randArray[i] = generateVal<T>(i);
	for (size_t i = 0; i < TEST_ARR_SIZE; i++)
		toTest.push_back(generateVal<T>(i));
	testFunctions(msg, toTest);
 	ft::vector<T> vectorItTest(std::begin(randArray), std::end(randArray));
 	ft::vector<T>	vec0;
 	ft::vector<T>	stdVec1;
 	ft::vector<T>	stdVec2;
 	testFunctions<T>(msg, vec0);
 	ft::vector<T>	vec1(stdVec1);
 	testFunctions<T>(msg, vec1);
 	ft::vector<T>	vec2 = stdVec2;
 	testFunctions<T>(msg, vec2);
 	vec2 = vec0;
 	testFunctions<T>(msg, vec2);
 	vec2 = stdVec2;
 	testFunctions<T>(msg, vec2);
 }
