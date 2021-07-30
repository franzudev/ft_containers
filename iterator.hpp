#pragma once
#include <cstddef>

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


	template<class Iterator>
	class reverse_iter
			: public iterator<typename iterator_traits<Iterator>::iterator_category,
					typename iterator_traits<Iterator>::value_type,
					typename iterator_traits<Iterator>::difference_type,
					typename iterator_traits<Iterator>::pointer,
					typename iterator_traits<Iterator>::reference> {
	protected:
		Iterator current;
	public:
		typedef Iterator                                            iterator_type;
		typedef typename iterator_traits<Iterator>::difference_type difference_type;
		typedef typename iterator_traits<Iterator>::reference       reference;
		typedef typename iterator_traits<Iterator>::pointer         pointer;

		reverse_iter(): current(nullptr) {}
		reverse_iter(Iterator ptr): current(ptr) {}
		template <class U> reverse_iter(const reverse_iter<U>& it) { *this = it;}
		~reverse_iter() {};

		Iterator	base() const {
			return current;
		}

		template <class U> reverse_iter& operator=(const reverse_iter<U>& it) {
			current = it.base();
			return *this;
		}

		template <class Iter>
		reverse_iter &operator=(Iter const & rit) {
			current = rit.base();
			return *this;
		}

		reverse_iter &operator=(Iterator it) {
			current = it;
			return *this;
		}

		reverse_iter &operator++() {
			current--;
			return *this;
		}

		reverse_iter operator++(int) {
			reverse_iter temp = *this;
			++*this;
			return temp;
		}

		reverse_iter &operator--() {
			current++;
			return *this;
		}

		reverse_iter operator--(int) {
			reverse_iter temp = *this;
			--*this;
			return temp;
		}

		reverse_iter &operator-(ptrdiff_t val) {
			while (val) {
				current--;
				val--;
			}
			return *this;
		}

		reverse_iter operator-(reverse_iter& val) {
			return current - val.current;
		}

		reverse_iter &operator+(ptrdiff_t val) {
			while (val) {
				current++;
				val--;
			}
			return *this;
		}

		reverse_iter operator+(reverse_iter& val) {
			return current + val.current;
		}

		reverse_iter &operator+=(int n) {
			current += n;
			return *this;
		}

		reverse_iter &operator-=(int n) {
			current -= n;
			return *this;
		}

		reference operator*() const {
			return *current;
		}
		pointer   operator->() const {
			return current;
		}

		bool operator==(const reverse_iter &rhs) {
			return current == rhs.current;
		}

		bool operator!=(const reverse_iter &rhs) {
			return current != rhs.current;
		}
	};

}
