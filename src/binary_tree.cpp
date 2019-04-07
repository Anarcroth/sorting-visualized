#include <iostream>
#include <iomanip>
#include <queue>

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
    } else if (key.h < root->key.h) {
        insert(root->left, key);

        if (height(root->left) - height(root->right) == 2) {
            if (key.h < root->left->key.h)
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

void binary_tree::find_key(SDL_Rect &key)
{
    if (root != nullptr)
        find_key(root, key);
}

void binary_tree::find_key(node *&root, SDL_Rect &key)
{
    if (key.h == root->key.h)
        std::cout << "The found key is: " << root->key.h << std::endl;
    else if (key.h < root->key.h && root->left != nullptr)
        find_key(root->left, key);
    else if (key.h >= root->key.h && root->right != nullptr)
        find_key(root->right, key);
}

void binary_tree::display_tree()
{
    if (root != nullptr)
        display_tree(root, 0);
}

void binary_tree::display_tree(node *&root, int indent)
{
    if ((bool)indent)
        std::cout << std::setw(indent) << " ";

    std::cout << root->key.h << std::endl;

    if (root->left != nullptr)
        display_tree(root->left, indent + 4);

    if (root->right != nullptr)
        display_tree(root->right, indent + 4);
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

	SDL_RenderFillRect(screen::renderer, &root->key);

	i += 1;
	std::cout << root->key.x << " ";
	std::cout << root->key.h << " ";

        in_order_traversal(root->right);

	// root->key.x = i * root->key.w;
	// SDL_SetRenderDrawColor(screen::renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	// SDL_RenderFillRect(screen::renderer, &root->key);
	// SDL_RenderPresent(screen::renderer);
	// i += 1;
    }
    SDL_RenderPresent(screen::renderer);
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

/*
  int main()
  {
  binary_tree<int> binary_tree;

  int answer = 0, elem = 0;

  std::cout << "----- BST/AVL Tree Menu -----\n";

  std::cout << "1. Insert element to the tree.\n";
  std::cout << "2. Find element from the tree.\n";
  std::cout << "3. Display contents of the tree.\n";
  std::cout << "4. Choose traversal method.\n";
  std::cout << "5. Quit.\n";

  do
  {
  std::cout << "\nTake action: ";
  std::cin >> answer;

  switch (answer)
  {
  case 1:
  std::cout << "Enter an element: ";
  std::cin >> elem;

  binary_tree.insert(elem);
  break;

  case 2:
  std::cout << "Enter an element: ";
  std::cin >> elem;

  binary_tree.find_key(elem);
  break;

  case 3:
  binary_tree.display_tree();

  break;

  case 4:
  std::cout << "1. Post Order Traversal.\n";
  std::cout << "2. In Order Traversal.\n";
  std::cout << "3. Pre Order Traversal.\n";
  std::cout << "4. Level Order Traversal.\n";

  std::cout << "Take action: ";
  std::cin >> answer;

  switch (answer)
  {
  case 1:
  binary_tree.post_order_traversal();
  break;

  case 2:
  binary_tree.in_order_traversal();
  break;

  case 3:
  binary_tree.pre_order_traversal();
  break;

  case 4:
  binary_tree.level_order_traversal();
  break;

  default:
  continue;
  }
  break;

  case 5:
  exit(0);

  default:
  continue;
  }

  } while ((bool) answer);

  return 0;
  }
*/
