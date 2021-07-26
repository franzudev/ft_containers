#pragma once

#include <memory>
#include <algorithm>
#include "enable_if.hpp"
#include "is_integral.hpp"
#include "lexicographical_compare.hpp"
#include "iterator.hpp"

namespace ft {

	template <class T, class Allocator = std::allocator<T> >
	class vector {
	public:
		struct iterator {
			typedef std::random_access_iterator_tag 	iterator_category;
			typedef std::ptrdiff_t						difference_type;
			typedef T									value_type;
			typedef T*									pointer;
			typedef T&									reference;
			iterator(pointer ptr): m_ptr(ptr) {}

			reference operator*() const { return *m_ptr; }
			pointer operator->() { return m_ptr; }

			// Prefix increment
			iterator& operator++() { m_ptr++; return *this; }

			// Postfix increment
			iterator operator++(int) { iterator tmp = *this; ++(*this); return tmp; }

			// Prefix decrement
			iterator& operator--() { m_ptr--; return *this; }

			// Postfix decrement
			iterator operator--(int) { iterator tmp = *this; --(*this); return tmp; }

			iterator operator-(size_t val) {
				iterator temp = *this;
				while (val) {
					temp.m_ptr--;
					val--;
				}
				return temp;
			}
			ptrdiff_t operator-(iterator& val) {
				return m_ptr - val.m_ptr;
			}
			iterator&	operator-=(size_t n) {
				m_ptr -= n;
				return *this;
			}
			iterator operator+(size_t val) {
				iterator tmp = *this;
				size_t i = 0;
				while (i < val) {
					tmp.m_ptr++;
					i++;
				}
				return tmp;
			}
			// to check
			ptrdiff_t operator+(iterator& val) {
				return m_ptr + val.m_ptr;
			}
			iterator&	operator+=(size_t n) {
				m_ptr += n;
				return *this;
			}

			friend bool operator== (const iterator& a, const iterator& b) { return a.m_ptr == b.m_ptr; };
			friend bool operator!= (const iterator& a, const iterator& b) { return a.m_ptr != b.m_ptr; };
		private:
			pointer m_ptr;
		};

		typedef T													value_type;
		typedef Allocator											allocator_type;
		typedef typename allocator_type::reference					reference;
		typedef typename allocator_type::const_reference			const_reference;
		typedef typename allocator_type::pointer					pointer;
		typedef typename allocator_type::const_pointer				const_pointer;
		typedef const iterator										const_iterator;
		// to implement
		typedef reverse_iterator<iterator>							reverse_iterator;
		typedef const reverse_iterator								const_reverse_iterator;
		typedef typename iterator_traits<iterator>::difference_type	difference_type;
		typedef size_t												size_type;

		// --- Constructors && Destructors
		explicit vector (const allocator_type& alloc = allocator_type()):
			allocator(alloc),
			_size(0),
			_capacity(0),
			_vec(allocator.allocate(1)) {}

		~vector() {
			allocator.deallocate(_vec, _capacity);
		}

		vector(vector const &vec): _size(0), _capacity(0), _vec(nullptr){
			*this = vec;
		}

		explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()):
			allocator(alloc),
			_size(n),
			_capacity(n),
			_vec(allocator.allocate(n))
		{
			for (size_type i = 0; i < n; i++)
				_vec[i] = val;
		}
		template <class InputIterator>
		vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type* = 0):
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
		vector<value_type> &operator=(vector<value_type> const &vec) {
			if (_capacity)
				allocator.deallocate(_vec, _capacity);
			_vec = allocator.allocate(vec._capacity);
			size_type i = 0;
			for (iterator start = vec.begin(), end = vec.end(), copy = begin(); start != end; start++, copy++, i++) {
				allocator.construct(_vec + i, (value_type)*start);
			}
			_size = vec._size;
			_capacity = vec._capacity;
			return *this;
		}

		// --- Iterators
		iterator begin() {
			return iterator(_vec);
		}
		iterator				end() {
			return iterator(&_vec[_size]);
		}
		const_iterator begin() const {
			return iterator(_vec);
		}
		const_iterator end() const {
				return iterator(&_vec[_size]);
		}
		reverse_iterator rbegin() {
			return reverse_iterator(&_vec[_size - 1]);
		}
		reverse_iterator rend() {
			return reverse_iterator(_vec - 1);
		}
		 const_reverse_iterator	rbegin() const {
			return reverse_iterator(&_vec[_size - 1]);
		 }
		 const_reverse_iterator	rend() const {
			return reverse_iterator(_vec - 1);
		 }

		//Modifiers
		template <class InputIterator>
		void	assign(InputIterator first, InputIterator last, typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type* = 0) {
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
			for (size_type i = _size; i < n; i++) {
				if (i > _capacity)
					_capacity = (_capacity ? _capacity : 1) * 2;
			}
			clean_vector(_capacity);
			for (size_type i = 0; i < n; i++)
				_vec[i] = val;
			_size = n;
		}

		void 	push_back(value_type i) {
			if (_size == _capacity)
				reserve(_capacity * 2);
			_vec[_size++] = i;
		}

		void	pop_back() {
			allocator.destroy(&_vec[_size - 1]);
			_size -= 1;
		}

		iterator insert (iterator position, const value_type& val)
		{
			if (_size == _capacity) {
				size_type index = 0;
				for (iterator start = begin(); start != position; start++)
					index++;
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
				reserve(_capacity + n);
			iterator newIt = iterator(&_vec[index]);
			traslate(newIt, n);
			_size += n;
			size_type i = 0;
			for (; i < n; i++)
				_vec[index++] = val;
		}

		template <class InputIterator>
    	void insert (iterator position, InputIterator first, InputIterator last) {
			size_type index = position - begin();
			size_type len = 0;
			for (InputIterator beg = first; beg != last; beg++)
				len++;
			if (_size + len > _capacity)
				reserve(_capacity + len);
			iterator newIt = iterator(_vec + index);
			traslate(newIt, len);
			_size += len;
			for (InputIterator start = first; start != last; start++)
				_vec[index++] = *start;
		}

		iterator erase (iterator position) {
			size_type index = position - begin();
			allocator.destroy(&_vec[index]);
			for (size_type i = index; i < _size; i++)
				_vec[i] = _vec[i + 1];
			--_size;
			return position;
		}

		// TODO to test very well
		iterator erase (iterator first, iterator last) {
			size_type diff = last - first;
			for (iterator begin = first; begin != last; begin++)
				allocator.destroy(&*begin);
			for (iterator begin = first; begin != end(); begin++)
				*begin = *(begin + diff);
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
				_capacity = n;
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
			if (n <= _capacity)
				return;
			pointer tmp = allocator.allocate(n);
			_capacity = n;
			for (size_type i = 0; i < _size; i++)
				tmp[i] = _vec[i];
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
			iterator enda = end() - 1;
			iterator revEnd = position - 1;
			iterator newit = enda + dist;
			for (; enda != revEnd; enda--, newit--)
				*newit = *enda;
		}

	protected:
		size_type 	_size;		// Elements
		size_type 	_capacity;	// Allocated Space
		value_type	*_vec;
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
