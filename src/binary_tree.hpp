#ifndef __BINARY_TREE_H_INCLUDED__
#define __BINARY_TREE_H_INCLUDED__

#include <SDL2/SDL.h>
#include <vector>

struct node
{
    SDL_Rect key;

    node *left;
    node *right;

    int height;

    node(SDL_Rect new_key, node *l, node *r, int h = 0) :
	key(new_key),
	left(l),
	right(r),
	height(h) {}
};

class binary_tree
{
public:
    binary_tree() = default;
    ~binary_tree();

    void insert(SDL_Rect &key);
    void in_order_traversal();

    std::vector<SDL_Rect> pillars;

private:
    void insert(node *&root, SDL_Rect &key);
    void delete_tree(node *&root);
    void in_order_traversal(node *&root);
    void right_rotation(node *&root);
    void double_right_rotation(node *&root);
    void left_rotation(node *&root);
    void double_left_rotation(node *&root);
    int inline height(node *&root);
    node *root{};

    int i = 0;
};

#endif
