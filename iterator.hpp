#pragma once
#include <cstddef>
#include <iostream>
namespace ft {

	// Iterator::iterator_category
	struct input_iterator_tag {
	};
	struct output_iterator_tag {
	};
	struct forward_iterator_tag : public input_iterator_tag {
	};
	struct bidirectional_iterator_tag : public forward_iterator_tag {
	};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {
	};
	template<class Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::difference_type difference_type;
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
		typedef typename Iterator::iterator_category iterator_category;
	};

	template<class T>
	struct iterator_traits<T*>
	{
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef random_access_iterator_tag iterator_category;
	};

	template<class Category, class T, class Distance = ptrdiff_t,
			class Pointer = T*, class Reference = T&>
	struct iterator
	{
		typedef T         value_type;
		typedef Distance  difference_type;
		typedef Pointer   pointer;
		typedef Reference reference;
		typedef Category  iterator_category;
	};


	template <class Iterator>
	class reverse_iterator
			: public iterator<typename iterator_traits<Iterator>::iterator_category,
					typename iterator_traits<Iterator>::value_type,
					typename iterator_traits<Iterator>::difference_type,
					typename iterator_traits<Iterator>::pointer,
					typename iterator_traits<Iterator>::reference>
	{
	protected:
		Iterator current;
	public:
		typedef Iterator                                            iterator_type;
		typedef typename iterator_traits<Iterator>::difference_type difference_type;
		typedef typename iterator_traits<Iterator>::reference       reference;
		typedef typename iterator_traits<Iterator>::pointer         pointer;

		reverse_iterator(): current() {}

		reverse_iterator(typename Iterator::value_type * ptr) { current = Iterator(ptr); }
		reverse_iterator(const Iterator & x) { current = x; --current; }

		template <class U>reverse_iterator(const reverse_iterator<U>& u) {*this = u;}

		template <class U>  reverse_iterator& operator=(const reverse_iterator<U>& u) {current = u.getCurrent(); return *this;}

		Iterator base() const {return ++Iterator(current);}
		Iterator getCurrent() const {return current;}

		reference operator*() const {return *current;}

		pointer   operator->() const {return &(*current);}

		reverse_iterator& operator++() {
			--current;
			return *this;
		}
		reverse_iterator  operator++(int) {
			reverse_iterator tmp = *this;
			--current;
			return tmp;
		}
		reverse_iterator& operator--() {
			++current;
			return *this;
		}
		reverse_iterator  operator--(int) {
			reverse_iterator tmp = *this;
			++current;
			return tmp;
		}
		reverse_iterator  operator+ (difference_type n) const {
			return current - n + 1;
		}
		reverse_iterator& operator+=(difference_type n) {
			current -= n;
			return *this;
		}
		reverse_iterator  operator- (difference_type n) const {
			return current + n + 1;
		}
		reverse_iterator& operator-=(difference_type n) {
			current += n;
			return *this;
		}
		reference         operator[](difference_type n) const {
			return *(*this + n);
		}
	};

	template <class Iterator1, class Iterator2>
	bool	operator==(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y) {
		return x.base() == y.base();
	}

	template <class _Iter1, class _Iter2>
	bool
	operator<(const reverse_iterator<_Iter1>& x, const reverse_iterator<_Iter2>& y)
	{
		return x.base() > y.base();
	}

	template <class _Iter1, class _Iter2>
	bool
	operator>(const reverse_iterator<_Iter1>& x, const reverse_iterator<_Iter2>& y)
	{
		return x.base() < y.base();
	}

	template <class _Iter1, class _Iter2>
	bool
	operator>=(const reverse_iterator<_Iter1>& x, const reverse_iterator<_Iter2>& y)
	{
		return x.base() <= y.base();
	}

	template <class _Iter1, class _Iter2>
	bool
	operator<=(const reverse_iterator<_Iter1>& x, const reverse_iterator<_Iter2>& y)
	{
		return x.base() >= y.base();
	}

	template <class Iterator1, class Iterator2>
	bool	operator!=(const reverse_iterator<Iterator1>& x, const reverse_iterator<Iterator2>& y) {
		return x.base() != y.base();
	}

	template <class Iterator>
	reverse_iterator<Iterator>
	operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& x) {
		return reverse_iterator<Iterator>(x.base() - n);
	}

	template <class Iterator1, class Iterator2>
	typename reverse_iterator<Iterator1>::difference_type
	operator-(reverse_iterator<Iterator1> n, const reverse_iterator<Iterator2>& x) {
		return x.base() - n.base();
	}
}
