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
	class reverse_iter
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

		reverse_iter(): current() {}
		explicit reverse_iter( iterator_type x ): current(x.base()) {}

		template <class U>reverse_iter(const reverse_iter<U>& u) {*this = u;}

		template <class U>  reverse_iter& operator=(const reverse_iter<U>& u) {current = u.base(); return *this;}

		Iterator base() const {return current;}

		reference operator*() const {
			Iterator tmp = current;
			--tmp;
			return *tmp;
		}

		pointer   operator->() const {return std::addressof(operator*());}

		reverse_iter& operator++() {
			--current;
			return *this;
		}
		reverse_iter  operator++(int) {
			reverse_iter tmp = *this;
			--current;
			return tmp;
		}
		reverse_iter& operator--() {
			++current;
			return *this;
		}
		reverse_iter  operator--(int) {
			reverse_iter tmp = *this;
			++current;
			return tmp;
		}
		reverse_iter  operator+ (difference_type n) const {
			return reverse_iter(current - n);
		}
		reverse_iter& operator+=(difference_type n) {
			current -= n;
			return *this;
		}
		reverse_iter  operator- (difference_type n) const {
			return reverse_iter(base() + n);
		}
		reverse_iter& operator-=(difference_type n) {
			current += n;
			return *this;
		}
		reference         operator[](difference_type n) const {
			return *(*this + n);
		}
	};

	template <class Iterator1, class Iterator2>
	bool	operator==(const reverse_iter<Iterator1>& x, const reverse_iter<Iterator2>& y) {
		return x.base() == y.base();
	}

	template <class Iterator1, class Iterator2>
	bool	operator!=(const reverse_iter<Iterator1>& x, const reverse_iter<Iterator2>& y) {
		return x.base() != y.base();
	}

	template <class Iterator>
	reverse_iter<Iterator>
	operator+(typename reverse_iter<Iterator>::difference_type n, const reverse_iter<Iterator>& x) {
		return reverse_iter<Iterator>(x.base() - n);
	}

	template <class Iterator1, class Iterator2>
	typename reverse_iter<Iterator1>::difference_type
	operator-(reverse_iter<Iterator1> n, const reverse_iter<Iterator2>& x) {
		return x.base() - n.base();
	}
}
