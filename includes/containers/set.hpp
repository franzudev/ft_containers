#pragma once

#ifndef USE_STL
#include "../utils/enable_if.hpp"
#endif
#include "../utils/lexicographical_compare.hpp"
#include "../rb_tree/rb_tree.hpp"
#include "../utils/pair.hpp"
#include "../utils/is_integral.hpp"
#include "../utils/less.hpp"


namespace ft {

	template < class Key, class Compare = ft::keyLess<Key>, class Alloc = std::allocator<const Key> >
	class set {
	public:
		// --- Definitions
		typedef Key													key_type;
		typedef key_type											mapped_type;
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
		typedef ft::rb_tree_iterator<Node<value_type> >				const_iterator;
		typedef ft::reverse_iterator<iterator>						reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>				const_reverse_iterator;
		// definitions

		class value_compare: public std::binary_function<value_type, value_type, bool>
		{
			friend class set;
		protected:
			key_compare comp;

			value_compare(key_compare c): comp(c) {}
		public:
			bool operator()(const value_type& x, const value_type& y) const {
				return comp(x, y);
			}
		};

		typedef rb_tree<value_type, Key, value_compare>				tree;
		typedef Node<value_type>*									node_ptr;

		// --- constructors
		explicit set( const Compare& comp = Compare(), const Alloc& alloc = Alloc()) : _tree(tree(value_compare(key_comp()))), _comp(comp), _alloc(alloc), _size(0) {}

		template< class InputIt > set( InputIt first, InputIt last, const Compare& comp = Compare(), const Alloc& alloc = Alloc()) : _tree(tree(value_compare(key_comp()))), _comp(comp), _alloc(alloc), _size(0) {
			for (; first != last; ++first)
				insert(*first);
		}

		set( const set& other ): _tree(tree(value_compare(key_comp()))) {
			*this = other;
		}

		~set() {
			_tree.destroy(true);
		}
		// constructors

		// ---operators overload
		set& operator=( const set& other ) {
			_tree.destroy(false);
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
			_tree.destroy(false);
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

		void erase( iterator pos ) {
			erase(pos.operator*());
		}
		void erase( iterator first, iterator last ) {
			if (first == begin() && last == end())
				return clear();
			size_type len = 0;
			for (iterator begin = first; begin != last; ++begin)
				len++;
			key_type toRem[len];
			iterator begin = first;
			size_type i = 0;
			for (; begin != last; ++begin, ++i)
				toRem[i] = begin.operator*();
			i = 0;
			while (i < len) {
				erase(toRem[i]);
				++i;
			}
		}
		size_type erase( const key_type& key ) {
			size_type ret;
			_size -= (ret = _tree.erase(key));
			return ret;
		}

		void swap( set& other ) {
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
			node_ptr found = _tree.find(key);
			if (!found)
				return 0;
			return 1;
		}

		iterator find( const Key& key ) {
			node_ptr found = _tree.find(key);
			if (!found)
				return end();
			return iterator(found);
		}

		const_iterator find( const Key& key ) const {
			node_ptr found = _tree.find(key);
			if (!found)
				return end();
			return const_iterator(found);
		}

		iterator lower_bound( const Key& key ) {
			return iterator(_tree.lower_bound(key));
		}

		const_iterator lower_bound( const Key& key ) const {
			return iterator(_tree.lower_bound(key));
		}

		iterator upper_bound( const Key& key ) {
			return iterator(_tree.upper_bound(key));
		}

		const_iterator upper_bound( const Key& key ) const {
			return iterator(_tree.upper_bound(key));
		}

		ft::pair<iterator,iterator> equal_range( const Key& key ) {
			return (ft::make_pair<iterator, iterator>(lower_bound(key), upper_bound(key)));
		}
		ft::pair<const_iterator,const_iterator> equal_range( const Key& key ) const {
			return (ft::make_pair<const_iterator, const_iterator>(lower_bound(key), upper_bound(key)));
		}
		//

		// --- Observers
		key_compare key_comp() const {
			return Compare();
		}
		set::value_compare value_comp() const {
			return value_compare(key_comp());
		}

	private:
		tree			_tree;
		key_compare		_comp;
		allocator_type	_alloc;
		size_type		_size;
	};

	template <typename Key, typename Compare>
	void swap(set<Key, Compare> &x, set<Key, Compare> &y)
	{
		x.swap(y);
	}
	template <class Key, class Compare, class Alloc>
	bool operator== (const set<Key,Compare,Alloc> & lhs, const set<Key,Compare,Alloc> & rhs)
	{
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class Key, class Compare, class Alloc>
	bool operator!= (const set<Key,Compare,Alloc> & lhs, const set<Key,Compare,Alloc> & rhs)
	{
		return (!(lhs == rhs));
	}

	template <class Key, class Compare, class Alloc>
	bool operator<  (const set<Key,Compare,Alloc> & lhs, const set<Key,Compare,Alloc> & rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <class Key, class Compare, class Alloc>
	bool operator<= (const set<Key,Compare,Alloc> & lhs, const set<Key,Compare,Alloc> & rhs)
	{
		return !(rhs < lhs);
	}
	template <class Key, class Compare, class Alloc>
	bool operator>  (const set<Key,Compare,Alloc> & lhs, const set<Key,Compare,Alloc> & rhs)
	{
		return (rhs < lhs);
	}

	template <class Key, class Compare, class Alloc>
	bool operator>= (const set<Key,Compare,Alloc> & lhs, const set<Key,Compare,Alloc> & rhs)
	{
		return (!(lhs < rhs));
	}
}
