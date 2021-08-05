#pragma once

#include "pair.hpp"
#include <iostream>
#include "iterator.hpp"

namespace ft {

	enum nodeColor {
		RED,
		BLACK
	};

	template <class T>
	struct less {
		bool operator ()(const T& lhs, const T& rhs) const {
			return lhs < rhs;
		}
	};

	template <class T>
	struct Node {
		typedef T							value_type;
		typedef T*							pointer;
		typedef T&							reference;
		typedef bidirectional_iterator_tag	iterator_category;
		typedef	ptrdiff_t					difference_type;

		value_type	key;
		bool		color;
		struct Node *parent;
		struct Node *left;
		struct Node *right;

		Node(T key): key(key), color(BLACK), parent(nullptr), left(nullptr), right(nullptr) {}

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

	template <class T, class Key, class Alloc = std::allocator<Node<T> > >
	class rb_tree {
	public:
		typedef	Node<T>												node;
		typedef node*												node_ptr;
		typedef typename node::value_type							node_value;
		typedef Alloc												allocator_type;
		typedef typename allocator_type::reference					reference;
		typedef typename allocator_type::const_reference			const_reference;
		typedef typename allocator_type::pointer					pointer;
		typedef typename allocator_type::value_type					value_type;
		typedef typename allocator_type::const_pointer				const_pointer;
		typedef typename allocator_type::size_type					size_type;
		typedef typename allocator_type::difference_type			difference_type;

	public:
		rb_tree(): _root(nullptr) {}

		void	_cycle(node_ptr& p) {
			if (!p)
				return ;
			if (p->left)
				_cycle(p->left);
			if (p->right)
				_cycle(p->right);
			_allocator.destroy(p);
			_allocator.deallocate(p, 1);
			p = nullptr;
		}
		~rb_tree() {
			_cycle(_root);
		}
		size_type	max_size() const { return _allocator.max_size(); }

		node_ptr	root() const {
			return _root;
		}

		ft::pair<node_ptr, bool> insert(T val) {
			if (!_root)
				return ft::make_pair(_root = createNode(val), true);
			return _insert(_root, val);
		}

		ft::pair<node_ptr, bool> insert(node_ptr hint, T val) {
			(void)hint;
			if (!_root)
				return ft::make_pair(_root = createNode(val), true);
			return _insert(_root, val);
		}

		node_value *find(const Key val) {
			node_ptr found = _find(_root, val);
			if (!found)
				return NULL;
			return &found->key;
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

	private:

		node_ptr	createNode(value_type val) {
			node_ptr	ptr;
			ptr = _allocator.allocate(1);
			_allocator.construct(ptr, val);
			return ptr;
		}

		ft::pair<node_ptr, bool> _insert(node_ptr start, T val) {
			if (start->key == val)
				return ft::make_pair(start, false);
			if (start->key > val) {
				if (!start->left)
					return _setLeftNode(start, createNode(val));
				return _insert(start->left, val);
			}
			if (start->key < val) {
				if (!start->right)
					return _setRightNode(start, createNode(val));
				return _insert(start->right, val);
			}
			return ft::make_pair(start, false);
		}

		node_ptr _find(node_ptr node, const Key val) {
			if (!node)
				return nullptr;
			if (node->key < val)
				return _find(node->right, val);
			if (node->key > val)
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
				std::cout << color << root->key.first << '/' << root->key.second << "\e[0m" << std::endl;
				_printTreeHelper(root->left, space);
			}
		}

	private:
		node_ptr		_root;
		allocator_type	_allocator;
	};
}
