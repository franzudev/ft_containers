#pragma once

#include "TestHelper.hpp"

template <class Key, class T>
struct MapTester {
	ft::map<Key, T> &map;

	MapTester(std::string msg, ft::map<Key, T> &map): map(map) {
		std::cout << msg << std::endl;
	};

	void printMap() {
		for (typename ft::map<Key, T>::iterator start = map.begin(); start != map.end(); start++)
			std::cout << "Key: " << start->first << " | Value: " << start->second << std::endl;
		std::cout << std::endl;
	}

	void	printSizes() {
		std::cout << std::endl;
		std::cout << "Size: 	" << map.size() << std::endl;
		std::cout << "Max_size: " << map.max_size() << std::endl;
		std::cout << "Empty: " << map.empty() << std::endl;
		std::cout << std::endl;
	}

	void testIterators()
	{
		if (map.empty())
			return ;
		typename ft::map<Key, T>::iterator			it;
		typename ft::map<Key, T>::reverse_iterator	rit;


		it = map.begin();
		typename ft::map<Key, T>::iterator			itCp(it);
		if (it == itCp)
			std::cout << "equal" << std::endl;
		// --- Iterations
		while (it != map.end())
		{
			std::cout << "Key: " << it->first << " | Value: " << it->second << std::endl;
			it++;
		}
		it = map.end();
		while (it != map.begin())
		{
			if (it != map.end())
				std::cout << "Key: " << it->first << " | Value: " << it->second << std::endl;
			it--;
		}
		// --- operations
		it = map.end();
		rit = map.rend();
		if (map.size())
			it--;
		typename ft::map<Key, T>::iterator			*itPointer;
		it = map.begin();
		itPointer = &it;
		if (map.size())
			std::cout << "Key: " << (*itPointer)->first << " | Value: " << (*itPointer)->second << std::endl;
		// --- ConstIterators
		if (map.size())
		{
			it = map.begin();
			rit = map.rbegin();

			typename ft::map<Key, T>::const_iterator cit;
			typename ft::map<Key, T>::const_reverse_iterator rcit;

			cit = map.begin();
			rcit = map.rbegin();
			std::cout << "Key: " << it->first << " | Value: " << it->second << std::endl;
			std::cout << "Key: " << rit->first << " | Value: " << rit->second << std::endl;
			std::cout << "Key: " << cit->first << " | Value: " << cit->second << std::endl;
			std::cout << "Key: " << rcit->first << " | Value: " << rcit->second << std::endl;
			while (cit != map.end())
			{
				cit++;
			}
			while (rcit != map.rend())
			{
				rcit++;
			}
		}
	}

	void	testPushBack(T &value) {
		printSizes();
		map.push_back(value);
		printSizes();
		printMap();

		for (size_t i = 0; i < 5; i++)
			map.push_back(value);
		printSizes();
		printMap();
	}

	void	testSingleInsert(const ft::pair<Key, T>& value) {
		printSizes();
		map.insert(map.begin(), value);
		printSizes();

		typename ft::map<Key, T>::iterator it = map.begin();
		for (size_t i = 0; i < 10; i++)
			it = map.insert(it, value);
		printSizes();
		printMap();
	}

	void	testSizedInsert(const ft::pair<Key, T>& val) {
		printSizes();
		map.insert(map.end(), val);
		printSizes();
		printMap();
	}

	template<class InputIterator>
	void	testIteratorsInsert(InputIterator first, InputIterator last) {
		printSizes();
		map.insert(first, last);
		printSizes();
		printMap();
	}

	void	testCount() {
		for (size_t i = 0; i < TEST_ARR_SIZE; ++i) {
			map.count(i);
		}
	}

	void	testFind() {
		for (size_t i = 0; i < TEST_ARR_SIZE; ++i) {
			if (map.find(i) != map.end())
				std::cout << "found " << i << std::endl;
		}
	}

	void 	testBounds() {
		typename ft::map<Key, T>::iterator it;
		for (size_t i = 0; i < TEST_ARR_SIZE - 1; ++i) {
			try {
				it = map.lower_bound(i);
				std::cout << "Key: " << it->first << " | Value: " << it->second << std::endl;
			} catch(std::exception &e) {
				std::cout << e.what() << std::endl;
			}
		}
		for (size_t i = 0; i < TEST_ARR_SIZE - 1; ++i) {
			try {
				it = map.upper_bound(i);
				std::cout << "Key: " << it->first << " | Value: " << it->second << std::endl;
			} catch(std::exception &e) {
				std::cout << e.what() << std::endl;
			}
		}
	}

	void 	testEqualRange() {

		for (size_t i = 0; i < TEST_ARR_SIZE; ++i) {
			ft::pair<typename ft::map<Key, T>::iterator,typename ft::map<Key, T>::iterator> pair;
			try {
				pair = map.equal_range(i);
				if (pair.first == pair.second)
					std::cout << "Key: " << pair.first->first << " | Value: " << pair.first->second << std::endl;
			} catch(std::exception &e) {
				std::cout << e.what() << std::endl;
			}
		}
	}

	void	testErase() {
		printSizes();
		map.erase(map.begin());
//		map.erase(map.begin() + 10);
		printSizes();
		printMap();
	}

	void	testEraseIterators() {
		printSizes();
		map.erase(map.begin(), map.end());
		printSizes();
		printMap();
	}

	void	testSwap(ft::map<Key, T> second) {
		printSizes();
		map.swap(second);
		printSizes();
		printMap();
	}


	void	clearMap() {
		printSizes();
		map.clear();
		printSizes();
	}

private:
	MapTester();
};

template <class Key, class T>
void	mapTestFunctions(std::string  msg, ft::map<Key, T> &toTest)
{
	MapTester<Key, T>	tester(msg, toTest);
	tester.testIterators();
	ft::pair<Key, T> randArray[TEST_ARR_SIZE];
	for (unsigned int i = 0; i < TEST_ARR_SIZE; ++i)
		randArray[i] = ft::make_pair(i, i + 10 % 7);
	ft::map<Key, T> mapItTest(std::begin(randArray), std::end(randArray));

	tester.clearMap();
	tester.clearMap();
	tester.testSingleInsert(ft::make_pair(345, 47274 + 10 % 7));
	tester.testSizedInsert(ft::make_pair(735, 5735724 + 10 % 7));
	tester.testIteratorsInsert(mapItTest.begin(), mapItTest.end());
	std::cout << "Is == " << (toTest == mapItTest) << std::endl;
	std::cout << "Is <  " << (toTest < mapItTest) << std::endl;
	std::cout << "Is <= " << (toTest <= mapItTest) << std::endl;
	std::cout << "Is >  " << (toTest > mapItTest) << std::endl;
	std::cout << "Is >= " << (toTest >= mapItTest) << std::endl;
	tester.testCount();
	tester.testFind();
	tester.testBounds();
	tester.testEqualRange();
	tester.testErase();
	tester.testSwap(mapItTest);
	tester.testErase();
	tester.testEraseIterators();
}

template <class Key, class T>
void	mapTestConstructors(std::string msg)
 {
 	ft::map<Key, T> toTest;
 	MapTester<Key, T>	tester(msg, toTest);
 	ft::pair<Key, T> randArray[TEST_ARR_SIZE];
 	for (unsigned int i = 0; i < TEST_ARR_SIZE; ++i)
 		randArray[i] = ft::make_pair(i, i + 10 % 7);
	for (size_t i = 0; i < TEST_ARR_SIZE; i++)
		toTest.insert(ft::make_pair(i, i + 10 % 7));
	mapTestFunctions(msg, toTest);
 	ft::map<Key, T> mapItTest(std::begin(randArray), std::end(randArray));
 	ft::map<Key, T>	vec0;
 	ft::map<Key, T>	stdVec1;
 	ft::map<Key, T>	stdVec2;
 	mapTestFunctions<T>(msg, vec0);
 	ft::map<Key, T>	vec1(stdVec1);
 	mapTestFunctions<T>(msg, vec1);
 	ft::map<Key, T>	vec2 = stdVec2;
 	mapTestFunctions<T>(msg, vec2);
 	vec2 = vec0;
 	mapTestFunctions<T>(msg, vec2);
 	vec2 = stdVec2;
 	mapTestFunctions<T>(msg, vec2);
 }
