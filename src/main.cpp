#include <sys/time.h>
#include <ctime>
#include <vector>
#include <string>
#include <fstream>

#include "sort.hpp"
#include "screen.hpp"
#include "number_set.hpp"
#include "command_parser.hpp"
#include "binary_tree.hpp"

// TODO
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

void sort_no_visuals(std::vector<int> &nums, algs a);
void sort_visuals(std::vector<SDL_Rect> &pillars, algs a);
void print_help();
algs get_alg_option(command_parser cp);
num_set get_num_set_option(command_parser cp);
int get_custom_num_set(command_parser cp);
std::string get_num_set_file(command_parser cp);
uint64 get_time();
std::vector<int> parse_file(std::string f);

int main(int argc, char* args[])
{
    command_parser cp(argc, args);
    algs a = get_alg_option(cp);
    num_set ns = get_num_set_option(cp);
    std::string file = get_num_set_file(cp);
    int set_size = get_custom_num_set(cp);

    std::vector<SDL_Rect> pillars = number_set::gen((int)ns, set_size);
    std::vector<int> nums;

    // init vectors
    if (!file.empty()) {
	nums = parse_file(file);
    } else if (set_size > screen::WIDTH) {
	for (auto& p : pillars)
	    nums.push_back(p.h);
    }

    uint64 start_time = get_time();
    if (set_size > screen::WIDTH || !file.empty())
	sort_no_visuals(nums, a);
    else
	sort_visuals(pillars, a);
    uint64 stop_time = get_time();

    printf("%s%llu%s\n", "Algorithm took ",
	   (stop_time - start_time),
	   " milliseconds to finish.");

    return 0;
}

void sort_no_visuals(std::vector<int> &nums, algs a)
{
    // Print before start.
    for (int n : nums)
	printf("%d ", n);
    printf("\n%s%zu", "Unsorted array size: ", nums.size());

    switch(a) {
    case algs::MERGE_SORT:
	sort::merge_sort(nums, 0, nums.size());
	break;
    case algs::BINARY_TREE_SORT:
	//nums = sort::binary_tree_sort(nums);
	break;
    case algs::QUICK_SORT:
	sort::quick_sort(nums, 0, nums.size());
	break;
    case algs::HEAP_SORT:
	sort::heap_sort(nums);
	break;
    case algs::SHELL_SORT:
	sort::shell_sort(nums);
	break;
    default:
	break;
    }

    // Print after sorting.
    printf("\n===========\n");
    for (int n : nums)
	printf("%d ", n);
    printf("\n%s%zu\n\n", "Sorted array size: ", nums.size());
}

void sort_visuals(std::vector<SDL_Rect> &pillars, algs a)
{
    if (!screen::init()) {
	printf("Failed to initialize!\n");
	exit(0);
    }

    screen::clear();
    screen::show_array(pillars);

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

    screen::finish(pillars);
    screen::close();
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

int get_custom_num_set(command_parser cp)
{
    if (cp.cmd_option_exists("--set-size"))
	return std::stoi(cp.get_cmd_option("--set-size").c_str());
    return 0;
}

std::string get_num_set_file(command_parser cp)
{
    if (cp.cmd_option_exists("--file"))
	return cp.get_cmd_option("--file");
    return "";
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

std::vector<int> parse_file(std::string f)
{
    std::ifstream infile(f);
    std::string line;
    std::vector<int> nums;

    while (std::getline(infile, line))
	nums.push_back(std::stoi(line.c_str()));

    return nums;
}
