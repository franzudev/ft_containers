//
// Created by Federico Francois on 7/19/21.
//

#include <iostream>
#include <algorithm>

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
#include <chrono>

class Timer {
	std::chrono::steady_clock::time_point start;
	std::chrono::steady_clock::time_point end;
	std::chrono::microseconds diff;

public:
	Timer(std::string msg) {
		std::cout << "< " << msg << " >" << std::endl;
		start = std::chrono::steady_clock::now();
	}
	long long int getDiff() {
		end = std::chrono::steady_clock::now();
		diff = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
		std::cout << STL << "execution time: " << diff.count() << "[µs]" << std::endl;
		return diff.count();
	}
};

struct Result {
	typedef long long int microseconds;
	Result() {}
	Result(microseconds ft, microseconds std) {
		(*this)(ft, std);
	}
	void operator()(microseconds ft, microseconds std) {
		bool res = ft < std;
		std::string winner = res ? "ft " : "std ";
		std::string loser = res ? "std" : "ft";
		float quotient = res ? (float)std / ft : (float)ft/ std;

		std::cout << winner << quotient << " times faster than " << loser << std::endl << std::endl;
	}
};

template <class T>
struct VectorTester {
	ft::vector<T> vector;
	VectorTester(std::string msg, ft::vector <T> &vector): vector(vector) {
		std::cout << msg << std::endl;
	};

	template<class InputIterator>
	void	testTemplatedAssign(InputIterator first, InputIterator last) {
		std::cout << "Testing assign method with template iterators" << std::endl;
		vector.assign(first, last);
	}

	void	testSizedAssign(size_t n, const T& val) {
		std::cout << "Testing assign method with template iterators" << std::endl;
		vector.assign(n, val);
	}

	void	testPushBack(T value) {
		std::cout << "Testing push_back method" << std::endl;
		vector.push_back(value);
	}

	void	testPopBack(T value) {
		std::cout << "Testing pop_back method" << std::endl;
		vector.pop_back(value);
	}

private:
	VectorTester();
};

int main() {
	Timer mainTest("Testing main");
	// int
	{

		std::cout << " ************* Testing int ************* " << std::endl;
		ft::vector<int> g;
		int a = 1, b = 10, c = 100;
		std::cout << "Push: int(" << a << ")" << std::endl;
		g.push_back(a);
		std::cout << "Size: " << g.size() << std::endl;
		std::cout << "Push: int(" << b << ")" << std::endl;
		g.push_back(b);
		std::cout << "Size: " << g.size() << std::endl;
		ft::vector<int>::iterator it = g.begin();

		std::cout << std::endl << std::endl;
		std::cout << " ***** Postfix operators ***** " << std::endl;
		std::cout << "it++: " << *(it++) << std::endl << std::endl;
		std::cout << "it  : " << *it << std::endl << std::endl;
		std::cout << "--it: " << *(--it) << std::endl << std::endl;
		std::cout << "++it: " << *(++it) << std::endl << std::endl;
		std::cout << "it--: " << *(it--) << std::endl << std::endl;
		std::cout << "it  : " << *it << std::endl << std::endl;

		for (ft::vector<int>::iterator start = g.begin();
			 start != g.end(); ++start)
		{
			std::cout << "val : " << *start << std::endl;
		}
		std::cout << "Push: int(" << c << ")" << std::endl;
		g.push_back(c);
		for (ft::vector<int>::iterator start = g.begin();
			 start != g.end(); ++start)
			std::cout << "val : " << *start << std::endl;

		std::cout << "  Resizing: " << std::endl;
		g.resize(1);
		for (ft::vector<int>::iterator start = g.begin();
			 start != g.end(); ++start)
			std::cout << "val : " << *start << std::endl;
		std::cout << std::endl;
		ft::vector<int> rvect;
		rvect.push_back(10);
		rvect.push_back(20);
		rvect.push_back(40);
		rvect.push_back(50);
		g.assign(100, 10);
		for (ft::vector<int>::iterator start = g.begin(); start != g.end(); ++start)
			std::cout << "val : " << *start << std::endl;
		g.assign(rvect.begin(), rvect.end());
		for (ft::vector<int>::iterator start = g.begin(); start != g.end(); ++start)
			std::cout << "val : " << *start << std::endl;
		std::cout << "pop" << std::endl;
		g.pop_back();


		ft::vector<int>::iterator twenty = g.begin();
		twenty++;
		twenty++;
		g.insert(twenty, 15);
		ft::vector<int>::iterator fifteen = g.begin();
		g.insert(fifteen, 15);
		ft::vector<int>::iterator fift = g.begin();
		g.insert(fift, 15);
		ft::vector<int> cvect;
		cvect.push_back(1000);
		cvect.push_back(2000);
		cvect.push_back(3000);
		cvect.push_back(4000);
		cvect.push_back(5000);
		cvect.push_back(6000);
		cvect.push_back(7000);
		cvect.push_back(8000);
		g.swap(cvect);
		cvect.clear();
		std::cout << (cvect == g) << std::endl;
		std::cout << g.max_size() << std::endl;
		ft::vector<int> provaStd(g.begin(), g.end());
		for (ft::vector<int>::iterator start = provaStd.begin(); start != provaStd.end(); start++)
			std::cout << "val : " << *start << std::endl;
		std::cout << std::endl << std::endl << std::endl;
		// copy constructor and assignment operator
		ft::vector<int> copy(g);
		std::cout << (copy == g) << std::endl;
		for (ft::vector<int>::iterator start = copy.begin(); start != copy.end(); start++)
			std::cout << "val : " << *start << std::endl;
		g.clear();
		std::cout << (copy == g) << std::endl;
		for (ft::vector<int>::iterator start = copy.begin(); start != copy.end(); start++)
			std::cout << "val : " << *start << std::endl;
		// end
		std::cout << std::endl << std::endl << std::endl;
		ft::vector<int> vec(copy.begin(), copy.end());
		std::cout << (vec == copy) << std::endl;
		std::cout << "Copy" << std::endl;
		for (ft::vector<int>::iterator start = vec.begin(); start != vec.end(); start++)
			std::cout << "val : " << *start << std::endl;
		std::cout << "G" << std::endl;
		copy.clear();
		for (ft::vector<int>::iterator start = copy.begin(); start != copy.end(); start++)
			std::cout << "val : " << *start << std::endl;
		g.clear();
		std::cout << (copy == g) << std::endl;

		int randArray[1000000];
		for (int i = 0; i < 1000000; i++)
			randArray[i]= rand() % 100000;

		// tester mock
		long long int std;
		long long int ft;
		Result r;
		{
			Timer test("vector constructor call with int *");
			ft::vector<int> testTime(std::begin(randArray), std::end(randArray));
		}

		{
			int cazzo = 10;
			Timer test("vector constructor call with int *");
			ft::vector<int> test5(100, cazzo);
		}
		{
			int cazzo = 10;
			Timer test("vector constructor call with int *");
			ft::vector<int> test5(100, cazzo);
		}
		r(ft, std);

		/*std::set<int> set;
		for (size_t i = 0; i < 100000; i++)
			set.insert(i);
		{
			Timer test("ft::vector constructor call with std:set<int>::iterator");
			ft::vector<int> f(std::begin(set), std::end(set));
		}
		{
			Timer test("std::vector constructor call with std:set<int>::iterator");
			std::vector<int> f(std::begin(set), std::end(set));
		}
		r(ft, std);

		{
			Timer test("ft::vector insert with three iterators");
			ft::vector<int> test345;
			test345.insert(test345.begin(), set.begin(), set.end());
		}
		{
			Timer test("std::vector insert with three iterators");
			std::vector<int> test345;
			test345.insert(test345.begin(), set.begin(), set.end());
		}
		r(ft, std);*/
		mainTest.getDiff();
	}
}