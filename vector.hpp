#pragma once

#include <memory>
#include <algorithm>
#include "enable_if.hpp"
#include "is_integral.hpp"
#include "lexicographical_compare.hpp"
#include "iterator.hpp"
#include "Timer.hpp"
#include <cstring>

namespace ft {

	template <class T, class Allocator = std::allocator<T> >
	class vector {
	public:
		template<class Pointer>
		struct iter {
			typedef Pointer                                                     iterator_type;
			typedef typename iterator_traits<iterator_type>::iterator_category	iterator_category;
			typedef typename iterator_traits<iterator_type>::value_type        	value_type;
			typedef typename iterator_traits<iterator_type>::difference_type   	difference_type;
			typedef typename iterator_traits<iterator_type>::pointer           	pointer;
			typedef typename iterator_traits<iterator_type>::reference         	reference;

			explicit iter(): m_ptr(nullptr){};

			explicit iter(iterator_type ptr): m_ptr(ptr) {}
			
			// explicit iter(pointer ptr): m_ptr(ptr) {}

			iter(iter const & other) : m_ptr(other.m_ptr) {}

			reference operator*() const { return *m_ptr; }
			
			pointer operator->() const { return m_ptr; }

			// Prefix increment
			reference operator++() { ++m_ptr; return *m_ptr; }

			// Postfix increment
			iterator_type operator++(int) { iterator_type tmp = m_ptr; ++m_ptr; return tmp; }

			// Prefix decrement
			reference operator--() { --m_ptr; return *m_ptr; }

			// Postfix decrement
			iterator_type operator--(int) { iterator_type tmp = m_ptr; --m_ptr; return tmp; }

			iterator_type operator-(difference_type val) {
				return iterator_type(m_ptr - val);
			}
			difference_type operator-(reference val) {
				return m_ptr - val.m_ptr;
			}
			reference	operator-=(difference_type n) {
				m_ptr -= n;
				return *m_ptr;
			}
			iterator_type operator+(difference_type val) const {
				return iterator_type(m_ptr + val);
			}
			difference_type operator+(reference val) const {
				return m_ptr + val.m_ptr;
			}
			reference	operator+=(difference_type n) {
				m_ptr += n;
				return *m_ptr;
			}
			
			pointer	base() const{
				return m_ptr;
			}

			template <class Iter>
			iter&	operator=(iter<Iter> const & other)
			{
				m_ptr = other.base();
				return *this;
			}

			friend bool operator== (const iter& a, const iter& b) { return a.m_ptr == b.m_ptr; };
			friend bool operator!= (const iter& a, const iter& b) { return a.m_ptr != b.m_ptr; };
		private:
			iterator_type m_ptr;
		}; //iter<>

		typedef T													value_type;
		typedef Allocator											allocator_type;
		typedef typename allocator_type::reference					reference;
		typedef typename allocator_type::const_reference			const_reference;
		typedef typename allocator_type::pointer					pointer;
		typedef typename allocator_type::const_pointer				const_pointer;
		typedef iter<pointer>										iterator;
		typedef iter<const_pointer>									const_iterator;
		// to implement
		typedef reverse_iterator<const_iterator>					const_reverse_iterator;
		typedef reverse_iterator<iterator>							reverse_iterator;
		typedef typename iterator_traits<iterator>::difference_type	difference_type;
		typedef size_t												size_type;

		// --- Constructors && Destructors
		explicit vector (const allocator_type& alloc = allocator_type()):
			allocator(alloc),
			_size(0),
			_capacity(0),
			_vec(nullptr) {}

		~vector() {
			// for (size_type i = 0; i < _size; i++)
			// 	allocator.destroy(&_vec[i]);
			// allocator.deallocate(_vec, _capacity);
		}

		vector(vector &vec): allocator(vec.get_allocator()), _size(0), _capacity(0), _vec(nullptr){
			*this = vec;
		}

		explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()):
			allocator(alloc),
			_size(n),
			_capacity(n),
			_vec(allocator.allocate(n))
		{
			for (size_type i = 0; i < n; i++)
				allocator.construct(_vec + i, val);
		}
		template <class InputIterator>
		vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0):
		allocator(alloc)
		{
			size_type len = 0;
			for (InputIterator beg = first; beg != last; beg++)
				len++;
			_vec = allocator.allocate(_size = _capacity = len);
			std::copy(first, last, _vec);
		}

		// Exceptions
		class out_of_range: public std::exception {
			const char * what() const throw() {
				return "Element out of bound";
			}
		};

		// --- Operator Overloads
		vector &operator=(vector<value_type> const &vec) {
			if (_capacity)
				allocator.deallocate(_vec, _capacity);
			_vec = allocator.allocate(vec._capacity);
			for (size_type i = 0; i < vec._size; ++i) {
				allocator.construct(_vec + i, vec[i]);
			}
//			for (iterator start = vec.begin(), end = vec.end(), copy = begin(); start != end; start++, copy++, i++) {
//				allocator.construct(_vec + i, (value_type)*start);
//			}
			_size = vec._size;
			_capacity = vec._capacity;
			return *this;
		}

		// --- Iterators
		iterator begin() {
			return iterator(_vec);
		}
		iterator end() {
			return iterator(&_vec[_size]);
		}
		const_iterator begin() const {
			return const_iterator(_vec);
		}
		const_iterator end() const {
				return const_iterator(&_vec[_size]);
		}
		reverse_iterator rbegin() {
			if (!_size)
				return reverse_iterator(iterator(NULL));							// BUG_FIX
			return reverse_iterator(iterator(&_vec[_size - 1]));					// BUG_FIX
		}
		reverse_iterator rend() {
			if (!_size)
				return reverse_iterator(iterator(NULL));							// BUG_FIX
			return reverse_iterator(iterator(_vec - 1));							// BUG_FIX
		}
		 const_reverse_iterator	rbegin() const {
			return const_reverse_iterator(const_iterator(&_vec[_size - 1]));		// BUG_FIX
		 }
		 const_reverse_iterator	rend() const {
			return const_reverse_iterator(const_iterator(_vec - 1));				// BUG_FIX
		 }

		//Modifiers
		template <class InputIterator>
		void	assign(InputIterator first, InputIterator last, typename enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0) {
			size_type new_size = std::abs(last - first);
			clean_vector(new_size);
			size_type i = 0;
			for (InputIterator start = first; start != last; start++, i++) {
				if (i > _capacity)
					reserve(_capacity * 2);
				allocator.construct(_vec + i, *start);
			}
			_size = new_size;
		}

		void	assign(size_type n, const value_type& val) {
			if (n > _capacity)
				_capacity = n;
			clean_vector(_capacity);
			for (size_type i = 0; i < n; i++)
				allocator.construct(_vec + i, val);
			_size = n;
		}

		void push_back(const_reference value) {
			if (_size == _capacity)
				reserve(_capacity * 2);
			_vec[_size++] = value;
		}

		void	pop_back() {
			allocator.destroy(&_vec[_size - 1]);
			_size -= 1;
		}

		iterator insert (iterator position, const value_type& val)
		{
			if (_size == _capacity) {
				size_type index = position - begin();
				reserve(_capacity * 2);
				iterator newPosition = begin() + index;
				traslate(newPosition, 1);
				*newPosition = val;
				_size += 1;
				return newPosition;
			}
			traslate(position, 1);
			*position = val;
			_size += 1;
			return position;
		}

		void insert (iterator position, size_type n, const value_type& val) {
			size_type	index = position - begin();
			if (_size + n > _capacity)
				reserve(_capacity + _size + n);
			iterator newIt = iterator(&_vec[index]);
			traslate(newIt, n);
			_size += n;
			size_type i = 0;
			for (; i < n; i++)
				_vec[index++] = val;
		}

		template <class InputIterator>
    	void insert (iterator position, InputIterator first, InputIterator last, typename enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0) {
			size_type index = position - begin();
			size_type len = 0;
			for (InputIterator beg = first; beg != last; beg++)
				len++;
			if (_size + len > _capacity) {
				reserve(_capacity + _size + len);
			}
			iterator newIt = iterator(_vec + index);
			traslate(newIt, len);
			_size += len;
			for (InputIterator start = first; start != last; start++)
				_vec[index++] = *start;
		}

		iterator erase (iterator const &position) {
			size_type index = position - begin();
			allocator.destroy(_vec + index);
			std::move(_vec + index + 1, _vec + _size, _vec + index);
			_size -= 1;
			return position;
		}

		iterator erase (iterator first, iterator last) {
			size_type diff = last - first;
			// pointer it = end().operator->();
			pointer nBegin = first.operator->() + diff;
			pointer lastP = last.operator->();
			for (pointer i = first.operator->(); i != lastP; i++)
				allocator.destroy(i);
			std::move(nBegin, end().operator->(), first.operator->());
			_size -= diff;
			return first;
		}

		void swap (vector& x) {
			size_type tSize = _size;
			size_type tCapacity = _capacity;
			value_type *tVec = _vec;
			_size = x.size();
			_capacity = x.capacity();
			_vec = x._vec;
			x._size = tSize;
			x._capacity = tCapacity;
			x._vec = tVec;
		}

		void clear() {
			for (iterator it = begin(); it != end(); it++)
				allocator.destroy(&*it);
			_size = 0;
		}

		// --- Getters
		size_type 	size()		const {return _size;}
		size_type 	max_size()	const {return allocator.max_size();}
		size_type 	capacity()	const {return _capacity;}
		bool		empty()		const {return !_size;}

		// --- Member Functions
		void 			resize(size_type n)
		{
			if (n < _size) {
				pointer tmp = allocator.allocate(n + 1);
				for (size_type i = 0; i < n; i++)
					tmp[i] = _vec[i];
				allocator.deallocate(_vec, _size);
				_vec = tmp;
				_size = n;
			}
			else if (n >= _size) {
				if (n > _capacity)
					reserve(n);
				for (size_type i = _size; i < n; i++)
					_vec[_size] = T();
				_size = n;
			}
		}

		void			reserve(size_type n) {
			if (!n)
				_capacity = 1;
			pointer tmp = allocator.allocate(n);
			_capacity = n;
			for (size_type i = 0; i < _size; ++i) {
				tmp[i] = _vec[i];
				allocator.destroy(&_vec[i]);
			}
			allocator.deallocate(_vec, _size);
			_vec = tmp;
		}

		allocator_type	get_allocator() const {
			return allocator;
		}
		// Element access
		reference		operator[](size_type index) {
			if (index >= _size)
				return *end();
			return _vec[index];
		}
		const_reference	operator[](size_type index) const {
			if (index >= _size)
				return *end();
			return _vec[index];
		}
		reference		at(size_type index) {
			if (index >= _size)
				throw out_of_range();
			return _vec[index];
		}
		const_reference	at(size_type index) const {
			if (index >= _size)
				throw out_of_range();
			return _vec[index];
		}
		reference		front() {
			return *begin();
		}
		const_reference	front() const {
			return *begin();
		}
		reference		back() {
			return *rbegin();
		}
		const_reference	back() const {
			return *rbegin();
		}

	private:
		allocator_type	allocator;

		/**
		 * Clean the vector before use ;)
		 *
		 * @param size_type new_size
		 * @return void
		 */
		void	clean_vector(size_type new_size) {
			for (size_type i = 0; i < _size; i++)
				allocator.destroy(_vec + i);
			allocator.deallocate(_vec, _size);
			_vec = allocator.allocate(new_size);
			_capacity = new_size;
		}

		/**
		 * Translate element's in vectors by dist.
		 *
		 * Creates space for the new reserved vector
		 *
		 * @param iterator Iterator to start traslation
		 * @param size_type distance to move the objects
		 * @return void
		 */
		void	traslate(iterator position, size_type dist) {
			pointer enda = end().operator->() - 1;
			pointer revEnd = position.operator->() - 1;
			pointer newit = enda + dist;
			for (; enda != revEnd; enda--, newit--)
				*newit = *enda;
		}

	protected:
		size_type 	_size;		// Elements
		size_type 	_capacity;	// Allocated Space
		T*			_vec;
	};

	template <class T>
	ptrdiff_t operator-(T t, T u) {
		return t - u;
	}

	template <class T, class Alloc>
	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y){
		x.swap(y);
	}

	template< class T, class Alloc >
	bool operator==( const ft::vector<T,Alloc>& lhs,
					 const ft::vector<T,Alloc>& rhs ) {
		return !ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()) && !ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
	}

	template <class T, class Alloc>
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return !(lhs == rhs);
	}

	template <class T, class Alloc>
	bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <class T, class Alloc>
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
		return !ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <class T, class Alloc>
	bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
	}

	template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return !ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
	}
}
