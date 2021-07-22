#pragma once

#include <memory>
#include <algorithm>
#include "iterator.hpp"

namespace ft {
	template <class T>
	class VectorIterator : public iterator<bidirectional_iterator_tag, T, ptrdiff_t, T*, T&> {
	protected:
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
		VectorIterator	operator++(int) {
			VectorIterator<T> temp = *this;
			++*this;
			return temp;
		}
		VectorIterator&	operator--() {
			p--;
			return *this;
		}
		VectorIterator	operator--(int) {
			VectorIterator<T> temp = *this;
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
	template <class T>
	class VectorReverseIterator : public iterator<bidirectional_iterator_tag, T, ptrdiff_t, T*, T&> {
	protected:
		T*	p;
	public:
		VectorReverseIterator() {
			p = nullptr;
		}
		~VectorReverseIterator() {};
		VectorReverseIterator(VectorReverseIterator const& it){
			p = it.p;
		}
		VectorReverseIterator(T *ptr){
			p = ptr;
		}
		VectorReverseIterator&	operator=(VectorReverseIterator& it) {
			*p = *it.p;
			return *this;
		}
		VectorReverseIterator&	operator=(T* it) {
			*p = *it;
			return *this;
		}
		VectorReverseIterator&	operator=(T it) {
			*p = it;
			return *this;
		}
		VectorReverseIterator&	operator++() {
			p--;
			return *this;
		}
		VectorReverseIterator	operator++(int) {
			VectorReverseIterator<T> temp = *this;
			++*this;
			return temp;
		}
		VectorReverseIterator&	operator--() {
			p++;
			return *this;
		}
		VectorReverseIterator	operator--(int) {
			VectorReverseIterator<T> temp = *this;
			--*this;
			return temp;
		}
		VectorReverseIterator operator-(ptrdiff_t val) {
			VectorReverseIterator<T> nV;
			p -= val;
			return *this;
		}
		VectorReverseIterator&	operator+=(int n){
			p += n;
			return *this;
		}
		T&				operator*(void){
			return *p;
		}
		bool operator==(const VectorReverseIterator<T>& rhs) {
			return p == rhs.p;
		}
		bool	operator!=(const VectorReverseIterator<T> &rhs) {
			return p != rhs.p;
		}
	};

	template <class T, class Allocator = std::allocator<T> >
	class vector {
	public:
		typedef T													value_type;
		typedef Allocator											allocator_type;
		typedef typename allocator_type::reference					reference;
		typedef typename allocator_type::const_reference			const_reference;
		typedef typename allocator_type::pointer					pointer;
		typedef typename allocator_type::const_pointer				const_pointer;
		typedef VectorIterator<value_type>							iterator;
		typedef const iterator										const_iterator;
		// to implement
		typedef VectorReverseIterator<value_type>					reverse_iterator;
		typedef const reverse_iterator								const_reverse_iterator;
		typedef typename iterator_traits<iterator>::difference_type	difference_type;
		typedef size_t												size_type;

		// --- Constructors && Destructors
		vector() {
			_vec = allocator.allocate(1);
			_size = 0;
			_capacity = 1;
		}
		~vector() {
			allocator.deallocate(_vec, _size);
		}
		vector(vector<value_type> const &vec) {
			*this = vec;
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
				allocator.deallocate(_vec, _size);
			_vec = allocator.allocate(vec._capacity);
			for (iterator start = vec.begin(), end = vec.end(), copy = this->begin; start != end; ++start, ++copy) {
				*copy = *start;
			}
			_size = vec._size;
			_capacity = vec._capacity;
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
		const_iterator 	begin(void) const{
			if (_size)
				return iterator(_vec);
			return iterator();
		}
		const_iterator	end(void) const{
			if (_size)
				return iterator(&_vec[_size]);
			return iterator();
		}
		reverse_iterator rbegin(void) {
			if (_size)
				return reverse_iterator(&_vec[_size - 1]);
			return reverse_iterator();
		}
		reverse_iterator rend(void) {
			if (_size)
				return reverse_iterator(_vec - 1);
			return reverse_iterator();
		}
		const_reverse_iterator rbegin(void) const{
			if (_size)
				return reverse_iterator(&_vec[_size - 1]);
			return reverse_iterator();
		}
		const_reverse_iterator rend(void) const{
			if (_size)
				return reverse_iterator(_vec - 1);
			return reverse_iterator();
		}

		//Modifiers


		// --- Getters
		size_type 	size(void)		const {return _size;}
		size_type 	max_size(void)	const {return allocator_type::max_size();}
		size_type 	capacity(void)	const {return _capacity;}
		bool		empty(void)		const {return !_size;}

		// --- Member Functions
		void 	resize(size_type n)
		{
			if (n < _size) {
				pointer tmp = allocator.allocate(n + 1);
				for (size_type i = 0; i < n; i++)
					tmp[i] = _vec[i];
				allocator.deallocate(_vec, _size);
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
			pointer tmp = allocator.allocate(n);
			_capacity = n;
			for (size_type i = 0; i < _size; i++)
				tmp[i] = _vec[i];
			allocator.deallocate(_vec, _size);
			_vec = tmp;
		}
		void 	push_back(T i){
			if (_size + 1 == _capacity)
				reserve(_capacity * 2);
			_vec[_size++] = i;
		}
		allocator_type get_allocator(void) const {
			return allocator;
		}
		// Element access
		reference operator[](size_type index) {
			if (index >= _size)
				return *end();
			return _vec[index];
		}
		const_reference operator[](size_type index) const {
			if (index >= _size)
				return *end();
			return _vec[index];
		}
		reference at(size_type index) {
			if (index >= _size)
				throw out_of_range();
			return _vec[index];
		}
		const_reference at(size_type index) const {
			if (index >= _size)
				throw out_of_range();
			return _vec[index];
		}
		reference front() {
			if (empty())
				return *end();
			return *begin();
		}
		const_reference front() const {
			if (empty())
				return *end();
			return *begin();
		}
		reference back() {
			if (empty())
				return *end();
			return *rbegin();
		}
		const_reference back() const {
			if (empty())
				return *end();
			return *rbegin();
		}

	protected:
		size_type 	_size;		// Elements
		size_type 	_capacity;	// Allocated Space
		value_type	*_vec;
	private:
		// maybe static
		allocator_type	allocator;
	};
}
