#pragma once

#include <memory>
#include <algorithm>
#include "enable_if.hpp"
#include "is_integral.hpp"
#include "lexicographical_compare.hpp"
#include "iterator.hpp"
#include <cstring>
#include <list>

namespace ft {

	template<class Pointer>
	struct vector_iterator {
		typedef Pointer                                                     iterator_type;
		typedef typename iterator_traits<iterator_type>::iterator_category	iterator_category;
		typedef typename iterator_traits<iterator_type>::value_type        	value_type;
		typedef typename iterator_traits<iterator_type>::difference_type   	difference_type;
		typedef typename iterator_traits<iterator_type>::pointer           	pointer;
		typedef typename iterator_traits<iterator_type>::reference         	reference;

		explicit vector_iterator(): m_ptr(nullptr){};

		explicit vector_iterator(iterator_type ptr): m_ptr(ptr) {}

		// explicit vector_iterator(pointer ptr): m_ptr(ptr) {}

		template<class Itter>
		vector_iterator(vector_iterator<Itter> const & other) {
			*this = other;
		}

		reference operator*() const { return *m_ptr; }

		pointer operator->() const { return m_ptr; }

		// Prefix increment
		vector_iterator &operator++() { ++m_ptr; return *this; }

		// Postfix increment
		vector_iterator operator++(int) { vector_iterator tmp = *this; ++m_ptr; return tmp; }

		// Prefix decrement
		vector_iterator &operator--() { --m_ptr; return *this; }

		// Postfix decrement
		vector_iterator operator--(int) { vector_iterator tmp = *this; --m_ptr; return tmp; }

		vector_iterator operator-(difference_type val) {
			return vector_iterator(m_ptr - val);
		}
//		difference_type operator-(reference val) {
//			return m_ptr - val.m_ptr;
//		}
		vector_iterator operator-(difference_type val) const {
			return vector_iterator(m_ptr - val);
		}
//		size_t operator-(vector_iterator val) {
//			return m_ptr - val.m_ptr;
//		}
		pointer	operator-=(difference_type n) {
			m_ptr -= n;
			return m_ptr;
		}
		vector_iterator operator+(difference_type val) const {
			return vector_iterator(m_ptr + val);
		}
		vector_iterator& operator+(vector_iterator<Pointer> &val) const {
			return vector_iterator(m_ptr + val.m_ptr);
		}
		pointer	operator+=(difference_type n) {
			m_ptr += n;
			return m_ptr;
		}

		reference	operator[](size_t index) {
			return *(m_ptr + index);
		}

		pointer	base() const{
			return m_ptr;
		}

		template <class Iter>
		vector_iterator&	operator=(vector_iterator<Iter> const & other)
		{
			m_ptr = other.base();
			return *this;
		}
	private:
		iterator_type m_ptr;
	};

	template <class T, class U>
	ptrdiff_t operator-(const vector_iterator<T> &lhs,const vector_iterator<U> &rhs) {
		return lhs.base() - rhs.base();
	}

	template <class T, class U>
	ptrdiff_t operator+(const vector_iterator<T> &lhs,const vector_iterator<U> &rhs) {
		return lhs.base() + rhs.base();
	}

	template <class T, class U>
	vector_iterator<U> operator+(T lhs, const vector_iterator<U> &rhs) {
		return rhs + lhs;
	}

	template <class T, class U>
	bool operator== (const vector_iterator<T> &lhs,const vector_iterator<U> &rhs) {
		return (lhs.base() == rhs.base());
	}

	template <class T, class U>
	bool operator!= (const vector_iterator<T> &lhs,const vector_iterator<U> &rhs) {
		return !(lhs == rhs);
	}

	template <class T, class U>
	bool operator< (const vector_iterator<T> &lhs,const vector_iterator<U> &rhs) {
		return (lhs.base() < rhs.base());
	}

	template <class T, class U>
	bool operator<= (const vector_iterator<T> &lhs,const vector_iterator<U> &rhs) {
		return lhs.base() <= rhs.base();
	}

	template <class T, class U>
	bool operator> (const vector_iterator<T> &lhs,const vector_iterator<U> &rhs) {
		return (lhs.base() > rhs.base());
	}

	template <class T, class U>
	bool operator>= (const vector_iterator<T> &lhs,const vector_iterator<U> &rhs) {
		return (lhs.base() >= rhs.base());
	}


	template <class T, class Allocator = std::allocator<T> >
	class vector {
	public:
		 //vector_iterator<>
		typedef T													value_type;
		typedef Allocator											allocator_type;
		typedef typename allocator_type::reference					reference;
		typedef typename allocator_type::const_reference			const_reference;
		typedef typename allocator_type::pointer					pointer;
		typedef typename allocator_type::const_pointer				const_pointer;
		typedef vector_iterator<pointer>							iterator;
		typedef vector_iterator<const_pointer>						const_iterator;
		// to implement
		typedef reverse_iterator<const_iterator>					const_reverse_iterator;
		typedef reverse_iterator<iterator>							reverse_iterator;
		typedef typename iterator_traits<iterator>::difference_type	difference_type;
		typedef size_t												size_type;

		// --- Constructors && Destructors
		// --- Empty constructor
		explicit vector (const allocator_type& alloc = allocator_type()):
				allocator(alloc),
				_size(0),
				_capacity(0),
				_vec(nullptr) {}

		~vector() {
			 for (size_type i = 0; i < _size; i++)
			 	allocator.destroy(&_vec[i]);
			 if (_capacity)
			 	allocator.deallocate(_vec, _capacity);
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
			for (size_type i = 0; i < _size; ++i, ++first)
				allocator.construct(_vec + i, *first);
		}

		// --- Operator Overloads
		vector &operator=(vector<value_type> const &vec) {
			if (_capacity <= vec.capacity()) {
				allocator.deallocate(_vec, _capacity);
				_vec = allocator.allocate(_capacity = vec.size());
			}
			for (size_type i = 0; i < vec.size(); ++i)
				allocator.construct(_vec + i, vec[i]);
			_size = vec._size;
			return *this;
		}

		class out_of_range: public std::out_of_range {
		public:
			explicit out_of_range(std::string str): std::out_of_range(str) {}
		};

		// --- Iterators
		iterator begin() {
			return iterator(_vec);
		}
		iterator end() {
			return iterator(_vec + _size);
		}
		const_iterator begin() const {
			return const_iterator(_vec);
		}
		const_iterator end() const {
			return const_iterator(_vec + _size);
		}
		reverse_iterator rbegin() {
			return reverse_iterator(end());
		}
		reverse_iterator rend() {
			return reverse_iterator(begin());
		}
		const_reverse_iterator	rbegin() const {
			return const_reverse_iterator(end());
		}
		const_reverse_iterator	rend() const {
			return const_reverse_iterator(begin());
		}

		//Modifiers
		template <class InputIterator>
		void	assign(InputIterator first, InputIterator last, typename enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0) {
			size_t new_size = 0;
			for (InputIterator i = first; i != last; ++i)
				new_size++;
			if (new_size > _capacity)
				_capacity = new_size;
			clean_vector(_capacity);
//			if (new_size > _capacity)
//				reserve(_capacity * 2);
			size_type i = 0;
			for (InputIterator start = first; start != last; ++start, ++i) {
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
			if (_size >= _capacity)
				reserve(_capacity * 2);
			_vec[_size++] = value;
		}

		void	pop_back() {
			allocator.destroy(&_vec[_size - 1]);
			_size -= 1;
		}

		iterator insert (iterator position, const value_type& val)
		{
			if (_size >= _capacity) {
				difference_type index = position - begin();
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
			if (_size + n > _capacity) {
				if (n >= size())
					reserve(_size + n);
				else
					reserve(size() * 2);
			}
			iterator newIt = iterator(&_vec[index]);
			traslate(newIt, n);
			_size += n;
			size_type i = 0;
			for (; i < n; i++)
				allocator.construct(_vec + index++, val);
		}

		template <class InputIterator>
		void insert (iterator position, InputIterator first, InputIterator last, typename enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0) {
			size_type index = position - begin();
			size_type len = 0;
			for (InputIterator beg = first; beg != last; beg++)
				len++;
			if (_size + len > _capacity) {
				if (_size + len < _capacity || _size + len > capacity() * 2)
					reserve(_size + len);
				else
					reserve(capacity() * 2);
			}
			iterator newIt = iterator(_vec + index);
			traslate(newIt, len);
			_size += len;
			for (InputIterator start = first; start != last; start++)
				allocator.construct(_vec + index++, *start);
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
		void resize( size_type n, T value = T() )
		{
			if (n < _size) {
				pointer tmp = allocator.allocate(n);
				for (size_type i = 0; i < n; i++)
					tmp[i] = _vec[i];
				allocator.deallocate(_vec, _size);
				_vec = tmp;
				_size = n;
			}
			else if (n >= _size) {
				if (n < _capacity || n > capacity() * 2)
					reserve(n);
				else
					reserve(capacity() * 2);
				for (size_type i = _size; i < n; i++)
					allocator.construct(_vec + i, value);
				_size = n;
			}
		}

		void			reserve(size_type n) {
			if (!n)
				_capacity = 1;
			_capacity = n < _capacity ? _capacity : n;
			pointer tmp = allocator.allocate(_capacity);
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
				throw out_of_range("Catch out_of_range exception!");
			return _vec[index];
		}
		const_reference	at(size_type index) const {
			if (index >= _size)
				throw out_of_range("Catch out_of_range exception!");
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
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return !ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <class T, class Alloc>
	bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
		return ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
	}

	template <class T, class Alloc>
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs){
		return !ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end());
	}

}
