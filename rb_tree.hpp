#pragma once

#include "pair.hpp"
#include <iostream>
#include "rb_tree_iterators.hpp"

namespace ft {

	enum nodeColor {
		RED,
		BLACK
	};

	template <class T>
	struct less {
		bool operator ()(const T& lhs, const T& rhs) const {
			return lhs < rhs && !(rhs < lhs);
		}
	};

	template <class T>
	struct Node {
		typedef T							value_type;
		typedef value_type					second_type;
		typedef T*							pointer;
		typedef T&							reference;
		typedef bidirectional_iterator_tag	iterator_category;
		typedef	ptrdiff_t					difference_type;

		value_type	data;
		bool		color;
		bool 		bound;
		struct Node *parent;
		struct Node *left;
		struct Node *right;

		Node(T data): data(data), color(BLACK), bound(false), parent(nullptr), left(nullptr), right(nullptr) {}

		bool 		isLeft() const {return parent && this == parent->left;}
		bool 		isRight() const {return parent && this == parent->right;}
		Node		*uncle() const {
			if (parent->parent && parent->isLeft())
				return parent->parent->right;
			if (parent->parent && parent->isRight())
				return parent->parent->left;
			return nullptr;
		}
	};

	template <class T, class Key, class Compare = std::less<Key>, class Alloc = std::allocator<Node<T> > >
	class rb_tree {
	public:
		typedef	Node<T>												node;
		typedef node*												node_ptr;
		typedef typename node::value_type							node_value;
		typedef typename node::second_type							mapped_type;
		typedef Alloc												allocator_type;
		typedef Compare												key_compare;
		typedef key_compare											value_compare;
		typedef typename allocator_type::reference					reference;
		typedef typename allocator_type::const_reference			const_reference;
		typedef typename allocator_type::pointer					pointer;
		typedef typename allocator_type::value_type					value_type;
		typedef typename allocator_type::const_pointer				const_pointer;
		typedef typename allocator_type::size_type					size_type;
		typedef typename allocator_type::difference_type			difference_type;

	public:

//		class value_compare: public std::binary_function<value_type, value_type, bool>
//		{
//			friend class rb_tree;
//		protected:
//			key_compare comp;
//
//			value_compare(key_compare c): comp(c) {}
//		public:
//			bool operator()(const value_type& x, const value_type& y) const {
//				return comp(x.data.first, y.data.first);
//			}
//		};

		//		rb_tree(): _root(nullptr) {}
		explicit rb_tree( const Compare& comp = Compare(), const Alloc& alloc = Alloc()) : _root(nullptr), _comp(comp), _allocator(alloc) {
			_sentinel = _allocator.allocate(1);
			_sentinel->bound = true;
		}
		rb_tree( const rb_tree& tree): _comp(tree._comp){ *this = tree; }

		rb_tree& operator=(const rb_tree& tree) {
			_root = tree.root();
			_sentinel = tree._sentinel;
			_allocator = tree._allocator;
			_comp = tree._comp;
			return *this;
		}

		/*node_ptr copy(node_ptr root) {
			node_ptr new_root;
			if(root!=NULL){
				new_root = _createNode(root->data);
				new_root->color = root->color;
				new_root->left = copy(root->left);
				if (new_root->left)
					new_root->left->parent = new_root;
				new_root->right = copy(root->right);
				if (new_root->right)
					new_root->right->parent = new_root;
			} else return NULL;
			return new_root;
		}*/

		~rb_tree() {}

		void destroy() {
			_cycle(_root);
		}

		size_type	max_size() const { return _allocator.max_size(); }

		node_ptr	root() const {
			return _root;
		}

		ft::pair<node_ptr, bool> insert(T val) {
			if (!_root) {
				_root = _createNode(val);
				add_sentinel();
				return ft::make_pair(_root, true);
			}
			remove_sentinel();
			ft::pair<node_ptr, bool> ret = _insert(_root, val);
			add_sentinel();
			return ret;
		}

		ft::pair<node_ptr, bool> insert(node_ptr hint, T val) {
			(void)hint;
			if (!_root) {
				_root = _createNode(val);
				add_sentinel();
				return ft::make_pair(_root, true);
			}
			remove_sentinel();
			ft::pair<node_ptr, bool> ret = _insert(_root, val);
			add_sentinel();
			return ret;
		}

		node_ptr find(const node_value val) const {
			node_ptr found = _find(_root, val);
			if (!found)
				return NULL;
			return found;
		}

		node_ptr deletion(Key val) {
			node_ptr toDelete = find(_root, val);
			if (!toDelete)
				return nullptr;
			//case root
			if (!toDelete->parent) {}
			//case leaf
			if (toDelete->parent && !toDelete->left && !toDelete->right) {

			}
			// case inside
			if (toDelete->parent) {}

		}

		void printTree() {
			_printTreeHelper(_root,0);
		}

		node_ptr	bound() const {
			return _sentinel;
		}

		node_ptr	right() {
			node_ptr	ptr = _root;
			if (!ptr)
				return ptr;
			while (ptr->right && ptr->right != _sentinel)
				ptr = ptr->right;
			return (ptr);
		}

		node_ptr	left() {
			node_ptr	ptr = _root;
			if (!ptr)
				return ptr;
			while (ptr->left && ptr->left != _sentinel)
				ptr = ptr->left;
			return (ptr);
		}
		node_ptr	right() const {
			node_ptr	ptr = _root;
			if (!ptr)
				return ptr;
			while (ptr->right && ptr->right != _sentinel)
				ptr = ptr->right;
			return (ptr);
		}

		node_ptr	left() const {
			node_ptr	ptr = _root;
			if (!ptr)
				return ptr;
			while (ptr->left && ptr->left != _sentinel)
				ptr = ptr->left;
			return (ptr);
		}

	private:

		void	add_sentinel() {
			right()->right = _sentinel;
			_sentinel->left = right();
			left()->left = _sentinel;
			_sentinel->right = left();
			_root->parent = _sentinel;
		}
		void	remove_sentinel() {
			right()->right = nullptr;
			left()->left = nullptr;
			_root->parent = nullptr;
		}
		void	_cycle(node_ptr& p) {
			if (!p || p->bound)
				return ;
			if (p->left)
				_cycle(p->left);
			if (p->right)
				_cycle(p->right);
			_allocator.destroy(p);
			_allocator.deallocate(p, 1);
			p = nullptr;
		}

		node_ptr	_createNode(value_type val) {
			node_ptr	ptr;
			ptr = _allocator.allocate(1);
			_allocator.construct(ptr, val);
			return ptr;
		}

		ft::pair<node_ptr, bool> _insert(node_ptr start, T val) {
			if (start->data == val)
				return ft::make_pair(start, false);
			if (!value_comp()(start->data, val)) {
				if (!start->left)
					return _setLeftNode(start, _createNode(val));
				return _insert(start->left, val);
			}
			if (value_comp()(start->data, val)) {
				if (!start->right)
					return _setRightNode(start, _createNode(val));
				return _insert(start->right, val);
			}
			return ft::make_pair(start, false);
		}

		node_ptr _find(node_ptr node, const node_value val) const {
			if (!node || node->bound)
				return nullptr;
			if (value_comp()(node->data, val) && !value_comp()(val, node->data))
				return _find(node->right, val);
			if (!value_comp()(node->data, val) && value_comp()(val, node->data))
				return _find(node->left, val);
			return node;
		}

		void	_balance(node_ptr ptr) {
			if (ptr == _root) {
				ptr->color = BLACK;
				return ;
			}
			if (!ptr)
				return ;
			if (!ptr->parent->color && !ptr->color) {
				if (ptr->uncle() && !ptr->uncle()->color) {
					ptr->parent->color = BLACK;
					ptr->uncle()->color = BLACK;
					ptr->parent->parent->color = RED;
				}
				else {
					if (ptr->isLeft() && ptr->parent->isLeft())
						_rightRotate(ptr->parent, ptr->parent->parent);
					else if (ptr->isRight() && ptr->parent->isRight())
						_leftRotate(ptr->parent, ptr->parent->parent);
					else if (ptr->isLeft() && ptr->parent->isRight())
						_rightLeftRotate(ptr, ptr->parent, ptr->parent->parent);
					else if (ptr->isRight() && ptr->parent->isLeft())
						_leftRightRotate(ptr, ptr->parent, ptr->parent->parent);
				}
			}
			_balance(ptr->parent);
		}

		void	 _rightRotate(node_ptr parent, node_ptr gparent) {
			node_ptr buff = parent->right;
			parent->right = gparent;
			if (gparent->parent && gparent->isLeft())
				gparent->parent->left = parent;
			else if (gparent->parent && gparent->isRight())
				gparent->parent->right = parent;
			parent->parent = gparent->parent;
			gparent->parent = parent;
			if (buff)
				buff->parent = gparent;
			gparent->left = buff;
			if (!parent->parent)
				_root = parent;
			gparent->color = RED;
			parent->color = BLACK;
		}

		void	_leftRotate(node_ptr parent, node_ptr gparent) {
			node_ptr buff = parent->left;
			parent->left = gparent;
			if (gparent->parent && gparent->isLeft())
				gparent->parent->left = parent;
			else if (gparent->parent && gparent->isRight())
				gparent->parent->right = parent;
			parent->parent = gparent->parent;
			gparent->parent = parent;
			if (buff)
				buff->parent = gparent;
			gparent->right = buff;
			if (!parent->parent)
				_root = parent;
			gparent->color = RED;
			parent->color = BLACK;
		}

		void	_leftRightRotate(node_ptr child, node_ptr parent, node_ptr gparent) {
			gparent->left = child;
			child->parent = gparent;
			if (child->left) {
				parent->right = child->left;
				child->left->parent = parent;
			} else
				parent->right = nullptr;
			child->left = parent;
			parent->parent = child;
			_rightRotate(child, gparent);
		}

		void	_rightLeftRotate(node_ptr child, node_ptr parent, node_ptr gparent) {
			gparent->right = child;
			child->parent = gparent;
			if (child->right){
				parent->left = child->right;
				child->right->parent = parent;
			} else
				parent->left = nullptr;
			child->right = parent;
			parent->parent = child;
			_leftRotate(child, gparent);
		}

		ft::pair<node_ptr, bool> _setNode(node_ptr parent, node_ptr child) {
			child->parent = parent;
			child->color = RED;
			_balance(child);
			return ft::make_pair(child, true);
		}

		ft::pair<node_ptr, bool> _setLeftNode(node_ptr parent, node_ptr child) {
			parent->left = child;
			return _setNode(parent, child);
		}

		ft::pair<node_ptr, bool> _setRightNode(node_ptr parent, node_ptr child) {
			parent->right = child;
			return _setNode(parent, child);
		}

		void _printTreeHelper(node_ptr root, int space)
		{
			int i;
			if(root != nullptr)
			{
				space = space + 10;
				_printTreeHelper(root->right, space);
				std::cout << std::endl;
				for ( i = 10; i < space; i++)
				{
					std::cout << " ";
				}
				std::string color = root->color ? "" : "\e[31m";
				std::cout << color << root->data.first << '/' << root->data.second << "\e[0m" << std::endl;
				_printTreeHelper(root->left, space);
			}
		}

		value_compare value_comp() const {
			return _comp;
		}

	private:
		node_ptr		_root;
		key_compare 	_comp;
		allocator_type	_allocator;
		node_ptr		_sentinel;
	};
}
