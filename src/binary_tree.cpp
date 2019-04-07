#include "binary_tree.hpp"
#include "screen.hpp"

void binary_tree::insert(SDL_Rect &key)
{
    if (root != nullptr)
        insert(root, key);
    else
        root = new node(key, nullptr, nullptr);
}

void binary_tree::insert(node *&root, SDL_Rect &key)
{
    if (root == nullptr) {
        root = new node(key, nullptr, nullptr);
    } else if (key.h <= root->key.h) {
        insert(root->left, key);

        if (height(root->left) - height(root->right) == 2) {
            if (key.h <= root->left->key.h)
                left_rotation(root);
            else
                double_left_rotation(root);
        }
    } else if (key.h > root->key.h) {
        insert(root->right, key);

        if (height(root->right) - height(root->left) == 2) {
            if (key.h > root->right->key.h )
                right_rotation(root);
            else
                double_right_rotation(root);
        }
    }

    root->height = std::max(height(root->left), height(root->right)) + 1;
}

int binary_tree::height(node *&root)
{
    return root != nullptr ? root->height : -1;
}

void binary_tree::in_order_traversal()
{
    if (root != nullptr)
        in_order_traversal(root);
}

void binary_tree::in_order_traversal(node *&root)
{
    if (root != nullptr) {
        in_order_traversal(root->left);

	root->key.x = i * root->key.w;
	pillars.push_back(root->key);
	i += 1;

	in_order_traversal(root->right);
    }
}

void binary_tree::right_rotation(node *&root)
{
    auto *temp = root->right;
    root->right = temp->left;
    temp->left = root;

    root->height = std::max(height(root->left), height(root->right)) + 1;
    temp->height = std::max(height(temp->left), height(temp->right)) + 1;
    root = temp;
}

void binary_tree::double_right_rotation(node *&root)
{
    left_rotation(root->right);
    right_rotation(root);
}

void binary_tree::left_rotation(node *&root)
{
    auto *temp = root->left;
    root->left = temp->right;
    temp->right = root;

    root->height = std::max(height(root->left), height(root->right)) + 1;
    temp->height = std::max(height(temp->left), height(temp->right)) + 1;
    root = temp;
}

void binary_tree::double_left_rotation(node *&root)
{
    right_rotation(root->left);
    left_rotation(root);
}

void binary_tree::delete_tree(node *&root)
{
    if (root != nullptr) {
        delete_tree(root->left);
        delete_tree(root->right);
    }
    delete root;
}

binary_tree::~binary_tree()
{
    delete_tree(root);
}
