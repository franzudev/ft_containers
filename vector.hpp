#pragma once

#include <memory>
#include <algorithm>
#include "enable_if.hpp"
#include "is_integral.hpp"
#include "iterator.hpp"

namespace ft {
	template <class T>
	class VectorIterator : public iterator<bidirectional_iterator_tag, T, ptrdiff_t, T*, T&> {
	protected:
		T*	current;
	public:
		VectorIterator() {
			current = nullptr;
		}
		~VectorIterator() {};
		VectorIterator(VectorIterator const& it) {
			current = it.current;
		}
		VectorIterator(T *ptr) {
			current = ptr;
		}
		VectorIterator&	operator=(VectorIterator& it) {
			current = it.current;
			return *this;
		}
		VectorIterator&	operator=(T* it) {
			current = it;
			return *this;
		}
		VectorIterator&	operator=(T it) {
			current = it;
			return *this;
		}
		VectorIterator&	operator++() {
			current++;
			return *this;
		}
		VectorIterator	operator++(int) {
			VectorIterator<T> temp = *this;
			++*this;
			return temp;
		}
		VectorIterator&	operator--() {
			current--;
			return *this;
		}
		VectorIterator	operator--(int) {
			VectorIterator<T> temp = *this;
			--*this;
			return temp;
		}
		ptrdiff_t operator-(size_t val) {
			return current - val;
		}
		ptrdiff_t operator-(VectorIterator& val) {
			return current - val.current;
		}
		VectorIterator&	operator+=(size_t n) {
			current += n;
			return *this;
		}
		VectorIterator&	operator-=(size_t n) {
			current -= n;
			return *this;
		}
		T&				operator*(void) {
			return *current;
		}
		template <class Iterator>
		bool operator==(const Iterator& rhs) {
			return current == rhs.current;
		}

		template <class Iterator>
		bool	operator!=(const Iterator &rhs) {
			return current != rhs.current;
		}
	};
	/*template <class T>
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
	}*/

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
		typedef reverse_iterator<iterator>							reverse_iterator;
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
			size_type i = 0;
			for (iterator start = vec.begin(), end = vec.end(), copy = this->begin; start != end; ++start, ++copy, i++) {
				*copy = allocator.construct(_vec + i, *start);
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
		template <class InputIterator>
		void assign (InputIterator first, InputIterator last, typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type* = 0) {
			size_type new_size = std::abs(last - first);
			clean_vector(new_size);
			size_type i = 0;
			for (InputIterator start = first; start != last; start++, i++) {
				allocator.construct(_vec + i, *start);
			}
			_size = new_size;
		}

		void assign(size_type n, const value_type& val) {
			clean_vector(n);
			for (size_type i = 0; i < n; i++)
				_vec[i] = val;
			_size = n;
		}

		void 	push_back(value_type i){
			if (_size + 1 == _capacity)
				reserve(_capacity * 2);
			_vec[_size++] = i;
		}

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
			return *begin();
		}
		const_reference front() const {
			return *begin();
		}
		reference back() {
			return *rbegin();
		}
		const_reference back() const {
			return *rbegin();
		}

	protected:
		size_type 	_size;		// Elements
		size_type 	_capacity;	// Allocated Space
		value_type	*_vec;
	private:
		// maybe static
		allocator_type	allocator;

		void	clean_vector(size_type new_size) {
			for (size_type i = 0; i < _size; i++)
				allocator.destroy(_vec + i);
			allocator.deallocate(_vec, _size);
			_vec = allocator.allocate(new_size + 1);
			_capacity = new_size + 1;
		}
	};
}
