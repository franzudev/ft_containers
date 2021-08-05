#pragma once

#include "enable_if.hpp"
#include "lexicographical_compare.hpp"
#include "rb_tree.hpp"
#include "pair.hpp"
#include "iterator.hpp"
#include "is_integral.hpp"

#include <map>

namespace ft {

	template <class Pair>
	struct keyLess {
		bool operator ()(const Pair& p1, const Pair& p2) const {
			return p1.first < p2.first;
		}
	};

	template<class Pointer, class Value>
	struct map_iterator {
		typedef Pointer*													iterator;
		typedef Pointer                                                     iterator_type;
		typedef Value														value;
		typedef typename iterator_traits<iterator_type>::iterator_category	iterator_category;
		typedef typename iterator_traits<iterator_type>::value_type			value_type;
		typedef typename iterator_traits<iterator_type>::difference_type	difference_type;
		typedef typename iterator_traits<iterator_type>::pointer			pointer;
		typedef typename iterator_traits<iterator_type>::reference         	reference;

		explicit map_iterator(): m_ptr(nullptr){};

		explicit map_iterator(iterator ptr): m_ptr(ptr) {}

		template<class Iter>
		map_iterator(map_iterator<Iter, Value> const & other) {
			*this = other;
		}

		value operator*() const { return m_ptr->key; }

		value *operator->() const { return &m_ptr->key; }

		// Prefix increment
		map_iterator &operator++() {
			if (m_ptr->right) {
				m_ptr = m_ptr->right;
				while (m_ptr->left)
					m_ptr = m_ptr->left;
			}
			else if (m_ptr->isLeft()) {
				m_ptr = m_ptr->parent;
			} else {
				while (m_ptr->parent && !m_ptr->isLeft())
					m_ptr = m_ptr->parent;
				m_ptr = m_ptr->parent;
			}
			return *this;
		}

		// Postfix increment
		map_iterator operator++(int) { map_iterator tmp = *this; ++*this; return tmp; }

		// Prefix decrement
		map_iterator &operator--() {
			if (m_ptr->left) {
				m_ptr = m_ptr->left;
				while (m_ptr->right)
					m_ptr = m_ptr->right;
			}
			else if (m_ptr->isRight()) {
				m_ptr = m_ptr->parent;
			} else {
				while (m_ptr->parent && !m_ptr->isRight())
					m_ptr = m_ptr->parent;
				m_ptr = m_ptr->parent;
			}
			return *this;
		}

		// Postfix decrement
		map_iterator operator--(int) { map_iterator tmp = *this; --*this; return tmp; }

		iterator	base() const {
			return m_ptr;
		}

		template <class Iter>
		map_iterator&	operator=(map_iterator<Iter, Value> const & other) {
			m_ptr = other.base();
			return *this;
		}

		friend bool	operator==(const map_iterator& lhs, const map_iterator& rhs) {
			return lhs.m_ptr == rhs.m_ptr;
		}
		friend bool	operator!=(const map_iterator& lhs, const map_iterator& rhs) {
			return lhs.m_ptr != rhs.m_ptr;
		}
	private:
		iterator m_ptr;
	};

	template < class Key, class T, class Compare = keyLess<ft::pair<const Key,T> >, class Alloc = std::allocator<ft::pair<const Key,T> > >
	class map {
	public:
		// --- Definitions
		typedef Key													key_type;
		typedef T													mapped_type;
		typedef Compare												key_compare;
		typedef Alloc												allocator_type;
		typedef typename allocator_type::reference					reference;
		typedef typename allocator_type::const_reference			const_reference;
		typedef typename allocator_type::pointer					pointer;
		typedef typename allocator_type::value_type					value_type;
		typedef typename allocator_type::const_pointer				const_pointer;
		typedef typename allocator_type::size_type					size_type;
		typedef typename allocator_type::difference_type			difference_type;
		typedef rb_tree<value_type>									tree;
		typedef Node<value_type>*									node_ptr;
		typedef Node<value_type>									node;

		typedef ft::map_iterator<node, value_type>					iterator;
		typedef ft::map_iterator<const node, const value_type>		const_iterator;
		typedef std::reverse_iterator<iterator>						reverse_iterator;
		typedef std::reverse_iterator<const_iterator>				const_reverse_iterator;
		// definitions

//		class value_compare: public binary_function<value_type, value_type, bool>
//		{
//			friend class map;
//		protected:
//			key_compare comp;
//
//			value_compare(key_compare c);
//		public:
//			bool operator()(const value_type& x, const value_type& y) const;
//		};

		// --- constructors
		explicit map( const Compare& comp = Compare(), const Alloc& alloc = Alloc()) : _comp(comp), _alloc(alloc), _size(0) {}
		template< class InputIt > map( InputIt first, InputIt last, const Compare& comp = Compare(), const Alloc& alloc = Alloc()) : _comp(comp), _alloc(alloc), _size(0) {
			for (; first != last; ++first)
				insert(*first);
		}
		map( const map& other ) {
			*this = other;
		}
		~map() {};
		// constructors

		// ---operators overload
		map& operator=( const map& other ) {
			_tree.~rb_tree();
			for (const_iterator it = other.begin(); it != other.end(); ++it)
				insert(it.base()->key);
			return *this;
		}
		// operators overload

		// ---getters
//		allocator_type get_allocator() const {}
		// getters

		// --- element access
//		mapped_type& operator[](const key_type& k) {}
//		mapped_type& at(const key_type& k) {}
//		const mapped_type& at(const key_type& k) const {}
		// element access

		// --- iterators
		iterator begin() {
			node_ptr ret = _tree.root();
			if (!ret)
				return iterator(ret);
			while (ret->left)
				ret = ret->left;
			return iterator(ret);
		}

		const_iterator begin() const {
			node_ptr ret = _tree.root();
			if (!ret)
				return const_iterator(ret);

			while (ret->left)
				ret = ret->left;
			return const_iterator(ret);
		}

		iterator end() {
			node_ptr ret = _tree.root();
			if (!ret)
				return iterator(ret);

			while (ret)
				ret = ret->right;
			return iterator(ret);
		}

		const_iterator end() const {
			node_ptr ret = _tree.root();
			if (!ret)
				return const_iterator(ret);

			while (ret)
				ret = ret->right;
			return const_iterator(ret);
		}

//		reverse_iterator rbegin() {}
//		const_reverse_iterator rbegin() const {}
//		reverse_iterator rend() {}
//		const_reverse_iterator rend()   const {}
		// iterators

		// --- Capacity
		bool empty() const {return !_size;}
		size_type size() const { return _size; }
		size_type max_size() const {return _tree.max_size();}
		// capacity

		// --- modifiers
//		void clear() {}

		template< class InputIt>
		void insert( InputIt first, InputIt last, typename enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = 0) {
			for (InputIt begin = first; begin != last; ++begin)
				insert(*begin);
		}

		ft::pair<iterator, bool> insert( const value_type& value ) {
			ft::pair<node_ptr, bool> inserted = _tree.insert(value);
			if (inserted.second) ++_size;
			return ft::make_pair(iterator(inserted.first), inserted.second);
		}

		iterator insert( iterator hint, const value_type& value ) {
			ft::pair<node_ptr, bool> inserted = _tree.insert(hint.base(), value);
			if (inserted.second) ++_size;
			return iterator(inserted.first);
		}

//		void erase( iterator pos ) {}
//		void erase( iterator first, iterator last ) {}
//		size_type erase( const key_type& key ) {}
//		void swap( map& other ) {}
		//

		// --- Lookup
//		size_type count( const Key& key ) const {}
//		iterator find( const Key& key ) {}
//		const_iterator find( const Key& key ) const {}
//		std::pair<iterator,iterator> equal_range( const Key& key ) {}
//		std::pair<const_iterator,const_iterator> equal_range( const Key& key ) const {}
//		iterator lower_bound( const Key& key ) {}
//		const_iterator lower_bound( const Key& key ) const {}
//		iterator upper_bound( const Key& key ) {}
//		const_iterator upper_bound( const Key& key ) const {}
		//

		// --- Observers
		key_compare key_comp() const {
			return key_compare();
		}
//		map::value_compare value_comp() const {}

	private:
		tree			_tree;
		key_compare		_comp;
		allocator_type	_alloc;
		size_type		_size;
	};
}
