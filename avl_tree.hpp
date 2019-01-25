#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

#include <algorithm>
#include <functional>

template<typename K, typename T>
class Avl_tree
{
	public:
		Avl_tree() = default;
		// Disable copy
		Avl_tree(const Avl_tree &) = delete;
		// Disable copy
		Avl_tree & operator = (const Avl_tree &) = delete;
		// Only allow move operation
		Avl_tree & operator = (Avl_tree &&x)
		{
			// Check if it is itself first
			if(root_ == x.root_)
				return *this;
			// Release the spaces
			release();
			root_ = x.root_;
			x.root_ = nullptr;
			return *this;
		}

		// Node type
		struct Node
		{
			K key;
			T data;
			// left child
			Node *left;
			// right child
			Node *right;
			// Current height to calculate inbalance value
			int height;
		};

		// Search
		Node * search(const K &key)
		{
			return find(root_, key);
		}

		// Insert (no duplicate allowed)
		void insert(const K &key, const T &data = T())
		{
			root_ = insert(root_, key, data);
		}

		// Remove
		void remove(const K &key)
		{
			root_ = remove(root_, key);
		}

		// Edit a key, change x to y
		void edit(const K &from, const K &to)
		{
			auto data = std::move(find(root_, from)->data);
			// Remove first
			root_ = remove(root_, from);
			// Then insert
			root_ = insert(root_, to, data);
		}

		// Use postorder to visit
		void postorder(std::function<void (Node *)> visit)
		{
			postorder(root_, visit);
		}

		// Insert if not exists
		Node * operator [] (const K &key)
		{
			// Find first
			Node *pos = search(key);
			if(pos == nullptr)
				insert(key);
			// Get the position
			pos = search(key);
			return pos;
		}

		~Avl_tree()
		{
			// Release
			release();
		}
	
	private:
		// Pointer to root
		Node *root_ = nullptr;

		void release()
		{
			// Use postorder to release
			postorder([](Node *root) {
				delete root;
			});
		}

		// postorder visit
		static void postorder(Node *root, std::function<void (Node *)> visit)
		{
			if(root == nullptr)
				return;
			// Recursive post order
			postorder(root->left, visit);
			postorder(root->right, visit);
			visit(root);
		}

		// Get the height of node
		static int height(Node *node)
		{
			// Nullptr means 0
			return node == nullptr ? 0 : node->height;
		}

		// Return a new sub tree
		static Node * leftRotate(Node *root)
		{
			// New root
			Node *nroot = root->right;
			root->right = nroot->left;
			nroot->left = root;
			// Update height
			// use height to prevent nullptr
			nroot->height = std::max(height(nroot->left), height(nroot->right));
			root->height = std::max(height(root->left), height(root->right));
			return nroot;
		}

		// Return a new sub tree
		static Node * rightRotate(Node *root)
		{
			// New root
			Node *nroot = root->left;
			root->left = nroot->right;
			nroot->right = root;
			// Update height
			// use height to prevent nullptr
			nroot->height = 1 + std::max(height(nroot->left), height(nroot->right));
			root->height = 1 + std::max(height(root->left), height(root->right));
			return nroot;
		}

		// Balance a sub tree
		// Return new current tree node
		static Node * adjust(Node *root)
		{
			if(root == nullptr)
				return root;

			// left tree higher than right tree
			if(height(root->left) - height(root->right) == 2)
			{
				// left tree can't be empty
				if(height(root->left->left) >= height(root->left->right))
				{
					// LL -> right rotate
					// update current root after rotate
					root = rightRotate(root);
				}
				else
				{
					// LR -> left and right rotate
					root->left = leftRotate(root->left);
					root = rightRotate(root);
				}
			}
			// right tree higher than left tree
			else if(height(root->right) - height(root->left) == 2)
			{
				// right tree can't be empty
				if(height(root->right->right) >= height(root->right->left))
				{
					// RR -> left rotate
					// update current root after rotate
					root = leftRotate(root);
				}
				else
				{
					// RL -> right and left rotate
					root->right = rightRotate(root->right);
					root = leftRotate(root);
				}
			}
			// update root's height
			root->height = 1 + std::max(height(root->left), height(root->right));
			return root;
		}

		// Find a key
		static Node * find(Node *root, const K &key)
		{
			// Emtpy
			if(root == nullptr)
				return nullptr;

			// On the left subtree
			if(key < root->key)
				return find(root->left, key);
			// On the right subtree
			else if(key > root->key)
				return find(root->right, key);
			// Equal
			else
				return root;
		}

		// Insert to a sub tree
		// Return new current tree node
		static Node * insert(Node *root, const K &key, const T &data)
		{
			// Already exists
			if(find(root, key) != nullptr)
				return root;

			// Create a new node
			if(root == nullptr)
				return new Node{key, data, nullptr, nullptr, 1};

			// Compare to find left or right to insert
			if(key < root->key)
			{
				// Insert and update left sub tree
				root->left = insert(root->left, key, data);
			}
			else
			{
				// Insert and update right sub tree
				root->right = insert(root->right, key, data);
			}
			// balance current root
			root = adjust(root);
			return root;
		}

		// Remove key in a sub tree
		// Return new current tree node
		static Node * remove(Node *root, const K &key)
		{
			// Empty
			if(root == nullptr)
				return nullptr;
			
			// Compare to find left or right to remove
			if(key < root->key)
			{
				// Remove in left subtree and update
				root->left = remove(root->left, key);
			}
			else if(key > root->key)
			{
				// Remove in right subtree and update
				root->right = remove(root->right, key);
			}
			else
			{
				// Remove current node
				if(root->right == nullptr)
				{
					// Empty right tree
					Node *t = root;
					// Use left tree as current tree
					root = root->left;
					delete t;
				}
				else
				{
					// right tree is not empty
					// find the min number in right tree
					Node *pos = root->right;
					while(pos->left)
						pos = pos->left;
					// pos is the min key
					root->key = pos->key;
					// Remove pos's key
					remove(root->right, pos->key);
				}
			}
			// balance current root
			root = adjust(root);
			return root;
		}
};

#endif
