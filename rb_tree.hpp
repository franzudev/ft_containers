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
		Node		*sibling() const {
			if (isLeft() && parent->right != NULL)
				return parent->right;
			if (isRight() && parent->left != NULL)
				return parent->left;
			return NULL;
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
		explicit rb_tree( const Compare& comp, const Alloc& alloc = Alloc()) : _root(nullptr), _comp(comp), _allocator(alloc) {
			_sentinel = _createNode(T());
			_sentinel->bound = true;
			_sentinel->right = _root;
			_sentinel->left = _root;
		}
		rb_tree( const rb_tree& tree): _comp(tree._comp){ *this = tree; }

		rb_tree& operator=(const rb_tree& tree) {
			_root = tree.root();
			_sentinel = tree._sentinel;
			_allocator = tree._allocator;
			_comp = tree._comp;
			return *this;
		}

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

		size_type	erase(const node_value& val) {
			remove_sentinel();
			size_type ret = _remove(val);
			add_sentinel();
			return ret;
		}
		void	erase(node_ptr val) {
			remove_sentinel();
			_deleteNode(val);
//			_remove(val);
			add_sentinel();
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

		//robk

		// Robk
		node_ptr climb(node_ptr node, const node_value &val) const
		{
			if (node->parent != _sentinel)
			{
				if (value_comp()(val, node->parent->data))
					return node->parent;
				else
					return (climb(node->parent, val));
			}
			return (nullptr);
		}

		node_ptr find_lower(node_ptr node, const node_value &val) const
		{
			// std::cout << "key"<< key << "node" << node->data.first << "val" << node->data.second << std::endl;
			if (!node)
				throw (std::exception());
			if (value_comp()(val, node->data))
			{
				if (node->left != _sentinel && node->left)
					return(find_lower(node->left, val));
				return node;
			}
			else if (!(value_comp()(node->data, val) && !value_comp()(val, node->data)))
				return node;
			else if (node->right != _sentinel && node->right)
				return(find_lower(node->right, val));
			else if (node_ptr ret = climb(node, val))
				return ret;
			return _sentinel;
		}


		node_ptr find_upper(node_ptr node, const node_value &val) const
		{
			if (!node)
				throw (std::exception());
			if (value_comp()(val, node->data))
			{
				if (node->left != _sentinel && node->left)
					return(find_upper(node->left, val));
				return node;
			}
			else if (node->right != _sentinel && node->right)
				return(find_upper(node->right, val));
			else if (node_ptr ret = climb(node, val))
				return ret;
			return _sentinel;
		}

		public:

		node_ptr lower_bound( const node_value &val ) const
		{
			return(find_lower(_root, val));
		}

		node_ptr upper_bound( const node_value &val ) const
		{
			return(find_upper(_root, val));
		}

		private:
		// --- Deletion
//		void 	_balance_del(node_ptr child, bool color) {
//		}

		void	_swap_leaf(node_ptr rem, node_ptr leaf) {
			if (leaf->right == _sentinel)
				leaf->parent->right = _sentinel;
			if (leaf->left == _sentinel)
				leaf->parent->left = _sentinel;
			if (rem->parent)
				leaf->parent = rem->parent;
			else
				leaf->parent = nullptr;
			leaf->left = rem->left;
			leaf->right = rem->right;
			if (leaf->right)
				leaf->right->parent = leaf;
			if (leaf->left)
				leaf->left->parent = leaf;
		}

		/*void	_simple_remove(node_ptr ptr) {
			if (ptr->right)
				_swap_leaf(ptr,*//*node after*//*);
			else
				_swap_leaf(ptr,*//*node before*//*);
		}*/

		size_type _remove(node_value val) {
			node_ptr ptr = find(val);
			if (ptr) {
				_simple_remove(ptr);
				_erase_one(ptr);
				return 1;
			}
			return 0;
		}

		void _deleteByVal(const node_value n) {
			if (_root == NULL)
				return;

			node_ptr node = find(n), *u;
			if (!node) {
				return;
			}

			_deleteNode(node);
		}

		node_ptr successor(node_ptr x) {
			node_ptr temp = x;

			while (temp->left != NULL)
				temp = temp->left;

			return temp;
		}

		node_ptr BSTreplace(node_ptr x) {
			// when node have 2 children
			if (x->left != NULL && x->right != NULL)
				return upper_bound(x->data);

			// when leaf
			if (x->left == NULL && x->right == NULL)
				return NULL;

			// when single child
			if (x->left != NULL)
				return x->left;
			else
				return x->right;
		}

		void fixDoubleBlack(node_ptr x) {
			if (x == _root)
				return;

			node_ptr sibling = x->sibling(), parent = x->parent;
			if (sibling == NULL) {
				// No sibiling, double black pushed up
				fixDoubleBlack(parent);
			} else {
				if (sibling->color == RED) {
					// Sibling red
					parent->color = RED;
					sibling->color = BLACK;
					if (sibling->isLeft()) {
						// left case
						_rightRotate(parent->left, parent);
					} else {
						// right case
						_leftRotate(parent->right, parent);
					}
					fixDoubleBlack(x);
				} else {
					// Sibling black
					if ((sibling->left && sibling->left->color == RED) || (sibling->right && sibling->right->color == RED)) {
						// at least 1 red children
						if (sibling->left != NULL && sibling->left->color == RED) {
							if (sibling->isLeft()) {
								// left left
								sibling->left->color = sibling->color;
								sibling->color = parent->color;
								_rightRotate(parent->left, parent);
							} else {
								// right left
								sibling->left->color = parent->color;
								_rightRotate(parent->left, parent);
								_leftRotate(parent->right, parent);
							}
						} else {
							if (sibling->isLeft()) {
								// left right
								sibling->right->color = parent->color;
								_leftRotate(parent->right, parent);
								_rightRotate(parent->left, parent);
							} else {
								// right right
								sibling->right->color = sibling->color;
								sibling->color = parent->color;
								_leftRotate(parent->right, parent);
							}
						}
						parent->color = BLACK;
					} else {
						// 2 black children
						sibling->color = RED;
						if (parent->color == BLACK)
							fixDoubleBlack(parent);
						else
							parent->color = BLACK;
					}
				}
			}
		}

		void _deleteNode(node_ptr v) {
			node_ptr u = BSTreplace(v);

			// True when u and v are both black
			bool uvBlack = ((u == NULL || u->color == BLACK) && (v->color == BLACK));
			node_ptr parent = v->parent;

			if (u == NULL) {
				// u is NULL therefore v is leaf
				if (v == _root) {
					// v is root, making root null
					_root = NULL;
				} else {
					if (uvBlack) {
						// u and v both black
						// v is leaf, fix double black at v
						fixDoubleBlack(v);
					} else {
						// u or v is red
						if (v->sibling() != NULL)
							// sibling is not null, make it red"
							v->sibling()->color = RED;
					}

					// delete v from the tree
					if (v->isLeft()) {
						parent->left = NULL;
					} else {
						parent->right = NULL;
					}
				}
				_erase_one(v);
				return;
			}

			if (v->left == NULL || v->right == NULL) {
				// v has 1 child
				if (v == _root) {
					// v is root, assign the value of u to v, and delete u
					v->data = u->data;
					v->left = v->right = NULL;
					_erase_one(u);
				} else {
					// Detach v from tree and move u up
					if (v->isLeft()) {
						parent->left = u;
					} else {
						parent->right = u;
					}
					_erase_one(v);
					u->parent = parent;
					if (uvBlack) {
						// u and v both black, fix double black at u
						fixDoubleBlack(u);
					} else {
						// u or v red, color u black
						u->color = BLACK;
					}
				}
				return;
			}

			// v has 2 children, swap values with successor and recurse
			//TODO https://www.geeksforgeeks.org/red-black-tree-set-3-delete-2/
			_swapValues(u, v);
			_deleteNode(u);
		}

		void _swapValues(node_ptr &u, node_ptr &v) {
			node_ptr temp = _createNode(u->data);
			temp->color = v->color;
			temp->right = v->right;
			if (temp->right)
				temp->right->parent = temp;
			temp->parent = v->parent;
			if (v->isLeft())
				temp->parent->left = temp;
			if (v->isRight())
				temp->parent->right = temp;
			temp->left = v->left;
			if (temp->left)
				temp->left->parent = temp;
			temp->bound = v->bound;
			u = v;
			v = temp;
		}

		void _remove(node_ptr ptr) {
			if (ptr) {
				_simple_remove(ptr);
				_erase_one(ptr);
			}
		}

		void 	_erase_one(node_ptr ptr) {
			_allocator.destroy(ptr);
			_allocator.deallocate(ptr, 1);
		}
		// Deletion
	private:
		node_ptr		_root;
		key_compare 	_comp;
		allocator_type	_allocator;
		node_ptr		_sentinel;
	};
}
