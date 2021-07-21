#pragma once

#include <memory>
#include <algorithm>
#include "iterator.hpp"

namespace ft {
	template <class T>
	class VectorIterator : public iterator<bidirectional_iterator_tag, T, ptrdiff_t, T*, T&> {
	private:
		T*	p;
	public:
		VectorIterator() {
			p = nullptr;
		}
		~VectorIterator() {};
		VectorIterator(VectorIterator const& it){
			p = it.p;
		}
		VectorIterator(T *ptr){
			p = ptr;
		}
		VectorIterator&	operator=(VectorIterator& it) {
			*p = *it.p;
			return *this;
		}
		VectorIterator&	operator=(T* it) {
			*p = *it;
			return *this;
		}
		VectorIterator&	operator=(T it) {
			*p = it;
			return *this;
		}
		VectorIterator&	operator++() {
			p++;
			return *this;
		}
		VectorIterator&	operator++(int) {
			VectorIterator<T> temp(*this);
			++*this;
			return temp;
		}
		VectorIterator&	operator--() {
			p--;
			return *this;
		}
		VectorIterator&	operator--(int) {
			VectorIterator<T> temp(*this);
			--*this;
			return temp;
		}
		VectorIterator operator-(ptrdiff_t val) {
			VectorIterator<T> nV;
			p -= val;
			return *this;
		}
		VectorIterator&	operator+=(int n){
			p += n;
			return *this;
		}
		T&				operator*(void){
			return *p;
		}
		bool operator==(const VectorIterator<T>& rhs) {
			return p == rhs.p;
		}
		bool	operator!=(const VectorIterator<T> &rhs) {
			return p != rhs.p;
		}
	};

	template <class T, class Allocator = std::allocator<T> >
	class vector {
	public:
		typedef T													value_type;
		typedef Allocator											allocator_type;
		typedef std::allocator_traits<allocator_type>         		__alloc_traits;
		typedef typename allocator_type::reference					reference;
		typedef typename allocator_type::const_reference			const_reference;
		typedef typename allocator_type::pointer					pointer;
		typedef typename allocator_type::const_pointer				const_pointer;
		typedef VectorIterator<value_type>							iterator;
		typedef const iterator_traits<value_type *>					const_iterator;
		// to implement
		typedef reverse_iterator<iterator>							reverse_iterator;
		typedef const reverse_iterator								const_reverse_iterator;
		typedef typename iterator_traits<iterator>::difference_type	difference_type;
		typedef size_t												size_type;

		// --- Constructors && Destructors
		vector() {
			allocator_type allocator;
			_vec = allocator.allocate(1);
			_size = 0;
			_capacity = 1;
			_empty = true;
		}
		~vector() {
			allocator_type allocator;
			allocator.deallocate(_vec, _size);
		}
		vector(vector<value_type> const &vec) {
			*this = vec;
		}

		// --- Operator Overloads
		vector<value_type> &operator=(vector<value_type> const &vec) {
			if (_capacity)
				allocator_type::deallocate(_vec, _size);
			_vec = allocator_type::allocate(vec._capacity);
			for (iterator start = vec.begin(), end = vec.end(), copy = this->begin; start != end; ++start, ++copy) {
				*copy = *start;
			}
			_size = vec._size;
			_capacity = vec._capacity;
			_empty = vec._empty;
			return *this;
		}

		// --- Iterators
		iterator	begin(void) {
			if (_size)
				return iterator(_vec);
			return iterator();
		}
		iterator	end(void) {
			if (_size)
				return iterator(&_vec[_size]);
			return iterator();
		}

		// --- Getters
		size_type 	size(void)		const {return _size;}
		size_type 	max_size(void)	const {return allocator_type::max_size();}
		size_type 	capacity(void)	const {return _capacity;}
		bool		empty(void)		const {return _empty;}

		// --- Member Functions
		void 	resize(size_type n)
		{
			if (n < _size) {
				T *tmp = allocator_type().allocate(n + 1);
				for (size_type i = 0; i < n; i++)
					tmp[i] = _vec[i];
				allocator_type().deallocate(_vec, _size);
				_vec = tmp;
				_capacity = n + 1;
				_size = n;
			}
			else if (n >= _size) {
				if (n + 1 > _capacity)
					reserve(n + 1);
				for (size_type i = _size; i < n; i++)
					_vec[_size] = T();
				_size = n;
			}
		}
		void	reserve(size_type n) {
			if (n <= _capacity)
				return;
			pointer tmp = allocator_type().allocate(n);
			_capacity = n;
			for (size_type i = 0; i < _size; i++)
				tmp[i] = _vec[i];
			allocator_type().deallocate(_vec, _size);
			_vec = tmp;
		}
		void 	push_back(T i){
			if (_size + 1 == _capacity)
				reserve(_capacity * 2);
			_vec[_size++] = i;
		}
	protected:
		size_type 	_size;		// Elements
		size_type 	_capacity;	// Allocated Space
		bool		_empty;
		value_type	*_vec;
	};
}
