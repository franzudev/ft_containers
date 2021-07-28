#pragma once

#include "vector.hpp"

namespace ft {

	template <class T, class Container = ft::vector<T> >
	class stack
	{
	public:
		typedef Container                                container_type;
		typedef typename container_type::value_type      value_type;
		typedef typename container_type::reference       reference;
		typedef typename container_type::const_reference const_reference;
		typedef typename container_type::size_type       size_type;

	protected:
		container_type c;

	public:
		stack() {};
		~stack() {};

		stack(const stack& q) {
			*this = q;
		}
		stack(stack& q) {
			*this = q;
		}
		stack& operator=(stack const& q) {
			c = q.c;
			return *this;
		}

		explicit stack(const container_type& c): c(c) {}

		bool empty() const {
			return c.empty();
		}
		size_type size() const {
			return c.size();
		}
		reference top() {
			return c.back();
		}
		const_reference top() const {
			return c.back();
		}

		void push(const value_type& x) {
			c.push_back(x);
		}
		void push(value_type& x) {
			c.push_back(x);
		}
		void pop() {
			c.pop_back();
		}
		friend
		bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return lhs.c == rhs.c; }
		friend
		bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return lhs.c > rhs.c; }
	};

	template <class T, class Container>
	bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return !(lhs == rhs);
	}

	template <class T, class Container>
	bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return !(lhs > rhs || lhs == rhs);
	}

	template <class T, class Container>
	bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return !(lhs > rhs);
	}

	template <class T, class Container>
	bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
		return !(lhs < rhs);
	}

	template <class T, class Container>
	void swap(stack<T, Container>& x, stack<T, Container>& y) {
		x.swap(y);
	}

} //namespace ft
