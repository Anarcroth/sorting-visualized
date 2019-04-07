#include <random>
#include <vector>
#include <iostream>

#include "sort.hpp"
#include "screen.hpp"
#include "number_set.hpp"
#include "binary_tree.hpp"
#include "command_parser.hpp"

// TODO
// Add timer
// Add statistics output

enum class algs
{
    MERGE_SORT,
    BINARY_TREE_SORT,
    QUICK_SORT,
    HEAP_SORT,
    SHELL_SORT
};

enum class num_set
{
    RANDOM,
    SEQ_RANDOM,
    REVERSED,
    FEW_UNIQUE
};

void print_help();
algs get_alg_option(command_parser cp);
num_set get_num_set_option(command_parser cp);

int main(int argc, char* args[])
{
    command_parser cp(argc, args);
    algs a = get_alg_option(cp);
    num_set ns = get_num_set_option(cp);

    std::vector<SDL_Rect> pillars = number_set::gen((int)ns);

    binary_tree bt;
    for (auto& p : pillars) {
   	bt.insert(p);
    }

    if (!screen::init()) {
	printf("Failed to initialize!\n");
	return(0);
    }

    screen::clear();
    screen::show_array(pillars);

    switch(a) {
    case algs::MERGE_SORT:
	sort::merge_sort(pillars, 0, pillars.size());
	break;
    case algs::BINARY_TREE_SORT:
	break;
    case algs::QUICK_SORT:
	sort::quick_sort(pillars, 0, pillars.size());
	break;
    case algs::HEAP_SORT:
	break;
    case algs::SHELL_SORT:
	break;
    default:
	break;
    }

    screen::finish(pillars);

    ///
    //screen::clear();
    //SDL_SetRenderDrawColor(screen::renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    //bt.in_order_traversal();
    //std::cin.get();
    ///

    screen::close();

    return 0;
}

void print_help()
{
    printf("Usage:\n");
    printf("\t./sortv.app [OPTION]\n\n");
    printf("Sorting Algorithm Visualization\n");
    printf("\tShow how the different sorting algorithms look like in action.\n\n");
    printf("Options:\n");
    printf("\t--merge-sort\n");
    printf("\t--binary-tree-sort\n");
    printf("\t--quick-sort\n");
    printf("\t--heap-sort\n");
    printf("\t--shell-sort\n\n");
    printf("\t--help\n");
    printf("\t--h\n");
    exit(0);
}

algs get_alg_option(command_parser cp)
{
    if (cp.cmd_option_exists("-h") || cp.cmd_option_exists("--help"))
	print_help();
    else if (cp.cmd_option_exists("--merge-sort"))
	return algs::MERGE_SORT;
    else if (cp.cmd_option_exists("--binary-tree-sort"))
	return algs::BINARY_TREE_SORT;
    else if (cp.cmd_option_exists("--quick-sort"))
	return algs::QUICK_SORT;
    else if (cp.cmd_option_exists("--heap-sort"))
	return algs::HEAP_SORT;
    else if (cp.cmd_option_exists("--shell-sort"))
	return algs::SHELL_SORT;
}

num_set get_num_set_option(command_parser cp)
{
    if (cp.cmd_option_exists("--random"))
	return num_set::RANDOM;
    else if (cp.cmd_option_exists("--seq-random"))
	return num_set::SEQ_RANDOM;
    else if (cp.cmd_option_exists("--reversed"))
	return num_set::REVERSED;
    else if (cp.cmd_option_exists("--few-unique"))
	return num_set::FEW_UNIQUE;
}
