#pragma once

#include <iostream>

#ifdef USE_STL
# define STL "std: "
# include <iterator>
# include <vector>
# include <array>
# include <set>
//namespace ft = std;
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
	Timer() {
		std::cout << STL << std::endl;
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
