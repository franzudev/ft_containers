#pragma once

#include "TestHelper.hpp"

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
	}
	template<class InputIterator>
	void	testTemplatedAssign(InputIterator first, InputIterator last) {
		printSizes();
		std::cout << "Testing templated assign(InputIterator, InputIterator) " << std::endl;
		vector.assign(first, last);
		for (InputIterator start = first; start != last; start++)
			std::cout << *start << std::endl;
		printSizes();
		printVector();
	}

	void	testSizedAssign(size_t n, const T& val) {
		printSizes();
		std::cout << "Testing assign(size_t, const T&) " << std::endl;
		vector.assign(n, val);
		printSizes();
		printVector();
	}

	void	testPushBack(T &value) {
		printSizes();
		vector.push_back(value);
		printSizes();
		printVector();

		for (size_t i = 0; i < 5; i++)
			vector.push_back(value);
		printSizes();
		printVector();
	}

	void	testPopBack() {
		printSizes();
		vector.pop_back();
		printSizes();
		printVector();

		for (size_t i = 0; i < 5; i++)
			vector.pop_back();
		printSizes();
		printVector();
	}

	void	testSingleInsert(const T& value) {
		printSizes();
		vector.insert(vector.begin(), value);
		printSizes();

		typename ft::vector<T>::iterator it = vector.begin();
		for (size_t i = 0; i < 10; i++)
			it = vector.insert(it, value);
		printSizes();
		printVector();
	}

	void	testSizedInsert(size_t n, const T& val) {
		printSizes();
		vector.insert(vector.end(), n, val);
		printSizes();
		printVector();
	}

	template<class InputIterator>
	void	testIteratorsInsert(InputIterator first, InputIterator last) {
		printSizes();
		vector.insert(vector.begin(), first, last);
		printSizes();
		printVector();
	}

	void	testErase() {
		printSizes();
		vector.erase(vector.begin());
//		vector.erase(vector.begin() + 10);
		printSizes();
		printVector();
	}

	void	testEraseIterators() {
		printSizes();
		vector.erase(vector.begin(), vector.begin() + 10);
		printSizes();
		printVector();
	}

	void	testSwap(ft::vector<T> second) {
		printSizes();
		vector.swap(second);
		printSizes();
		printVector();
	}

	void	testResize(size_t n) {
		printSizes();
		vector.resize(n);
		printSizes();
		printVector();
	}

	void	clearVector() {
		printSizes();
		vector.clear();
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
	VectorTester<T>	tester(msg, toTest);
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
	tester.testResize(1);
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
 	VectorTester<T>	tester(msg, toTest);
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
