#pragma once

#include "enable_if.hpp"
#include "lexicographical_compare.hpp"
#include "rb_tree.hpp"
#include "pair.hpp"
#include "is_integral.hpp"

#include <map>

namespace ft {

	template <class Pair>
	struct keyLess {
		bool operator ()(const Pair& p1, const Pair& p2) const {
			return p1 < p2;
		}
	};

	template < class Key, class T, class Compare = ft::keyLess<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > >
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

		typedef ft::rb_tree_iterator<Node<value_type> >				iterator;
		typedef ft::const_rb_tree_iterator<Node<value_type> >		const_iterator;
		typedef ft::reverse_iterator<iterator>						reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>				const_reverse_iterator;
		// definitions

		class value_compare: public std::binary_function<value_type, value_type, bool>
		{
			friend class map;
		protected:
			key_compare comp;

			value_compare(key_compare c): comp(c) {}
		public:
			bool operator()(const value_type& x, const value_type& y) const {
				return comp(x.first, y.first);
			}
		};

		typedef rb_tree<value_type, Key, value_compare>					tree;
		typedef Node<value_type>*									node_ptr;
		typedef Node<value_type>									node;

		// --- constructors
		explicit map( const Compare& comp = Compare(), const Alloc& alloc = Alloc()) : _tree(tree(value_compare(key_comp()))), _comp(comp), _alloc(alloc), _size(0) {
			;
		}
		template< class InputIt > map( InputIt first, InputIt last, const Compare& comp = Compare(), const Alloc& alloc = Alloc()) : _tree(tree(value_compare(key_comp()))), _comp(comp), _alloc(alloc), _size(0) {
			for (; first != last; ++first)
				insert(*first);
		}
		map( const map& other ): _tree(tree(value_compare(key_comp()))) {
			*this = other;
		}
		~map() {
			_tree.destroy();
		}
		// constructors

		// ---operators overload
		map& operator=( const map& other ) {
			_tree.destroy();
			insert(other.begin(), other.end());
			_size = other._size;
			return *this;
		}
		// operators overload

		// ---getters
		allocator_type get_allocator() const {
			return _alloc;
		}
		// getters

		// --- element access
		class out_of_range: public std::out_of_range {
		public:
			explicit out_of_range(std::string str): std::out_of_range(str) {}
		};

		mapped_type& operator[](const key_type& k) {
			node_ptr found = _tree.find(ft::make_pair(k, mapped_type()));
			if (!found)
				return insert(ft::make_pair(k, T())).first->second;
			return found->data.second;
		}
		mapped_type& at(const key_type& k) {
			node_ptr found = _tree.find(ft::make_pair(k, mapped_type()));
			if (!found)
				throw out_of_range("map::at:  key not found");
			return found->data.second;
		}
		const mapped_type& at(const key_type& k) const {
			node_ptr found = _tree.find(ft::make_pair(k, mapped_type()));
			if (!found)
				throw out_of_range("map::at:  key not found");
			return found->data.second;
		}
		// element access

		// --- iterators
		iterator begin() {
			if (!_tree.root())
				return end();
			return iterator(_tree.left());
		}

		const_iterator begin() const {
			if (!_tree.root())
				return end();
			return const_iterator(_tree.left());
		}

		iterator end() {
			return iterator(_tree.bound());
		}

		const_iterator end() const {
			return iterator(_tree.bound());
		}

		reverse_iterator rbegin() {
			return reverse_iterator(end());
		}
		const_reverse_iterator rbegin() const {
			return reverse_iterator(end());
		}
		reverse_iterator rend() {
			return reverse_iterator(begin());
		}
		const_reverse_iterator rend()   const {
			return reverse_iterator(begin());
		}
		// iterators

		// --- Capacity
		bool empty() const {return !_size;}
		size_type size() const { return _size; }
		size_type max_size() const {return _tree.max_size();}
		// capacity

		// --- modifiers
		void clear() {
			_tree.destroy();
			_size = 0;
		}

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
		void swap( map& other ) {
			tree tmp = other._tree;
			size_type size = other._size;

			other._tree = _tree;
			_tree = tmp;
			other._size = _size;
			_size = size;

		}
		//

		// --- Lookup
		size_type count( const Key& key ) const {
			node_ptr found = _tree.find(ft::make_pair(key, mapped_type()));
			if (!found)
				return 0;
			return 1;
		}
		iterator find( const Key& key ) {
			node_ptr found = _tree.find(ft::make_pair(key, mapped_type()));
			if (!found)
				return end();
			return iterator(found);
		}
		const_iterator find( const Key& key ) const {
			node_ptr found = _tree.find(ft::make_pair(key, mapped_type()));
			if (!found)
				return end();
			return const_iterator(found);
		}
		iterator lower_bound( const Key& key ) {
			return iterator(_tree.lower_bound(ft::make_pair(key, mapped_type())));
		}
		const_iterator lower_bound( const Key& key ) const {
			return iterator(_tree.lower_bound(ft::make_pair(key, mapped_type())));
		}
		iterator upper_bound( const Key& key ) {
			return iterator(_tree.upper_bound(ft::make_pair(key, mapped_type())));
		}
		const_iterator upper_bound( const Key& key ) const {
			return iterator(_tree.upper_bound(ft::make_pair(key, mapped_type())));
		}
		//

		ft::pair<iterator,iterator> equal_range( const Key& key ) {
			return (ft::make_pair<iterator, iterator>(this->lower_bound(key), this->upper_bound(key)));
		}
		ft::pair<const_iterator,const_iterator> equal_range( const Key& key ) const {
			return (ft::make_pair<const_iterator, const_iterator>(this->lower_bound(key), this->upper_bound(key)));
		}

		// --- Observers
		key_compare key_comp() const {
			return Compare();
		}
		map::value_compare value_comp() const {
			return value_compare(key_comp());
		}
		void ft_print()
		{
			_tree.printTree();
		}
	private:
		tree			_tree;
		key_compare		_comp;
		allocator_type	_alloc;
		size_type		_size;
	};

	template <class InputIterator1, class InputIterator2>
	bool equal (InputIterator1 lit, InputIterator1 lend, InputIterator2 rit, InputIterator2 rend)
	{
		while (lit != lend)
		{
			if (rit == rend || *rit != *lit)
				return (false);
			++lit, ++rit;
		}

		return (rit == rend);
	}

	template <typename Key, typename T, typename Compare>
	void swap(map<Key, T, Compare> &x, map<Key, T, Compare> &y)
	{
		x.swap(y);
	}
	template <class Key, class T, class Compare, class Alloc>
	bool operator== (const map<Key,T,Compare,Alloc> & lhs, const map<Key,T,Compare,Alloc> & rhs)
	{
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator!= (const map<Key,T,Compare,Alloc> & lhs, const map<Key,T,Compare,Alloc> & rhs)
	{
		return (!(lhs == rhs));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<  (const map<Key,T,Compare,Alloc> & lhs, const map<Key,T,Compare,Alloc> & rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<= (const map<Key,T,Compare,Alloc> & lhs, const map<Key,T,Compare,Alloc> & rhs)
	{
		return !(rhs < lhs);
	}
	template <class Key, class T, class Compare, class Alloc>
	bool operator>  (const map<Key,T,Compare,Alloc> & lhs, const map<Key,T,Compare,Alloc> & rhs)
	{
		return (rhs < lhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>= (const map<Key,T,Compare,Alloc> & lhs, const map<Key,T,Compare,Alloc> & rhs)
	{
		return (!(lhs < rhs));
	}
}
