#pragma once

#include "TestHelper.hpp"

template <class T>
struct SetTester {
	ft::set<T> &set;

	SetTester(std::string msg, ft::set <T> &set): set(set) {
		std::cout << msg << std::endl;
	};

	void printSet() {
		for (typename ft::set<T>::iterator start = set.begin(); start != set.end(); start++)
			std::cout << *start;
		std::cout << std::endl;
	}

	void	printSizes() {
		std::cout << std::endl;
		std::cout << "Size: 	" << set.size() << std::endl;
//		std::cout << "Capacity: " << set.capacity() << std::endl;
		std::cout << "Max_size: " << set.max_size() << std::endl;
		std::cout << "Empty: " << set.empty() << std::endl;
		std::cout << std::endl;
	}

	void testIterators()
	{
		if (set.empty())
			return ;
		typename ft::set<T>::iterator			it;
		typename ft::set<T>::reverse_iterator	rit;


		it = set.begin();
		typename ft::set<T>::iterator			itCp(it);
		if (it == itCp)
			std::cout << "equal" << std::endl;
		// --- Iterations
		while (it != set.end())
		{
			std::cout << *it << std::endl;
			it++;
		}
		it = set.end();
		while (it != set.begin())
		{
			if (it != set.end())
				std::cout << *it << std::endl;
			it--;
		}
		// --- operations
		it = set.end();
		rit = set.rend();
		if (set.size())
			it--;
		typename ft::set<T>::iterator			*itPointer;
		it = set.begin();
		itPointer = &it;
		if (set.size())
			std::cout << **itPointer << std::endl;
		// --- ConstIterators
		if (set.size())
		{
			it = set.begin();
			rit = set.rbegin();

			typename ft::set<T>::const_iterator cit;
			typename ft::set<T>::const_reverse_iterator rcit;

			cit = set.begin();
			rcit = set.rbegin();
			std::cout << *it << *rit << std::endl;
			std::cout << *cit << *rcit << std::endl;
			while (cit != set.end())
			{
				cit++;
			}
			while (rcit != set.rend())
			{
				rcit++;
			}
		}
	}

	void	testPushBack(T &value) {
		printSizes();
		set.push_back(value);
		printSizes();
		printSet();

		for (size_t i = 0; i < 5; i++)
			set.push_back(value);
		printSizes();
		printSet();
	}

	void	testSingleInsert(const T& value) {
		printSizes();
		set.insert(set.begin(), value);
		printSizes();

		typename ft::set<T>::iterator it = set.begin();
		for (size_t i = 0; i < 10; i++)
			it = set.insert(it, value);
		printSizes();
		printSet();
	}

	void	testSizedInsert(const T& val) {
		printSizes();
		set.insert(set.end(), val);
		printSizes();
		printSet();
	}

	template<class InputIterator>
	void	testIteratorsInsert(InputIterator first, InputIterator last) {
		printSizes();
		set.insert(first, last);
		printSizes();
		printSet();
	}

	void	testCount() {
		for (size_t i = 0; i < TEST_ARR_SIZE; ++i) {
			set.count(i);
		}
	}

	void	testFind() {
		for (size_t i = 0; i < TEST_ARR_SIZE; ++i) {
			if (set.find(i) != set.end())
				std::cout << "found " << i << std::endl;
		}
	}

	void 	testBounds() {
		typename ft::set<T>::iterator it;
		for (size_t i = 0; i < TEST_ARR_SIZE - 1; ++i) {
			try {
				it = set.lower_bound(i);
				std::cout << *it << std::endl;
			} catch(std::exception &e) {
				std::cout << e.what() << std::endl;
			}
		}
		for (size_t i = 0; i < TEST_ARR_SIZE - 1; ++i) {
			try {
				it = set.upper_bound(i);
				std::cout << *it << std::endl;
			} catch(std::exception &e) {
				std::cout << e.what() << std::endl;
			}
		}
	}

	void 	testEqualRange() {

		for (size_t i = 0; i < TEST_ARR_SIZE; ++i) {
			ft::pair<typename ft::set<T>::iterator,typename ft::set<T>::iterator> pair;
			try {
				pair = set.equal_range(i);
				if (pair.first == pair.second)
					std::cout << pair.first << std::endl;
			} catch(std::exception &e) {
				std::cout << e.what() << std::endl;
			}
		}
	}

	void	testErase() {
		printSizes();
		set.erase(set.begin());
//		set.erase(set.begin() + 10);
		printSizes();
		printSet();
	}

	void	testEraseIterators() {
		printSizes();
		set.erase(set.begin(), set.end());
		printSizes();
		printSet();
	}

	void	testSwap(ft::set<T> second) {
		printSizes();
		set.swap(second);
		printSizes();
		printSet();
	}


	void	clearSet() {
		printSizes();
		set.clear();
		printSizes();
	}

private:
	SetTester();
};

template <typename T>
void	setTestFunctions(std::string  msg, ft::set<T> &toTest)
{
	SetTester<T>	tester(msg, toTest);
	tester.testIterators();
	T randArray[TEST_ARR_SIZE];
	for (unsigned int i = 0; i < TEST_ARR_SIZE; ++i)
		randArray[i] = generateVal<T>(i);
	ft::set<T> setItTest(std::begin(randArray), std::end(randArray));

	tester.clearSet();
	tester.clearSet();
	tester.testSingleInsert(generateVal<T>(4));
	tester.testSizedInsert(generateVal<T>(5));
	tester.testIteratorsInsert(setItTest.begin(), setItTest.end());
	std::cout << "Is == " << (toTest == setItTest) << std::endl;
	std::cout << "Is <  " << (toTest < setItTest) << std::endl;
	std::cout << "Is <= " << (toTest <= setItTest) << std::endl;
	std::cout << "Is >  " << (toTest > setItTest) << std::endl;
	std::cout << "Is >= " << (toTest >= setItTest) << std::endl;
	tester.testCount();
	tester.testFind();
	tester.testBounds();
	tester.testErase();
	tester.testSwap(setItTest);
	tester.testErase();
	tester.testEraseIterators();
}

void	stringSetTestFunctions(std::string  msg, ft::set<std::string> &toTest)
{
	SetTester<std::string>	tester(std::string(STL) + msg, toTest);
	std::string randArray[TEST_ARR_SIZE];
	for (unsigned int i = 0; i < TEST_ARR_SIZE; ++i)
		randArray[i] = std::to_string(i);
	ft::set<std::string> setItTest(std::begin(randArray), std::end(randArray));

	tester.clearSet();
	tester.clearSet();
	tester.testSingleInsert(std::to_string(4));
	tester.testSizedInsert(std::to_string(5));
	tester.testIteratorsInsert(setItTest.begin(), setItTest.end());
	std::cout << "Is == " << (toTest == setItTest) << std::endl;
	std::cout << "Is <  " << (toTest < setItTest) << std::endl;
	std::cout << "Is <= " << (toTest <= setItTest) << std::endl;
	std::cout << "Is >  " << (toTest > setItTest) << std::endl;
	std::cout << "Is >= " << (toTest >= setItTest) << std::endl;
	tester.testErase();
	tester.testEraseIterators();
}

template <class T>
void	setTestConstructors(std::string msg)
 {
 	ft::set<T> toTest;
 	SetTester<T>	tester(msg, toTest);
 	T randArray[TEST_ARR_SIZE];
 	for (unsigned int i = 0; i < TEST_ARR_SIZE; ++i)
 		randArray[i] = generateVal<T>(i);
	for (size_t i = 0; i < TEST_ARR_SIZE; i++)
		toTest.insert(generateVal<T>(i));
	setTestFunctions(msg, toTest);
 	ft::set<T> setItTest(std::begin(randArray), std::end(randArray));
 	ft::set<T>	vec0;
 	ft::set<T>	stdVec1;
 	ft::set<T>	stdVec2;
 	setTestFunctions<T>(msg, vec0);
 	ft::set<T>	vec1(stdVec1);
 	setTestFunctions<T>(msg, vec1);
 	ft::set<T>	vec2 = stdVec2;
 	setTestFunctions<T>(msg, vec2);
 	vec2 = vec0;
 	setTestFunctions<T>(msg, vec2);
 	vec2 = stdVec2;
 	setTestFunctions<T>(msg, vec2);
 }
