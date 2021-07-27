#pragma once

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
#endif
#include "Timer.hpp"

template <class T>
struct VectorTester {
	ft::vector<T> vector;
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
		std::cout << std::endl;
	}

	template<class InputIterator>
	void	testTemplatedAssign(std::string msg, InputIterator first, InputIterator last) {
		printSizes();
		Timer test(std::string(STL) + "Testing templated assign(InputIterator, InputIterator) " + msg);
		vector.assign(first, last);
		test.getDiff();
		for (InputIterator start = first; start != last; start++)
			std::cout << *start << std::endl;
		printSizes();
		printVector();
	}

	void	testSizedAssign(std::string msg, size_t n, const T& val) {
		printSizes();
		Timer test(std::string(STL) +"Testing assign(size_t, const T&) " + msg);
		vector.assign(n, val);
		test.getDiff();
		printSizes();
		printVector();
	}

	void	testPushBack(T value) {
		printSizes();
		Timer test(std::string(STL) +"Testing push_back(T value) single ");
		vector.push_back(value);
		test.getDiff();
		printSizes();
		printVector();

		Timer test2(std::string(STL) +"Testing push_back(T value) with 1000 iterations ");
		for (size_t i = 0; i < 1000; i++)
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
		for (size_t i = 0; i < 1000; i++)
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
		std::cout << "here" << std::endl;
		typename ft::vector<T>::iterator it = vector.begin();
		std::cout << "there" << std::endl;
		for (size_t i = 0; i < 10; i++)
			it = vector.insert(it, value);
		std::cout << "and there" << std::endl;
		test2.getDiff();
		printSizes();
		printVector();
	}

	void	testSizedInsert(size_t n, const T& val) {
		printSizes();
		Timer test(std::string(STL) + "Testing insert(iterator, size_t, const T&");
		vector.insert(vector.end() - 1, n, val);
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
		printVector();
	}

	void	testEraseIterators() {
		printSizes();
		Timer test(std::string(STL) + "Testing erase(iterator, iterator)");
		vector.erase(vector.begin() + 10, vector.begin() + 100);
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
