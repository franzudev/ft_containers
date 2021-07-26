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
		stack();
		~stack();

		stack(const stack& q);
		stack(stack& q);

		stack& operator=(const stack& q);
		stack& operator=(stack& q);

		explicit stack(const container_type& c);
		explicit stack(container_type& c);

		bool empty() const;
		size_type size() const;
		reference top();
		const_reference top() const;

		void push(const value_type& x);
		void push(value_type& x);
		void pop();

		void swap(stack& c) noexcept(is_nothrow_swappable_v<Container>)
	};

	template <class T, class Container>
	bool operator==(const stack<T, Container>& x, const stack<T, Container>& y);
	template <class T, class Container>
	bool operator< (const stack<T, Container>& x, const stack<T, Container>& y);
	template <class T, class Container>
	bool operator!=(const stack<T, Container>& x, const stack<T, Container>& y);
	template <class T, class Container>
	bool operator> (const stack<T, Container>& x, const stack<T, Container>& y);
	template <class T, class Container>
	bool operator>=(const stack<T, Container>& x, const stack<T, Container>& y);
	template <class T, class Container>
	bool operator<=(const stack<T, Container>& x, const stack<T, Container>& y);

	template <class T, class Container>
	void swap(stack<T, Container>& x, stack<T, Container>& y) {
		x.swap(y);
	}

}
