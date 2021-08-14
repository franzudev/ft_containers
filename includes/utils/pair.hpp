#pragma once
#include <utility>

namespace ft {

	template <class T1, class T2>
	struct pair
	{
		typedef T1 first_type;
		typedef T2 second_type;

		T1 first;
		T2 second;

		pair() : first(), second() {};
		pair (const first_type& a, const second_type& b) : first(a), second(b) {};
		template<class U, class V>
		pair (const pair<U,V>& pr) : first(pr.first), second(pr.second) {}

		pair& operator=(const pair& pr) {
			first = pr.first;
			second = pr.second;
			return *this;
		}

	}; // struct pair


	// --- pair relational operators
	template <class T1, class T2> bool operator==(const pair<T1,T2>& x, const pair<T1,T2>& y) {
		return x.first == y.first;
	}
	template <class T1, class T2> bool operator!=(const pair<T1,T2>& x, const pair<T1,T2>& y) {
		return !(x == y);
	}
	template <class T1, class T2> bool operator< (const pair<T1,T2>& x, const pair<T1,T2>& y) {
		return x.first < y.first || (!(y.first < x.first) && x.second < y.second);
	}
	template <class T1, class T2> bool operator> (const pair<T1,T2>& x, const pair<T1,T2>& y) {
		return y < x;
	}
	template <class T1, class T2> bool operator>=(const pair<T1,T2>& x, const pair<T1,T2>& y) {
		return !(x < y);
	}
	template <class T1, class T2> bool operator<=(const pair<T1,T2>& x, const pair<T1,T2>& y) {
		return !(y < x);
	}
	// pair relational operators


	template <class T1,class T2>
	pair<T1,T2> make_pair (T1 x, T2 y) {
		return ( pair<T1,T2>(x,y) );
	} // make_pair

} // namespace ft
