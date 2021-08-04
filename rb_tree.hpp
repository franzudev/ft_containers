#pragma once

#include "pair.hpp"

namespace ft {

	enum nodeColor {
		RED,
		BLACK
	};

	template <class T>
			struct Node {
				typedef T	value_type;

				value_type	key;
				bool		color;
				struct Node *parent;
				struct Node *left;
				struct Node *right;

				Node(T key): key(key), color(BLACK), parent(nullptr), left(nullptr), right(nullptr) {}

				bool 		isLeft() {return parent && this == parent->left;}
				bool 		isRight() {return parent && this == parent->right;}
				Node		*uncle() {
					if (parent->parent && parent->isLeft())
						return parent->parent->right;
					if (parent->parent && parent->isRight())
						return parent->parent->left;
					return nullptr;
				}

			};

	template <class T>
			class rb_tree {
				rb_tree(rb_tree<T>& tree): root(nullptr) {(void)tree;}
				rb_tree& operator=(rb_tree<T>& tree) {(void)tree; return *this;}
			public:
				typedef	Node<T>	node;
				typedef node*	node_ptr;

			public:
				rb_tree(): root(nullptr) {}

				ft::pair<node_ptr, bool> insert(T val) {
					if (!root) {
						root = new node(val);
						return ft::make_pair(root, true);
					}
					return _insert(root, val);
				}

				node_ptr insert(node_ptr hint, T val) {
					return _insert(hint, val).first;
				}

				node_ptr find(T val) {
					return _find(root, val);
				}

				node_ptr deletion(T val) {
					node_ptr toDelete = find(root, val);
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

				void printTree()
				{
					_printTreeHelper(root,0);
				}

			private:

				ft::pair<node_ptr, bool> _insert(node_ptr start, T val) {
					if (start->key == val)
						return ft::make_pair(start, false);
					if (val < start->key){
						if (!start->left)
							return _setLeftNode(start, new node(val));
						return _insert(start->left, val);
					}
					if (!start->right)
						return _setRightNode(start, new node(val));
					return _insert(start->right, val);
				}

				node_ptr _find(node_ptr node, T val) {
					if (!node)
						return nullptr;
					if (node->key == val)
						return node;
					if (val > node->key)
						return _find(node->right, val);
					if (val < node->key)
						return _find(node->left, val);
					return node;
				}

				void	_balance(node_ptr ptr) {
					if (ptr == root) {
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
						root = parent;
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
						root = parent;
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
						std::cout << color << root->key << "\e[0m" << std::endl;
						_printTreeHelper(root->left, space);
					}
				}

			private:
				node_ptr	root;
			};
}
