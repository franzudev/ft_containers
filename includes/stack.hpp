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
		stack (const container_type& c = container_type()) {
			this->c = c;
		}
		~stack() {}

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

		bool empty() const {
			return this->c.empty();
		}
		size_type size() const {
			return this->c.size();
		}
		reference top() {
			return this->c.back();
		}
		const_reference top() const {
			return this->c.back();
		}

		void push(const value_type& x) {
			this->c.push_back(x);
		}
		void push(value_type& x) {
			this->c.push_back(x);
		}
		void pop() {
			this->c.pop_back();
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
