#include <sys/time.h>
#include <ctime>
#include <vector>

#include "sort.hpp"
#include "screen.hpp"
#include "number_set.hpp"
#include "command_parser.hpp"
#include "binary_tree.hpp"

// TODO
// Add timer
// Add statistics output

typedef unsigned long long uint64;

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
uint64 get_time();

int main(int argc, char* args[])
{
    command_parser cp(argc, args);
    algs a = get_alg_option(cp);
    num_set ns = get_num_set_option(cp);

    std::vector<SDL_Rect> pillars = number_set::gen((int)ns);

    if (!screen::init()) {
	printf("Failed to initialize!\n");
	return(0);
    }

    screen::clear();
    screen::show_array(pillars);

    uint64 start_time = get_time();
    switch(a) {
    case algs::MERGE_SORT:
	sort::merge_sort(pillars, 0, pillars.size());
	break;
    case algs::BINARY_TREE_SORT:
	pillars = sort::binary_tree_sort(pillars);
	for (size_t i = 0; i < pillars.size() - 1; i++) {
	    screen::clear();
	    SDL_SetRenderDrawColor(screen::renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	    SDL_RenderFillRect(screen::renderer, &pillars[i]);
	    SDL_SetRenderDrawColor(screen::renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	    SDL_RenderFillRect(screen::renderer, &pillars[i + 1]);
	    SDL_RenderPresent(screen::renderer);
	}
	break;
    case algs::QUICK_SORT:
	sort::quick_sort(pillars, 0, pillars.size());
	break;
    case algs::HEAP_SORT:
	sort::heap_sort(pillars);
	break;
    case algs::SHELL_SORT:
	sort::shell_sort(pillars);
	break;
    default:
	break;
    }
    uint64 stop_time = get_time();

    screen::finish(pillars);
    screen::close();

    printf("%s%llu%s\n", "Algorithm took ",
	   (stop_time - start_time),
	   " milliseconds to finish.");

    return 0;
}

void print_help()
{
    printf("Usage:\n");
    printf("\t./sortv.app [OPTION]\n\n");
    printf("Sorting Algorithm Visualization\n");
    printf("\tShow how the different sorting algorithms look like in action.\n\n");
    printf("Options:\n");
    printf("\t--random\tuse random number set\n");
    printf("\t--seq-random\tuse randomized sequential numbers\n");
    printf("\t--reversed\tuse reversed sequential numbers\n\n");
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
    else
	print_help();
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
    else
	return num_set::SEQ_RANDOM;
}

uint64 get_time()
{
 struct timeval tv;
 gettimeofday(&tv, NULL);

 uint64 ret = tv.tv_usec;
 ret /= 1000;
 ret += (tv.tv_sec * 1000);

 return ret;
}
