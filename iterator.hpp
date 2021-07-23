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
	struct iterator_traits {
		typedef typename Iterator::difference_type difference_type;
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
		typedef typename Iterator::iterator_category iterator_category;
	};

	template<class T>
	struct iterator_traits<T *> {
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef T *pointer;
		typedef T &reference;
		typedef random_access_iterator_tag iterator_category;
	};

	template<class Category, class T, class Distance = ptrdiff_t,
			class Pointer = T *, class Reference = T &>
	struct iterator {
		typedef T value_type;
		typedef Distance difference_type;
		typedef Pointer pointer;
		typedef Reference reference;
		typedef Category iterator_category;
	};

	/*template<class Iterator>
	class reverse_iterator: public iterator<typename iterator_traits<Iterator>::iterator_category,
					typename iterator_traits<Iterator>::value_type,
					typename iterator_traits<Iterator>::difference_type,
					typename iterator_traits<Iterator>::pointer,
					typename iterator_traits<Iterator>::reference>
					{
	protected:
		Iterator current;
	public:
		typedef Iterator iterator_type;
		typedef typename iterator_traits<Iterator>::difference_type difference_type;
		typedef typename iterator_traits<Iterator>::reference reference;
		typedef typename iterator_traits<Iterator>::pointer pointer;

		reverse_iterator();

		explicit reverse_iterator(Iterator x);

		template<class U>
		reverse_iterator(const reverse_iterator<U> &u);

		template<class U>
		reverse_iterator &operator=(const reverse_iterator<U> &u);

		Iterator base() const;

		reference operator*() const;

		pointer operator->() const;

		reverse_iterator &operator++()
		{
			current--;
			return *this;
		}

		reverse_iterator operator++(int)
		{
			iterator_type tmp = *this;
			++*this;
			return tmp;
		}

		reverse_iterator &operator--()
		{
			current++;
			return *this;
		}

		reverse_iterator operator--(int)
		{
			iterator_type tmp = *this;
			--*this;
			return tmp;
		}

		reverse_iterator operator+(difference_type n) const;

		reverse_iterator &operator+=(difference_type n);

		reverse_iterator operator-(difference_type n) const;

		reverse_iterator &operator-=(difference_type n);

		reference operator[](difference_type n) const;
	};*/


	template<class Iterator>
	class reverse_iterator
			: public iterator<typename iterator_traits<Iterator>::iterator_category,
					typename iterator_traits<Iterator>::value_type,
					typename iterator_traits<Iterator>::difference_type,
					typename iterator_traits<Iterator>::pointer,
					typename iterator_traits<Iterator>::reference> {
	protected:
		Iterator current;
	public:
		reverse_iterator() {
			current = nullptr;
		}

		~reverse_iterator()
		{};

		reverse_iterator(Iterator &ptr) {
			current = ptr;
		}
		reverse_iterator(typename Iterator::value_type *ptr) {
			current = ptr;
		}

		reverse_iterator &operator=(reverse_iterator &it) {
			current = it.current;
			return *this;
		}

		reverse_iterator &operator=(reverse_iterator const & rit) {
			current = rit.current;
			return *this;
		}

		reverse_iterator &operator=(Iterator it) {
			current = it;
			return *this;
		}

		reverse_iterator &operator++() {
			current--;
			return *this;
		}

		reverse_iterator operator++(int) {
			reverse_iterator temp = *this;
			++*this;
			return temp;
		}

		reverse_iterator &operator--() {
			current++;
			return *this;
		}

		reverse_iterator operator--(int) {
			reverse_iterator temp = *this;
			--*this;
			return temp;
		}

		reverse_iterator &operator-(ptrdiff_t val) {
			while (val) {
				current--;
				val--;
			}
			return *this;
		}

		ptrdiff_t operator-(reverse_iterator& val) {
			return current - val.current;
		}

		reverse_iterator &operator+=(int n) {
			current += n;
			return *this;
		}

		typename Iterator::value_type &operator*(void) {
			return *current;
		}

		bool operator==(const reverse_iterator &rhs) {
			return current == rhs.current;
		}

		bool operator!=(const reverse_iterator &rhs) {
			return current != rhs.current;
		}
	};

}
